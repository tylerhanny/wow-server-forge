# Wildcard creative-quality pass 1

```text
STATE=PRELAUNCH_CONCEPT_COMPARISON
AUTHORITY_READ=origin/main at 10ff406; WILDCARD_AUTEUR.md plus updated AGENTS.md, prompts/WILDCARD.md, BACKLOG.md
IMPLEMENTATION_APPROVED=NO
SPRINT_LAUNCHED=NO
CONCEPT_COUNT=5 mechanically distinct concepts
SHORTLIST=STORMWRIGHT; HOLDFAST; WARBAND_ARENA
WILDCARD_PREFERENCE=STORMWRIGHT, pending Director and Reviewer floors; no final implementation selection yet
```

This is a fresh mechanics-first pass. The Small Council is not a candidate and must not be revived by this note. None of the concepts below has been implemented, compiled, played, or accepted by the official gate. Source findings establish available APIs, not encounter balance or operational readiness.

The design objective is an activity a player would voluntarily repeat after understanding all its text. Each option still works as a game if all narrative is removed. I discarded ambient lore systems, score-only passive event tracking, another bundle of bot command shortcuts, and a generic sequence of kill quotas before choosing this set. A fresh-context scout independently contributed Stormwright and Warband Arena to challenge my initial three options. This completes the bounded five-option pass; further breadth is not needed if a shortlisted option passes the independent floors.

## Five-way tournament result

| Option | Distinct mechanic | Repeat value | Visible showcase | V1 finish confidence | Shortlist |
|---|---|---|---|---|---|
| **Stormwright** | Turn a boss's delayed lightning into stored environmental charge; choose protection or a damage window. | Movement mastery, charge allocation, routing pursuing adds, three bounded difficulty presets. | Bait lightning into a physical rod, dodge its locked impact, discharge through adds into a shielded boss. | Medium-high after a bounded stock-visual/site feasibility check; smallest actor/AI surface of the strongest showcases. | **1 — creative preference** |
| **Holdfast** | Preserve a vulnerable objective across waves; repair costs potential extraction score. | Interception priorities, changing assault lanes, risk versus safe extraction, run records. | Save a nearly destroyed beacon from two-lane sappers, surrender score to repair, then choose another assault. | Medium-high; no broad world/path framework. | **2 — strongest fallback** |
| **Warband Arena** | Draft and position a small fighting squad, then fight personally alongside it while carrying casualties/economy between bouts. | Roster/class synergies, opponent adaptation, preserving veterans versus replacing them. | Counter a visible enemy lineup with a changed formation and protect the drafted medic during the actual fight. | Medium; four short AIs and class/roster balance need a strict cap. | **3 — deepest strategic alternative** |
| Counterweight Run | Cargo is both delivery reward and repair resource on a moving escort. | Cargo/speed/survival tradeoffs and shuffled route ambushes. | Sacrifice part of the visible manifest to repair while ambushers close on the next road segment. | Medium; route/pathing/follow behavior is the primary risk. | No: less closure confidence than Holdfast. |
| Wanted Alive | Killable targets must be controlled and captured within a real window rather than burst down. | Timing, restraint, tool conservation, three escape/defense behaviors. | Stop a wounded runner from crossing its escape line and land the last available capture attempt. | Medium; bot/DoT overshoot threatens the feel of the core mechanic. | No: unusually strong objective but greater product-feel risk. |

This is differentiation by gameplay, not a claim that no other WoW/private-server implementation has ever explored these ideas. No exhaustive module-market novelty search was conducted.

## Detailed comparison of the initial three options

| Quality dimension | Holdfast | Counterweight Run | Wanted Alive |
|---|---|---|---|
| Primary player action | Defend a vulnerable objective, intercept different attack lanes, ration repair, decide when to extract. | Keep a convoy moving, split attention between escort and ambushers, sacrifice cargo to survive. | Subdue a dangerous target without killing it, prevent escape, commit a limited capture tool at the right moment. |
| Decisions that change the outcome | Focus attackers versus peel for the objective; spend unbanked score on repairs versus retain payout; bank now versus take an advertised harder assault. | Preserve valuable cargo versus consume it for repair; escort close versus move ahead to intercept; accept a heavier load versus retain mobility. | Continue damage versus stop before lethal; save a control charge versus interrupt an escape; attempt a risky low-health capture versus reset positioning. |
| Replay driver | Escalation, three attack roles, changing lane compositions, reproducible daily challenge seed, extracted-score records by party size. | Cargo-risk choices plus shuffled ambush locations/compositions; improve delivery value and time with different groups. | Three distinct escape/defense behaviors, scarce tools, capture streaks, and improving live-capture grade. |
| Server impact | A repeatable 10–15 minute group PvE activity usable by a human with ordinary bot companions; the party must protect something other than itself. | Roads become tactical group content, with an objective moving through the world instead of a stationary quest target. | Changes the combat objective from maximum damage to control and restraint; creates a reason to use slows, stuns, positioning, and pet/bot discipline. |
| Differentiation | Objective integrity persists across waves and can only be repaired by surrendering potential extraction score. Surviving combat is insufficient if the objective falls. | The thing being protected is also the run's consumable survival resource. A damaged successful delivery can be worth less than a cautious smaller one. | Targets are worth more alive, can escape, and are not made conveniently unkillable. The usual burst-down solution can fail the mission. |
| Worth installing/testing | Strongest of this set: a compact alternative to another dungeon run with clear player failure and improvement. | Strong if route and escort movement prove reliable; weaker if it degenerates into waiting beside a slow NPC. | Strong as a focused control challenge, but bot overshoot could make it frustrating rather than tactical. |
| Credible full-gate completion | **Medium-high** relative confidence: one bounded site, module-owned actors, ordinary combat and local AI state. | **Medium**: pathing/terrain/escort recovery add material integration risk. | **Medium**: capture timing, crowd control, and autonomous companions need an early gameplay feasibility checkpoint. |
| Disposition after five-way comparison | **Shortlisted; strongest fallback to Stormwright.** | Defer: moving-route integration costs more for the expected V1 payoff. | Defer: capture with autonomous companions carries higher feel risk. |

