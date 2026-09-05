// SPDX-License-Identifier: GPL-2.0-or-later
#include "TriageNightRules.h"
#include "Chat.h"
#include "Config.h"
#include "Creature.h"
#include "CreatureScript.h"
#include "Log.h"
#include "Map.h"
#include "MapMgr.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "PlayerScript.h"
#include "ScriptedCreature.h"
#include "TemporarySummon.h"
#include "WorldScript.h"
#include "WorldSession.h"

#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <deque>
#include <map>
#include <mutex>
#include <string>

namespace TriageNight
{
using namespace std::chrono_literals;
using namespace Acore::ChatCommands;

constexpr uint32 ControllerEntry = 911100;
constexpr std::array<uint32, PatientCount> PatientEntries{{911101, 911102, 911103}};
constexpr uint32 ActorLifetimeMs = TimeLimitMs + 30000;
constexpr uint32 MaxRuns = 4;
constexpr std::size_t MaxSessions = 128;
constexpr float RunRadius = 20.0f;
std::atomic<bool> Enabled{false};
std::atomic<uint64> Generation{0};

enum class Action { Help, Training, Veteran, Status, StabilizeOne, StabilizeTwo, StabilizeThree, Stop };
struct Request
{
    Action action;
    ObjectGuid expectedController;
};
struct Session
{
    ObjectGuid controller;
    std::deque<Request> requests;
    std::deque<std::string> results;
    uint32 attempts = 0;
    bool reserved = false;
    bool invalidated = false;
};
struct SessionStore
{
    std::mutex mutex;
    std::map<ObjectGuid, Session> sessions;
    uint32 activeRuns = 0;
};
SessionStore& Store()
{
    static SessionStore store;
    return store;
}
bool Human(Player const* player)
{
    return player && player->GetSession() && !player->GetSession()->IsBot();
}
void Tell(Player* player, std::string const& text)
{
    if (Human(player))
        ChatHandler(player->GetSession()).SendSysMessage("Triage Night: " + text);
}
bool Bound(ObjectGuid pilot, ObjectGuid controller)
{
    auto& store = Store();
    std::lock_guard<std::mutex> lock(store.mutex);
    auto const found = store.sessions.find(pilot);
    return found != store.sessions.end() && found->second.controller == controller && !found->second.invalidated;
}
void Help(Player* player)
{
    Tell(player, "One level-80 priest. Five 45-second rounds, four 10-second breaks, three persistent patients. "
        "Use your ordinary direct heals and real mana. Keep all three alive. Two stabilizations pause one patient's wounds for six seconds.");
    Tell(player, ".triage start [training|veteran] | .triage status | .triage stabilize 1|2|3 | .triage stop. "
        "Patient One/Two/Three are normal friendly heal targets; enable friendly nameplates or target by name. "
        "Deterioration bypasses shields. Other healer classes and party/AoE compatibility are not promised. No bots are needed.");
}

char const* StartProblem(Player* player)
{
    if (!Enabled.load())
        return "the module is disabled";
    if (!Human(player) || !player->IsInWorld() || player->GetSession()->PlayerLogout() ||
        player->HasUnitState(UNIT_STATE_LOGOUT_TIMER) || !player->IsAlive())
        return "start alive and fully in the world";
    if (player->GetLevel() != 80 || player->GetClass() != CLASS_PRIEST)
        return "the complete V1 requires one level-80 priest with ordinary direct healing spells and healing gear";
    if (player->IsInCombat() || player->IsNonMeleeSpellCast(true))
        return "finish combat and your current cast/channel before starting; casting is allowed throughout the shift";
    if (player->IsPvP() || player->IsFFAPvP() || player->duel)
        return "clear PvP flags and duels before starting";
    if (player->IsBeingTeleported() || player->GetTransport() || player->GetVehicle() || player->IsInFlight() ||
        player->IsMounted() || player->IsFlying() || player->IsHovering() || player->IsFalling() ||
        player->HasUnitMovementFlag(MOVEMENTFLAG_FALLING | MOVEMENTFLAG_FALLING_FAR) ||
        player->IsInWater() || player->isSwimming() || !player->GetCharmerGUID().IsEmpty())
        return "start on stable dry ground, unmounted and in normal control";
    Map* map = player->GetMap();
    if (!map || !map->IsWorldMap() || map->IsDungeon() || map->IsRaid() || map->IsBattlegroundOrArena() || !player->IsOutdoors())
        return "choose a normal outdoor world location";
    return nullptr;
}

bool Ground(Player* player, float x, float y, Position& result)
{
    WorldLocation probe(player->GetMapId(), x, y, player->GetPositionZ(), player->GetOrientation());
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(probe.GetPositionZ()) ||
        !std::isfinite(probe.GetOrientation()) || !MapMgr::IsValidMapCoord(probe))
        return false;
    Map* map = player->GetMap();
    map->LoadGrid(x, y);
    float const z = map->GetHeight(player->GetPhaseMask(), x, y, probe.GetPositionZ() + 2.0f, true, 6.0f);
    if (!std::isfinite(z) || z <= INVALID_HEIGHT || std::abs(z - probe.GetPositionZ()) > 1.5f)
        return false;
    LiquidData const liquid = map->GetLiquidData(player->GetPhaseMask(), x, y, z + 0.05f, player->GetCollisionHeight(), {});
    if ((liquid.Status & MAP_LIQUID_STATUS_IN_CONTACT) != 0 || !player->IsWithinLOS(x, y, z + 1.0f))
        return false;
    result.Relocate(x, y, z + 0.05f, player->GetOrientation() + 3.14159265f);
    return true;
}

