#include "FieldRepairsRules.h"

#include "Bag.h"
#include "Chat.h"
#include "Config.h"
#include "DBCStores.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "Log.h"
#include "Map.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "World.h"
#include "WorldSession.h"

#include <chrono>
#include <iterator>
#include <map>
#include <mutex>
#include <string>

namespace
{
using namespace Acore::ChatCommands;

struct SessionStore
{
    std::mutex mutex;
    bool enabled = true;
    std::uint64_t generation = 0;
    std::map<ObjectGuid, std::uint64_t> consent;
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

std::string Money(std::uint64_t copper)
{
    return std::to_string(copper / 10000) + "g " + std::to_string(copper / 100 % 100) +
        "s " + std::to_string(copper % 100) + "c";
}

Player* Human(ChatHandler* handler)
{
    WorldSession* session = handler->GetSession();
    return session && !session->IsBot() ? session->GetPlayer() : nullptr;
}

char const* Ineligible(Player* player)
{
    if (!player->IsInWorld() || player->GetSession()->PlayerLogout() ||
        player->HasUnitState(UNIT_STATE_LOGOUT_TIMER))
        return "wait until you are in the world and not logging out";
    if (!player->IsAlive())
        return "recover normally before requesting service";
    if (player->IsInCombat())
        return "leave combat first";
    if (player->IsPvP() || player->IsFFAPvP() || player->duel)
        return "clear PvP flags and finish any duel first";
    if (player->GetTradeData())
        return "close your trade first";
    if (player->IsBeingTeleported())
        return "finish the existing teleport first";
    if (player->IsInFlight() || player->GetTransport() || player->GetVehicle())
        return "leave the taxi, transport or vehicle first";
    if (player->HasUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED | UNIT_STATE_CONFUSED |
        UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED | UNIT_STATE_CHARMED | UNIT_STATE_POSSESSED |
        UNIT_STATE_DIED | UNIT_STATE_JUMPING | UNIT_STATE_CHARGING) || !player->GetCharmerGUID().IsEmpty())
        return "wait until you have normal control of your character";
    if (player->IsNonMeleeSpellCast(true))
        return "finish your cast or channel first";
    Map* map = player->GetMap();
    if (!map || !map->IsWorldMap() || map->IsDungeon() || map->IsRaid() || map->IsBattlegroundOrArena())
        return "use Field Repairs on a normal outdoor world map";
    if (!player->IsOutdoors())
        return "step outdoors first";
    return nullptr;
}

struct Condition
{
    uint32 current;
    uint32 maximum;
};

struct Inspection
{
    std::map<ObjectGuid, Condition> items;
    uint32 damaged = 0;
    uint32 wallet = 0;
    char const* problem = nullptr;
};

// Match the exact pinned DurabilityRepairAll slot iteration. Bank, buyback and
// keys are not visited. Read-only inspection always finishes before native repair.
template<class Visitor>
void VisitCarriedItems(Player* player, Visitor visit)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            visit(item);
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
        for (uint8 slot = 0; slot < MAX_BAG_SIZE; ++slot)
            if (Item* item = player->GetItemByPos(bag, slot))
                visit(item);
}

Inspection Inspect(Player* player, bool checkPrices)
{
    Inspection result;
    result.wallet = player->GetMoney();
    float const rate = sWorld->getRate(RATE_REPAIRCOST);
    VisitCarriedItems(player, [&](Item* item)
    {
        if (result.problem)
            return;
        uint32 const maximum = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
        if (!maximum)
            return;
        uint32 const current = item->GetUInt32Value(ITEM_FIELD_DURABILITY);
        if (current > maximum)
        {
            result.problem = "an item has invalid durability; ask the operator to inspect it";
            return;
        }
        if (!result.items.emplace(item->GetGUID(), Condition{current, maximum}).second)
        {
            result.problem = "carried item identities are inconsistent; ask the operator to inspect them";
            return;
        }
        if (current == maximum)
            return;
        ++result.damaged;
        if (!checkPrices)
            return;

        ItemTemplate const* itemTemplate = item->GetTemplate();
        if (!itemTemplate || itemTemplate->Quality >= MAX_ITEM_QUALITY)
        {
            result.problem = "an item's repair data is invalid; ask the operator to inspect it";
            return;
        }
        bool const weapon = itemTemplate->Class == ITEM_CLASS_WEAPON;
        bool const armor = itemTemplate->Class == ITEM_CLASS_ARMOR;
        if ((!weapon && !armor) || (weapon && itemTemplate->SubClass >= MAX_ITEM_SUBCLASS_WEAPON) ||
            (armor && itemTemplate->SubClass >= MAX_ITEM_SUBCLASS_ARMOR))
        {
            result.problem = "a damaged item has an unsupported repair classification";
            return;
        }
        DurabilityCostsEntry const* costs = sDurabilityCostsStore.LookupEntry(itemTemplate->ItemLevel);
        DurabilityQualityEntry const* quality = sDurabilityQualityStore.LookupEntry((itemTemplate->Quality + 1) * 2);
        if (!costs || !quality)
        {
            result.problem = "required repair price data is missing; ask the operator to inspect it";
            return;
        }
        std::uint64_t const rawIndex = static_cast<std::uint64_t>(itemTemplate->SubClass) + (armor ? 21 : 0);
        if (rawIndex >= std::size(costs->multiplier))
        {
            result.problem = "a damaged item has an invalid repair price index";
            return;
        }
        uint32 const multiplier = costs->multiplier[static_cast<std::size_t>(rawIndex)];
        if (!FieldRepairs::NativeCostSafe(maximum, current, multiplier, quality->quality_mod, rate))
            result.problem = "a repair price exceeds safe native limits; ask the operator to inspect item data and repair rate";
    });
    return result;
}

