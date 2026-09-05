#include "HuntRhythmRules.h"

#include "Chat.h"
#include "Config.h"
#include "Creature.h"
#include "Log.h"
#include "Map.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "World.h"
#include "WorldSession.h"

#include <chrono>
#include <map>
#include <mutex>

namespace
{
using namespace Acore::ChatCommands;

struct SessionStore
{
    std::mutex mutex;
    HuntRhythm::Settings settings;
    std::map<ObjectGuid, HuntRhythm::Chain> chains;
};

SessionStore& Store()
{
    static SessionStore store;
    return store;
}

std::uint64_t NowMs()
{
    return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

// Core calls and chat run outside the store lock; configuration and all session
// mutations share the lock, including map-thread XP/death and world-thread reload.
char const* IneligiblePlayer(Player* player)
{
    if (!player || !player->GetSession())
        return "a player session is required";
    if (!player->IsAlive())
        return "you must be alive";
    if (player->HasPlayerFlag(PLAYER_FLAGS_NO_XP_GAIN) || player->HasPlayerFlag(PLAYER_FLAGS_NO_PLAY_TIME))
        return "XP gain is currently disabled for your character";

    uint32 cap = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
    uint32 const trialCap = sWorld->getIntConfig(CONFIG_TRIAL_LEVEL_CAP);
    if (trialCap && player->GetSession()->IsTrialAccount())
        cap = std::min(cap, trialCap);
    if (player->GetLevel() >= cap)
        return "you have reached your effective level cap";

    Map* map = player->GetMap();
    if (!map || !map->IsWorldMap() || map->IsDungeon() || map->IsRaid() || map->IsBattlegroundOrArena())
        return "hunt in an outdoor world map";
    return nullptr;
}

bool EligibleKill(Player* player, Unit* victim, uint32 amount, uint8 source)
{
    if (source != XPSOURCE_KILL || !amount || !victim || IneligiblePlayer(player))
        return false;
    Creature* creature = victim->ToCreature();
    if (!creature || creature->GetMap() != player->GetMap() || !creature->hasLootRecipient())
        return false;
    if (creature->IsPet() || creature->IsSummon() || creature->IsTotem() || creature->IsCritter() ||
        !creature->GetCharmerOrOwnerGUID().IsEmpty() || creature->isElite() || creature->isWorldBoss())
        return false;
    return player->IsHostileTo(creature) && player->isHonorOrXPTarget(creature);
}

void ClearSession(Player* player)
{
    if (!player)
        return;
    ObjectGuid const guid = player->GetGUID();
    auto& store = Store();
    std::lock_guard<std::mutex> lock(store.mutex);
    store.chains.erase(guid);
}

void ResetChain(Player* player, char const* message)
{
    if (!player)
        return;
    ObjectGuid const guid = player->GetGUID();
    bool hadChain = false;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto const itr = store.chains.find(guid);
        if (itr != store.chains.end())
        {
            hadChain = itr->second.kills != 0;
            itr->second = {};
        }
    }
    if (hadChain && player->GetSession())
        ChatHandler(player->GetSession()).SendSysMessage(message);
}

bool Status(ChatHandler* handler)
{
    Player* player = handler->GetSession() ? handler->GetSession()->GetPlayer() : nullptr;
    if (!player)
        return false;
    ObjectGuid const guid = player->GetGUID();
    std::uint64_t const now = NowMs();
    HuntRhythm::Settings settings;
    HuntRhythm::Chain chain;
    bool optedIn = false;
    bool expired = false;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        settings = store.settings;
        auto const itr = store.chains.find(guid);
        if (itr != store.chains.end())
        {
            optedIn = true;
            expired = HuntRhythm::Expire(itr->second, now, settings);
            chain = itr->second;
        }
    }
    if (!settings.enabled)
    {
        handler->SendSysMessage("Hunt Rhythm is disabled by the server operator.");
        return true;
    }
    if (expired)
        handler->SendSysMessage("Hunt Rhythm: your chain expired. Your next eligible kill starts a new chain.");
    char const* reason = IneligiblePlayer(player);
    handler->PSendSysMessage("Hunt Rhythm: {}. Eligibility: {}.", optedIn ? "opted in" : "opted out", reason ? reason : "ready");
    if (optedIn)
        handler->PSendSysMessage("Streak: {} kills. Window remaining: {}s. Next eligible kill: +{}% base XP (cap {}%). Use .rhythm stop to exit.",
            chain.kills, HuntRhythm::RemainingSeconds(chain, now, settings),
            HuntRhythm::Percent(HuntRhythm::NextKills(chain.kills), settings), settings.maxBonusPercent);
    else
        handler->SendSysMessage("Use .rhythm start to opt in for this login session.");
    return true;
}

bool Start(ChatHandler* handler)
{
    Player* player = handler->GetSession() ? handler->GetSession()->GetPlayer() : nullptr;
    if (!player)
        return false;
    if (char const* reason = IneligiblePlayer(player))
    {
        handler->PSendSysMessage("Hunt Rhythm cannot start: {}.", reason);
        return true;
    }
    HuntRhythm::Settings settings;
    bool inserted = false;
    ObjectGuid const guid = player->GetGUID();
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        settings = store.settings;
        if (settings.enabled)
            inserted = store.chains.emplace(guid, HuntRhythm::Chain{}).second;
    }
    if (inserted)
        handler->PSendSysMessage("Hunt Rhythm started. Chain ordinary outdoor XP kills less than {}s apart; the first gives 0%, then +{} percentage points per kill up to {}%. Death or changing maps resets the chain. Use .rhythm stop to exit.",
            settings.windowSeconds, settings.stepPercent, settings.maxBonusPercent);
    // Repeated start only reports status; it never refreshes an existing window.
    return Status(handler);
}

