# Exact source and stock assets

Source target: `mod-playerbots/azerothcore-wotlk` commit
`47960183bb03b83e8943eb2f0f39c16df9710c9d`; Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
DBC evidence uses public `ac-data/ac-data` commit
`74643b700b1cd806845a1dfd926a2c46e7890dbe`. This is a recorded data
reference, not permission to update either source dependency or the client.

## Models

Each referenced display was found in the exact CreatureDisplayInfo DBC and followed
to its CreatureModelData asset path. These are stock model references only: the
module does not copy existing NPC scripts, auras, spells, loot, or faction behavior.

| Owned role | Display | Model | Stock asset path | Pinned template reference |
|---|---:|---:|---|---|
| Registrar | 5443 | 182 | `Character/Gnome/Male/GnomeMale.mdx` | 4720 Rizzle Brassbolts |
| Capacitor | 17856 | 2388 | `Creature/QuestObjects/Creature_PowerCrystal.mdx` | 16364 Infused Crystal |
| Boss | 26382 | 2898 | `Creature/RevenantAir/RevenantAir.mdx` | 28858 Storm Revenant |
| Pursuer | 23349 | 69 | `Creature/ElementalEarth/ElementalEarth.mdx` | 26316 Crystalline Ice Elemental |
| Mark | 26753 | 3030 | `Creature/PowerSparkCreature/PowerSparkCreature.mdx` | 30084 Power Spark |

Rejected candidates: display 13069 (Tesla Coil) resolves to InvisibleStalker;
23767 (Crystal Spike) resolves to InvisibleMan. NPC names are not visual evidence.

Verified Git blob identities:

- `CreatureDisplayInfo.dbc`: `ac0fd4d64da74f8d9b750b18cd15ee2ff21941ae`, 24,262 records, 16 fields.
- `CreatureModelData.dbc`: `05faab49646ac73885bcc7c3a2c1d3899a76ded8`, 1,331 records, 28 fields.
- Pinned `creature_template_model.sql`: `75a03c8219212f1d8f51f607695c556f80484a47`.
- Pinned `creature_template.sql`: `899a56b0f5d7bac6536a48e038acb23ba8a70812`.
- Pinned `npc_text.sql`: `d81eb968fa17b8cceb807a5f1cfbb496b5ca60d9`.

The three template tables contain no base row in the reserved 910900–910904 range
(npc_text uses only 910900). A server's other custom modules can still collide;
installation deliberately fails on duplicate keys instead of replacing them.

## Visual packets

Pinned `Unit.cpp:15194–15219` sends a GUID and SpellVisualKit index in
`SendPlaySpellVisual` / `SendPlaySpellImpact`. These methods perform no spell cast,
aura application, trigger, damage, or healing. All gameplay effects live in the
controller. Visual packets are feedback only.

| Use | DBC reference path | Packet kit |
|---|---|---:|
| Tracking orb | Spell 62186 → SpellVisual 13114 → StateKit | 12201 |
| Discharge casting flash | Spell 421 → SpellVisual 36 → CastingKit | 321 |
| Strike / discharge impact | Spell 403 → SpellVisual 173 → ImpactKit | 283 |

All three kits exist in the exact SpellVisualKit DBC. **None of those spells is
cast.** Spell 62186 actually has a periodic trigger and is forbidden as a shortcut.
The orb's owned actor is despawned after impact; casting/impact kits use their
one-shot packet paths. No visual state is attached to the human player.

Verified blobs: Spell.dbc `804810aca3e4fa3bf17247ea6b6e8781eccaf595`;
SpellVisual.dbc `bf7cd0124dda3b83c39009e9f6d0afd832ae84ef`;
SpellVisualKit.dbc `07d8b6c08d12b68f644b035a728688cc1019f9b3`.
Pinned DBCStructure.h documents SpellVisual at fields 131–132, and the
SpellVisualEntry kit ordering. Binary WDBC record size/file length and Git blob
hashes were verified before parsing.

**Still pending in-game:** rendering, scale, clickability, signal readability,
effect lifetime, terrain, pathing, public access, and ordinary bot combat feel.
An asset path and existing kit prove references, not those outcomes.

## Site and native integration

Northern Mirage Raceway apron remains the bounded validation target: map 1,
center XY (-6250, -3750); registrar 40 yards south; rods 13 yards from center.
There is no authored fallback Z. `Map::GetGridHeight` supplies nearby raw terrain,
then the phase-aware `GetHeight` verifies a bounded floor search. Water, missing
data, excessive height deltas and an unsuitable sampled footprint prevent startup.
Start also checks registrar-to-rod LOS. Height samples are not a navigation test.

Pinned spawn and race-path comparisons are recorded in the Forge's
`prelaunch/stormwright-venue-scout.md`; no original race/quest object is changed.
The available public DBC data has no extracted maps/vmaps/mmaps. A dry-run cannot
validate this site: pinned dry-run exits before WorldScript::OnStartup and world
updates, and skips MapMgr::ExistMapAndVMap startup-area checks.

Native module discovery loads `src/` and `conf/`. Pinned UpdateFetcher.cpp:159–193
discovers `modules/<module>/data/sql/db-world/` for module SQL. Manual uninstall is
outside that automatic path. CreatureScript gossip uses sender/action and the
core's ordinary interaction/menu checks; pinned Player.cpp:2115–2167 and
MiscHandler.cpp selection logic impose no global in-combat gossip prohibition.
