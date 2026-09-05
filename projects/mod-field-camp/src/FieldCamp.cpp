#include "Chat.h"
#include "Config.h"
#include "Log.h"
#include "Map.h"
#include "MapMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "WorldSession.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <map>
#include <mutex>

namespace
{
using namespace Acore::ChatCommands;

constexpr float GroundTolerance = 1.5f;
constexpr float FloorChangeTolerance = 0.5f;

struct Camp
{
    WorldLocation location;
    uint32 phase = 0;
    float floor = 0.0f;
    bool bound = false;
    std::uint64_t readyAt = 0;
    std::uint64_t revision = 0;
};

struct CampStore
{
    std::mutex mutex;
    bool enabled = true;
    uint32 cooldownSeconds = 600;
    std::uint64_t generation = 0;
    std::map<ObjectGuid, Camp> camps;
};

CampStore& Store()
{
    static CampStore store;
    return store;
}

std::uint64_t NowMs()
{
    return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

std::uint64_t Remaining(Camp const& camp, std::uint64_t now)
{
    return now >= camp.readyAt ? 0 : (camp.readyAt - now + 999) / 1000;
}

Player* Human(ChatHandler* handler)
{
    WorldSession* session = handler->GetSession();
    if (!session || session->IsBot())
        return nullptr;
    return session->GetPlayer();
}

char const* UnsafePlayer(Player* player)
{
    if (!player->IsInWorld() || player->GetSession()->PlayerLogout() ||
        player->HasUnitState(UNIT_STATE_LOGOUT_TIMER))
        return "wait until you are fully in the world and not logging out";
    if (!player->IsAlive())
        return "you must be alive; recover normally before retrying";
    if (player->IsInCombat())
        return "leave combat first";
    if (player->IsPvP() || player->IsFFAPvP() || player->duel)
        return "PvP flags and duels must be cleared first";
    if (player->IsBeingTeleported() || player->HasDelayedTeleport())
        return "wait for your existing teleport to finish";
    if (player->GetTransport() || player->GetVehicle() || player->IsInFlight())
        return "leave the transport, vehicle or taxi first";
    if (player->IsFlying() || player->IsHovering() || player->IsFalling() ||
        player->HasUnitMovementFlag(MOVEMENTFLAG_FALLING | MOVEMENTFLAG_FALLING_FAR))
        return "stand on stable ground first";
    if (player->IsInWater() || player->isSwimming())
        return "leave the water first";
    // TeleportTo removes some control auras before its script veto. Reject them
    // here so this convenience command cannot be used to escape those effects.
    if (player->HasUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED | UNIT_STATE_CONFUSED |
        UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED | UNIT_STATE_CHARMED | UNIT_STATE_POSSESSED |
        UNIT_STATE_DIED | UNIT_STATE_JUMPING | UNIT_STATE_CHARGING) || !player->GetCharmerGUID().IsEmpty())
        return "wait until you have normal control of your character";
    if (player->IsNonMeleeSpellCast(true))
        return "finish your cast or channel first";
    Map* map = player->GetMap();
    if (!map || !map->IsWorldMap() || map->IsDungeon() || map->IsRaid() || map->IsBattlegroundOrArena())
        return "use Field Camp on a normal outdoor world map";
    if (!player->IsOutdoors())
        return "step outdoors first";
    return nullptr;
}

char const* UnsafeGround(Player* player, WorldLocation const& location, uint32 phase, float& floor)
{
    if (!std::isfinite(location.GetPositionX()) || !std::isfinite(location.GetPositionY()) ||
        !std::isfinite(location.GetPositionZ()) || !std::isfinite(location.GetOrientation()) ||
        !MapMgr::IsValidMapCoord(location))
        return "the position is invalid";
    Map* map = player->GetMap();
    if (!map || location.GetMapId() != map->GetId())
        return "return to your camp's world map by ordinary travel first";
    map->LoadGrid(location.GetPositionX(), location.GetPositionY());
    floor = map->GetHeight(phase, location.GetPositionX(), location.GetPositionY(),
        location.GetPositionZ() + 2.0f, true, 6.0f);
    if (!std::isfinite(floor) || floor <= INVALID_HEIGHT ||
        std::abs(location.GetPositionZ() - floor) > GroundTolerance)
        return "no stable nearby floor could be verified; try another outdoor spot";
    LiquidData const liquid = map->GetLiquidData(phase, location.GetPositionX(), location.GetPositionY(),
        location.GetPositionZ(), player->GetCollisionHeight(), {});
    if ((liquid.Status & MAP_LIQUID_STATUS_IN_CONTACT) != 0)
        return "the position touches liquid; choose dry ground";
    return nullptr;
}

void ClearSession(Player* player)
{
    if (!player)
        return;
    ObjectGuid const guid = player->GetGUID();
    auto& store = Store();
    std::lock_guard<std::mutex> lock(store.mutex);
    store.camps.erase(guid);
}

bool Status(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    Camp camp;
    bool enabled;
    uint32 cooldown;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        enabled = store.enabled;
        cooldown = store.cooldownSeconds;
        auto const itr = store.camps.find(player->GetGUID());
        if (itr != store.camps.end())
            camp = itr->second;
    }
    if (!enabled)
    {
        handler->SendSysMessage("Field Camp is disabled by the server operator.");
        return true;
    }
    if (camp.bound)
        handler->PSendSysMessage("Field Camp: map {}, position ({:.1f}, {:.1f}, {:.1f}), phase {}. Same map/phase now: {}.",
            camp.location.GetMapId(), camp.location.GetPositionX(), camp.location.GetPositionY(),
            camp.location.GetPositionZ(), camp.phase,
            player->GetMapId() == camp.location.GetMapId() && player->GetPhaseMask() == camp.phase ? "yes" : "no");
    else
        handler->SendSysMessage("Field Camp: no camp set. Stand safely outdoors and use .camp set.");
    handler->PSendSysMessage("Return cooldown remaining: {}s ({}s after an accepted request). Clear or replace keeps this cooldown.",
        Remaining(camp, NowMs()), cooldown);
    if (char const* reason = UnsafePlayer(player))
        handler->PSendSysMessage("Currently unavailable: {}.", reason);
    handler->SendSysMessage("Use .camp set, .camp return, .camp status or .camp clear. Camp and cooldown last only this login; a server configuration reload clears both.");
    return true;
}