bool Stop(ChatHandler* handler)
{
    Player* player = handler->GetSession() ? handler->GetSession()->GetPlayer() : nullptr;
    if (!player)
        return false;
    ClearSession(player);
    handler->SendSysMessage("Hunt Rhythm stopped. Your chain is cleared; subsequent XP follows ordinary core rules.");
    return true;
}

class HuntRhythmCommands final : public CommandScript
{
public:
    HuntRhythmCommands() : CommandScript("HuntRhythmCommands") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable const commands = {
            {"start", Start, SEC_PLAYER, Console::No},
            {"status", Status, SEC_PLAYER, Console::No},
            {"stop", Stop, SEC_PLAYER, Console::No},
            {"", Status, SEC_PLAYER, Console::No}
        };
        static ChatCommandTable const root = {{"rhythm", commands}};
        return root;
    }
};

class HuntRhythmPlayer final : public PlayerScript
{
public:
    HuntRhythmPlayer() : PlayerScript("HuntRhythmPlayer", {
        PLAYERHOOK_ON_GIVE_EXP, PLAYERHOOK_ON_PLAYER_JUST_DIED,
        PLAYERHOOK_ON_LOGIN, PLAYERHOOK_ON_LOGOUT, PLAYERHOOK_ON_MAP_CHANGED}) { }

    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 source) override
    {
        if (!EligibleKill(player, victim, amount, source))
            return;

        ObjectGuid const guid = player->GetGUID();
        uint32 const currentXp = player->GetUInt32Value(PLAYER_XP);
        std::uint64_t const now = NowMs();
        HuntRhythm::Chain chain;
        HuntRhythm::Settings settings;
        HuntRhythm::Award award{amount, 0, false};
        bool notice = false;
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            auto const itr = store.chains.find(guid);
            if (!store.settings.enabled || itr == store.chains.end())
                return;
            settings = store.settings;
            HuntRhythm::Expire(itr->second, now, settings);
            uint32 const previousPercent = HuntRhythm::Percent(itr->second.kills, settings);
            bool const previousDeclined = itr->second.bonusDeclined;
            HuntRhythm::Advance(itr->second, now, settings);
            uint32 const percent = HuntRhythm::Percent(itr->second.kills, settings);
            award = HuntRhythm::AddBonus(amount, percent, currentXp);
            itr->second.bonusDeclined = award.declined;
            notice = itr->second.kills == 1 || percent != previousPercent || award.declined != previousDeclined;
            chain = itr->second;
        }
        amount = award.amount;
        if (notice && player->GetSession())
        {
            ChatHandler chat(player->GetSession());
            if (award.declined)
                chat.SendSysMessage("Hunt Rhythm: this bonus exceeded safe XP bounds and was withheld. Your ordinary XP is unchanged.");
            else
                chat.PSendSysMessage("Hunt Rhythm: {} kills, +{}% base XP (+{} XP before normal core bonuses).{}",
                    chain.kills, HuntRhythm::Percent(chain.kills, settings), award.added,
                    HuntRhythm::Percent(chain.kills, settings) == settings.maxBonusPercent ? " Bonus cap reached!" : "");
        }
    }

    void OnPlayerJustDied(Player* player) override
    {
        ResetChain(player, "Hunt Rhythm: death broke your chain. You remain opted in; recover and retry.");
    }

    void OnPlayerMapChanged(Player* player) override
    {
        ResetChain(player, "Hunt Rhythm: entering a map reset your chain. You remain opted in.");
    }

    void OnPlayerLogin(Player* player) override { ClearSession(player); }
    void OnPlayerLogout(Player* player) override { ClearSession(player); }
};

class HuntRhythmWorld final : public WorldScript
{
public:
    HuntRhythmWorld() : WorldScript("HuntRhythmWorld", {WORLDHOOK_ON_AFTER_CONFIG_LOAD}) { }

    void OnAfterConfigLoad(bool reload) override
    {
        bool const enabled = sConfigMgr->GetOption<bool>("HuntRhythm.Enable", true);
        int32 const window = sConfigMgr->GetOption<int32>("HuntRhythm.WindowSeconds", 60);
        int32 const step = sConfigMgr->GetOption<int32>("HuntRhythm.StepPercent", 2);
        int32 const cap = sConfigMgr->GetOption<int32>("HuntRhythm.MaxBonusPercent", 10);
        HuntRhythm::Settings const settings = HuntRhythm::Normalize(enabled, window, step, cap);
        if (window != static_cast<int32>(settings.windowSeconds) || step != static_cast<int32>(settings.stepPercent) ||
            cap != static_cast<int32>(settings.maxBonusPercent))
            LOG_WARN("module", "Hunt Rhythm: out-of-range configuration clamped to window={} step={} cap={}",
                settings.windowSeconds, settings.stepPercent, settings.maxBonusPercent);
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            store.settings = settings;
            store.chains.clear();
        }
        LOG_INFO("module", "HUNT_RHYTHM_CONFIG reload={} enabled={} window={} step={} cap={}; all sessions opted out",
            reload ? 1 : 0, enabled ? 1 : 0, settings.windowSeconds, settings.stepPercent, settings.maxBonusPercent);
    }
};
}

void Addmod_hunt_rhythmScripts()
{
    new HuntRhythmCommands();
    new HuntRhythmPlayer();
    new HuntRhythmWorld();
}
