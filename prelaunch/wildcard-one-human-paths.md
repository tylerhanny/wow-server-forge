# Wildcard shortlist — complete one-human paths

```text
STATE=PRELAUNCH_DESIGN_ADDENDUM
TOURNAMENT=ad264556c8fd688ea462ead3ab7ece753f142819; five concepts preserved
AUTHORITY_READ=ONE_HUMAN_PLAYABILITY.md at origin/main 7317977
IMPLEMENTATION_APPROVED=NO
ONE_HUMAN_REVIEW=PENDING_INDEPENDENT_DISPOSITION
SPRINT_LAUNCHED=NO
OWNER_RESUME=Explicit instruction received; prelaunch work only
RULE=One human completes every custom decision/mechanic; ordinary bots or owned NPC helpers may provide combat support
```

This addendum supersedes any tournament wording that suggests a second human is needed, notably Holdfast's simultaneous two-lane showcase. It adds concrete solo and helper boundaries to the three shortlisted concepts. It is a design reassessment, not evidence that any candidate has been implemented, balanced, played, or passed the independent judge.

The complete supported experience must be available to Tyler alone at one client/account. No bot is required to open gossip, choose a difficulty, spend a resource, operate an object/item, stand on a pressure plate, reach an exact coordinate, stop damage at a health threshold, or execute synchronized/custom raid choreography. All custom choices belong to the one human. Existing bot combat/follow/ordinary supported commands are optional support, not an unpublished implementation of the mechanics.

## Comparison under the new floor

| Concept | Complete primary one-human path | Zero-Playerbots path | Custom decisions/mechanics | Remaining highest risk |
|---|---|---|---|---|
| **Stormwright** | Human pilot does all storm/rod decisions while normal controllable bots supply ordinary tank/heal/DPS if desired. | A complete Solo Pilot combat profile: same storm/rod loop, one pursuing add cap, survivable ordinary damage, and human-operated Ground also restores pilot health at the cost of a discharge window. | Start, difficulty, bait/lock/dodge, rod choice, Ground/Discharge, retry/exit. | Proving readable stock-client telegraphs and tuning solo incoming damage/recovery without a required tank/healer. |
| **Holdfast** | One captain defends ONE central beacon, handles all repair/rest/extract choices, and directs their ordinary character combat; bots may fight normally. | Solo scaling, short converging lanes, serialized sapper arming, and safe intermission rest remove hidden second-defender/healer requirements. | Start, difficulty, target priorities, repair, party rest, continue/extract, retry/exit. | Bounded solo enemy pressure and ensuring persistent beacon integrity cannot evade-heal or receive normal healing. |
| **Warband Arena** | One captain makes every draft/repair/promotion/formation choice and fights beside module-owned AI allies. | This is the default design. Playerbots is not needed for the squad or any step. | Every menu/economy/formation decision, captain combat, next bout, retry/exit. | Four compact allied roles, healer target/faction correctness, and preserving the intended casualty economy across bouts. |

All three retain their defining mechanics. This is not approval to implement three projects. Final Director/Reviewer floors and the author's choice remain required, followed by formal launch.

## Stormwright — one pilot controls the entire storm

### Human and helper responsibilities

The enrolling human is the sole pilot and sole custom decision maker. That character baits the tracking marker, steps away after lock, chooses a charged rod, chooses Ground or Discharge, and handles the encounter's ordinary movement/combat. Rod interactions are sequential; no two controls ever need simultaneous activation.

Normal controllable bots, when used, only attack the boss/adds, tank, heal, and follow through existing behavior. No precise tank coordinate, bespoke stay location, bot-operated rod, mark transfer, or synchronized action is required. The three rods are within a compact arena around the boss; bot location never determines whether a rod charges or whether a discharge opens vulnerability. Misses consume the shared ward; there is no special raid mechanic that requires bots to recognize and dodge a marked floor spot. Bots can contribute ordinary damage during the vulnerability interval without being told to stop or start at a threshold; outside-window damage reduction is owned by the boss AI.

### Complete no-bots combat profile