class ControllerAI final : public ScriptedAI
{
public:
    explicit ControllerAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetRegeneratingHealth(false);
        me->setActive(true);
    }
    ~ControllerAI() override { Release({}); }
    void AttackStart(Unit* /*target*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*school*/) override { damage = 0; }
    void EnterEvadeMode(EvadeReason /*reason*/) override { RequestAbort("controller evaded"); }
    bool Active() const { return _initialized && !_finished; }
    void RequestAbort(std::string const& reason) { if (Active()) _abort = reason; }
    Player* Pilot() const { return ObjectAccessor::GetPlayer(*me, _pilot); }

    bool ValidPilot(Player const* pilot) const
    {
        // Starting a shift forbids casting. Continuing it deliberately does not:
        // normal priest casts and channels are the primary gameplay.
        return Active() && Enabled.load() && _generation == Generation.load() && Human(pilot) &&
            pilot->IsInWorld() && pilot->IsAlive() && !pilot->GetSession()->PlayerLogout() &&
            !pilot->HasUnitState(UNIT_STATE_LOGOUT_TIMER) && pilot->GetGUID() == _pilot &&
            pilot->GetMap() == me->GetMap() && pilot->GetPhaseMask() == _phase &&
            !pilot->IsBeingTeleported() && !pilot->GetTransport() && !pilot->GetVehicle() &&
            !pilot->IsInFlight() && !pilot->IsMounted() && !pilot->IsFlying() &&
            pilot->GetCharmerGUID().IsEmpty() && me->GetDistance2d(pilot) <= RunRadius &&
            std::abs(me->GetPositionZ() - pilot->GetPositionZ()) <= 5.0f && Bound(_pilot, me->GetGUID());
    }
    bool PermitsHeal(Unit* healer, ObjectGuid patient) const
    {
        Player* pilot = Pilot();
        if (!ValidPilot(pilot) || !healer || healer->GetGUID() != _pilot)
            return false;
        for (ObjectGuid const& guid : _patients)
            if (guid == patient)
                return true;
        return false;
    }

    void Begin(Player* pilot, bool veteran, std::size_t rotation, std::array<Position, PatientCount> const& positions)
    {
        _pilot = pilot->GetGUID();
        _ownsLease = true;
        _phase = pilot->GetPhaseMask();
        _generation = Generation.load();
        _positions = positions;
        _rules.Begin(veteran, rotation);
        _initialized = true;
        bool attached = false;
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            auto const found = store.sessions.find(_pilot);
            if (found != store.sessions.end() && found->second.reserved)
            {
                found->second.controller = me->GetGUID();
                found->second.reserved = false;
                found->second.invalidated = false;
                attached = true;
            }
        }
        if (!attached)
        {
            Finish(false, "player session ended during start");
            return;
        }
        for (std::size_t i = 0; i < PatientCount; ++i)
        {
            Creature* patient = me->SummonCreature(PatientEntries[i], _positions[i], TEMPSUMMON_TIMED_DESPAWN, ActorLifetimeMs);
            if (!patient)
            {
                Finish(false, "patient creation failed; check installed owned SQL");
                return;
            }
            _patients[i] = patient->GetGUID();
            patient->AI()->SetGUID(me->GetGUID());
            patient->SetRegeneratingHealth(false);
            patient->SetMaxHealth(PatientHealth);
            patient->SetHealth(PatientHealth);
            patient->SetStandState(UNIT_STAND_STATE_KNEEL);
            patient->setActive(true);
            if (!pilot->IsValidAssistTarget(patient) || !pilot->IsWithinLOSInMap(patient))
            {
                Finish(false, "a patient is not a visible friendly heal target; no guessed targetability");
                return;
            }
        }
        Help(pilot);
        Tell(pilot, std::string(veteran ? "VETERAN" : "TRAINING") +
            " shift begins in 10 seconds. Stay within 20 yards. Patient health carries between rounds; rest normally in each finite break.");
        LOG_INFO("module", "TRIAGE_NIGHT_START pilot={} preset={} map={} x={} y={} z={} rotation={}",
            _pilot.ToString(), veteran ? "veteran" : "training", me->GetMapId(),
            me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), rotation);
    }

    std::string Status() const
    {
        std::string text = std::string(_rules.Veteran() ? "Veteran" : "Training") +
            " | round " + std::to_string(_rules.Round()) + "/5 | " +
            (_rules.CurrentPhase() == Phase::Round ? "injuries active" : "briefing/recovery") +
            " | stabilization " + std::to_string(_rules.Charges()) + "/2 | patients ";
        for (std::size_t i = 0; i < PatientCount; ++i)
        {
            Creature* patient = Patient(i);
            text += std::to_string(i + 1) + ":" + (patient ? std::to_string(patient->GetHealth()) : "missing") +
                (_rules.PausedSeconds(i) ? "[stabilized] " : " ");
        }
        return text;
    }
    void Stabilize(Player* pilot, std::size_t index)
    {
        Creature* patient = Patient(index);
        if (!ValidPilot(pilot) || !patient || !patient->IsAlive() ||
            !pilot->IsWithinLOSInMap(patient) || !_rules.Stabilize(index))
        {
            Tell(pilot, "Stabilization unavailable: use it during an injury round on an unstabilized visible patient while charges remain.");
            return;
        }
        Tell(pilot, "Patient " + std::to_string(index + 1) + " stabilized for six seconds. " +
            std::to_string(_rules.Charges()) + " emergency charge(s) remain. Their existing wounds still need healing.");
    }
    void Stop(Player* pilot)
    {
        if (pilot && pilot->GetGUID() == _pilot)
            Finish(false, "pilot stopped the shift");
    }

    void UpdateAI(uint32 diff) override
    {
        if (!Active())
            return;
        Player* pilot = Pilot();
        if (!ValidPilot(pilot) || !_abort.empty())
        {
            Finish(false, _abort.empty() ? "pilot died, departed, logged out, or configuration changed" : _abort);
            return;
        }
        for (std::size_t i = 0; i < PatientCount; ++i)
        {
            Creature* patient = Patient(i);
            if (!patient || !patient->IsAlive() || !patient->GetHealth() || !patient->GetCharmerGUID().IsEmpty() ||
                patient->GetDistance2d(_positions[i].GetPositionX(), _positions[i].GetPositionY()) > 1.5f)
            {
                Finish(false, "a patient died, disappeared, changed control or left their station");
                return;
            }
        }
        Step const step = _rules.Tick(diff);
        if (step.event == Event::Timeout)
        {
            Finish(false, "six-minute hard time limit reached");
            return;
        }
        if (step.event == Event::None)
            return;
        if (step.warning < PatientCount)
            Tell(pilot, "BURST IN FOUR SECONDS: Patient " + std::to_string(step.warning + 1) + ". Prepare a heal or spend stabilization.");
        for (std::size_t i = 0; i < PatientCount; ++i)
        {
            Creature* patient = Patient(i);
            uint32 const injury = step.injury[i];
            if (injury >= patient->GetHealth())
            {
                patient->SetHealth(1);
                patient->SetStandState(UNIT_STAND_STATE_DEAD);
                Finish(false, "Patient " + std::to_string(i + 1) + " was lost");
                return;
            }
            if (injury)
                patient->ModifyHealth(-static_cast<int32>(injury));
            bool const critical = uint64(patient->GetHealth()) * 4 <= patient->GetMaxHealth();
            if (critical && step.event != Event::RoundStarted)
                ++_criticalSeconds;
            patient->SetStandState(critical ? UNIT_STAND_STATE_DEAD : UNIT_STAND_STATE_KNEEL);
            if (critical && !_critical[i])
                Tell(pilot, "CRITICAL: Patient " + std::to_string(i + 1) + " is at or below 25% health.");
            _critical[i] = critical;
        }
        if (step.event == Event::RoundStarted)
            AnnounceRound(pilot);
        else if (step.event == Event::BreakStarted)
            Tell(pilot, "Round survived. Ten-second recovery break: wounds persist; heal or use ordinary mana recovery. " + Status());
        else if (step.event == Event::Complete)
            Finish(true, "all three patients survived all five rounds");
    }