These are not three difficulty variants of one mechanic. Holdfast is stationary defense and extraction; Counterweight is moving escort/resource conservation; Wanted Alive is nonlethal target control. All use normal class combat, but their win conditions and best player decisions differ.

## Option A — Holdfast

| Required field | Concrete proposal |
|---|---|
| Player fantasy | Be the last defenders of an extraction beacon, deciding how much danger the party can still afford. |
| Repeatable loop | Defend an assault, inspect the next one, spend unbanked score to repair or keep it, then extract or continue. |
| Decisions/challenge | Peel versus damage; intercept the threatened lane; repair versus payout; continue versus bank. |
| Short session | Self-service registrar starts an approximately 10–15 minute attempt with a clear success/failure/extraction endpoint. |
| Multiple sessions | Improve coordination and extraction records, change party composition, and adapt to reproducible daily assault compositions. |
| Visible changes | Physical beacon health bar, two directions of attacking creatures, threatening sappers, visible damage/repair, and complete cleanup. |
| Differentiation | The objective's persistent integrity and costly repair make winning a fight different from protecting the run's value. |
| Strongest demo | Two sappers reach opposite sides of a nearly broken beacon; the group splits, saves it, pays to repair, and knowingly risks the next wave. |
| Complete V1 | One site, three roles, eight assaults, frozen 1–5 roster scaling, repair/extract flow, records, bounded lifecycle and validated install data. |
| Exact-pin risks | Owned-AI targeting/evade, summon failures, healing prevention, fixed roster/bots, and map/site/reference validation. |
| Finish confidence | Medium-high relative estimate; 8–12 implementation hours plus independent build/install/startup/review buffer. |

Records are explicitly **open-world assisted encounter records grouped by starting roster size**. Outsiders can heal/buff participants or otherwise help. V1 does not claim fair competitive rankings, exclusive-party enforcement, or anti-assistance detection, and has no economic payout. This is the scope correction from independent Reviewer feedback, not a future anti-cheat promise.

### Repeatable play loop

One player or a party of up to five enters a clearly marked defense site through its registrar. The group locks its starting roster and begins with a beacon at full integrity. Attackers arrive from visible approach lanes. Runners rush the beacon, brutes occupy defenders, and sappers must be intercepted before their short, clearly telegraphed detonation near the objective. These roles use module-owned creatures; ordinary world creatures and quests are not repurposed.

After each completed assault, the group has a brief safe checkpoint. The captain sees the next assault's composition and reward, then chooses to extract or continue. Repairs consume unbanked extraction score, so a badly defended wave has a lasting cost even when nobody dies. The objective does not accept ordinary healing spells. The pressure is protecting both the party and its future payout, not merely killing a larger pile of enemies.

Example decision: the beacon is at 35% after wave four. Repairing it to 60% costs part of the current score. The next assault advertises sappers from both lanes. A group with good crowd control may continue without repairing; a weaker group can buy safety or extract its existing result. Both choices have a coherent purpose.

Failure: beacon destroyed, whole roster dead/absent beyond a short grace period, captain abandons, encounter exceeds its hard time limit, or the group leaves the event bounds. Failure discards the unbanked run result and cleans up only that run's actors. Successful extraction records its score, highest cleared wave, and time. Personal/group-size records and cleared difficulty ranks are the V1 progression; they change through actual successful play. There is no external economy payout or gear inflation in V1.

### Smallest worthwhile complete V1

