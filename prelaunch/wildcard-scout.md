# Wildcard prelaunch scouting

Status: **DESIGN / SOURCE RESEARCH ONLY**. The sprint remains `ARMED_NOT_STARTED`.
No harvest implementation, compile, startup, official gate, or gameplay test has been performed for these concepts.

Lane: `lane/wildcard`, isolated worktree `.worktrees/wildcard`.
Authority/state reviewed: the seven required root files, `prompts/WILDCARD.md`, and `build/pins.env`; current fetched coordination reference was `origin/main` at `7ffa2bd`.

## Recommendation: The Small Council

Ordinary wild critters secretly belong to three absurdly serious courts. A player opts in, targets a nearby critter, and bows. The animal presents a private, short riddle in chat; the player answers through stock WoW emotes. Three correct answers earn that court's seal and unlock its account of what the small creatures think the great heroes are actually doing. Finding all three courts reveals a final story. The world has acquired a quiet, funny layer without replacing its creatures or combat.

Example tone: "The court recognizes that you are tall. It asks whether you have any other qualifications." A court may demand a salute, a laugh at one's own importance, then a kneel to see the world at the witness's height. The writing should make the familiar emotes feel like a conversation, not arbitrary passwords.

Smallest worthwhile complete V1:

- Explicit `.smallcouncil join`, `leave`, `help`, `journal`, and `hint` commands; opting out clears the current audience.
- Three authored courts, three short riddles per audience, helpful recovery text, and an ending for collecting all three seals.
- Classify a naturally spawned, alive wild critter by a documented stable function of its existing creature entry. Species retain their court; no creature-template IDs, spawn coordinates, or custom client assets need to be assumed.
- Bow begins or deliberately restarts an audience. Other accepted emotes answer the current riddle. Bind an audience to the specific creature GUID and map, with a generous timeout and explicit wrong-answer recovery.
- A compact persistent character journal: three seal bits and explicit participation state in one module-owned characters table. An in-progress audience is ephemeral and ends on logout, death, map change, opt-out, expiry, or loss of the target. Idempotent seal writes; no player currency, item, title, or combat-stat reward.
- All authored responses go privately to the participant. The ordinary emote remains visible through the existing client behavior.
- Config for enablement, maximum interaction distance, and timeout, with bounded values and a startup/module-load marker. No world SQL changes, NPC AI replacement, summons, spells, core edits, or Playerbots source edits.

Decision note:

| Criterion | Assessment |
|---|---|
| Player value / fun | A small secret to discover and share; readable, replayable emote conversations with a complete narrative ending. |
| Novelty | High relative to combat progression: the overlooked animals judge the heroes. |
| Pinned feasibility | Strong source evidence for targeted text-emote hooks, private chat, commands, creature classification, lifecycle cleanup, and bot-session exclusion. |
| Technical risk | Low to moderate: schema lifecycle, repeated input, target invalidation, config reload, and overlap with ordinary creature emote scripts. |
| Expected size | Roughly one module source file, one small deterministic rules helper, one characters migration, config, and complete install/smoke documentation. Estimate: 4–6 focused implementation hours plus actual external build/review time. |
| Completion confidence | High relative to other creative concepts, conditional on the official judge smoke succeeding and real pinned compilation. Not a tested probability or an acceptance claim. |
| Decision | **Preferred launch candidate**, subject to Director claim/launch. Suggested slug: `mod-small-council`. |

Scope boundaries and closure checks:

1. Filter to real, non-bot sessions and explicit opt-in. Playerbots can generate the same text-emote callback as humans; accepting every callback would be incorrect.
2. Accept only the finite authored text-emote IDs. The pinned hook fires before the core validates the ID against the DBC.
3. Resolve the target through `ObjectAccessor::GetCreature(*player, guid)` and require same map/phase, within range, alive, a critter, a database spawn, and no owner/charmer/creator. Revalidate on every answer; never retain a raw creature pointer.
4. Never mutate or consume the creature's ordinary emote handling. The base AI callback still runs later. Puzzles must use an emote whitelist that avoids known stock quest interactions where practical; any existing behavior remains a compatibility test item.
5. Give no durable seal until the full three-step audience succeeds. Bound state per online opted-in player; rate-limit processing and help/error replies.
6. Keep the story journal independent of economic rewards. Failure/replay should be pleasant; a timeout is not punishment.
7. Before finalizing court classification, confirm that the disposable pinned world data provides naturally spawned critters for all three classes. If distribution is poor, adjust the product classification before candidate review, without adding world spawns.
8. Deterministic developer tests should exercise correct/incorrect steps, target switch, expiry, duplicate final input, restart/opt-out, and seal idempotency. Official compilation/install/startup/reviewer evidence is still mandatory.
9. In-game tests must cover all three courts and ending; out-of-range/dead/pet/summoned/wrong-phase targets; ordinary creature AI coexistence; bot emote reactions; relog/restart persistence; and disabling the module. These remain future Tyler tests, not prelaunch evidence.

## Alternative: The Courtesy Duel

A two-player duel fought entirely through manners. A bow invites a nearby player. After explicit acceptance, each secretly chooses Courage (`salute`), Wit (`laugh`), or Grace (`kneel`) in private commands, then the server reveals both choices together: Courage beats Wit, Wit beats Grace, and Grace beats Courage. First to three wins receives a private herald's account of the ridiculous contest. A solo practice opponent makes the loop usable when nobody else is online.

Smallest worthwhile V1: invite/accept/decline; one active match per player; first-to-three bounded rounds; private locked choices; explicit rules and score; timeout/forfeit/disconnect cleanup; a practice opponent; no wager, paid currency, prizes, cross-faction chat bridge, or permanent ranking. The stock emotes are ceremony; **secret choices use `.courtesy choose ...`**, because an ordinary `/salute` is broadcast by the core and would leak the first player's choice.

This is a compact social bluffing game with fewer data dependencies than Small Council. It is technically feasible through the same command/private-message APIs plus map-local GUID lookup and logout hooks. Primary risks are two-player state consistency, self/duplicate invitations, round-choice leakage, simultaneous input, and match cleanup. Estimated size is 300–500 lines of module/state-machine code plus config/docs/tests; closure confidence is high after pinned compilation, but its atmosphere and discovery value are lower. **Reserve candidate**, not currently claimed.

## Exact pinned API evidence

All source URLs below name the immutable commit used in `build/pins.env`, not a moving default branch. Files were read from public GitHub. No live endpoints or other Tyler projects were accessed.

### AzerothCore

Pin: `47960183bb03b83e8943eb2f0f39c16df9710c9d` from `mod-playerbots/azerothcore-wotlk`.