bool Set(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    if (char const* reason = UnsafePlayer(player))
    {
        handler->PSendSysMessage("Field Camp cannot be set: {}.", reason);
        return true;
    }
    WorldLocation const location(player->GetMapId(), *player);
    uint32 const phase = player->GetPhaseMask();
    float floor = 0.0f;
    if (char const* reason = UnsafeGround(player, location, phase, floor))
    {
        handler->PSendSysMessage("Field Camp cannot be set: {}.", reason);
        return true;
    }
    bool enabled;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        enabled = store.enabled;
        if (enabled)
        {
            Camp& camp = store.camps[player->GetGUID()];
            camp.location = location;
            camp.phase = phase;
            camp.floor = floor;
            camp.bound = true;
            ++camp.revision;
        }
    }
    if (enabled)
        handler->SendSysMessage("Field Camp saved. Travel normally for supplies, then use .camp return from the same world map and phase. Your running cooldown is unchanged.");
    return Status(handler);
}

bool Clear(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto const itr = store.camps.find(player->GetGUID());
        if (itr != store.camps.end())
        {
            itr->second.bound = false;
            ++itr->second.revision;
        }
    }
    handler->SendSysMessage("Field Camp cleared. No automatic return is scheduled. Any running return cooldown remains until it expires.");
    return true;
}