void ClearConsent(Player* player)
{
    if (!player)
        return;
    ObjectGuid const guid = player->GetGUID();
    auto& store = Store();
    std::lock_guard<std::mutex> lock(store.mutex);
    store.consent.erase(guid);
}

bool Status(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    bool enabled;
    std::uint64_t seconds = 0;
    ObjectGuid const guid = player->GetGUID();
    std::uint64_t const now = NowMs();
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        enabled = store.enabled;
        auto const itr = store.consent.find(guid);
        if (itr != store.consent.end())
        {
            seconds = FieldRepairs::ConsentSeconds(itr->second, now);
            if (!seconds)
                store.consent.erase(itr);
        }
    }
    if (!enabled)
    {
        handler->SendSysMessage("Field Repairs is disabled by the server operator.");
        return true;
    }
    Inspection const current = Inspect(player, false);
    if (current.problem)
        handler->PSendSysMessage("Field Repairs cannot inspect your gear: {}.", current.problem);
    else
        handler->PSendSysMessage("Field Repairs: {} damaged carried/equipped items. Balance: {}. Consent remaining: {}s.",
            current.damaged, Money(current.wallet), seconds);
    if (char const* reason = Ineligible(player))
        handler->PSendSysMessage("Currently unavailable: {}.", reason);
    handler->SendSysMessage("Paid service uses current native prices without vendor reputation discounts and may repair only some items. Use .fieldrepair request, .fieldrepair confirm or .fieldrepair cancel.");
    return true;
}

bool Request(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    ClearConsent(player);
    if (char const* reason = Ineligible(player))
    {
        handler->PSendSysMessage("Field Repairs cannot start: {}. Nothing was charged.", reason);
        return true;
    }
    Inspection const current = Inspect(player, true);
    if (current.problem)
    {
        handler->PSendSysMessage("Field Repairs cannot start: {}. Nothing was charged.", current.problem);
        return true;
    }
    if (!current.damaged)
    {
        handler->SendSysMessage("Field Repairs: no carried/equipped item needs repair. Nothing was charged.");
        return true;
    }
    bool enabled;
    ObjectGuid const guid = player->GetGUID();
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        enabled = store.enabled;
        if (enabled)
            store.consent[guid] = NowMs() + FieldRepairs::ConsentMilliseconds;
    }
    if (!enabled)
        return Status(handler);
    handler->PSendSysMessage("Field Repairs request: {} damaged items; balance {}. Confirm authorizes CURRENT native personal-gold repair charges for ALL carried/equipped gear, without vendor reputation discounts. Prices and items are checked again when you confirm; this is not a price quote.",
        current.damaged, Money(current.wallet));
    handler->SendSysMessage("If you cannot afford every item, the core may repair only some and leave others damaged. No guild money is used. Within 30s use .fieldrepair confirm, or .fieldrepair cancel to leave without payment.");
    return true;
}

