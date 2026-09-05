# Post-primary Wildcard tournament and final selection

Recorded 2026-09-05 after the bounded read-only tournament and its independent dispositions. This preserves the existing comparison; it does not reopen ideation or claim implementation or gameplay testing.

## Authority, ownership and timing

- Wildcard's accepted flagship, Stormwright, is frozen at candidate 60c6a91925eed80049bec47994f87df739ac7725, accepted by official run 33960843535 and independent review. Owner-reported fixes preempt the additional project.
- The Director authorized a bounded post-primary comparison after both primaries were independently accepted. The comparison was completed in messages while two documentation-branch requests remained blocked by automatic approval review. No branch, source or accepted-project mutation occurred during that comparison.
- Direct owner authorization received at approximately 2026-09-05T13:27Z subsequently resolved execution authorization for exactly Field Repairs and the selected Triage Night, one additional project per lane. The Director instructed Wildcard to preserve this decision in ignored scratch first; root will integrate decision/state before substantive implementation and release a separate project/triage-night worktree from updated main.
- Target source and documentation effort: at most four hours. Additional candidate cutoff: 2026-09-05T22:34:32Z. Feature freeze: 2026-09-06T06:34:32Z. Owner installation/testing window: 2026-09-06T12:34:32Z through hard end 2026-09-06T18:34:32Z. Preserve time for independent review and up to two approximately two-hour full official runs. No further concepts/projects are authorized.
- This note records proposal-level judgments only. No new candidate has compiled, installed, executed a logged-in encounter or received implementation acceptance.

## Locked compatibility and shared implementation envelope

Exact AzerothCore target: mod-playerbots/azerothcore-wotlk commit 47960183bb03b83e8943eb2f0f39c16df9710c9d. Exact Playerbots target: mod-playerbots/mod-playerbots commit 2f7d9f774987d0157c6a0d0cc08c40bec3db3945. Stock WoW 3.3.5a build 12340; Ubuntu Server 24.04 x86-64. No dependency, core or Playerbots source changes; no custom client, Docker, paid/runtime API, private endpoint, live server or Adventure Nexus access.

The proposals use ordinary public SEC_PLAYER help/start/status/stop commands. No GM teleport, second operated account or OnStartup registrar is assumed. A player-triggered start uses the human's current valid outdoor position and bounded nearby ground/LOS samples; missing or invalid ground fails start rather than inventing a Z coordinate. Height samples do not certify paths, collision or a safe venue. Any owned temporary actors have bounded counts and lifetimes. One run per human and a bounded global run count are required. Death, logout, map departure, abort, disable, time limit and partial-spawn failure must end or clean up the run. No stock-world damage or economy reward is proposed. Personal records make no competitive-equality claim.

The existing official build/install/SQL/config/dry-run/module-load/unit and integrity checks remain mandatory at the exact candidate SHA. They do not execute a logged-in encounter. Player-triggered actors avoid introducing another OnStartup registrar whose execution would need a separate observer; the Stormwright-specific normal-startup helper is not claimed to validate these encounters. No bespoke validation framework is planned. Actual client interactions, presentation and tuning remain explicit later manual validation, subject to the normal independent finish gate.

## Five mechanically distinct concepts

### 1. Triage Night — shortlisted and selected

#### Eleven mandatory concept fields

