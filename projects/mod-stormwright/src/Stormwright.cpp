// SPDX-License-Identifier: GPL-2.0-or-later

#include "StormwrightRules.h"
#include "Chat.h"
#include "Config.h"
#include "Creature.h"
#include "CreatureScript.h"
#include "Group.h"
#include "Log.h"
#include "Map.h"
#include "MapMgr.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "TemporarySummon.h"
#include "WorldScript.h"
#include "WorldSession.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>

namespace Stormwright
{
using namespace std::chrono_literals;

constexpr uint32 RegistrarEntry = 910900;
constexpr uint32 RodEntry = 910901;
constexpr uint32 BossEntry = 910902;
constexpr uint32 AddEntry = 910903;
constexpr uint32 MarkerEntry = 910904;
constexpr uint32 GossipText = 910900;
constexpr uint32 MapId = 1;
constexpr float CenterX = -6250.0f;
constexpr float CenterY = -3750.0f;
constexpr float ArenaRadius = 45.0f;
constexpr float CaptureRadius = 4.5f;
constexpr uint32 OwnedLifetimeMs = TimeLimitMs + 60000;
constexpr uint32 OrbVisualKit = 12201; // Packet-only; never cast spell 62186.
constexpr uint32 AbortAction = 20;
constexpr uint32 StatusAction = 21;
constexpr uint32 DischargeAction = 30;
constexpr uint32 GroundAction = 31;

std::atomic<bool> Enabled{false};

void Tell(Player* player, std::string const& message)
{
    if (player && player->GetSession())
        ChatHandler(player->GetSession()).SendSysMessage("Stormwright: " + message);
}

bool Human(Player const* player)
{
    return player && player->GetSession() && !player->GetSession()->IsBot();
}

float Distance2D(Position const& a, Position const& b)
{
    return std::hypot(a.GetPositionX() - b.GetPositionX(), a.GetPositionY() - b.GetPositionY());
}

// Z comes only from the installed map's height query. Missing extracted terrain
// never turns into a guessed spawn height. This is not a navigation/client test.
bool GroundPoint(Map* map, float x, float y, Position& result)
{
    map->LoadGrid(x, y);
    float const terrain = map->GetGridHeight(x, y);
    if (!std::isfinite(terrain) || terrain < -1000.0f || terrain > 3000.0f)
        return false;
    float const z = map->GetHeight(uint32(1), x, y, terrain + 2.0f, true, 6.0f);
    if (!std::isfinite(z) || z < -1000.0f || z > 3000.0f ||
        std::abs(z - terrain) > 4.0f ||
        map->IsInWater(1, x, y, z + 0.5f, 2.0f))
        return false;
    result.Relocate(x, y, z + 0.05f, 0.0f);
    return true;
}

struct Site
{
    Position center;
    Position registrar;
    Position add;
    std::array<Position, 3> rods{};
};

bool ReadSite(Map* map, Site& site)
{
    if (map->GetId() != MapId || !GroundPoint(map, CenterX, CenterY, site.center) ||
        !GroundPoint(map, CenterX, CenterY - 40.0f, site.registrar) ||
        !GroundPoint(map, CenterX - 20.0f, CenterY, site.add))
        return false;
    constexpr std::array<std::array<float, 2>, 3> offsets{{
        {{0.0f, 13.0f}}, {{-11.26f, -6.5f}}, {{11.26f, -6.5f}}
    }};
    for (std::size_t i = 0; i < offsets.size(); ++i)
        if (!GroundPoint(map, CenterX + offsets[i][0], CenterY + offsets[i][1], site.rods[i]))
            return false;
    // Sample the encounter footprint rather than accepting one valid center.
    for (int x = -36; x <= 36; x += 6)
        for (int y = -36; y <= 36; y += 6)
        {
            if (x * x + y * y > 36 * 36)
                continue;
            Position point;
            if (!GroundPoint(map, CenterX + float(x), CenterY + float(y), point) ||
                std::abs(point.GetPositionZ() - site.center.GetPositionZ()) > 4.0f)
                return false;
        }
    return std::abs(site.registrar.GetPositionZ() - site.center.GetPositionZ()) <= 4.0f;
}

class ControllerAI final : public ScriptedAI
{
public:
    explicit ControllerAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
        me->setActive(true);
    }