- One authored outdoor defense site, one registrar, two approach lanes, three enemy roles, and eight escalating assaults with a complete final extraction. Maximum run length: approximately 15 minutes, with bounded enemies and spawn lifetimes.
- A fixed, documented party-size scaling rule, roster locked at start, ordinary player pets/bots allowed, and records separated by party size. A solo human with four bot companions counts as five combatants.
- A reproducible daily composition seed drawn from a small reviewed set of assault packets. Composition varies; the same daily seed supports comparable encounter layouts and learning, without promising equal or unassisted competition. No procedural dungeon or world-generation framework.
- Two choices at checkpoints: repair using unbanked score, and extract/continue. No optional talent tree, random item economy, or large affix system.
- Complete success/failure/cancel/disconnect/death/map-change cleanup, concurrency limit of one run at the initial site, clear busy-state feedback, and startup validation of every module-owned template/reference.
- Module-owned world SQL for new templates and registrar placement only; a small characters table for extracted records. Idempotent install and safe module-only removal documentation. No updates to existing creature templates, paths, quests, or dungeon scripts.

The registrar/site are part of the deliverable, not an instruction for Tyler to invent a playable arena. The exact site, coordinates, display references, and any visuals must be chosen and checked against disposable pinned map/world data before an implementation is considered complete. If the site cannot be bounded without overlapping ordinary quest traffic, select another site; never remove existing spawns to make room.

### Feasibility and closure risk

Pinned APIs support owned AI, summoning, cleanup, damage/healing hooks, party snapshots, and gossip. `HealReceived` lets the beacon reject ordinary healing while explicit repair changes its health through the public API. Sapper detonation can be a bounded change to the owned beacon's integrity; it does not need a spell affecting unrelated players. The run controller should live in the owned registrar/beacon AI with GUID references, rather than a global map updated by multiple map threads.

The important engineering risks are unauthorized gossip/replay, leashes, summon failure, stale GUIDs, duplicate completion, and group mutation. Participant attribution must include pets and registered bot GUIDs. Outside assistance is allowed under the explicit record semantics above. The beacon must reject ordinary healing and must not gain a free reset through combat evade; its integrity is run state. Only the captain can repair/extract, regardless of who helps with combat.

Bot companions should perform ordinary fighting and healing; no custom AI directives are promised. The human captain makes checkpoint decisions and handles objective priorities. Natural bot participation is plausible from pinned normal attack/party target code, but it requires later in-game verification. The design must remain fun with human companions as well.

Estimate: 8–12 focused implementation hours plus real compile/fix/SQL/startup/reviewer time. High-leverage first technical slice after approval/launch: discover the module, validate templates/site, summon one owned attacker, observe damage and cleanup in a disposable context. Preserve an independent review buffer. If the three combat roles and extraction decision cannot be completed, do not label a generic wave spawner as this V1.

## Option B — Counterweight Run

| Required field | Concrete proposal |
|---|---|
| Player fantasy | Run a dangerous supply convoy and bring home as much of its load as the party can keep alive. |
| Repeatable loop | Choose load, escort through ambushes, repair/jettison/continue at checkpoints, deliver or lose the run. |
| Decisions/challenge | Heavy valuable cargo slows the convoy; repairs consume the prize; interception leaves the wagon less protected. |
| Short session | Self-service depot starts a 10–15 minute route with three checkpoint decisions and one delivery endpoint. |
| Multiple sessions | Try heavier loads, faster routes through encounters, different role allocations and changing ambush packages. |
| Visible changes | A physical transport moves through the world while actual attackers pursue it; its health/speed change with run decisions. |
| Differentiation | Cargo is a survival resource and objective value at once; the party chooses the cost of continuing. |
| Strongest demo | An ambush nearly destroys a heavily loaded convoy; the captain spends cargo to repair, sheds more for speed, and the party fights its way to delivery. |
| Complete V1 | One route/depot/transport, two attacker roles, two starting loads, three checkpoints, delivery records and full cleanup. |
| Exact-pin risks | Escort waypoint traversal, terrain/navmesh, combat pause/resume, bot follow, bounded recovery from a stuck transport. |
| Finish confidence | Medium; 10–14 implementation hours plus independent validation, with an early entire-route go/no-go. |

### Repeatable play loop

A party loads a transport at a depot and escorts it along one authored route with three checkpoints. Cargo is the score to deliver and the material used to repair the transport. A heavier manifest offers more potential delivery value and causes a slower journey, leaving the convoy exposed for longer. At a checkpoint, the captain may consume cargo for repairs, jettison some to regain speed, or keep the load and accept the next ambush with less margin.

While moving, defenders decide who stays close enough to protect the transport and who intercepts ranged/sapper threats. Ambush compositions and their eligible route segments change between runs. Repair and cargo choices use the same simple inventory of cargo units; there is no separate passive lore progression.

Failure: transport destroyed, party deserts, escort becomes unrecoverably stuck and hits a bounded timeout, or hard run limit expires. Success records cargo actually delivered and delivery time, giving a clear high-value versus fast-run tradeoff. No player loses existing items or money. The run starts from a free standard manifest, so failure never locks a player out.