1. **Fantasy:** Be the sole field medic who brings three casualties through a dangerous shift.
2. **Repeatable loop:** Keep the same three patients alive through five authored 45-second injury rounds, separated by fixed 10-second recovery breaks. Ordinary player healing addresses their wounds. Two total stabilization charges each pause one patient's scripted deterioration for six seconds.
3. **Meaningful decisions/challenge:** Choose quick expensive versus slower efficient direct heals; prioritize burst injury against sustained bleeding; spend a rescue now or reserve it for a later overlap. Patient health carries between rounds. The player's ordinary mana and spell costs remain real; the module never refills player mana or health.
4. **Short-session experience:** Approximately five minutes including briefing and result, with a finite whole-shift success or failure.
5. **Multiple-session value:** Improve spell efficiency, critical-health time and emergency-resource use across two pressure presets and changing patient-role assignments. Five authored pressure schedules provide different priorities; normal healing gear remains relevant. No permanent power reward or progression framework is required for the skill/mastery loop.
6. **Visible change:** Three named wounded actors in a tight semicircle, stock target/friendly-nameplate health bars, ordinary healing animations, low-health poses and recovery to upright. Brief warnings identify approaching injury pressure. Actual readability remains a client check.
7. **Differentiation:** A repeatable support-role encounter built around actual healing and mana choices rather than an XP/convenience modifier. Stock WoW already has First Aid Triage. That quest's pinned script recognizes a designated bandage spell; this design retains three patients across five rounds and asks the player to choose ordinary spells, targets and intervention timing. No global novelty claim is made.
8. **Strongest demo moment:** Two patients deteriorate while the third faces an announced burst. Stabilize one, land an efficient heal on another, then save the third before the next injury. The simultaneous health states and normal spell animations show why the choices matter.
9. **Smallest complete V1:** Three patients, one controller, five pressure schedules, two presets, two stabilization charges, per-session personal result history, clean success/failure/result/retry/abort, owned SQL/config, installation/rollback notes and a future 60–90-second demo/capture script. No custom UI, injury-dispel system, gear normalization, support for every healer, or progression framework.
10. **Exact-pin technical risks:** Ordinary assists require living, selectable, friendly patients with CAN_ASSIST; NON_ATTACKABLE, immune-PC and unattackable state can block player healing. Use owned DamageTaken filtering instead of those targetability-blocking flags. Native Unit::DealHeal invokes the patient's AI HealReceived before ModifyHealth, allowing non-pilot healing to be rejected. Disable native patient regeneration and prevent evade/reset from restoring wounds. Scripted deterioration is health loss, explicitly not shield-preventable combat damage. Party-targeted/AoE heal behavior is not assumed. Stock visibility, actual direct-heal targetability and gear/pressure tuning require later client validation.
11. **Completion confidence:** Medium-high, approximately 75% as a planning judgment, with source/docs in three to four hours and room for independent review plus up to two full official gates. This is not a probability measurement or a claim that balance/client tests passed.

#### Nine mandatory One-Human Playability fields

1. **Exact complete path:** One level-80 priest with ordinary learned direct single-target healing spells and healing gear brings all three patients through all five rounds, receives the result and can replay.
2. **Solo or bots:** Truly solo is the qualifying path.
3. **Human responsibilities:** Discover the public commands, start/select a preset, read the objective and warnings, target/cast every heal, choose both stabilization targets/times, read the result, rest/retry and stop.
4. **Bot/helper responsibilities:** None. Patients/controllers execute injury schedules only; no healer helper is supplied.
5. **Why ordinary pinned behavior suffices:** No bot cognition is required. Direct player healing follows the reviewed native assist-target checks and HealReceived-before-health-gain path. Non-pilot healing is excluded from this qualifying design.
6. **Scaling:** Exactly three patients and no enemies. Two presets scale authored injury pressure; bot count does not change the encounter.
7. **No-bots case:** Zero bots supplies the entire primary loop, not a tutorial or partial demonstration.
8. **Whole-loop access:** Public help → eligible safe start → briefing → five rounds with finite breaks → all-patients-alive success or patient-lost/player-death/leave/time failure → result → normal rest and retry or stop. No second character, client, operated account or person is required. Patient health carries across rounds, breaks are finite, and no player resources are granted for free.
9. **Later assumptions/exclusions:** Other healer classes, party-targeted/AoE healing and helpful bot healing are not claimed as qualifying configurations. Actual stock health-bar/pose readability, direct-heal interaction and pressure tuning are PENDING LIVE/IN-GAME VALIDATION. Scripted deterioration bypasses shields; this limitation must be explicit in the product documentation.

### 2. Blindside — shortlisted, deferred

#### Eleven mandatory concept fields

