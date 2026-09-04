# Stormwright — bounded venue scout

```text
STATE=PRELAUNCH_SOURCE_RESEARCH_ONLY
AUTHORITY_STATE=origin/main 70108321e0359b37539390688faf37d627d857b2; ARMED_NOT_STARTED
SELECTED_PROJECT=mod-stormwright
IMPLEMENTATION=NOT_STARTED
SITE_VALIDATION=NOT_RUN
RECOMMENDATION=Validate northern Mirage Raceway apron first; retain outdoor Ring of Trials only as conditional backup
```

This scout narrows the next site-validation task; it does not approve coordinates for installation. No module, SQL change/application, map simulation, client test, or candidate branch was created. Public pinned base SQL and runtime DBC files were inspected as inert data in this lane's ignored research directory.

## First choice: northern Mirage Raceway apron, Kalimdor

Use the existing raceway as the recognizable destination, with a **new module-owned registrar on the northern approach to the proposed encounter footprint**. Do not reuse or alter a quest NPC. The pinned [`game_tele.sql` row 620](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/game_tele.sql#L661) identifies Mirage Raceway at map 1, `(-6221.35,-3927.64,-58.7495)`. This is a location reference, not a proposed player teleport or access requirement.

The first ground-check target is the apron around **XY `(-6250,-3750)`**, roughly 180 yards north of that reference. Its final Z, registrar location, boundary and rod positions are deliberately unset. An initial compact footprint of roughly 35–40 yards radius is worth checking here; the actual usable ground must accommodate the existing three-rod route and ordinary chase movement.

Pinned base-data screening gives these horizontal separations from that proposed center:

| Reference | Approximate separation | What it establishes |
|---|---:|---|
| Nearest creature spawn, Rizzle Brassbolts 4720 / GUID 21577 | 82.3yd | Existing quest NPC lies outside a small proposed footprint; not proof of aggro or movement clearance. |
| Nearest gameobject, Rizzle's Guarded Plans 179888 / GUID 17087 | 81.6yd | Quest interaction space needs a buffer. |
| Rizzle path 4720 / Zamek path 4709 | 82.3 / 97.7yd | Their explicitly scripted distraction route is south of this candidate. |
| Gnome staging path 425200 / main race 425201 | 106.5 / 146.5yd | Known racing traffic is substantially farther away here. |
| Goblin staging path 425100 / main race 425101 | 156.1 / 155.5yd | Same for the other racer. |

Distances are calculations against base spawn XY coordinates and line segments between recorded waypoints, not measured terrain paths, actor footprints, or guarantees about splines. Static creature screening subtracts configured wander distance. Three additional nearby waypoint actors with paths 213010, 213110, 214970 remain at least 270 yd from the target in this limited screen. Dynamic events and the fully updated world database still need checking.

**Rejected nearby placement:** `(-6325,-3925)` looked clear from stationary spawn positions but is only 24 yd from Goblin race path 425101. Do not place the encounter there or in the populated raceway center. The race paths are in [`waypoint_data.sql`](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/waypoint_data.sql#L41277); [`smart_scripts.sql`](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/smart_scripts.sql#L8317) identifies both racers' active paths. Zamek's quest 1191 also starts a route, summons Explosive Charge 144065 and activates Rizzle's event; preserve all of it ([event actions](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/smart_scripts.sql#L40935), [quest paths](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/waypoints.sql#L1349)).

## Conditional backup: outdoor Ring of Trials, Nagrand

The pinned [location row 1124](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/game_tele.sql#L1165) is map 530 at `(-1999.94,6581.71,11.32)`. It is not the instanced Nagrand Arena map 559. A registrar would have to be placed outside its existing gates, with ordinary walking access into and out of the actual encounter ground demonstrated.

This option has more concrete complications. Burning Braziers 183189–183192 and two arena doors 183288–183289 already occupy the ring: the closest braziers are about 10 yd from the reference, the doors about 14 and 33 yd. Their [templates](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/gameobject_template.sql#L12128) bind the braziers to `go_flames`; they must not be assumed harmless scenery. Nearby Windrocs, a 40 yd-wandering Windy Cloud and a waypoint Dust Howler also need clearance checks. Do not remove, disable or reposition these existing objects or creatures to make Stormwright fit.

Area flags add a significant warning. Exact DBC row 3638, The Ring of Trials, lacks `AREA_FLAG_ARENA`, but row 3701 **Arena Floor** has it (`0x40004480`). Both [door spawns](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/gameobject.sql#L14869) record area 3701. The actual walked route's area transitions and resulting PvP/faction/bot behavior must be checked, not inferred from the named parent area. This is a reason to prefer Mirage, without declaring the entire outdoor ring unusable.

## Public access, one human, and return

Both candidates are common outdoor world maps in the exact runtime `Map.dbc`: maps 1 and 530 have type 0; map 559 has type 4. The [pinned enum](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/shared/DataStores/DBCEnums.h#L346) and [MapEntry helpers](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/shared/DataStores/DBCStructure.h#L1387) distinguish ordinary continents from instanced arenas. Mirage Raceway 2240 and Shimmering Flats 439 have flags `0x40000040`: neither arena nor sanctuary. Normal realm/world-PvP rules still apply.

The proposed qualifying path is ordinary level 80 travel to the Shimmering Flats raceway, walk to the registrar, start Solo Pilot, perform every rod decision, finish/fail, reuse the registrar, and walk away. No `.tele`, GM spawn, queue opponent, gate operator, second account or player teleport is part of that path. Death uses ordinary release/recovery and return. A future README must document and verify the approach from public roads and the return/corpse route; the teleport table alone cannot prove either route.

Optional bots travel/follow and fight normally. Pinned [`FollowMasterStrategy`](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Strategy/FollowMasterStrategy.cpp#L9) selects ordinary `follow`; this is source support, not a successful site traversal test. Start uses nearby present roster members and never assumes the module can relocate missing bots. No forced teleport or new bot behavior is needed. With zero bots, the complete selected Solo Pilot profile remains mandatory: one pursuing add maximum, human Ground recovery, meaningful discharge damage and every environmental choice preserved. An open compact footprint supports that design without another operator or precise tank placement, subject to actual ground and chase validation.

## Required next validation, then stop scouting

After formal launch, check this one Mirage candidate against the fully assembled pinned disposable database, relevant event/path spawns and map/vmap/mmap ground, collision, liquid and height data. Validate the whole bounded footprint and public approach/return; reject any need to edit existing world content. Client checks must cover rod line of sight/interactions, ordinary chase without evade/reset surprises, Solo Pilot survival while moving, optional bot following, arena-boundary cleanup and repeat attempts. Stock visual-kit visibility and lifetime must be checked against the bright salt-flat background. Spell 62186 remains unapproved; this site scout adds no visual approval.

**Disposition:** northern Mirage is a credible first validation target with specific known conflicts avoided. It is not a certified safe site. Keep Ring of Trials only as a conditional backup; no broader venue search or gameplay work is justified before launch.

## Evidence identity and limits

All SQL above is public `mod-playerbots/azerothcore-wotlk` at `47960183bb03b83e8943eb2f0f39c16df9710c9d`; the base files were downloaded without execution and their Git blob hashes matched that commit's tree. Key blobs: `creature.sql`=`46038b8f4237fca31054496493c59021f592d6a4`, `gameobject.sql`=`d7d0b3b2c8b5fd615ffb3d97defb9d01d17f38ea`, `waypoint_data.sql`=`e0e7245d3946a31b10731a1d00e84925d3daacd0`, `smart_scripts.sql`=`1b89e8261141e9dce05ece5f26722bc8233e6b87`.

Runtime DBCs are public [ac-data/ac-data at 74643b700b1cd806845a1dfd926a2c46e7890dbe](https://github.com/ac-data/ac-data/tree/74643b700b1cd806845a1dfd926a2c46e7890dbe), matching the previously reviewed runtime-data reference: `Map.dbc` blob `e3d49360f15adb42ce21fe50995a62d276ace0de`; `AreaTable.dbc` blob `9c979a62d652da6a46112aa55c5ce4c2352fab34`. Their binary records were parsed using the exact core DBC structure field indices. DBC area names/flags do not map an arbitrary XY coordinate to its true area; extracted map data is still required. This scout has not applied the pinned SQL update chain or exhausted dynamic spawn sources. No terrain, gameplay, independent site-review, official candidate-gate or live-server success is claimed.