When the start roster contains only the pilot, use **Solo Pilot** parameters rather than pretending five-person damage budgets work for one character. The core rules remain: track → lock → catch lightning in a rod → choose Ground or Discharge → manage cooling rods → recover or exploit vulnerability. Successful discharge remains a substantial, explicit source of boss damage, so a character occupied with movement can still finish instead of needing a second player to supply continuous DPS.

- At most **one pursuing add** is active. A surviving add blocks another add spawn; enemy count cannot accumulate into an unintended group requirement.
- Ordinary boss/add damage is deliberately budgeted for one character moving and using controls, without assuming any class has a heal or can tank indefinitely. The boss cannot require a separate character to pin it at an exact location while the pilot moves.
- **Ground restores one missing ward point and a bounded fraction of the living pilot's maximum health**, clamped to maximum health, while consuming the rod charge and foregoing its damage window. Ground remains available at full ward if the pilot is injured. This makes sustained solo survival an explicit human resource decision instead of a hidden healer requirement.
- Ground does not resurrect a dead pilot, trigger outside an active owned run, heal bystanders, or provide a reusable free heal after leaving. Pilot death is a clean failed attempt. All recipients/state/range are revalidated before spending charge or restoring health.
- Solo keeps the same rod cooldown, required repositioning, capture timing, ward-failure condition, pursuing-add role, and hard encounter end. Combat numbers may be lower; the environmental problem is not removed.

The precise damage/health/heal values are a required balance output, not figures falsely presented as tested. A convincing Solo Pilot validation must show that a correctly executed route plus deliberate Ground decisions has a sustainable health budget for a level-80 character without healing abilities, and that offense-versus-recovery still costs time/opportunity. If that cannot be achieved without erasing the rod choices or using an invulnerable hidden helper, reduce ordinary combat pressure or reject this implementation path.

### Difficulty and participant scaling

V1 targets level-80 characters to avoid a broad level-scaling framework. At start, capture the alive, eligible, nearby roster and its size, including ordinary bot characters; select solo parameters for one and party combat parameters for two through five. Freeze those parameters for the attempt. Late arrivals, bot relogs, group edits or departures cannot silently recalculate a live boss into an easier difficulty. Loss of support is the pilot's choice to continue or abort; no helper disappearance leaves a mandatory special mechanic unassigned.

Party size changes boss/ordinary-add combat health, damage and bounded add pressure. It does **not** multiply pilot-only interactions, require more rods at once, or shorten the human's route below a feasible solo interaction budget. There is one pilot in every profile. Normal plus tighter presets change clearly advertised timing/recovery margins within a one-human feasible envelope. No special mode may require a second operator.

### Whole-loop path at one client

| Stage | Exact human path; helper dependency |
|---|---|
| Access/configuration | Install the future complete module/config/data once in the eventual authorized environment; the delivered world data places a public registrar. Gameplay uses ordinary player permissions and documented travel/location, not GM spawning or another account. Enablement/admin limits are config; preset selection is the human's menu. No live installation is part of this forge task. |
| Start | Travel to registrar, optionally assemble ordinary controllable bots through their existing supported controls, read concise rules, select preset, and start. With no bots, the same registrar starts the complete Solo Pilot profile. A busy arena reports its state and allows a later attempt. |
| Objective | Defeat the armored boss before ward failure/time cap; boss/adds/rods and their current states are visible. Helpers are not asked to understand this text. |
| Mechanics | Human catches marks in rods and chooses every Ground/Discharge. Bots, if present, only perform ordinary combat. Solo uses the same custom sequence and human-selected recovery. |
| Success | Any legitimate killing blow on the owned boss can finish the run; no human last-hit requirement. Controller records one completed result, reports it to the pilot, cleans actors, and releases the arena. |
| Failure | Zero ward, pilot death/leave/logout/map departure, full wipe, time cap or irrecoverable actor failure ends the run once, cleans actors and leaves no unresolved charge/credit. No second person must release a lock or approve abort. |
| Outcome | Report preset, fixed starting roster size, success/time/misses. If records are retained, label them assisted encounter records; outside help is not claimed to be prevented or competitively fair. No loot-economy or account-power dependency. |
| Retry | Living pilot returns to/reuses the registrar; a dead pilot uses ordinary WoW release/recovery, then returns. Registrar is reusable without a GM, second client or manual database reset. A fresh attempt starts with full encounter state. |
| Exit | Pilot may cancel through the documented player action or leave the event bounds. Owned actors are cleaned up; normal travel/gameplay resumes. Logout and map change are also terminal cleanup paths. |