1. **Fantasy:** Cross a guarded yard by reading patrols and moving through their blind spots.
2. **Loop:** Observe two sentries, cross their moving vision cones, remain still four seconds to open each of two caches, then extract.
3. **Decisions/challenge:** Route and timing against gradual awareness; spend either of two distractions early or save one for escape; bank one cache or risk the second for full completion.
4. **Short session:** Three to five minutes.
5. **Replay:** Different patrol directions and starting phases reward observation and cleaner extraction rather than one memorized opening.
6. **Visible change:** Moving/turning sentries, caches opening, alert reactions and warnings before detection. No unproven floor-cone visual is assumed.
7. **Differentiation:** A spatial stealth challenge available without the Rogue Stealth spell, rather than a text-led scavenger hunt.
8. **Demo moment:** Distract one sentry, cross behind it and open a cache, then halt as the second guard turns across the exit.
9. **Complete V1:** Two guards, two caches, two patrol variants, two distractions, one compact player-anchored yard and complete extraction/failure/result/retry/abort.
10. **Pinned risks:** HasInArc, IsWithinLOSInMap, MovePoint and owned summons support the components. They do not establish fair detection, usable patrol paths or readable facing. Height is not a path/LOS certificate. Class movement/teleport behavior creates additional edge cases.
11. **Confidence:** Approximately 50% closure confidence. Code may fit four hours, but fair detection and presentation could demand more actual client iteration than the remaining window permits.

#### Nine One-Human Playability fields

1. **Complete path:** One normal character observes patrols, opens both caches and extracts.
2. **Mode:** Solo qualifies by design.
3. **Human actions:** All movement, observation, distractions, cache interactions, extraction, retry and stop.
4. **Helpers:** Sentries patrol automatically; no helper task exists.
5. **Pinned bot sufficiency:** Bots need neither hide nor interact and are irrelevant to detection; no bot cognition is assumed.
6. **Scaling:** Two guards remain fixed; awareness and timing change difficulty rather than party size.
7. **No bots:** This is the intended whole primary experience.
8. **Whole loop:** Public start/briefing → infiltration/caches → extraction/result or alarm/time/leave failure → retry/stop, all by one operator.
9. **Later assumptions:** Optional followers are not claimed as gameplay assistance. Patrol path, facing, LOS and warning fairness require actual client verification and are the reason for deadline deferral.

### 3. Kill Switch — shortlisted, deferred

#### Eleven mandatory concept fields

1. **Fantasy:** Survive an ambush by building the explosive trap yourself.
2. **Loop:** Plant up to three landmines, lure armored pursuers through them, trigger one and propagate a proximity-linked chain, then clear five waves.
3. **Decisions/challenge:** Dispersed coverage versus connected blasts; detonate safely now or wait for more targets; conserve limited ammunition against enemies resistant to ordinary attacks.
4. **Short session:** Six to eight minutes.
5. **Replay:** Improve placement geometry/chain efficiency against changing enemy entry positions.
6. **Visible change:** Actual landmines, staggered impacts/disappearances and enemies falling along the player's placement graph.
7. **Differentiation:** Player-created geometry differs from fixed environmental objectives, but lure-and-discharge overlaps Stormwright and weakens the value of installing this as the second Wildcard project.
8. **Demo moment:** A curved three-mine chain destroys separated pursuers while the pilot narrowly clears the last blast radius.
9. **Complete V1:** Three mines per wave, two slow melee enemy sizes, five waves, two entry patterns, owned-only damage, between-wave normal recovery and complete result/retry/abort.
10. **Pinned risks:** Owned summons, ordinary chase AI, damage hooks and packet-only impacts are available. Exact ac-data display 6271 maps through model 712 to Creature/Spells/LandMine01.mdx. A new impact kit would still require data-reference audit. The impact packet API requires an explicit GUID. Ammunition exhaustion must be a clean failure, not a softlock; chain readability, pilot blast damage, native chase and optional bot threat need closure.
11. **Confidence:** Approximately 60%; source/docs might fit three to four hours, but combat/balance and overlap make this a poorer use of the remaining window than Triage.

#### Nine One-Human Playability fields

