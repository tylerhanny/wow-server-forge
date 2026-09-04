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
window increase that qualifying kill's XP by a small step, capped at 10%. Death,
logout, changing maps, stopping, or chain expiry resets the streak. No rewards
other than the explicitly configured XP adjustment.

The default rules are fixed in the One-Human Playability section below: the first
eligible kill starts at zero bonus; each subsequent eligible kill adds two
percentage points, capped at 10% on the sixth kill.
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

## One-Human Playability

Proposal reassessment: the primary loop is designed to be complete with one human
playing solo. One human with ordinary pinned Playerbots is an optional supported
path. No second human, second client, or second human account is required.
This is a source-grounded design assessment, not completed gameplay validation.
Independent Reviewer quality/one-human disposition: **PENDING**.

### Access, configuration, and complete loop

- Access: one normal player character can use `.rhythm start`, `.rhythm status`,
  and `.rhythm stop` through `SEC_PLAYER`, with console use disabled. No GM,
  party leader, NPC, second player, bot command, client addon, or external tool is
  needed. The player sees English system chat plus the normal client XP display.
- Operator setup: install the isolated module and its config in the exact pinned
  disposable server. Proposed canonical settings are `HuntRhythm.Enable = 1`,
  `HuntRhythm.WindowSeconds = 60`, `HuntRhythm.StepPercent = 2`, and
  `HuntRhythm.MaxBonusPercent = 10`. Bound the window to 15–300 seconds, step to
  1–5%, and cap to 1–20%; clamp out-of-range numeric config with a warning.
  Every player starts opted out. No account-specific configuration is required.
- Start: an eligible character types `.rhythm start` once. The response explains
  the window, cap, zero current streak, and `.rhythm stop`. Repeating start while
  opted in reports status and does not extend an active deadline.
- Objective and player decisions: chain ordinary XP-bearing outdoor kills while
  balancing route distance, health/mana recovery, and pull safety. The human
  chooses the route and targets and performs their normal class combat. Reaching
  six consecutive qualifying kills reaches the default 10% plateau; sustaining
  it continues the repeatable loop. There is no hidden final encounter.
- Scoring: the first qualifying kill grants no added XP. Qualifying kills two
  through six receive 2%, 4%, 6%, 8%, and 10% added to the hook's base amount;
  later qualifying kills remain at 10%. Use integer floor arithmetic on the
  bonus with wide intermediates and no unsigned overflow. Very small XP awards
  can round a fractional bonus down to zero.
- Timing: each qualifying kill refreshes the window. An elapsed interval of
  **60 seconds or more** at the default setting breaks the chain before the
  next qualifying kill, which becomes kill one at 0%. Status evaluates expiry
  too. Ineligible events do not advance or refresh it.
- Feedback and success: show personal notices at streak start and each increase
  through the cap, including the bonus percentage and added base XP. At cap,
  ordinary XP awards continue with the cap but no per-kill chat spam. Status
  reports opt-in, current eligibility, streak, remaining time, and the bonus
  scheduled for the next eligible kill. Reaching and receiving the capped
  award completes one full success cycle; it requires no other human action.
- Failure: death, map changes, or timeout clears the streak. Earned XP stays
  earned; there is no additional penalty, reward rollback, or locked state.
  These resets leave the session opted in so the next eligible kill can retry.
- Retry: after recovery or route adjustment, kill another eligible creature.
  This starts a new zero-bonus chain without another participant or reset vote.
- Exit: `.rhythm stop` immediately removes opt-in and streak; subsequent kills
  receive normal core awards. Logout, server restart, and config reload also
  clear session opt-in and streak. The complete loop has no persistent cleanup
  dependency, claim screen, shared reward chest, or unclaimed reward state.

### Eligibility, scaling, solo path, and bots

An eligible award requires module enabled, explicit session opt-in, a living
character below the core's effective level cap (including trial-account cap),
XP gain permitted by the core's player flags, `XPSOURCE_KILL`, and positive base
XP. Both character and victim must be in the same outdoor map; exclude dungeons,
raids, battlegrounds, and arenas. The victim must be a hostile XP-bearing
creature, not a player, pet, totem, temporary summon, player-owned/charmed unit,
critter, elite, or world boss. Core normal loot/kill credit and XP eligibility
remain mandatory. No extra XP is generated for a zero/rejected award. Quest,
exploration, and battleground rewards do not qualify.

The primary path supports every ordinary leveling class from level 1 up to the
effective cap minus one. It does not require a pet, heal, interrupt, tank,
particular profession, movement ability, or multi-target damage. Level-capped
and XP-locked play are explicitly outside the leveling feature; commands must
explain ineligibility. The later demonstration should use an ordinary level
10–30 character so fractional-XP rounding does not hide the feedback.