### Exact-pin support and later checks

Owned AI, targeted damage reduction, health/ward state, GUID ownership, normal combat and sequential gossip all have pinned source support. `Unit::ModifyHealth(int32)` at `Unit.h:1128` supplies a bounded direct health-change API for the explicit Ground mechanic; it must be guarded to the living pilot in the owned active event, not treated as a general healing command. The visual design continues to prefer direct `SpellVisualKit` packets. Spell 62186 remains unapproved; no caster aura or Thorim trigger is needed to decide charge state.

Later validation must separately cover Solo Pilot with no bots; one human with a normal tank/heal/DPS bot group; losing a bot mid-run; no exact bot location assumptions; rod interaction while ordinary combat continues; solo recovery with full ward; no healing after abort; repeated success/failure/retry; and client readability. These are requirements and future manual checks, not completed gameplay evidence.

## Holdfast — one central objective, one human route

### Human and helper responsibilities

There is **one central beacon**, not two remote objectives. The two enemy approach lanes converge on it within a compact defense area. The captain performs every start/preset/repair/rest/continue/extract choice. During an assault, the captain fights and prioritizes targets using ordinary class abilities. Bots may provide normal fighting/healing support; they are not assigned a custom defense point or expected to infer which lane matters.

All sapper arming windows are serialized: **at most one armed sapper countdown exists at a time, in every participant profile**. A second sapper may be visible approaching, but cannot begin a simultaneous countdown that requires another human to solve. Lane geometry, travel time, arming duration and sapper health must allow the sole captain to address each threat in sequence. Higher difficulty can increase ordinary combat pressure and narrow margins only within that one-person route budget.

This corrects the earlier showcase wording. The memorable scene is now one captain moving between two approaching threats around a single nearly broken beacon, with the next sapper's danger staged after the first. There is never a need for a second human to operate another switch or for bots to choose the correct remote objective.

### Solo scaling and recovery

Freeze the starting eligible level-80 roster, including bots, and scale enemy health/counts to one through five combatants. Use a small explicit solo wave table: all three roles and all eight assaults still appear, but simultaneous ordinary attackers are capped at two for the initial solo V1; additional enemies arrive as bounded reinforcements rather than all at once. One armed sapper remains the global limit. Solo retains meaningful target/repair/extraction choices rather than replacing the event with a tutorial that never threatens the beacon.

Between assaults, after all owned enemies are gone, the human can choose **Rally** once from the same checkpoint interface to restore living roster health/mana. This eliminates an implicit healer/consumable requirement for a no-bots character. Rally never repairs the beacon, resurrects dead characters, works during an assault, or affects bystanders. Beacon repair still costs unbanked extraction score and is a separate human choice. The module's defining attrition resource remains objective integrity and potential payout, not whether the player's class has a heal.

The checkpoint provides enough time for one person to read and choose sequentially; a clearly documented timeout extracts the current completed result instead of silently beginning another wave while a menu is open. Start/continue/extract decisions never require party votes or bot gossip. Difficulty changes ordinary assault pressure, not the number of simultaneous custom operators.

### Whole-loop path at one client

