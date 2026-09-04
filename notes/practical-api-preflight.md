# Hunt Rhythm API preflight addendum

RESEARCH_ONLY, 2026-09-04. Adds concrete details missing from
`practical-first-project.md`; no gameplay implementation or runtime test occurred.
AC pin: `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
Playerbots pin: `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.

## Reward details to carry into implementation review

- The previously documented group-share/aura → module hook ordering is correct.
  More precisely, the hook amount then enters `Player::GiveXP`, which applies
  favored-area +5%, the effective normal/trial level-cap check, and partial-play-
  time halving before RAF/rested handling. RAF adds twice that player amount and
  excludes rested XP. Rested adds `min(player amount, rested pool)` and **consumes
  that amount from the pool**. Pet XP uses the hook amount (solo 100%, group 50%),
  without those later player-only adjustments. Therefore added base XP is not a
  promise of identical percentage changes to the final player/pet rewards.
  Sources: [KillRewarder.cpp:149–188](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/KillRewarder.cpp#L149),
  [Player.cpp:2404–2475](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/Player.cpp#L2404),
  [rested pool:9095–9105](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/Player.cpp#L9095).
- Explicitly reject a creature without `hasLootRecipient()` **before advancing or
  refreshing the chain**: `GiveXP` rejects it after the hook. Likewise check both
  `PLAYER_FLAGS_NO_XP_GAIN` and `PLAYER_FLAGS_NO_PLAY_TIME`; partial play time is
  reduced XP, not rejection. Effective cap is the minimum of configured maximum
  and nonzero trial cap when `GetSession()->IsTrialAccount()`. Core also calls
  `OnPlayerBeforeGetLevelForXPGain`; do not assume an arbitrary additional module
  overriding that hook is compatible without separate review.
- Wide intermediates protect the module's percentage multiplication/addition;
  they do not fix the existing core's later `uint32` RAF multiplication and
  `curXP + xp + bonus_xp` accumulation. Saturating module output to `UINT32_MAX`
  would therefore be unsafe. At implementation time, bound/decline the **added
  bonus** when downstream headroom cannot be established, preserving the
  original core award. Do not claim to repair pre-existing extreme-XP core
  arithmetic or mutate dependency code.
- The pinned Playerbots XP override returns without changing a human's award.
  Its random-bot multiplier also returns when the bot's group includes a real
  player. No new human XP-hook ordering conflict was found in that script.
  [Playerbots.cpp:265–290](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Script/Playerbots.cpp#L265).

## Exact exclusion and lifecycle details

The exclusion APIs exist: `Unit::IsSummon/IsPet/IsTotem/IsCritter`,
`GetCharmerOrOwnerGUID`, `IsHostileTo`; `Creature::isElite`, `isWorldBoss`,
`hasLootRecipient`; and `Map::IsWorldMap/IsDungeon/IsRaid/IsBattlegroundOrArena`.
`isHonorOrXPTarget` alone does not enforce every proposed exclusion.
Sources: [Unit.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.h),
[Creature.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Creature/Creature.h),
[Map.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Maps/Map.h).

- `OnPlayerJustDied(Player*)` fires from `Player::KillPlayer` after corpse state
  is set ([Player.cpp:4628–4653](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/Player.cpp#L4628)).
- `OnPlayerMapChanged(Player*)` is dispatched on successful map entry, including
  login entry, through `Map::AddPlayerToMap` → `OnPlayerEnterMap`. It is not a
  zone-change callback; same-map travel does not automatically reset a chain.
  [AllMapScript.cpp:184–194](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/AllMapScript.cpp#L184).
- `OnPlayerLogout(Player*)` runs before deletion on ordinary logout; the core
  skips it when `redirecting` is true. A fresh-login clear can ensure a GUID-keyed
  session store never carries opt-in across login even on that unusual path.
  Do not dereference map state during logout cleanup.
  [WorldSession.cpp:850–873](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Server/WorldSession.cpp#L850).
- `OnAfterConfigLoad(bool reload)` runs after successful initial/reloaded world
  settings. A failed config read returns before it; failed reload must not be
  reported as a successful settings/session reset.
  [World.cpp:168–301](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/World/World.cpp#L168).

Useful source uncertainties for this bounded check are resolved. Actual class,
pet/rested and ordinary bot-group behavior remains pending one-human gameplay
validation. Implementation decisions wait for recorded launch and claim.
