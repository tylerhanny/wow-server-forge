# Stormwright

**Turn the boss's storm into your weapon before it tears the arena apart.**

Status: **BUILDING — first implementation checkpoint, not installable or accepted yet.**
The actual C++ controller, deterministic encounter rules and configuration now exist.
Module-owned template/model SQL, final visual polish, complete package documentation,
compilation and independent validation are still being completed. Do not install this
checkpoint as a finished candidate.

One human pilot leads tracking lightning into three capacitor rods, moves after the mark
locks, then chooses what the stored charge buys: Ground restores pilot health and ward;
Discharge damages the armored boss, opens an eight-second damage window, and destroys
nearby pursuers. Cooling rods force new routes. Three missed catches shatter the ward;
every attempt has a twelve-minute cap. Normal, Surge and Tempest retain the same solo loop.

## One-Human Playability

The complete target is one level-80 human at one client/account. Solo Pilot has at most
one live pursuing add and a human-operated recovery choice that remains usable at full
ward when injured. Optional ordinary bots may tank, heal, attack and follow; they never
operate rods, make custom decisions or require an exact tank position. The starting
nearby roster is frozen, with at most five participants. Party play changes ordinary
combat pressure, not the number of custom operators.

The registrar owns every attempt, checks pilot/roster/actor identities, and exposes normal
player gossip. Death, leaving, disconnect, timeout, missing actors, disablement and evade
end the attempt; all owned actors are bounded and cleaned. Outcomes are assisted encounter
results, never an outsider-proof ranking. This checkpoint holds the last result in memory
at its registrar and records terminal outcomes in the module log; it has no persistent
economy or character-power reward.

The intended public venue is the northern Mirage Raceway apron, map 1, research center
XY (-6250, -3750). The implementation derives Z from installed extracted terrain, validates
a bounded ground footprint and refuses to substitute a guessed height. Neither those
source checks nor DBC-only startup prove public walking access, collision/navmesh safety,
visual readability or competent bot traversal. These remain explicit site/client checks.
There is no GM teleport or second account in the intended access/start/outcome/retry/exit loop.

## Exact target and current checks

- Stock WoW 3.3.5a build 12340.
- AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- Ubuntu Server 24.04 x86-64; no production dependency/source edits or client modification.
- Selected C++ method signatures were checked against those exact source files.
- Full compilation, installation, startup, rules execution and official candidate gate:
  **NOT RUN for this checkpoint**.
- Independent implementation review: **PENDING**.
- Actual gameplay, terrain, visuals, class balance and bot feel: **PENDING IN-GAME VALIDATION**.

The marker currently uses direct SpellVisualKit packet 12201 on a bounded owned actor.
Its DBC reference exists; its appearance/lifetime is not yet client-tested. Spell 62186
is never cast. Final delivery will include actual stock model/reference evidence, install
instructions, a complete one-human smoke checklist, creator's note and an implemented
60–90 second capture sequence.