bool Confirm(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    ObjectGuid const guid = player->GetGUID();
    std::uint64_t const now = NowMs();
    std::uint64_t generation;
    bool authorized = false;
    bool enabled;
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        enabled = store.enabled;
        generation = store.generation;
        auto const itr = store.consent.find(guid);
        if (itr != store.consent.end())
        {
            authorized = enabled && FieldRepairs::ConsentValid(itr->second, now);
            store.consent.erase(itr); // One attempt consumes consent even on refusal.
        }
    }
    if (!enabled)
        return Status(handler);
    if (!authorized)
    {
        handler->SendSysMessage("Field Repairs: no active consent. Nothing was charged. Use .fieldrepair request first.");
        return true;
    }
    if (char const* reason = Ineligible(player))
    {
        handler->PSendSysMessage("Field Repairs cannot continue: {}. Nothing was charged; request again when ready.", reason);
        return true;
    }
    Inspection const before = Inspect(player, true);
    if (before.problem)
    {
        handler->PSendSysMessage("Field Repairs cannot continue: {}. Nothing was charged; request again after correction.", before.problem);
        return true;
    }
    if (!before.damaged)
    {
        handler->SendSysMessage("Field Repairs: no carried/equipped item needs repair. Nothing was charged.");
        return true;
    }
    {
        auto& store = Store();
        std::lock_guard<std::mutex> lock(store.mutex);
        authorized = store.enabled && store.generation == generation;
    }
    if (!authorized)
    {
        handler->SendSysMessage("Field Repairs configuration changed. Nothing was charged; request service again if enabled.");
        return true;
    }
    // Native repair owns all affordability checks, gold debits and item/stat
    // changes. Its return value is not personal money spent. No lock crosses it.
    player->DurabilityRepairAll(true, 1.0f, false);
    Inspection const after = Inspect(player, false);
    bool const decreased = after.wallet < before.wallet;
    std::uint64_t const difference = decreased ? before.wallet - after.wallet : after.wallet - before.wallet;
    handler->PSendSysMessage("Field Repairs wallet change: {}{}; current balance {}.",
        decreased ? "-" : "+", Money(difference), Money(after.wallet));
    if (after.problem)
    {
        handler->SendSysMessage("Field Repairs completed its native request, but resulting item state could not be fully verified. Inspect your gear and contact the operator; no automatic retry will occur.");
        return true;
    }
    uint32 repaired = 0;
    for (auto const& entry : before.items)
    {
        auto const itr = after.items.find(entry.first);
        if (entry.second.current < entry.second.maximum && itr != after.items.end() &&
            itr->second.maximum == entry.second.maximum && itr->second.current == itr->second.maximum)
            ++repaired;
    }
    handler->PSendSysMessage("Field Repairs: {} of {} previously damaged items repaired; {} carried/equipped items remain damaged.",
        repaired, before.damaged, after.damaged);
    if (after.damaged)
        handler->SendSysMessage("Some items remain damaged. Native repair can skip unaffordable items and repair later cheaper ones. Earn more gold if needed, then request service again.");
    else
        handler->SendSysMessage("Your carried/equipped gear is fully repaired. Service is finished; there is no automatic payment or pending request.");
    return true;
}

bool Cancel(ChatHandler* handler)
{
    Player* player = Human(handler);
    if (!player)
        return false;
    ClearConsent(player);
    handler->SendSysMessage("Field Repairs consent cleared. Nothing was charged; no repair will occur automatically.");
    return true;
}

class FieldRepairsCommands final : public CommandScript
{
public:
    FieldRepairsCommands() : CommandScript("FieldRepairsCommands") { }
    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable const commands = {
            {"status", Status, SEC_PLAYER, Console::No},
            {"request", Request, SEC_PLAYER, Console::No},
            {"confirm", Confirm, SEC_PLAYER, Console::No},
            {"cancel", Cancel, SEC_PLAYER, Console::No},
            {"", Status, SEC_PLAYER, Console::No}
        };
        static ChatCommandTable const root = {{"fieldrepair", commands}};
        return root;
    }
};

class FieldRepairsPlayer final : public PlayerScript
{
public:
    FieldRepairsPlayer() : PlayerScript("FieldRepairsPlayer", {PLAYERHOOK_ON_LOGIN, PLAYERHOOK_ON_LOGOUT,
        PLAYERHOOK_ON_PLAYER_JUST_DIED, PLAYERHOOK_ON_MAP_CHANGED}) { }
    void OnPlayerLogin(Player* player) override { ClearConsent(player); }
    void OnPlayerLogout(Player* player) override { ClearConsent(player); }
    void OnPlayerJustDied(Player* player) override { ClearConsent(player); }
    void OnPlayerMapChanged(Player* player) override { ClearConsent(player); }
};

class FieldRepairsWorld final : public WorldScript
{
public:
    FieldRepairsWorld() : WorldScript("FieldRepairsWorld", {WORLDHOOK_ON_AFTER_CONFIG_LOAD}) { }
    void OnAfterConfigLoad(bool reload) override
    {
        bool const enabled = sConfigMgr->GetOption<bool>("FieldRepairs.Enable", true);
        {
            auto& store = Store();
            std::lock_guard<std::mutex> lock(store.mutex);
            store.enabled = enabled;
            ++store.generation;
            store.consent.clear();
        }
        LOG_INFO("module", "FIELD_REPAIRS_CONFIG reload={} enabled={} consent=30", reload ? 1 : 0, enabled ? 1 : 0);
    }
};
}

void Addmod_field_repairsScripts()
{
    new FieldRepairsCommands();
    new FieldRepairsPlayer();
    new FieldRepairsWorld();
}