| Source | Verified capability and implication |
|---|---|
| [PlayerScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/PlayerScript.h#L328) | `OnPlayerTextEmote(Player*, uint32 textEmote, uint32 emoteNum, ObjectGuid guid)` provides the targeted text emote. Constructor at line 230 supports explicitly enabled hooks. Lifecycle hooks include `OnPlayerJustDied` at 234, login/logout at 337/343, `OnPlayerMapChanged` at 367, and `OnPlayerDeleteFromDB(CharacterDatabaseTransaction, uint32)` at 522. |
| [ChatHandler.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Handlers/ChatHandler.cpp#L717) | `HandleTextEmoteOpcode`: alive/mute/spectator checks precede the hook; line 752 dispatches the hook; line 754 validates `sEmotesTextStore`; line 778 resolves the target; line 789 calls existing creature AI `ReceiveEmote`. This is observation/addition, not an interception hook. `OnPlayerEmote` at line 681 is a different restricted animation path and is unsuitable for the puzzle. |
| [ObjectAccessor.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Globals/ObjectAccessor.h) | Map-local `GetCreature(WorldObject const&, ObjectGuid const&)` and `GetPlayer(WorldObject const&, ObjectGuid const&)` exist. The header explicitly warns that whole-world player access is not thread-safe; neither concept needs a world-wide player scan. |
| [Object.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Object/Object.h#L549) and [Object.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Object/Object.cpp#L1381) | `IsWithinDistInMap` exists and its implementation checks non-null target, same map, same phase, and distance. `IsWithinLOSInMap` is also available if the design chooses to require line of sight. |
| [Unit.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.h#L714) | `GetOwnerGUID`, `GetCreatorGUID`, and `GetCharmerGUID` are available. `IsCritter()` at line 834 checks `GetCreatureType() == CREATURE_TYPE_CRITTER`. |
| [Creature.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Creature/Creature.h#L69) | `GetSpawnId()` exposes a database spawn identifier, allowing exclusion of ephemeral/player-created summons in conjunction with ownership and type checks. |
| [SharedDefines.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/shared/SharedDefines.h#L1656) | Exact text-emote constants include `BOW=17`, `CHEER=21`, `CHICKEN=22`, `DANCE=34`, `KNEEL=59`, `LAUGH=60`, `SALUTE=78`, `WAVE=101`, `LOVE=225`. Use named constants in eventual code. |
| [WorldSession.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Server/WorldSession.h#L1230) | `IsBot()` exposes the session's bot flag, sufficient to reject ordinary Playerbots sessions without linking module internals. Do not claim this proves exclusion of human-client selfbot automation. |
| [Chat.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Chat/Chat.h#L141) and [CommandScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/CommandScript.h#L31) | `ChatHandler::SendSysMessage(std::string_view, bool)` and the `CommandScript::GetCommands()` builder-vector API exist. Use fixed authored text/private session feedback; do not broadcast player-supplied arbitrary text. |

### Playerbots

Pin: `2f7d9f774987d0157c6a0d0cc08c40bec3db3945` from `mod-playerbots/mod-playerbots`.

| Source | Verified compatibility boundary |
|---|---|
| [EmoteAction.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Actions/EmoteAction.cpp#L632) | Lines 632–638 construct a text-emote packet and call `bot->GetSession()->HandleTextEmoteOpcode(data)`. Bot-generated inputs reach the same core hook. Lines 751–757 provide another explicit text-emote path. |
| [PlayerbotAI.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Bot/PlayerbotAI.cpp#L4410) | `IsRealPlayer` returns `player && !GET_PLAYERBOT_AI(player)` and explicitly excludes selfbots. A core `IsBot()` check is a narrower condition. The V1 intentionally offers no AI control/reward/economy integration; selfbot behavior remains a documented compatibility test. |
| [Playerbots.h](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Script/Playerbots.h#L31) | `GET_PLAYERBOT_AI` maps to `sPlayerbotsMgr.GetPlayerbotAI`. Available if a future project genuinely needs direct bot integration; neither proposed V1 needs to take on that include/link dependency. |
| [PlayerbotCommandScript.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Script/PlayerbotCommandScript.cpp#L22) | Pinned working module example uses `ChatCommandTable`, `SEC_PLAYER`, `Console::No`, nested commands, and `ChatHandler*` handlers. This is the command-registration compatibility reference. |

## Evidence limitations and next action

These are direct source findings, not proof of compilation, schema correctness, world startup, or gameplay. No dependency versions were changed. Public downloaded headers remain ignored in the lane's `.forge-local/pinned-source`; only this design note is intended for the lane commit.

Next action: Director selects/claims the launch concept after the independent official-gate smoke passes. Small Council should first prove module discovery, hook signatures, config, and harmless startup on the exact pinned target, then add the complete narrative/state/persistence loop. A failed official gate must be resolved in the product or referred to Reviewer with evidence; builders must not change the judge.