private:
    Creature* Patient(std::size_t index) const
    {
        if (index >= PatientCount || _patients[index].IsEmpty())
            return nullptr;
        Creature* patient = ObjectAccessor::GetCreature(*me, _patients[index]);
        return patient && patient->GetEntry() == PatientEntries[index] ? patient : nullptr;
    }
    void AnnounceRound(Player* pilot)
    {
        std::string const a = std::to_string(_rules.Patient(0) + 1);
        std::string const b = std::to_string(_rules.Patient(1) + 1);
        std::string const c = std::to_string(_rules.Patient(2) + 1);
        std::string pattern;
        switch (_rules.Round())
        {
            case 1: pattern = "Steady wounds: Patient " + a + " bleeds fastest."; break;
            case 2: pattern = "Burst watch: Patient " + a + " faces repeated bursts; others keep bleeding."; break;
            case 3: pattern = "Split priorities: Patients " + a + " and " + b + " both bleed heavily."; break;
            case 4: pattern = "Competing crises: all bleed; burst targets rotate. Read each warning."; break;
            default: pattern = "Final watch: Patients " + a + "/" + b + " bleed heavily; Patient " + c + " faces bursts."; break;
        }
        Tell(pilot, "ROUND " + std::to_string(_rules.Round()) + "/5. " + pattern);
    }
    void Release(std::string const& result)
    {
        if (!_ownsLease)
            return;
        _ownsLease = false;
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        if (store.activeRuns)
            --store.activeRuns;
        auto const found = store.sessions.find(_pilot);
        if (found != store.sessions.end() && found->second.controller == me->GetGUID())
        {
            found->second.controller.Clear();
            found->second.reserved = false;
            found->second.invalidated = false;
            if (!result.empty())
            {
                found->second.results.push_back(result);
                if (found->second.results.size() > 5)
                    found->second.results.pop_front();
            }
        }
    }
    void Finish(bool success, std::string const& reason)
    {
        if (_finished)
            return;
        _finished = true;
        _rules.End();
        std::string const result = std::string(success ? "SHIFT COMPLETE" : "SHIFT ENDED") +
            " | " + (_rules.Veteran() ? "Veteran" : "Training") + " | " + reason +
            " | round " + std::to_string(_rules.Round()) + "/5 | emergency charges used " +
            std::to_string(2 - _rules.Charges()) + " | critical patient-seconds " + std::to_string(_criticalSeconds);
        Player* pilot = Pilot();
        Tell(pilot, result);
        Tell(pilot, "Rest normally, then .triage start to replay. .triage status shows your last five results this login. "
            "No player health, mana, items, gold or experience were granted. These are personal practice records, not fair rankings.");
        LOG_INFO("module", "TRIAGE_NIGHT_RESULT pilot={} success={} elapsed_ms={} result={}",
            _pilot.ToString(), success, _rules.ElapsedMs(), result);
        for (std::size_t i = 0; i < PatientCount; ++i)
            if (Creature* patient = Patient(i))
            {
                if (success)
                    patient->SetStandState(UNIT_STAND_STATE_STAND);
                patient->DespawnOrUnsummon(success ? 1500ms : 1ms);
            }
        Release(result);
        me->DespawnOrUnsummon(success ? 2000ms : 1ms);
    }

    ObjectGuid _pilot;
    std::array<ObjectGuid, PatientCount> _patients{};
    std::array<Position, PatientCount> _positions{};
    std::array<bool, PatientCount> _critical{};
    Rules _rules;
    uint64 _generation = 0;
    uint32 _phase = 0;
    uint32 _criticalSeconds = 0;
    bool _ownsLease = false;
    bool _initialized = false;
    bool _finished = false;
    std::string _abort;
};