### Smallest worthwhile complete V1

One depot, one short route with three checkpoints, one transport, two attacker roles, light/heavy starting manifests, repair/jettison/continue choices, and delivery records. One active convoy; 1–5 fixed participants; no world economy, multiple route network, faction territory, player PvP flags, or bot pathfinding changes. All attackers and transport are module-owned, and the route is delivered as validated module data.

Pinned `npc_escortAI` has authored waypoints, pause/resume, explicit owner GUID, endpoint/desertion controls, and waypoint callbacks. The transport can pause at checkpoints and resume when the captain makes a validated choice. Its health and speed can change on that owned creature through public APIs.

### Why it is an alternative, not my first pick

The moving objective could make roads feel substantially different and offers meaningful group positioning. However, a single bad waypoint, navmesh gap, evade behavior, or bot follow conflict can ruin a whole run. The extra map/path validation is material. A static replacement would destroy the idea rather than preserve its V1.

Estimate: 10–14 focused implementation hours plus validation/review; medium completion confidence. Go/no-go should depend early on the entire empty route completing correctly in disposable validation, including pauses, combat interruptions, owner loss, and timeout cleanup. If the route cannot be proven reliable, defer it rather than spending the deadline fighting terrain.

## Option C — Wanted Alive

| Required field | Concrete proposal |
|---|---|
| Player fantasy | Be a skilled live-capture hunter whose restraint and control matter more than raw damage. |
| Repeatable loop | Choose target, fight into a capture window, stop damage/control escape, spend a tool, then bank or take another contract. |
| Decisions/challenge | Burst versus control, conserve versus spend a charge, handle an escape instead of chasing damage numbers. |
| Short session | Self-service hunting registrar starts a three-contract expedition of approximately 8–12 minutes. |
| Multiple sessions | Master the three target behaviors, improve capture grades/tool efficiency, and change class/party tactics. |
| Visible changes | A physical target flees, exhausts or calls reinforcements; players restrain/capture it or visibly kill/lose it. |
| Differentiation | Maximum damage can lose the encounter; targets remain killable and class control tools acquire direct value. |
| Strongest demo | A low-health runner breaks toward escape; the player stops a pet, catches it with a slow, and lands the final capture charge before the boundary. |
| Complete V1 | One site, three owned target AIs, one capture action, fixed per-run tool budget, three contracts, extracted records and cleanup. |
| Exact-pin risks | Damage-over-time/bot overshoot, capture concurrency, CC interactions, movement/escape boundaries and legible timing. |
| Finish confidence | Medium; 10–14 implementation hours plus validation, conditional on a convincing first live-capture feasibility slice. |

### Repeatable play loop

A hunting party enters a bounded capture ground and chooses one of three target behaviors: a runner that attempts to reach an escape point when wounded, a bruiser whose brief exhaustion windows allow restraint, or a caller whose alarm brings reinforcements unless disrupted. The party receives a small fixed number of capture-tool charges. It must fight, position, and control the target, then commit a capture attempt inside an explicit health/window threshold. Excess damage kills the target and fails the live-capture objective; fleeing out of bounds also fails it.

The decision is whether to keep damaging, conserve a stun/slow for the escape phase, reposition the target, or risk a scarce capture charge. A target is not secretly invulnerable at one hit point. The visible threshold/window and tool rules must be generous enough to plan around. Three contracts form a short expedition, with score based on live captures, tool efficiency, and elapsed time; extracting between contracts banks the current expedition result.

Failure is understandable and recoverable: a dead/escaped target closes that contract without awarding capture credit; depleted tools force extraction; the next expedition starts with a free standard kit. Records track actual live-capture performance. No journal completion or species collection is the primary reward.

### Smallest worthwhile complete V1

One bounded hunting site, three module-owned target AIs, a standard reusable starting kit with a small per-run charge budget, one validated capture action, clear telegraphs/health requirements, three-contract expeditions, and extracted records. Use a stock-client action exposed through a short command or registrar interaction; do not depend on a client addon or invent a new client spell. No capturing existing quest mobs, permanent pet ownership, player cages, auctionable captures, full monster-taming system, or transport phase.

Pinned owned-creature `DamageTaken`/`JustDied`, health queries, `MovePoint`/movement callbacks, owner attribution, gossip/commands, and timed update hooks support this state machine. The capture result must atomically move the run state before despawning the owned target, so a repeated input cannot duplicate credit. All control spells used by normal players remain normal core behavior; the module controls only its targets and whether a capture window is open.

### Why it is an alternative, not my first pick

This has the strongest change to the usual kill-everything objective. It also has the largest feel risk: pets, damage-over-time, or autonomous bots may overshoot the threshold. The group should be able to solve that with normal tactical stop/hold controls, but that has not been proven. If success requires disabling ordinary class abilities, hidden lethal-damage caps, or rewriting Playerbots behavior, the concept has failed its design envelope.