1. **Complete path:** One level-80 character places/triggers mines, lures and fights through all five waves.
2. **Mode:** Solo qualifies in design; ordinary combat bots are optional.
3. **Human actions:** Every placement/detonation, lure, next-wave readiness, retry and abort decision.
4. **Helpers:** Optional bots only tank/heal/attack; immunity to module blasts avoids requiring custom dodge choreography.
5. **Pinned bot sufficiency:** Conventional hostile combat is the only optional bot role; solo is independent of it.
6. **Scaling:** Solo has at most three slow melee pursuers. A fixed optional starting roster conservatively scales ordinary enemy health/count, never simultaneous special duties.
7. **No bots:** Kiteable enemy speed and between-wave normal rest/food avoid requiring a healer.
8. **Whole loop:** Public start/briefing → planting and five waves → clear victory or explicit ammunition/death/time failure → result → normal rest/retry or stop.
9. **Later assumptions:** Actual chase/speed, class sustain, command responsiveness and optional bot threat are unproven. Any-class balance is not claimed as validated. These risks and reduced differentiation support deferral.

### 4. Switchback — outside shortlist, deferred

#### Eleven mandatory concept fields

1. **Fantasy:** Win a foot race by choosing when to risk the shortcut.
2. **Loop:** Run four ordered checkpoints through safe bends and shorter timed hazard crossings.
3. **Decisions/challenge:** Accept extra distance or risk a closing gate and time penalty; commit or brake.
4. **Short session:** Sixty to 120 seconds.
5. **Replay:** Route mastery and improved times under reversed gate phases.
6. **Visible change:** Temporary gate actors, changing opening markers and a finish effect.
7. **Differentiation:** Movement execution and route choice rather than combat bonuses.
8. **Demo moment:** Cross consecutive closing gaps and beat a displayed safe-route benchmark; no ghost actor is included.
9. **Complete V1:** Four checkpoints, two route branches, two timed hazards, stopwatch/penalties/results/retry. No custom movement physics, client, ghost system or speed buffs.
10. **Pinned risks:** Player updates, position checks and temporary actors are available, but height cannot prove collision/traversability. Mounts, leaps and teleports complicate timing. A tiny course could feel like a drill rather than a worthwhile installation.
11. **Confidence:** Approximately 40%; source could fit, but meaningful readable terrain validation and showcase value are not convincing within this window.

#### Nine One-Human Playability fields

1. **Complete path:** One unmounted character runs the whole course.
2. **Mode:** Solo.
3. **Human actions:** Start, route decisions, movement, retry and stop.
4. **Helpers:** None.
5. **Pinned bot sufficiency:** Ordinary player movement alone is intended; no bot cognition.
6. **Scaling:** Fixed course; timing changes difficulty. No enemies or roster scaling.
7. **No bots:** Intended complete path.
8. **Whole loop:** Public access/start → countdown → checkpoints/finish or timeout/leave failure → time result → retry/stop.
9. **Later assumptions:** Terrain, collision, hazard cues and speed-altering class abilities remain unresolved. This is deferred research, not an approved implementation path.

### 5. Borrowed Body — outside shortlist, deferred

#### Eleven mandatory concept fields

1. **Fantasy:** Fight an encounter from inside the monster.
2. **Loop:** Possess one owned brute, use its three stock action-bar abilities through three combat rounds, return to the original body and replay.
3. **Decisions/challenge:** Charge, cleave and defensive cooldown timing against differing target priorities.
4. **Short session:** Five to seven minutes.
5. **Replay:** Master an unfamiliar toolkit and improve sequencing against alternating enemy arrangements.
6. **Visible change:** Camera/control transfer into a large creature with a real possession action bar, followed by a clean return.
7. **Differentiation:** Changes the playable combat role rather than adding statistics or convenience.
8. **Demo moment:** Take control, charge through the frontline, cleave two foes and return safely.
9. **Complete V1:** One body, three audited abilities, three rounds, body protection/return/results/cleanup. No monster roster, progression tree or vehicle framework.
10. **Pinned risks:** SetCharmedBy and RemoveCharmedBy expose native control paths. Their existence does not prove correct action-bar initialization, original-body protection, targeting or every logout/death/map-change return path.
11. **Confidence:** Approximately 30%; reliable possession and spell auditing would likely exceed four source/documentation hours.

#### Nine One-Human Playability fields

