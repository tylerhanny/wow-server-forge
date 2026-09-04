# Practical first-project proposal

Status: RESEARCH_ONLY / awaiting Director launch and claim.
This lane note is not part of a candidate branch. No gameplay implementation has
started and the forge clock remains `ARMED_NOT_STARTED`.

Project: `mod-hunt-rhythm`
Lane: Practical
Decision: SCOUT; recommend BUILD once launch is authorized.

## Smallest worthwhile V1

An opt-in outdoor hunting streak gives leveling players a reason to keep a route
moving. `.rhythm start` opts the current character in for this login session;
`.rhythm status` reports their current streak, remaining chain window, and bonus;
`.rhythm stop` clears it. Consecutive eligible creature kills within a 60-second
window increase the next awarded kill XP by a small step, capped at 10%. Death,
logout, changing maps, stopping, or chain expiry resets the streak. No rewards
other than the explicitly configured XP adjustment.

The exact first-kill and breakpoint rules must be fixed in the project README
before implementation. Proposed default: first eligible kill starts at zero
bonus; each subsequent eligible kill adds two percentage points, capped at 10%.
Display brief personal notices only at meaningful bonus changes, not every kill.

There is no SQL, item reward, quest injection, spell cast, creature template,
client addon, database persistence, global leaderboard, or Playerbots source
change. Players in ordinary bot-assisted parties use the core's normal XP credit
rules. Bots do not automatically opt themselves in.

## Selection rationale

- Player value / fun: modest, immediate leveling loop with visible personal
  progress; provides a reason to plan routes and survive without a large system.
- Novelty: medium-low; the value is a polished, low-risk server-side vertical
  slice, leaving more experimental territory to Wildcard.
- Pinned-API feasibility: strong. Required extension hook, death/logout/map
  reset hooks, typed commands, security-level handling, and config hooks were
  inspected at the exact pin.
- Technical risk: low-to-medium. Reject non-kill XP, zero XP, player/pet/summon
  victims, dead or XP-locked characters, battlegrounds, arenas, dungeons, and
  capped-level characters. Prevent arithmetic overflow and bound all config.
  Synchronize state without holding a lock across core calls; verify hook thread
  context or per-player extension storage before choosing the container.
- Expected size: one module translation unit, small deterministic streak/bonus
  helper, config, README, and focused helper tests. Roughly 250–450 implementation
  lines, no framework.
- Finish confidence before BUILD closes: high conditional on the official
  disposable gate becoming healthy; estimated 85% for this scope after launch.

## Exact pinned source findings

All source references below use AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`; validation must also include Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945` on Ubuntu 24.04 x86-64.

- [PlayerScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/PlayerScript.h)
  declares `OnPlayerGiveXP(Player*, uint32&, Unit*, uint8)`,
  `OnPlayerJustDied(Player*)`, `OnPlayerLogout(Player*)`, and
  `OnPlayerMapChanged(Player*)`, with explicit enabled-hook selection.
- [KillRewarder.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/KillRewarder.cpp)
  calls the XP hook at line 184 with `XPSOURCE_KILL`, after group share, gray
  penalty, and XP aura calculations. The modified amount subsequently reaches
  `Player::GiveXP` and the existing pet-XP path. Pet XP and rested/RAF interactions
  must be documented and covered in the manual checklist, not concealed.
- [Player.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/Player.cpp)
  `GiveXP` begins at line 2404 and checks XP locks, life state, and level caps,
  then calculates rested/RAF bonus. Module eligibility should avoid creating a
  streak for an award this function would reject.
- [Player.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/Player.h)
  declares `PlayerXPSource` near line 1005, `HasPlayerFlag`, and
  `isHonorOrXPTarget`.
- [ChatCommand.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Chat/ChatCommands/ChatCommand.cpp)
  lines 519–523 distinguish RBAC IDs from legacy security levels 0–4.
  `SEC_PLAYER` plus `Console::No` is therefore an explicitly supported path for
  self-service module commands; no auth permission SQL is needed.

## Focused closure plan

After Director launch/claim: specify the exact loop, implement the minimal hook
and command flow, compile through the official gate early, then independently
review. Deterministic helper tests should cover first kill, cap, exact expiration
boundary, restart after expiry, overflow protection, and invalid configuration.
Manual gameplay checks must cover grouping and bots, pets, death, map changes,
logout, XP lock, level cap, rested XP, excluded victims/maps, config reload, and
ordinary quest/exploration XP remaining unaffected.

The design offers no live-validation claim. If reward interactions prove too
uncertain, reduce scope or defer before spending time on optional persistence or
additional rewards.