Estimate: 10–14 focused implementation hours plus validation/review; medium completion confidence. An early approved technical/gameplay feasibility slice must demonstrate one runner can be captured using the stated rules without making it unkillable, and that failure/expiry/cancel cannot leave an actor or credit behind. If the control-versus-damage decision is frustrating rather than legible, reject it instead of replacing it with an automatic kill bounty.

## Option D — Stormwright

**Hook:** Turn the boss's storm into your weapon before it tears the arena apart.

| Required field | Concrete proposal |
|---|---|
| Player fantasy | Outwit an armored storm boss by catching its lightning in the arena's machinery and choosing when to unleash it. |
| Repeatable loop | Bait a delayed strike onto a rod, escape its locked impact, then spend the captured charge to protect the ward or open a boss damage window. |
| Decisions/challenge | Safe ground versus damage now; which rod remains available; when to lock the strike; whether to kite pursuing adds into a discharge. |
| Short session | A public registrar lets a human and up to four companions start/reset a complete 8–12 minute encounter without a GM. |
| Multiple sessions | Master marker timing, rod routes, cooldown overlap and recovery choices; change party composition and take on two tighter presets after learning normal. |
| Visible changes | Three physical rods, a moving then locked lightning marker, a strike that visibly charges a rod, a discharge into the boss, a clear vulnerability interval, and pursuing adds caught in the blast. |
| Differentiation | The player actively routes an enemy attack into a shared environmental resource; the same charge buys safety or offense. It is not just a boss with larger numbers or automatic colored lights. |
| Strongest demo | The pilot lures adds toward a rod while marked, steps clear after the lock, catches the lightning, then discharges through the adds into the boss and the party exploits the vulnerability. |
| Complete V1 | One authored arena, one boss, three rods, one add role, one designated human pilot, three ward points, charge/ground/discharge/cooldown states, success/abort/reset, normal plus two parameter presets, complete install and demo docs. |
| Exact-pin risks | Stock-client telegraph readability, safe visual spell/model selection, in-combat rod interaction, marker movement/synchronization, bot tank positioning and bounded actor cleanup. |
| Finish confidence | Medium-high after an early bounded asset/site check; roughly 8–12 implementation hours plus real build/install/startup/reviewer buffer. Lower than Holdfast on visual uncertainty, higher on memorable showcase value. |

### Complete encounter shape

The enrolling human is the **pilot**. Companions, including ordinary Playerbots, tank/heal/fight normally; bots are not required to understand rods or dodge the mechanic. The boss periodically places a lightning marker on the pilot: four seconds tracking, then two seconds locked at the final position. The pilot must route it onto one of three rods and step away after the lock. A correct impact charges that rod. A miss removes one of the arena's three ward-integrity points; the consequence is explicit encounter failure pressure rather than an undisclosed demand that bots execute raid mechanics.

A charged rod offers two ordinary interaction choices to the pilot, with state/distance/GUID authorization rechecked on use. **Discharge** consumes charge, visibly strikes the boss, opens a roughly twelve-second vulnerability window, and damages nearby module-owned adds. **Ground** instead restores one missing ward point. A spent rod cools for approximately thirty seconds, so the pilot must move between rods and decide whether to recover or press damage. Exact values are initial tuning targets, not validated balance.

The boss takes heavily reduced damage outside discharge windows; the reduction belongs to its owned AI and is not an undocumented core/global damage change. Depleted ward, full wipe, pilot death/leave/logout, map departure, unrecoverable summon failure, or hard time cap cleanly aborts the run. Boss death wins. Success/failure returns the registrar to a usable state for a later attempt. Records, if retained, are assisted encounter records, never a claim of outsider-proof competition.

The initially considered orb spell **62186 is UNAPPROVED and must not be cast as a harmless placeholder**. Independent Reviewer parsed the exact judge's public DBC input and found that it applies periodic-trigger aura 23 every 8000 ms to 62278; the pinned Thorim script associates that path with damage/buff behavior. A name ending in “VISUAL” is not proof of harmlessness.

The preferred bounded alternative is the core's direct **visual-kit packet** API. `Unit::SendPlaySpellVisual` and `SendPlaySpellImpact` at the exact pin only write GUID and `SpellVisualKit.dbc` index into client packets; they do not cast a spell, apply an aura, run a trigger or deal damage. This allows validated kit effects on owned rods/marker/boss, combined with stock creature models and scale/state changes. A SpellVisual ID is not interchangeable with a SpellVisualKit ID. The specific kit/model records and any graphical linkage still need deterministic reference checks and later stock-client legibility verification; no particular effect is represented as already tested.