class PatientAI final : public ScriptedAI
{
public:
    explicit PatientAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetRegeneratingHealth(false);
    }
    void SetGUID(ObjectGuid const& guid, int32 /*id*/) override { _controller = guid; }
    ControllerAI* Controller() const
    {
        Creature* controller = _controller.IsEmpty() ? nullptr : ObjectAccessor::GetCreature(*me, _controller);
        return controller && controller->GetEntry() == ControllerEntry ? dynamic_cast<ControllerAI*>(controller->AI()) : nullptr;
    }
    void AttackStart(Unit* /*target*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*school*/) override { damage = 0; }
    void HealReceived(Unit* healer, uint32& amount) override
    {
        ControllerAI* controller = Controller();
        if (!controller || !controller->PermitsHeal(healer, me->GetGUID()))
            amount = 0;
    }
    void Reset() override
    {
        me->SetRegeneratingHealth(false);
        if (ControllerAI* controller = Controller())
            controller->RequestAbort("a patient reset; wounds cannot refill mid-shift");
    }
    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (ControllerAI* controller = Controller())
            controller->RequestAbort("a patient evaded; wounds cannot refill mid-shift");
    }
    void UpdateAI(uint32 /*diff*/) override
    {
        me->SetRegeneratingHealth(false);
        if (!Controller())
            me->DespawnOrUnsummon(1ms);
    }