No enemies are spawned or scaled. Their health, damage, number, and core XP stay
under normal world rules except the documented eligible XP bonus. Solo players
can pull one normal non-elite at a time. The module has no group-size or
class-composition requirement, escalating wave count, simultaneous objectives,
or population-based difficulty. A less effective route may drop the chain; it
never prevents retry or access. The same default timer and percentage cap apply
solo and grouped. The operator can lengthen the bounded timer if later playtests
show the default unfairly favors particular classes or outdoor densities.

With optional bots, the human still opts in and chooses the route/ordinary
combat target. Bots only perform their existing combat and support roles under
normal settings. They do not need to read the module's chat, issue `.rhythm`
commands, solve mechanics, select custom menus, coordinate positions, stop
damage on special targets, or obey a newly added strategy. The player's eligible
shared kill-XP awards advance only their own opted-in streak; bots do not
automatically enroll and another character's opt-in cannot boost the human.
Normal group share, level disparity, gray-target penalties, and credit distance
still apply. Bots can make kills faster but do not change the cap or create a
different completion requirement. With no bots available, the solo loop above
is the entire feature and requires no substitute participant.

The pinned [Playerbots README](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/README.md)
describes bot parties and leveling. Its existing
[AttackAction.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Actions/AttackAction.cpp)
contains normal target attack and master's-target attack actions. Combined with
the inspected core's per-player shared-XP path, this supports the limited bot
role proposed here; it does not prove bot pathfinding, group credit, or combat
feel in an actual play session.

Pet and bonus interactions remain in scope: the XP hook is before core pet XP,
rested XP, and RAF processing. The proposal accepts the core deriving those
normal rewards from the adjusted base rather than independently granting or
recalculating them. Thus the feature's percentage is a base kill-XP percentage,
not a promised separate percentage of every final XP component. Document and
manually check this behavior. No second account is required to use or demonstrate
the primary loop; RAF compatibility can be source-reviewed and recorded as
untested if it cannot be exercised under the one-account test constraint.

### Later manual checks — one human only

All steps below are **PENDING LIVE/IN-GAME VALIDATION**. They are planned
expectations, not claims of performed testing. Use one standard 3.3.5a client
session and one normal leveling character; no simultaneous second client or
human-controlled account is part of any step.

1. With the canonical config installed in a disposable test server, enter an
   ordinary outdoor area with several normal XP-bearing hostile creatures.
   Remain solo, with no bots present. Type `.rhythm status`; confirm opted out.
2. Type `.rhythm start`; confirm access without GM rights and visible rules.
   Kill one suitable creature using ordinary combat, then type `.rhythm status`.
   Expect streak one, a live window, and 2% scheduled for the next eligible kill.
3. Kill five more eligible creatures, each within 60 seconds of the previous
   one. Expect applied bonuses 2/4/6/8/10%, native XP feedback, and a cap notice
   on kill six. Kill one more within the window: expect 10%, with no additional
   cap chat spam. This is the full solo success loop.
4. Wait at least 60 seconds without a qualifying kill, then query status and
   kill another eligible creature. Expect expired/zero streak followed by a
   fresh streak-one 0% award. Retry needs no menu, other player, or vote.
5. During another chain, allow the character to die in ordinary combat, recover
   through the normal client flow, and make a new qualifying kill. Expect a
   fresh chain and no removal of XP earned before death.
6. Type `.rhythm stop`; make another eligible kill and confirm no Rhythm bonus.
   Start again, change maps, and verify the chain resets. Log out and back into
   the same account/client: expect opted out. These complete voluntary exit and
   clean retry checks without involving another human.
7. Optionally repeat steps 2–6 with an already available, normally configured
   pinned bot party using only existing grouping/combat controls. Only the human
   enters Rhythm commands; confirm their ordinary eligible shared-XP awards
   build the streak while the bots fight normally. Remove bots and repeat a solo
   chain to confirm there is no dependency on them.
8. On the same character, check that ordinary quest/exploration XP does not
   advance or refresh the chain, XP locks/cap reject participation clearly, and
   excluded creatures/maps do not advance it. For a pet class and rested
   character, inspect the documented core-derived XP behavior; report actual
   limitations rather than assuming parity with a non-pet, non-rested character.

Remaining assumptions: class/route pacing, system-chat clarity, pet/rested award
feel, ordinary bot pathfinding and group-credit behavior are pending the later
one-human playtest. The module cannot promise all routes maintain a chain, and
the timer must be adjusted if evidence shows the stock setting creates a poor
solo experience. The feature's limited novelty is unchanged: it is a practical
leveling modifier, not the Wildcard flagship.

The eventual project README and handoff must both retain an exact
`One-Human Playability` heading and carry the independent Reviewer's explicit
disposition before any harvest classification. Proposal approval cannot replace
review of the implementation, official gate evidence, or the pending gameplay
checks above. No implementation is authorized before the recorded forge launch.