Reviewer additionally verified that SpellVisual 13114 references StateKit 12201 and that kit 12201 exists in the judge's exact public `ac-data` commit `74643b700b1cd806845a1dfd926a2c46e7890dbe` (SpellVisual blob `bf7cd0124dda3b83c39009e9f6d0afd832ae84ef`; SpellVisualKit blob `07d8b6c08d12b68f644b035a728688cc1019f9b3`). This is a concrete reference-check starting point, not proof that a state kit is readable or terminates correctly when used as a packet effect. The candidate must use bounded markers/lifetimes and document remaining client checks.

Gameplay state owns charge, misses and vulnerability; feedback never controls those transitions. Rod idle/charged/cooling and tracking/locked marker states must be visually distinguishable in the stock client. If they cannot be made legible with validated stock assets, the flagship does not pass its quality floor simply because chat messages report the missing visuals. This is an explicit early asset/site feasibility prerequisite, not a reason to import encounter spells with hidden behavior.

### Proposed 75-second showcase and future capture targets

This is a future manual demonstration plan, not footage or validation already obtained. The final delivered timings must be reconciled to the implemented encounter.

| Time | Player action and what the viewer sees |
|---|---|
| 0–10s | Show the three rods and boss; start normal at the public registrar. The short rules explain catch, ground, discharge. |
| 10–25s | Party engages; pilot is marked and moves toward an idle rod. Pursuing adds make that movement a combat choice. |
| 25–35s | Marker locks; pilot steps clear. Lightning lands on the rod and its charged state becomes obvious. |
| 35–50s | Pilot activates Discharge. Lightning hits the boss, catches nearby adds, and the party attacks during the visible vulnerability. |
| 50–65s | The used rod is cooling. Pilot takes the next marker to a different rod, showing why the encounter cannot be solved by standing on one spot. |
| 65–75s | Show Ground as the alternative after a deliberate miss or briefly show its choice and the ward counter. The viewer understands offense versus recovery. |

Tyler's eventual capture checklist: clean arena before start; tracking and locked marker; charged versus cooling rod; discharge connecting to boss; adds caught near the rod; ward loss/recovery; boss victory; cleanup and a second self-service start. The flagship README must include the exact final 60–90 second flow, these capture targets, stock-client feedback descriptions, and a concise creator note. My current creator judgment is that environmental control makes the human player the encounter's conductor while ordinary companions still matter. The intentional tradeoff is one polished encounter rather than a large configurable boss framework.

## Option E — Warband Arena

**Hook:** Draft a tiny army, then fight beside it and live with the casualties.

| Required field | Concrete proposal |
|---|---|
| Player fantasy | Captain a small warband whose formation and survival depend on both your draft and your own combat decisions. |
| Repeatable loop | Inspect the next enemy lineup, recruit/repair/promote within a small budget, place allies, fight personally, then carry survivors and purse into the next bout. |
| Decisions/challenge | Recruit a counter versus heal a veteran; spend on promotion versus reserve; protect a fragile medic or let an ally fall to win faster; choose a formation around your class. |
| Short session | Self-service arena marshal starts a six-bout run of about 10–15 minutes for one human captain with up to three module-owned allies. |
| Multiple sessions | Try class/roster synergies, adapt to a changing order of visible enemy lineups, preserve more survivors, and succeed with stricter starting budgets. |
| Visible changes | The chosen allies actually appear on formation pads, fight alongside the captain, heal/attack, survive or die, and change the next bout's available roster. |
| Differentiation | A constrained draft and casualty economy changes the team available for the next fight. It uses owned scripted creatures, not a renamed wrapper around Playerbots commands. |
| Strongest demo | See enemy double-marksman staging, recruit a shieldbearer, protect a rear medic while personally intercepting enemies, then face a new lineup that makes a different draft attractive. |
| Complete V1 | One flat arena, four ally archetypes, three roster slots, six-point starting budget, six enemy lineups/bouts, three formation pads, fixed purse/casualty rules, win/fail/reset and cleanup. |
| Exact-pin risks | Ally/enemy target restriction, medic healing scope/factions, re-targeting after deaths, formation movement, leashes, and balance across captain classes. |
| Finish confidence | Medium; approximately 12–16 implementation hours plus independent validation. Credible only with four deliberately small AIs and no persistent army, client action bar, or Playerbots integration framework. |

The four archetypes are shieldbearer, marksman, arcanist and medic. The opposing lineup is visible before purchases lock, so the draft responds to information. An in-run six-point budget, three slots, fixed victory income and costly casualty replacement produce actual tradeoffs. Promotions and repairs affect only this run's owned allies. The captain remains in ordinary WoW combat and can complement the roster: tank to protect fragile allies, deal damage behind a shieldbearer, or heal a damage-heavy squad.

All progress is inside a complete six-bout run; repeat value is roster mastery and changing opponent order, not a permanent power grind. A total defeat/abandonment closes the run; victory produces an assisted run record and resets the arena. The player can start another attempt from the marshal without a GM. Existing Playerbots remains installed but is not asked to implement the squad. Outsider help is not treated as a fair-competition claim.