private:
    ObjectGuid _controller;
};

void Start(Player* pilot, bool veteran)
{
    if (char const* reason = StartProblem(pilot))
    {
        Tell(pilot, std::string("Cannot start: ") + reason + ".");
        return;
    }
    Position center;
    std::array<Position, PatientCount> positions{};
    bool suitable = Ground(pilot, pilot->GetPositionX(), pilot->GetPositionY(), center);
    constexpr std::array<float, PatientCount> angles{{-0.65f, 0.0f, 0.65f}};
    for (std::size_t i = 0; suitable && i < PatientCount; ++i)
    {
        float const angle = pilot->GetOrientation() + angles[i];
        suitable = Ground(pilot, pilot->GetPositionX() + 5.0f * std::cos(angle),
            pilot->GetPositionY() + 5.0f * std::sin(angle), positions[i]);
    }
    if (!suitable)
    {
        Tell(pilot, "No clear dry nearby patient stations could be verified. Face an open outdoor area and try elsewhere; no shift started.");
        return;
    }
    bool reserved = false;
    std::size_t rotation = 0;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto const found = store.sessions.find(pilot->GetGUID());
        if (found != store.sessions.end() && found->second.controller.IsEmpty() && !found->second.reserved && store.activeRuns < MaxRuns)
        {
            reserved = true;
            found->second.reserved = true;
            found->second.invalidated = false;
            rotation = found->second.attempts++ % PatientCount;
            ++store.activeRuns;
        }
    }
    if (!reserved)
    {
        Tell(pilot, "Your preceding shift is still active/cleaning up, or all four practice slots are occupied. Use .triage status or retry shortly.");
        return;
    }
    Creature* creature = pilot->SummonCreature(ControllerEntry, center, TEMPSUMMON_TIMED_DESPAWN, ActorLifetimeMs);
    auto* controller = creature ? dynamic_cast<ControllerAI*>(creature->AI()) : nullptr;
    if (!controller)
    {
        if (creature)
            creature->DespawnOrUnsummon(1ms);
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            if (store.activeRuns)
                --store.activeRuns;
            auto const found = store.sessions.find(pilot->GetGUID());
            if (found != store.sessions.end())
                found->second.reserved = false;
        }
        Tell(pilot, "Controller creation failed. Check the installed owned SQL and module script bindings; no shift started.");
        return;
    }
    controller->Begin(pilot, veteran, rotation, positions);
}