    void AttackStart(Unit* /*target*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/,
        SpellSchoolMask /*school*/) override { damage = 0; }

    Player* Pilot() const { return ObjectAccessor::GetPlayer(*me, _pilot); }
    bool Active() const { return _rules.Active(); }
    bool Vulnerable() const { return _rules.Vulnerable(); }
    uint32 Serial() const { return _serial; }
    bool Contains(Player const* player) const
    {
        return player && std::find(_roster.begin(), _roster.end(), player->GetGUID()) != _roster.end();
    }

    std::size_t RodIndex(Creature const* rod) const
    {
        auto const found = std::find(_rods.begin(), _rods.end(), rod->GetGUID());
        return static_cast<std::size_t>(std::distance(_rods.begin(), found));
    }

    void RequestAbort(char const* reason) { if (Active()) _abort = reason; }
    void BossDied(ObjectGuid const& guid) { if (Active() && guid == _boss) _won = true; }

    std::string Status() const
    {
        if (!Active())
            return _lastResult.empty() ? "Arena available. All special actions belong to one human pilot." : _lastResult;
        return std::string(_rules.Settings().name) + " | ward " + std::to_string(_rules.Ward()) + "/3 | " +
            std::to_string(_rules.Elapsed() / 1000) + "s | starting roster " + std::to_string(_roster.size());
    }

    bool Start(Player* player, std::size_t preset)
    {
        if (!Enabled.load() || !Human(player) || !player->IsAlive() || player->IsInCombat() ||
            player->GetLevel() != 80 || player->GetMap() != me->GetMap() || player->GetDistance(me) > 5.0f)
        {
            Tell(player, "Start as a living level-80 human, out of combat, beside the registrar.");
            return false;
        }
        if (Active())
        {
            Tell(player, "An attempt is already running. " + Status());
            return false;
        }
        if (Group* group = player->GetGroup())
            if (!group->IsLeader(player->GetGUID()) || group->GetMembersCount() > 5)
            {
                Tell(player, "The pilot must lead a party of at most five. Solo Pilot requires no group.");
                return false;
            }
        if (!ReadSite(me->GetMap(), _site))
        {
            Tell(player, "The arena's ground data is unavailable or unsuitable; no attempt was started.");
            return false;
        }
        for (Position const& rod : _site.rods)
            if (!me->IsWithinLOS(rod.GetPositionX(), rod.GetPositionY(), rod.GetPositionZ() + 1.0f))
            {
                Tell(player, "The registrar cannot see every rod position; no attempt was started.");
                return false;
            }

        _roster.clear();
        _roster.push_back(player->GetGUID());
        if (Group* group = player->GetGroup())
            for (GroupReference* reference = group->GetFirstMember(); reference; reference = reference->next())
                if (Player* member = reference->GetSource())
                    if (member != player && member->IsAlive() && member->GetLevel() == 80 &&
                        member->GetMap() == me->GetMap() && member->GetDistance(me) <= 50.0f)
                        _roster.push_back(member->GetGUID());
        if (!_rules.Begin(preset))
            return false;
        ++_serial;
        if (_serial == 0)
            ++_serial;
        _pilot = player->GetGUID();
        _pilotMaxHealth = player->GetMaxHealth();
        _won = false;
        _abort.clear();
        _nextAdd = 18000;
        _adds.clear();

        for (std::size_t i = 0; i < _rods.size(); ++i)
        {
            Creature* rod = Spawn(RodEntry, _site.rods[i]);
            if (!rod)
            {
                Finish(false, "rod creation failed");
                return false;
            }
            _rods[i] = rod->GetGUID();
        }
        Creature* boss = Spawn(BossEntry, _site.center);
        if (!boss)
        {
            Finish(false, "boss creation failed");
            return false;
        }
        _boss = boss->GetGUID();
        ConfigureEnemy(boss, true);
        boss->AI()->AttackStart(player);
        Tell(player, "Catch each tracking mark in an available rod, then move when it locks. Click charged rods: "
            "Ground restores your health/ward; Discharge cracks the boss and blasts nearby pursuers. "
            "Three missed catches lose the ward. First mark in 12 seconds. Leave the arena or use the registrar to abort.");
        Tell(player, "Starting " + Status() + ". Outside assistance is allowed; this is not a competitive ranking.");
        return true;
    }