bool Return(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    if (char const* reason = UnsafePlayer(player))
    {
        handler->PSendSysMessage("Field Camp cannot return: {}.", reason);
        return true;
    }
    Camp camp;
    std::uint64_t generation;
    uint32 cooldown;
    bool enabled;
    ObjectGuid const guid = player->GetGUID();
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        enabled = store.enabled;
        generation = store.generation;
        cooldown = store.cooldownSeconds;
        auto const itr = store.camps.find(guid);
        if (itr != store.camps.end())
            camp = itr->second;
    }
    if (!enabled || !camp.bound)
        return Status(handler);
    if (std::uint64_t const seconds = Remaining(camp, NowMs()))
    {
        handler->PSendSysMessage("Field Camp: wait {}s before another return request.", seconds);
        return true;
    }
    if (player->GetMapId() != camp.location.GetMapId() || player->GetPhaseMask() != camp.phase)
    {
        handler->SendSysMessage("Field Camp: travel normally to the saved world map and exact phase before returning, or set a new camp. No cooldown was spent.");
        return true;
    }
    float currentFloor = 0.0f;
    WorldLocation const current(player->GetMapId(), *player);
    char const* reason = UnsafeGround(player, current, camp.phase, currentFloor);
    if (!reason)
        reason = UnsafeGround(player, camp.location, camp.phase, currentFloor);
    if (!reason && std::abs(currentFloor - camp.floor) > FloorChangeTolerance)
        reason = "the saved floor has changed; travel normally and set a new camp";
    if (reason)
    {
        handler->PSendSysMessage("Field Camp cannot return: {}. No cooldown was spent.", reason);
        return true;
    }
    std::uint64_t const reservation = NowMs() + static_cast<std::uint64_t>(cooldown) * 1000;
    bool reserved = false;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        auto const itr = store.camps.find(guid);
        if (store.enabled && store.generation == generation && itr != store.camps.end() &&
            itr->second.bound && itr->second.revision == camp.revision && itr->second.readyAt == camp.readyAt)
        {
            itr->second.readyAt = reservation;
            reserved = true;
        }
    }
    if (!reserved)
    {
        handler->SendSysMessage("Field Camp changed while checking the destination. Use .camp status and retry.");
        return true;
    }
    // Never hold the session lock across core calls or third-party teleport hooks.
    // Default options preserve native veto/ACK/pet behavior; no privileged flags.
    if (!player->TeleportTo(camp.location))
    {
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            auto const itr = store.camps.find(guid);
            if (store.generation == generation && itr != store.camps.end() && itr->second.readyAt == reservation)
                itr->second.readyAt = camp.readyAt;
        }
        handler->SendSysMessage("Field Camp: the server rejected the return request. No cooldown was spent; your camp remains available unless the session was reset.");
        return true;
    }
    handler->PSendSysMessage("Field Camp: return requested; {}s cooldown started. Your client must finish the transfer. The camp remains set.", cooldown);
    return true;
}

class FieldCampCommands final : public CommandScript
{
public:
    FieldCampCommands() : CommandScript("FieldCampCommands") { }
    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable const commands = {
            {"set", Set, SEC_PLAYER, Console::No},
            {"return", Return, SEC_PLAYER, Console::No},
            {"status", Status, SEC_PLAYER, Console::No},
            {"clear", Clear, SEC_PLAYER, Console::No},
            {"", Status, SEC_PLAYER, Console::No}
        };
        static ChatCommandTable const root = {{"camp", commands}};
        return root;
    }
};

class FieldCampPlayer final : public PlayerScript
{
public:
    FieldCampPlayer() : PlayerScript("FieldCampPlayer", {PLAYERHOOK_ON_LOGIN, PLAYERHOOK_ON_LOGOUT}) { }
    void OnPlayerLogin(Player* player) override { ClearSession(player); }
    void OnPlayerLogout(Player* player) override { ClearSession(player); }
};

class FieldCampWorld final : public WorldScript
{
public:
    FieldCampWorld() : WorldScript("FieldCampWorld", {WORLDHOOK_ON_AFTER_CONFIG_LOAD}) { }
    void OnAfterConfigLoad(bool reload) override
    {
        bool const enabled = sConfigMgr->GetOption<bool>("FieldCamp.Enable", true);
        int32 const requested = sConfigMgr->GetOption<int32>("FieldCamp.CooldownSeconds", 600);
        uint32 const cooldown = static_cast<uint32>(std::clamp(requested, int32(60), int32(3600)));
        if (requested != static_cast<int32>(cooldown))
            LOG_WARN("module", "Field Camp: CooldownSeconds clamped to {} (allowed 60..3600)", cooldown);
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            store.enabled = enabled;
            store.cooldownSeconds = cooldown;
            ++store.generation;
            store.camps.clear();
        }
        LOG_INFO("module", "FIELD_CAMP_CONFIG reload={} enabled={} cooldown={}; session camps and cooldowns cleared",
            reload ? 1 : 0, enabled ? 1 : 0, cooldown);
    }
};
}

void Addmod_field_campScripts()
{
    new FieldCampCommands();
    new FieldCampPlayer();
    new FieldCampWorld();
}