| Stage | Exact human path; helper dependency |
|---|---|
| Access/configuration | Public delivered registrar at the authored site; ordinary player permissions. Install/admin config once, then choose gameplay preset from the captain's menu. No GM-triggered wave setup. |
| Start | Human optionally brings normally controlled bots, selects preset, confirms roster, begins. No bots automatically uses the complete solo wave table. |
| Objective | Preserve central beacon integrity through assaults, then extract an achieved result. Physical beacon health and actual attackers show the stakes. |
| Mechanics | Human directs ordinary combat, handles serialized sapper priorities, and alone chooses Rally/repair/continue/extract at checkpoints. Bots only fight/heal/follow; normal target-assist controls are sufficient if the human wants to focus one target. |
| Success | Clear an assault and extract, or clear final assault for full completion. Human extraction commits one result and cleans the event. No specific participant must land a final blow. |
| Failure | Beacon destruction, captain death/absence/abandonment, relevant terminal wipe, bound/time violation or unrecoverable spawn error ends the run and its unbanked result. No second player is needed to unlock the site. |
| Outcome | Show extracted score, repaired amount, cleared wave and fixed starting roster category as assisted encounter records. No promised fair ranking/economic payout. |
| Retry | Return to the public registrar after normal death recovery if necessary and start a fresh, full-integrity run. Neither a bot nor GM resets it. |
| Exit | Captain cancels or leaves; logout/map change clean owned actors and release the site. Existing characters/pets/bots remain their normal game entities. |

### Exact-pin support and later checks

Existing summon tracking, owned `DamageTaken`/`HealReceived`, public health/power APIs, group snapshots and gossip support these boundaries. Beacon healing rejection and persistent integrity must survive evade/reset paths; only paid captain repair restores the owned objective. Wave generation must assert the solo live-enemy cap and the single armed-sapper invariant for every seed and preset.

Later validation must show all eight assaults and an extraction with **one human and no bots**, plus one human with normal bot support. The test must never quietly substitute a second target caller/defender. Record lane travel/arming budgets, prove Rally is unavailable in combat/after abort and cannot repair the beacon, and verify cleanup on death/relog. If the solo wave table cannot preserve pressure without requiring simultaneous defenders, revise the wave/timing data instead of claiming bots will solve it.

## Warband Arena — one captain, owned scripted allies

### Human and helper responsibilities

This design already uses a single human captain and **module-owned creatures**, not an extra player or a Playerbots command wrapper. The human sequentially reads the opposing lineup, buys/replaces/promotes/repairs allies, assigns each owned ally to a formation pad, and starts the bout. Once fighting begins, the human uses ordinary class combat while the four small ally AIs handle their normal attack/tank/ranged/healing roles.

No ally makes a purchase, opens gossip, activates an object, picks a formation, or advances the encounter. Formation selection is a human command to the owned creature; the script performs and verifies the movement. This does not ask an ordinary bot to achieve an exact custom coordinate. If a formation move cannot complete, the setup must report it and offer reset/cancel instead of requiring another client or a GM to nudge an actor.

### No-bots case and scaling

**Zero participating Playerbots is the complete default path.** The module creates the chosen temporary squad through its own templates/AI and never needs a second account, bot ownership login, Playerbot AI API or custom bot strategy. The official build still includes the exact pinned Playerbots module; zero means no bot participants, not an unpinned validation target. Nearby ordinary bots or people are outside assistance under the explicitly assisted-record semantics, not required roster members or operators.

V1 is a level-80 human captain, three owned squad slots, four archetypes, six-point starting budget, six bouts, and a bounded opponent table. It does not scale from untracked nearby player/bot counts. Presets change advertised budget/opponent parameters while keeping a complete one-captain route; no preset assumes another human must keep a medic alive or command a second squad.

Between bouts, the captain can restore their own basic health/mana through the marshal's rest option, without class-specific healing/consumables. Owned ally wounds remain part of the draft economy: their out-of-bout healing is blocked except for paid controller repair; the medic cannot erase all injuries while the human deliberates. In-bout healing is an allowed tactical benefit of the captain's class or drafted medic. Casualties and replacing/repairing/promoting allies still consume the in-run purse. Thus solo access does not remove the core roster/economy choices.

### Whole-loop path at one client