    void RodMenu(Player* player, Creature* rod)
    {
        ClearGossipMenuFor(player);
        std::size_t const index = RodIndex(rod);
        if (!ValidPilot(player) || index >= _rods.size())
        {
            Tell(player, "Only the active pilot operates this run's capacitors.");
            CloseGossipMenuFor(player);
            return;
        }
        if (_rules.Charged(index))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "DISCHARGE: boss damage + 8 seconds exposed; blast nearby pursuers", _serial, DischargeAction);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "GROUND: recover health and one ward; sacrifice the damage window", _serial, GroundAction);
        }
        else
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, _rules.Ready(index) ? "Ready: bait a locked strike here." :
                "Cooling: " + std::to_string(_rules.CoolingSeconds(index)) + " seconds.", _serial, StatusAction);
        SendGossipMenuFor(player, GossipText, rod->GetGUID());
    }

    void ActivateRod(Player* player, Creature* rod, uint32 serial, uint32 action)
    {
        if (!ValidPilot(player) || serial != _serial || player->GetDistance(rod) > 5.0f ||
            !player->IsWithinLOSInMap(rod))
            return;
        std::size_t const index = RodIndex(rod);
        if (index >= _rods.size() || (action != GroundAction && action != DischargeAction))
            return;
        bool const ground = action == GroundAction;
        if (!_rules.Activate(index, ground ? Spend::Ground : Spend::Discharge, player->GetHealth() < player->GetMaxHealth()))
        {
            Tell(player, "That activation is unavailable. Full health plus full ward does not consume Ground.");
            return;
        }
        if (ground)
        {
            uint64 const healing = uint64(player->GetMaxHealth()) * _rules.Settings().healPercent / 100;
            player->SetHealth(static_cast<uint32>(std::min<uint64>(player->GetMaxHealth(), uint64(player->GetHealth()) + healing)));
            Tell(player, "GROUNDED. Health recovered; " + Status());
        }
        else
        {
            if (Creature* boss = Owned(_boss))
            {
                uint32 const damage = static_cast<uint32>(uint64(boss->GetMaxHealth()) * _rules.Settings().damagePercent / 100);
                Unit::DealDamage(rod, boss, damage, nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NATURE);
            }
            for (ObjectGuid const& guid : _adds)
                if (Creature* add = Owned(guid))
                    if (add->IsAlive() && rod->GetDistance(add) <= 8.0f)
                        Unit::DealDamage(rod, add, add->GetMaxHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NATURE);
            Tell(player, "DISCHARGED. Armor open for 8 seconds. Nearby pursuers are struck by the capacitor blast.");
        }
        RefreshRods();
    }

    void Abort(Player* player)
    {
        if (ValidPilot(player))
            Finish(false, "pilot aborted");
    }

    void UpdateAI(uint32 diff) override
    {
        if (!Active())
            return;
        if (_won)
        {
            Finish(true, "storm broken");
            return;
        }
        Player* pilot = Pilot();
        if (!Enabled.load() || !pilot || !pilot->IsAlive() ||
            Distance2D(pilot->GetPosition(), _site.center) > ArenaRadius || !_abort.empty())
        {
            Finish(false, !_abort.empty() ? _abort : "pilot died, left, disconnected, or module disabled");
            return;
        }
        Creature* boss = Owned(_boss);
        if (!boss || !boss->IsAlive())
        {
            Finish(false, "boss became unavailable without a confirmed victory");
            return;
        }
        for (ObjectGuid const& guid : _rods)
            if (!Owned(guid))
            {
                Finish(false, "a capacitor became unavailable");
                return;
            }

        if (_rules.CurrentPhase() == Phase::Tracking)
            if (Creature* marker = Owned(_marker))
                marker->NearTeleportTo(pilot->GetPositionX(), pilot->GetPositionY(), pilot->GetPositionZ(), 0.0f);
        Event const event = _rules.Tick(diff);
        switch (event)
        {
            case Event::Mark:
            {
                Creature* marker = Spawn(MarkerEntry, pilot->GetPosition());
                if (!marker)
                {
                    Finish(false, "tracking marker creation failed");
                    return;
                }
                _marker = marker->GetGUID();
                marker->SendPlaySpellVisual(OrbVisualKit);
                Tell(pilot, "TRACKING YOU: lead the storm into an available capacitor.");
                break;
            }
            case Event::Lock:
                if (Creature* marker = Owned(_marker))
                {
                    _locked = marker->GetPosition();
                    marker->SetObjectScale(2.0f);
                    Tell(pilot, "LOCKED: move away from the marker now!");
                }
                else
                {
                    Finish(false, "tracking marker disappeared");
                    return;
                }
                break;
            case Event::Impact:
            {
                std::size_t caught = _rods.size();
                for (std::size_t i = 0; i < _rods.size(); ++i)
                    if (_rules.Ready(i) && Distance2D(_locked, _site.rods[i]) <= CaptureRadius)
                    {
                        caught = i;
                        break;
                    }
                bool const success = _rules.Resolve(caught);
                if (Creature* marker = Owned(_marker))
                    marker->DespawnOrUnsummon(1ms);
                _marker.Clear();
                if (Distance2D(pilot->GetPosition(), _locked) <= 3.5f)
                    Unit::DealDamage(boss, pilot, static_cast<uint32>(uint64(pilot->GetMaxHealth()) * 15 / 100), nullptr,
                        DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NATURE);
                Tell(pilot, success ? "CAPACITOR CHARGED: click it to choose Ground or Discharge." :
                    "MISSED CATCH. " + Status());
                if (_rules.Ward() == 0)
                {
                    Finish(false, "ward shattered");
                    return;
                }
                break;
            }
            case Event::Timeout:
                Finish(false, "12-minute limit reached");
                return;
            case Event::None:
                break;
        }
        if ((_rules.CurrentPhase() == Phase::Tracking || _rules.CurrentPhase() == Phase::Locked) && !Owned(_marker))
        {
            Finish(false, "storm marker unavailable");
            return;
        }
        RefreshRods();
        boss->SetObjectScale(_rules.Vulnerable() ? 1.35f : 1.0f);
        SpawnPursuer(pilot);
    }