1. **Complete path:** One character possesses and operates the whole encounter, then returns.
2. **Mode:** Solo.
3. **Human actions:** Every ability, target, possession/release, retry and abort choice.
4. **Helpers:** Enemies use ordinary AI; no bot helper.
5. **Pinned bot sufficiency:** No bot dependency; native possession/client control still needs proof.
6. **Scaling:** One fixed monster power budget and bounded enemy lineups, independent of player gear or bot count.
7. **No bots:** Intended whole experience.
8. **Whole loop:** Public start → possession → three rounds → return/result or body/monster death/leave/time failure → clean release/retry/stop.
9. **Later assumptions:** Action-bar ability behavior and every failure return path are unresolved client/lifecycle assumptions. The concept is deferred, not implementation-approved.

## Three-concept comparison and eight mandatory decision tests

The strongest three are Triage Night, Blindside and Kill Switch. Triage gives distinct support-role priorities with the least navigation/hostile-AI burden. Blindside offers genuinely different spatial observation but detection fairness is its core, not optional polish. Kill Switch has tangible action, but overlap with Stormwright and solo-sustain/chain risks reduce its second-install value. A fresh-context independent critic reached the same Triage preference and advised deferring the other four.

| Mandatory test | Triage Night | Blindside | Kill Switch | Switchback | Borrowed Body |
|---|---|---|---|---|---|
| Worth installing | YES | YES if completed | Weaker alongside Stormwright | Uncertain | YES if completed |
| Voluntary repeat use | YES | YES | YES | Uncertain | YES |
| Real gameplay | YES | YES | YES | YES | YES |
| Understandable short demonstration | YES | YES | YES | Uncertain | YES |
| Memorable visible moment | YES | YES | YES | Not convincing in this V1 | YES |
| Value after surprise | YES | YES | YES | Uncertain | YES |
| Complete independent validation before deadline | YES at scoped proposal level | NO convincing confidence | NO convincing confidence | NO | NO |
| Authentic Wildcard design judgment | YES | YES | YES | YES | YES |

The selected Triage Night passes all eight tests at design scope. Conditional appeal of another concept does not authorize its implementation. No lowering of the quality bar, extra project or further tournament is proposed.

## Independent Reviewer disposition

Reviewer supplied the following final disposition in messages after reading the full five concepts and all eleven/nine fields:

- **Triage Night QUALITY/INSTALLATION VALUE=PASS; ONE_HUMAN_REVIEW=PASS; bounded exact-pin FEASIBILITY=PASS**, for the explicitly limited level-80 priest/direct-heal V1.
- Reviewer judged persistent patient health, finite stabilization, varied burst/bleed pressure and ordinary mana to create distinct repeated decisions. Stock health bars/poses and spell feedback offer a credible visible demonstration.
- Reviewer independently confirmed the pinned assist-flag restrictions. Preserve the entire solo start → five rounds → success/failure → result → normal rest/retry/stop path; no native regeneration/reset healing; pilot-only healing; filtered outside damage; finite breaks; no free player resources; honest shield, party-AoE and other-healer exclusions.
- Source/docs at most four hours plus up to two full approximately two-hour runs is credible at proposal scope. Client targetability/readability and tuning remain pending. Existing native SQL/config/module-load evidence must pass; no logged-in encounter execution is inferred.
- Blindside: gameplay and one-human concept plausible; FEASIBILITY/DEADLINE DEFER for patrol/facing/LOS cues and map uncertainty.
- Kill Switch: one-human concept plausible; weaker second-install value and FEASIBILITY/DEADLINE DEFER for overlap, chain readability and any-class sustain.
- Switchback and Borrowed Body: DEFER.

This is independent proposal review, not source review of a future implementation, official candidate acceptance or proof of client play.

## Director disposition

Director subsequently passed Triage Night on all required quality, installation, replay, showcase, one-human and feasibility dimensions for the stated priest V1. The Director explicitly judged persistent-health rounds, real mana, injury prioritization and two finite stabilizations to make a worthwhile repeat support challenge distinct from stock First Aid Triage and Stormwright. All eight decision tests are YES at design scope only.

Director deferred Blindside for detection/terrain fairness, Kill Switch for overlap and sustain/chain risks, and Switchback/Borrowed Body for their stated installation/closure issues. Director preserved the exact direct-priest qualification, scripted-health-loss/shield and party-AoE limitations, pilot-only heals, no native regeneration/evade refill, no free player resources, full outcome/retry/abort flow and no new OnStartup observer.

## Final Wildcard choice and creator rationale