| Stage | Exact human path; helper dependency |
|---|---|
| Access/configuration | Public delivered arena marshal, normal player permissions, shipped preset/config/data. No GM-spawned army. |
| Start | Human enrolls alone, selects preset, gets the standard in-run purse, sees first opposing lineup. No bot setup or additional account exists in this path. |
| Objective | Win six bouts while managing drafted roles, wounds, replacements and budget. Opponents and allies physically stage in the arena. |
| Mechanics | Human makes every purchase/repair/promotion/formation choice at their own sequential interface, then starts combat and fights. Owned AI only executes its assigned combat role and movement. |
| Success | Defeat the final owned lineup; controller records one completed run and releases all temporary actors. Success does not require the human's killing blow. |
| Failure | Captain death/abandonment, total relevant defeat, time/bounds violation or unrecoverable setup error ends the run with a clear result and cleanup. A lost ally alone is a casualty/economy event, not a second-human rescue task. |
| Outcome | Report bouts cleared, survivors, purchases/repairs and preset as assisted run records. All squad power/currency belongs to the attempt; no external economy, persistent pet ownership or second-player reward collection. |
| Retry | Human returns after ordinary death recovery if needed; marshal immediately offers a fresh standard-budget run. No owner of an NPC/bot must log in to release it. |
| Exit | Human cancel/leave/logout/map change ends the attempt and despawns only its squad/opponents. No summoned ally follows the player out indefinitely. |

### Exact-pin support and later checks

Scripted creature AI, controlled summons, GUID state, ordinary movement, health/power updates, healing callbacks and gossip exist at the exact target. The medic selects only the captain and controller-owned squad GUIDs, not a generic scan of every nearby friendly player/NPC. A strict combat/setup phase boundary ensures in-bout healing and paid between-bout repair cannot accidentally collapse into free permanent squad healing.

Later validation must run a complete six-bout sequence with no Playerbots participating, covering each archetype, human formation/repair choices, squad casualty/replacement, captain rest, final outcome, retry and abandonment cleanup. Solo class balance and four reliable ally roles remain a larger closure risk than Stormwright/Holdfast; the one-human rule does not magically resolve that engineering workload.

## Shared exact-source basis and acceptance boundaries

The detailed pinned links remain in the tournament note. Especially relevant here:

- AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`: [Unit.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.h#L1125) exposes health mutation; [UnitAI.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/CoreAI/UnitAI.h#L371) exposes damage/healing callbacks; [Group.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Groups/Group.h#L238) supports roster inspection; [CreatureScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/CreatureScript.h#L33) supports human gossip/owned AI.
- Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`: [AttackAction.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Actions/AttackAction.cpp#L31) implements `AttackMyTargetAction` from the master's selected target and uses normal attack logic. [GrindTargetValue.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Value/GrindTargetValue.cpp#L33) considers master/group/attackers. These support ordinary combat assistance only. They are not evidence of any custom mechanic understanding or completed gameplay.

No core/Playerbots source change, newer dependency, client patch, external API, exposed DB, private endpoint or additional human is proposed. No actual live/in-game validation is claimed. Deterministic tests and the unchanged official compile/install/startup/reference gates remain mandatory; Tyler's later one-client gameplay test remains separately pending.

The eventual chosen candidate README and final handoff must each contain the exact section title **One-Human Playability**, including supported solo/normal-bot configurations, bot requirements if any, human-only custom actions, scaling/limits, and complete one-client manual smoke steps. The independent Reviewer must record `ONE_HUMAN_REVIEW=PASS / FAIL / PENDING` with evaluated path, evidence and remaining assumptions. This builder addendum does not assign that disposition. Actual client/bot feel remains `PENDING LIVE/IN-GAME VALIDATION` even after source/disposable checks pass.

For final selection, Reviewer/Director should evaluate **these corrected whole-loop paths**, not assume the earlier two-lane screenshot implies two human operators. My preference remains Stormwright if its readable stock feedback and complete Solo Pilot profile pass both floors. Holdfast is a credible one-human fallback. Warband passes the operator-count design test directly but retains the largest AI/balance surface. This addendum does not choose a final implementation or start the sprint.
