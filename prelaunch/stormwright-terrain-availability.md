# Stormwright — existing terrain-data availability

```text
STATE=PRELAUNCH_READ_ONLY_SCOUT
FORGE_MAIN_READ=ff41da7f40a6168dc68babfaf2a6c1a4cae882fb
SPRINT=ARMED_NOT_STARTED
SITE=Previously recommended northern Mirage Raceway apron, map 1
RESEARCH_XY=(-6250,-3750); not an approved spawn position
FINAL_POSITION=UNSET
FINAL_Z=UNSET
REGISTRAR_AND_ROD_POSITIONS=UNSET
TERRAIN_AND_ACCESS_VALIDATION=UNAVAILABLE_FROM_EXISTING_FORGE_DATA
```

The existing Forge material does **not** substantiate terrain height or ordinary walking access for this apron. This is a bounded availability finding, not a rejection of Stormwright or a newly approved site.

The Forge workspace and its ignored research/worktree directories were inventoried for extracted `.map`, `.vmtree`, `.vmtile`, `.mmap`, and `.mmtile` files. No matching terrain, collision or navigation tiles were found. Git internals, agent metadata and unrelated Python library directories were excluded; no live installation or filesystem outside the Forge was searched.

The previously obtained complete recursive public [ac-data tree at `74643b700b1cd806845a1dfd926a2c46e7890dbe`](https://github.com/ac-data/ac-data/tree/74643b700b1cd806845a1dfd926a2c46e7890dbe) is not truncated. It contains 249 entries: a README, the `dbc` directory, and 247 entries under `dbc`. There is no `maps`, `vmaps` or `mmaps` tree. Its `dbc` tree identity is `cfd606952f288cf2acc26d80e130617dacd2cc89`.

The local previously verified `Map.dbc` blob `e3d49360f15adb42ce21fe50995a62d276ace0de` and `AreaTable.dbc` blob `9c979a62d652da6a46112aa55c5ce4c2352fab34` support the continent/area metadata recorded in `stormwright-venue-scout.md`. They do not contain an extracted ground-height surface, collision geometry or navigation mesh for this XY point. Nearby pinned SQL spawn heights and waypoint coordinates likewise do not prove continuous ground, line of sight, liquid status, an obstacle-free footprint or an accessible road/corpse-return route. Do not copy the raceway teleport-reference Z or interpolate neighboring NPC heights into approved placements.

The official workflow currently obtains `ac-data` from its public `master` branch and records the resolved commit in `runtime-data-sha.txt`. This scout does not establish the current clean run's eventual resolved data commit, successful runtime result, or terrain availability. A DBC-backed startup result must not be represented as a successful apron height/path test.

The exact compatibility target remains AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. No dependency, map data, SQL, validation input or gameplay source was modified; no new external data was downloaded for this scout.

**Next evidence needed after launch:** authorized disposable extracted terrain/collision/navigation material compatible with the pinned client/core, or the explicitly documented later client/site inspection, must establish the actual ground and public approach/return. Validate the complete encounter footprint, registrar/rod interaction heights, actor chase/evade behavior and optional normal bot traversal. Source-only approval must not claim those results. Keep the full Solo Pilot mechanics and ordinary-player access requirement intact; lack of terrain data does not authorize a GM-teleport-only demonstration or unsupported bot relocation.

Scouting stops here. The earlier northern Mirage recommendation remains a first validation target with its known race/quest exclusions, and every final placement stays UNSET.