**I choose Triage Night, scoped slug mod-triage-night.** Wildcard retains exclusive creative and implementation ownership when the Director releases the new project branch/worktree.

I want support players to have a repeatable challenge that uses their actual spells and mana without waiting for a party. Three persistent patients create competing priorities while keeping navigation and AI scope small. The narrow priest path is an intentional complete-V1 tradeoff, not a promise of balanced support for every healer.

The lasting value is practicing healing choices across cumulative pressure: wounds persist through five rounds, mana carries forward, injury schedules change priorities and only two stabilizations can rescue mistakes. Stock First Aid Triage uses a designated quest bandage. This challenge instead asks the player to select spells, targets and timing repeatedly, improving efficiency and crisis management after the novelty fades. It does not depend on flavor text or a one-time surprise.

Retain all conditions above. Source implementation begins only after root persists the decision/state and releases the separate project worktree. Owner-reported fixes to accepted projects preempt this work; no new concept or project follows it.

## Exact public evidence inspected during the bounded comparison

All AzerothCore references below were fetched at commit 47960183bb03b83e8943eb2f0f39c16df9710c9d, never a moving branch.

- src/server/game/Entities/Unit/Unit.cpp, blob 9caf5369970fee5bcc0578642bdda2fcc893dce1: 8109–8123 DealHeal invokes victim AI HealReceived before ModifyHealth; 10889–10977 assist checks, particularly 10920–10934 targetability/immunity restrictions and 10968–10975 CAN_ASSIST/TREAT_AS_RAID_UNIT requirement; 14619+ SetCharmedBy; 14823+ RemoveCharmedBy; 15194–15219 visual/impact packet-only implementation.
- src/server/game/AI/CoreAI/UnitAI.h, blob a4c01dd47ddee532fe9b86158495e178c46f1933: 371 DamageTaken; 374 HealReceived.
- src/server/game/Entities/Creature/Creature.h, blob a26e257a895c87636da5ad2885bb58af6f37c745: 287 DespawnOrUnsummon duration types; 328 SetRegeneratingHealth. Earlier exact-pin review established native regeneration and evade/reset require separate attention.
- src/server/game/Entities/Unit/Unit.h, blob edaf3e9e3a18f72eb46646758d712a55fff1d7a3: 1324 SetCharmedBy; 1328 RemoveCharmedBy; 2032–2034 visual/impact declarations. SendPlaySpellImpact requires ObjectGuid and kit ID.
- src/server/game/Entities/Object/Position.h, blob f1e0cfab6458a1d24084ef2869bf6a9a3f600f9c: 232 HasInArc.
- src/server/game/Entities/Object/Object.h, blob ce311a2ef17dc776ccdf240dd8305196210c2072: 537–538 distance; 552 IsWithinLOSInMap; 639–640 SummonCreature with uint32 lifetime.
- src/server/game/Movement/MotionMaster.h, blob f7f475c541f3048887343872c4522b1c8f3763b4: 230 MoveFollow; 240–242 MovePoint with path-generation options.
- src/server/game/Scripting/ScriptDefines/PlayerScript.h: cached exact-pin 284 OnPlayerUpdate. Public SEC_PLAYER command registration and module config loading also have accepted exact-pin Forge precedents; those precedents do not validate a new implementation.
- src/server/scripts/World/npcs_special.cpp, blob 14069c94b93db7003c4d7844813855da64f9a475: 1006–1048 stock injured-patient reset/pose and timed health reduction; 1053–1057 recognizes spell 20804; 1064–1071 changes selectability and pose after its quest treatment. This is differentiation/reference evidence, not a request to change or reuse the stock quest.
- Exact public ac-data commit 74643b700b1cd806845a1dfd926a2c46e7890dbe: CreatureDisplayInfo.dbc blob ac0fd4d64da74f8d9b750b18cd15ee2ff21941ae and CreatureModelData.dbc blob 05faab49646ac73885bcc7c3a2c1d3899a76ded8 establish display 6271 → model 712 → Creature/Spells/LandMine01.mdx. This reference does not prove appearance/legibility in an encounter.

No public-source/API observation above is represented as a new module build, live server access, in-client gameplay validation or an implementation finish-gate PASS.