private:
    bool ValidPilot(Player const* player) const
    {
        return Active() && Human(player) && player->IsAlive() && player->GetGUID() == _pilot &&
            player->GetMap() == me->GetMap() && Distance2D(player->GetPosition(), _site.center) <= ArenaRadius;
    }
    Creature* Owned(ObjectGuid const& guid) const
    {
        return guid.IsEmpty() ? nullptr : ObjectAccessor::GetCreature(*me, guid);
    }
    Creature* Spawn(uint32 entry, Position const& position)
    {
        Creature* creature = me->SummonCreature(entry, position, TEMPSUMMON_TIMED_DESPAWN, OwnedLifetimeMs);
        if (creature)
        {
            _owned.push_back(creature->GetGUID());
            creature->AI()->SetGUID(me->GetGUID());
            creature->SetRegeneratingHealth(false);
        }
        return creature;
    }
    void ConfigureEnemy(Creature* enemy, bool boss)
    {
        uint32 const roster = static_cast<uint32>(_roster.size());
        uint32 const health = (boss ? 1200000u : 9000u) * (roster + 1) / 2;
        enemy->SetMaxHealth(health);
        enemy->SetFullHealth();
        float const damage = float(_pilotMaxHealth) * (boss ? 0.004f : 0.003f) * float(roster + 1) / 2.0f;
        enemy->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, damage);
        enemy->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, damage);
        enemy->UpdateDamagePhysical(BASE_ATTACK);
        enemy->SetAttackTime(BASE_ATTACK, 2000);
        enemy->SetRegeneratingHealth(false);
    }
    void SpawnPursuer(Player* pilot)
    {
        if (_rules.Elapsed() < _nextAdd)
            return;
        _nextAdd = _rules.Elapsed() + 18000;
        _adds.erase(std::remove_if(_adds.begin(), _adds.end(), [this](ObjectGuid const& guid)
        {
            Creature* add = Owned(guid);
            return !add || !add->IsAlive();
        }), _adds.end());
        std::size_t const cap = _roster.size() == 1 ? 1 : 2;
        if (_adds.size() >= cap)
            return;
        if (Creature* add = Spawn(AddEntry, _site.add))
        {
            ConfigureEnemy(add, false);
            _adds.push_back(add->GetGUID());
            add->AI()->AttackStart(pilot);
        }
        else
            RequestAbort("pursuer creation failed");
    }
    void RefreshRods()
    {
        for (std::size_t i = 0; i < _rods.size(); ++i)
            if (Creature* rod = Owned(_rods[i]))
                rod->SetObjectScale(_rules.Charged(i) ? 1.8f : (_rules.Ready(i) ? 1.0f : 0.6f));
    }
    void Finish(bool won, std::string const& reason)
    {
        if (!Active())
            return;
        _lastResult = std::string(won ? "VICTORY" : "ATTEMPT ENDED") + " | " + reason + " | " + Status() +
            " | discharges " + std::to_string(_rules.Discharges()) + " | grounds " + std::to_string(_rules.Grounds()) +
            " | misses " + std::to_string(_rules.Misses()) + ". Assisted encounter result; return here to retry.";
        _rules.End(); // Terminal state precedes callbacks/despawns: outcome exactly once.
        Tell(Pilot(), _lastResult);
        LOG_INFO("module", "STORMWRIGHT_RESULT pilot={} serial={} won={} roster={} elapsed={} reason={}",
            _pilot.ToString(), _serial, won, _roster.size(), _rules.Elapsed(), reason);
        for (ObjectGuid const& guid : _owned)
            if (Creature* actor = Owned(guid))
                actor->DespawnOrUnsummon(1ms);
        _owned.clear();
        _adds.clear();
        _rods.fill(ObjectGuid::Empty);
        _boss.Clear();
        _marker.Clear();
        _pilot.Clear();
        _roster.clear();
    }

    Rules _rules;
    Site _site;
    ObjectGuid _pilot;
    ObjectGuid _boss;
    ObjectGuid _marker;
    Position _locked;
    std::array<ObjectGuid, 3> _rods{};
    std::vector<ObjectGuid> _roster;
    std::vector<ObjectGuid> _owned;
    std::vector<ObjectGuid> _adds;
    uint32 _serial = 0;
    uint32 _pilotMaxHealth = 0;
    uint64 _nextAdd = 0;
    bool _won = false;
    std::string _abort;
    std::string _lastResult;
};