The exact pinned APIs expose ordinary scripted AI, summons, movement, targeting and healing helpers. Generic friendly scans must **not** be used blindly: the medic should select from the captain and the controller's owned GUID roster, so unrelated friendly players/NPCs are not healed accidentally. Each ally and opponent has a hard arena leash and finite lifetime. Broad autonomous tactics, eight classes of hirelings, cross-session owned armies and dozens of ability loadouts are outside V1. If four archetypes still cannot be made distinct and reliable, do not present three differently named melee creatures as the promised squad game.

## Mandatory decision tests for the shortlist

These are the creative owner's assessments for review, not fabricated test results or Director/Reviewer approval. Independent dispositions must be recorded before final choice and launch work.

| Mandatory test | Stormwright | Holdfast | Warband Arena |
|---|---|---|---|
| Worth installing? | **YES** — a complete environmental boss encounter that a human can run with ordinary companions. | **YES** — a compact objective-defense activity with real extraction decisions. | **YES** — a playable roster/draft game coupled to normal character combat. |
| Voluntary repeat use? | **YES** — positioning and charge allocation improve with practice and presets. | **YES** — better defense and risk decisions change extraction outcomes. | **YES** — opponent order and class/roster choices create new plans. |
| Adds real gameplay? | **YES** — bait, lock, route, ground/discharge, exploit windows. | **YES** — intercept, protect, repair, continue/extract. | **YES** — draft, position, fight, preserve/replace. |
| Understandably cool in a short demo? | **YES** — the boss's attack visibly becomes the player's weapon. | **YES** — saving a nearly broken objective explains the stakes quickly. | **YES** — the purchased formation visibly changes the ensuing fight. |
| Memorable visible moment? | **YES** — rod-to-boss discharge through pursuing adds. | **YES** — simultaneous lane interception before the beacon falls. | **YES** — a protected medic keeps a carefully drafted squad alive against its counter. |
| Value after surprise? | **YES** — execution, recovery and timing remain skill tests. | **YES** — party roles, resource tradeoffs and score risk remain. | **YES** — roster economy and adaptations remain even when all archetypes are known. |
| Complete independent V1 by deadline? | **YES, credible estimate** with one arena/boss/add and an early asset check; reject the path if readable stock telegraphs fail. | **YES, credible estimate** with strict actor/site/wave bounds and the assisted-record scope. | **FEASIBILITY FLOOR STILL NEEDED** — four AI roles plus balance have the largest implementation surface of the shortlist; do not treat this as approved simply to fill a slot. |
| Authentically Wildcard's choice? | **YES** — my preference after independent comparison: the human controls the encounter's environment instead of merely optimizing damage. | **YES** — I would choose this if Stormwright fails its visual/technical floor. | **YES** as a strategic alternative; I would not choose it merely to satisfy variety if the deadline case is weak. |

My ordered shortlist is **Stormwright, Holdfast, Warband Arena**. Director and Reviewer should pass/veto each on concrete quality/feasibility grounds. I will choose among those that pass both floors, with Stormwright the current preference. Only one flagship proceeds. Another project cannot start until that flagship passes independent review and the official gate, while BUILD and remaining time still permit it.

## Exact pinned API evidence

Every URL is pinned to the required commit. These were inspected directly from public source. No live server, private endpoint, Adventure Nexus repository, credential, or mutable dependency checkout was accessed.