void Status(Player* player, ControllerAI* controller)
{
    if (controller && controller->Active())
        Tell(player, controller->Status());
    std::deque<std::string> results;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto const found = store.sessions.find(player->GetGUID());
        if (found != store.sessions.end())
            results = found->second.results;
    }
    if (results.empty() && !controller)
        Tell(player, "No active shift or completed results this login. Use .triage help or .triage start.");
    for (std::string const& result : results)
        Tell(player, result);
}

template<Action action>
bool Queue(ChatHandler* handler)
{
    Player* player = handler->GetSession() ? handler->GetSession()->GetPlayer() : nullptr;
    if (!Human(player))
        return false;
    bool queued = false;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto found = store.sessions.find(player->GetGUID());
        if (found == store.sessions.end() && store.sessions.size() < MaxSessions)
            found = store.sessions.emplace(player->GetGUID(), Session{}).first;
        if (found != store.sessions.end() && found->second.requests.size() < 4)
        {
            found->second.requests.push_back({action, found->second.controller});
            queued = true;
        }
    }
    if (!queued)
        handler->SendSysMessage("Triage Night: request queue is full; wait for your current actions, then retry.");
    return true;
}
class Commands final : public CommandScript
{
public:
    Commands() : CommandScript("TriageNightCommands") { }
    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable const start = {
            {"training", Queue<Action::Training>, SEC_PLAYER, Console::No},
            {"veteran", Queue<Action::Veteran>, SEC_PLAYER, Console::No},
            {"", Queue<Action::Training>, SEC_PLAYER, Console::No}
        };
        static ChatCommandTable const stabilize = {
            {"1", Queue<Action::StabilizeOne>, SEC_PLAYER, Console::No},
            {"2", Queue<Action::StabilizeTwo>, SEC_PLAYER, Console::No},
            {"3", Queue<Action::StabilizeThree>, SEC_PLAYER, Console::No}
        };
        static ChatCommandTable const commands = {
            {"start", start}, {"stabilize", stabilize},
            {"help", Queue<Action::Help>, SEC_PLAYER, Console::No},
            {"status", Queue<Action::Status>, SEC_PLAYER, Console::No},
            {"stop", Queue<Action::Stop>, SEC_PLAYER, Console::No},
            {"", Queue<Action::Help>, SEC_PLAYER, Console::No}
        };
        static ChatCommandTable const root = {{"triage", commands}};
        return root;
    }
};