class OwnedAI : public ScriptedAI
{
public:
    explicit OwnedAI(Creature* creature) : ScriptedAI(creature) { }
    void SetGUID(ObjectGuid const& guid, int32 /*id*/) override { _controller = guid; }
    ControllerAI* Controller() const
    {
        Creature* creature = ObjectAccessor::GetCreature(*me, _controller);
        return creature && creature->GetEntry() == RegistrarEntry ? dynamic_cast<ControllerAI*>(creature->AI()) : nullptr;
    }
private:
    ObjectGuid _controller;
};

class PassiveAI final : public OwnedAI
{
public:
    explicit PassiveAI(Creature* creature) : OwnedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
    }
    void AttackStart(Unit* /*target*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/,
        SpellSchoolMask /*school*/) override { damage = 0; }
};

class EnemyAI final : public OwnedAI
{
public:
    explicit EnemyAI(Creature* creature) : OwnedAI(creature)
    {
        me->SetReactState(REACT_AGGRESSIVE);
        me->SetRegeneratingHealth(false);
    }
    bool CanAIAttack(Unit const* target) const override
    {
        ControllerAI* controller = Controller();
        return controller && controller->Active() && target &&
            controller->Contains(target->GetCharmerOrOwnerPlayerOrPlayerItself());
    }
    void EnterEvadeMode(EvadeReason /*reason*/) override
    {
        if (ControllerAI* controller = Controller())
            controller->RequestAbort("an enemy evaded; integrity cannot reset mid-attempt");
    }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/,
        SpellSchoolMask /*school*/) override
    {
        ControllerAI* controller = Controller();
        if (!controller || !controller->Active())
            damage = 0;
        else if (me->GetEntry() == BossEntry && !controller->Vulnerable())
            damage /= 20;
    }
    void JustDied(Unit* /*killer*/) override
    {
        if (ControllerAI* controller = Controller())
            if (me->GetEntry() == BossEntry)
                controller->BossDied(me->GetGUID());
    }
    void UpdateAI(uint32 /*diff*/) override
    {
        ControllerAI* controller = Controller();
        if (!controller || !controller->Active())
        {
            me->DespawnOrUnsummon(1ms);
            return;
        }
        if (std::hypot(me->GetPositionX() - CenterX, me->GetPositionY() - CenterY) > ArenaRadius + 5.0f)
        {
            controller->RequestAbort("an enemy left the arena");
            return;
        }
        if (UpdateVictim())
            DoMeleeAttackIfReady();
    }
};