| Capability | Evidence and exact implication |
|---|---|
| Own a creature's behavior and interaction | [CreatureScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/CreatureScript.h#L33) exposes `OnGossipHello`, `OnGossipSelect`, and `GetAI` at line 57. New module-owned templates can bind a module script; no existing AI replacement is needed. |
| Distinguish damage, healing, participants, and internal state | [UnitAI.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/CoreAI/UnitAI.h#L205) exposes `CanAIAttack`; lines 218–221 expose data/GUID hooks; lines 371/374 expose **four-argument** `DamageTaken(Unit*, uint32&, DamageEffectType, SpellSchoolMask)` and `HealReceived(Unit*, uint32&)`. Older three-argument override examples would be wrong for this pin. |
| Run owned encounter state and track deaths/movement | [CreatureAI.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/CreatureAI.h#L146) exposes `JustDied`, `JustSummoned`, `SummonedCreatureDespawn`, `SummonedCreatureDies`, and `MovementInform` at line 187. [ScriptedCreature.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/ScriptedAI/ScriptedCreature.h#L199) has the matching damage/update overrides and ordinary melee helpers. |
| Bound every spawned actor's lifetime | [Object.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Object/Object.h#L639) provides `SummonCreature` with temporary-summon type and despawn time. [TemporarySummon.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Creature/TemporarySummon.h#L57) has `UnSummon(Milliseconds)`. [ScriptedCreature.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/ScriptedAI/ScriptedCreature.h#L88) has GUID-based `SummonList` registration/removal and `DespawnAll`. |
| Bound and tune only owned actors | [Unit.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.h#L1111) exposes `GetHealthPct`; lines 1125–1126 expose `SetHealth`/`SetMaxHealth`; line 1295 exposes `GetCharmerOrOwnerPlayerOrPlayerItself`; line 1741 exposes `SetSpeed`. No general modification of normal-world enemies is required. |
| Fixed party membership and captain checks | [Group.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Groups/Group.h#L238) exposes `IsMember`, `IsLeader`, `GetFirstMember`, and `GetMembersCount`. Capture GUIDs once; do not grant late group joiners retroactive participation/rewards. |
| Legible decisions in the stock client | [ScriptedGossip.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/ScriptedAI/ScriptedGossip.h#L88) exposes string gossip options, menu send, and close. Commands/private messages are available through the previously inspected pinned `CommandScript` and `ChatHandler` APIs. Never rely on a gossip menu being open as authorization; revalidate captain, state, distance, and action on selection. |
| Authored moving convoy | [ScriptedEscortAI.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/ScriptedAI/ScriptedEscortAI.h#L81) provides `AddWaypoint`, `WaypointReached`, `Start` with explicit owner GUID, `SetEscortPaused`, and despawn-at-end/far settings. This is source feasibility, not proof that a proposed road is traversable. |
| Escape and chase routes | [MotionMaster.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Movement/MotionMaster.h#L232) exposes `MoveChase`, `MoveFleeing`, and `MovePoint` with path generation. A deterministic authored escape point is preferable to unbounded random fleeing for the capture V1. |
| Visual feedback without spell execution | [Unit.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.h#L2032) declares visual/impact helpers. [Unit.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.cpp#L15194) implements them as GUID + **SpellVisualKit** index packets. No `CastSpell`, aura or damage is invoked by these helpers. Validate actual kit IDs; do not pass a spell/SpellVisual ID by assumption. |
| In-combat rod interaction is source-feasible | [Player.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Player/Player.cpp#L2115) checks NPC existence, player/creature life, flight, flags, charm, reaction and range; it does not globally reject combat. Gameobject checks follow at2167. This supports a friendly rod's gossip path; final handler/template interaction still requires integration validation. |
| Avoid confusing an encounter visual with safe behavior | [boss_thorim.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/scripts/Northrend/Ulduar/Ulduar/boss_thorim.cpp#L46) names62186 and casts it at1007. Reviewer's DBC finding above means that name is not a safety guarantee;62186 is excluded pending a complete trigger audit, with direct visual packets preferred. |
| Small owned squad | [ScriptedCreature.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/AI/ScriptedAI/ScriptedCreature.h#L342) exposes friendly-health/buff helpers; [MotionMaster.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Movement/MotionMaster.h#L230) exposes `MoveFollow`. Warband should instead restrict its healer target search to the controller's owned GUID roster and captain. The general helpers' existence does not establish safe faction/target behavior. |
| Bot boundary | [WorldSession.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Server/WorldSession.h#L1230) provides `IsBot()` for excluding ordinary bot sessions from captain/start/menu authority while still including roster bots as combatants. This does not establish full human-client selfbot exclusion. |
| Ordinary Playerbots combat remains the integration path | At Playerbots pin `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, [AttackAction.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Actions/AttackAction.cpp#L55) validates/sets a combat target and calls ordinary `bot->Attack` at line 195. [GrindTargetValue.cpp](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Base/Value/GrindTargetValue.cpp#L33) considers master/group/attackers. This supports an inference that ordinary fighting is available; it does **not** prove bots understand objectives, respect a capture window, or will behave well at the selected site. |

## Mandatory validation and decision boundary

All three require the unchanged official default-branch candidate judge, exact dependency pins, complete module SQL/config/reference validation, real compile/install/startup evidence, and independent source review. Developer tests should target the actual state invariants: one active run, frozen roster, finite actor counts, legal transitions, duplicate input/completion, participant attribution, timeout/cancel/death cleanup, idempotent extracted records, and failed summon recovery. Source checks cannot substitute for those executions.

The proposed custom template IDs, models, faction values, and site/route coordinates have deliberately not been invented as if validated. They must be selected from or checked against the disposable exact-pinned data and remain project-local. Any requirement for core edits, Playerbots edits, client changes, live-server access, or a newer dependency rejects that implementation path.

Director and Reviewer must now compare the **three shortlisted concepts** and record quality/feasibility dispositions. Wildcard then makes the final choice among concepts passing both floors. My current preference is Stormwright, with Holdfast as the clearest fallback; Warband Arena remains a serious strategic alternative with a larger closure risk. If none clears the bar, run a fresh set rather than reviving rejected flavor concepts. The chosen coherent V1, final creator rationale, both independent dispositions and ownership must be recorded before substantive work. A design choice is still not permission to implement before the official judge is proven and the sprint formally launched.