class PlayerHooks final : public PlayerScript
{
public:
    PlayerHooks() : PlayerScript("TriageNightPlayer", {PLAYERHOOK_ON_UPDATE, PLAYERHOOK_ON_LOGIN,
        PLAYERHOOK_ON_LOGOUT, PLAYERHOOK_ON_PLAYER_JUST_DIED, PLAYERHOOK_ON_MAP_CHANGED}) { }
    void OnPlayerUpdate(Player* player, uint32 /*diff*/) override
    {
        std::deque<Request> requests;
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            auto const found = store.sessions.find(player->GetGUID());
            if (found == store.sessions.end())
                return;
            requests.swap(found->second.requests);
        }
        for (Request const& request : requests)
        {
            ObjectGuid guid;
            {
                auto& store = Store();
                std::lock_guard<std::mutex> lock(store.mutex);
                auto const found = store.sessions.find(player->GetGUID());
                if (found == store.sessions.end())
                    return;
                guid = found->second.controller;
            }
            Creature* creature = guid.IsEmpty() ? nullptr : ObjectAccessor::GetCreature(*player, guid);
            auto* controller = creature && creature->GetEntry() == ControllerEntry ? dynamic_cast<ControllerAI*>(creature->AI()) : nullptr;
            switch (request.action)
            {
                case Action::Help: Help(player); break;
                case Action::Training: Start(player, false); break;
                case Action::Veteran: Start(player, true); break;
                case Action::Status: Status(player, controller); break;
                default:
                    if (!controller || guid != request.expectedController)
                    {
                        Tell(player, "That action has no matching active shift. Use .triage status or start a new shift.");
                        break;
                    }
                    if (request.action == Action::Stop)
                        controller->Stop(player);
                    else
                        controller->Stabilize(player, static_cast<std::size_t>(request.action) - static_cast<std::size_t>(Action::StabilizeOne));
                    break;
            }
        }
    }
    void OnPlayerLogin(Player* player) override { Forget(player); }
    void OnPlayerLogout(Player* player) override { Forget(player); }
    void OnPlayerJustDied(Player* player) override { Invalidate(player); }
    void OnPlayerMapChanged(Player* player) override { Invalidate(player); }
private:
    static void Forget(Player* player)
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        store.sessions.erase(player->GetGUID());
        // Active actor leases are released by their controller, not here. This
        // prevents logout/relogin from bypassing the global owned-actor cap.
    }
    static void Invalidate(Player* player)
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto const found = store.sessions.find(player->GetGUID());
        if (found != store.sessions.end())
        {
            found->second.invalidated = true;
            found->second.requests.clear();
        }
    }
};
class World final : public WorldScript
{
public:
    World() : WorldScript("TriageNightWorld", {WORLDHOOK_ON_AFTER_CONFIG_LOAD}) { }
    void OnAfterConfigLoad(bool reload) override
    {
        Enabled.store(sConfigMgr->GetOption<bool>("TriageNight.Enable", true));
        ++Generation;
        LOG_INFO("module", "TRIAGE_NIGHT_CONFIG reload={} enabled={}; priest solo, no OnStartup actors, active shifts end on reload",
            reload, Enabled.load());
    }
};
}

void Addmod_triage_nightScripts()
{
    new TriageNight::Commands();
    new TriageNight::PlayerHooks();
    new TriageNight::World();
    new GenericCreatureScript<TriageNight::ControllerAI>("npc_triage_night_controller");
    new GenericCreatureScript<TriageNight::PatientAI>("npc_triage_night_patient");
}