class RegistrarScript final : public CreatureScript
{
public:
    RegistrarScript() : CreatureScript("npc_stormwright_registrar") { }
    CreatureAI* GetAI(Creature* creature) const override { return new ControllerAI(creature); }
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        auto* controller = dynamic_cast<ControllerAI*>(creature->AI());
        if (!controller)
            return false;
        ClearGossipMenuFor(player);
        Tell(player, controller->Status());
        if (!controller->Active())
            for (std::size_t i = 0; i < Presets.size(); ++i)
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, std::string("Start ") + Presets[i].name +
                    " - Solo Pilot or your nearby party", GOSSIP_SENDER_MAIN, static_cast<uint32>(i + 1));
        else
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Abort my current attempt", GOSSIP_SENDER_MAIN, AbortAction);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Rules: bait, lock, move; then choose Ground or Discharge", GOSSIP_SENDER_MAIN, StatusAction);
        SendGossipMenuFor(player, GossipText, creature->GetGUID());
        return true;
    }
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        CloseGossipMenuFor(player);
        auto* controller = dynamic_cast<ControllerAI*>(creature->AI());
        if (!controller || sender != GOSSIP_SENDER_MAIN)
            return true;
        if (action >= 1 && action <= Presets.size())
            controller->Start(player, action - 1);
        else if (action == AbortAction)
            controller->Abort(player);
        else if (action == StatusAction)
            Tell(player, "One human operates every capacitor. Catch the mark while it tracks you; step away after lock. "
                "Large rods hold charge, small rods are cooling. Discharge attacks; Ground restores health/ward. "
                "Ordinary bots only fight. No special bot positioning or clicks are required. " + controller->Status());
        return true;
    }
};

class RodScript final : public CreatureScript
{
public:
    RodScript() : CreatureScript("npc_stormwright_rod") { }
    CreatureAI* GetAI(Creature* creature) const override { return new PassiveAI(creature); }
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        auto* owned = dynamic_cast<OwnedAI*>(creature->AI());
        if (owned)
            if (ControllerAI* controller = owned->Controller())
                controller->RodMenu(player, creature);
        return true;
    }
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        CloseGossipMenuFor(player);
        auto* owned = dynamic_cast<OwnedAI*>(creature->AI());
        if (owned)
            if (ControllerAI* controller = owned->Controller())
                controller->ActivateRod(player, creature, sender, action);
        return true;
    }
};

class World final : public WorldScript
{
public:
    World() : WorldScript("StormwrightWorld", { WORLDHOOK_ON_AFTER_CONFIG_LOAD, WORLDHOOK_ON_STARTUP }) { }
    void OnAfterConfigLoad(bool reload) override
    {
        Enabled.store(sConfigMgr->GetOption<bool>("Stormwright.Enable", true));
        LOG_INFO("server.loading", "STORMWRIGHT_CONFIG reload={} enabled={}", reload, Enabled.load());
    }
    void OnStartup() override
    {
        if (!Enabled.load())
            return;
        Map* map = sMapMgr->CreateBaseMap(MapId);
        Site site;
        if (!map || !ReadSite(map, site))
        {
            LOG_ERROR("module", "STORMWRIGHT_SITE_UNAVAILABLE: extracted ground data/footprint check failed; no guessed registrar spawn");
            return;
        }
        Creature* registrar = map->SummonCreature(RegistrarEntry, site.registrar);
        LOG_INFO("module", "STORMWRIGHT_REGISTRAR spawned={} map={} x={} y={} derived_z={}; client/path validation remains separate",
            registrar != nullptr, MapId, site.registrar.GetPositionX(), site.registrar.GetPositionY(), site.registrar.GetPositionZ());
    }
};
}

void Addmod_stormwrightScripts()
{
    new Stormwright::World();
    new Stormwright::RegistrarScript();
    new Stormwright::RodScript();
    new GenericCreatureScript<Stormwright::EnemyAI>("npc_stormwright_enemy");
    new GenericCreatureScript<Stormwright::PassiveAI>("npc_stormwright_marker");
}
