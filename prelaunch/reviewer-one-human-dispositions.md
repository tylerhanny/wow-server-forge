# Independent proposal dispositions after the one-human requirement

```text
REVIEW_STAGE=PREIMPLEMENTATION_DESIGN
AUTHORITY=ONE_HUMAN_PLAYABILITY.md; WILDCARD_AUTEUR.md; AGENTS.md
WILDCARD_TOURNAMENT=ad264556c8fd688ea462ead3ab7ece753f142819
WILDCARD_ONE_HUMAN_ADDENDUM=84df9c388f4a7b0b5b0968bae966b11c885f29d3
PRACTICAL_PROPOSAL=87d44127c8049526a6213beebf084e97cd1c6ddc
IMPLEMENTATION_REVIEW=NOT_RUN; no gameplay implementation exists
PROJECT_OFFICIAL_GATES=NOT_RUN
HARVEST_APPROVAL=NONE
LIVE_OR_IN_GAME_VALIDATION=NOT_PERFORMED
```

These are independent selection-stage judgments about the exact written designs and available pinned APIs. A `ONE_HUMAN_REVIEW=PASS` below applies **only to the evaluated proposal design**. The eventual candidate must receive a new implementation/source/disposable review, pass the official judge at its exact SHA, retain the required README/handoff section, and preserve honest pending client/bot tests. No proposal pass starts the sprint or authorizes prelaunch implementation.

## Comparative disposition

| Proposal | Gameplay / installation floor | Pinned technical and finish floor | One-human proposal disposition | Reviewer judgment |
|---|---|---|---|---|
| Stormwright | PASS | PASS for the written bounded V1; medium-high relative confidence, with early visual/site and solo-health-budget checks | `ONE_HUMAN_REVIEW=PASS` | Strongest showcase choice. The player repeatedly turns an enemy attack into a resource and trades recovery against a damage window. |
| Holdfast | PASS | PASS for one compact site, three roles, finite eight-assault tables; medium-high relative confidence | `ONE_HUMAN_REVIEW=PASS` | Strong fallback. Persistent beacon damage and paid repair/extraction remain meaningful after serializing the human's special duties. |
| Warband Arena | PASS | PASS in principle for exactly four compact roles, three slots and six bouts; medium confidence and the greatest closure risk | `ONE_HUMAN_REVIEW=PASS` | A credible alternative, with a larger AI/targeting/healing/balance workload. Prefer deferring it as the first flagship when the stronger bounded showcase is available; this is a comparative recommendation, not an invented API prohibition. |
| Hunt Rhythm | PASS for Practical's modest, useful leveling scope | PASS; narrow hook/command arithmetic and no custom world data; high relative confidence | `ONE_HUMAN_REVIEW=PASS` | A coherent low-risk Practical slice whose complete primary loop is genuinely solo. |

Wildcard retains its choice among options passing both Director and Reviewer floors. The Reviewer does not require a new ideation tournament: five mechanically distinct ideas and a meaningful three-way comparison exist. Stormwright and Holdfast both provide convincing gameplay, repeat use, visible demonstration value, enduring decisions, and a credible bounded finish path. Warband also supplies those gameplay qualities, but its finish estimate has less margin. These estimates assume the shared clean gate is repaired/proven and normal BUILD time remains; they are not elapsed-time guarantees.

## Stormwright — evaluated complete path

**Qualifying path:** one level-80 human, one ordinary client/account, zero Playerbots, using the complete Solo Pilot profile. Optional human-plus-bots remains ordinary combat support.

The public registrar exposes rules/preset/start to the human. The same human fights, routes the tracking mark, moves after lock, catches charge, chooses Ground or Discharge, handles cooling rods, defeats the boss or loses the ward/attempt, receives the outcome, retries and exits. There is never a second rod operator. Discharge supplies material boss damage; Ground provides guarded pilot recovery as well as ward recovery, including when the ward is full but the pilot is hurt. This preserves the original resource tradeoff while removing an implicit healer requirement.

Normal bots, if brought, only tank/heal/attack/follow. Rod success never depends on a bot's exact position, a custom menu, a mark transfer, a damage-stop threshold or a second participant's synchronized action. Party scaling changes bounded combat pressure, not how many custom operators are required.

Conditions for preserving this pass in implementation:

- Deliver the public location, registrar, ordinary-player interactions, results, abort and retry; GM-only startup or an empty demonstration is insufficient.
- Freeze the eligible starting roster and retain a complete no-bot profile. Bound the solo add count to one, and show a workable level-80 non-healer incoming-damage/recovery budget through the hard time cap. Higher presets must retain one-human feasibility.
- Ground must revalidate the living pilot, owned active run, distance and available charge, cannot resurrect/heal bystanders, and cannot be used after abort. Repeated inputs cannot spend or award twice.
- Preserve a real offense/recovery choice. A permanently safe idle loop or automatic discharge would erase the promised mechanic.
- Validate distinct tracking/locked/charged/cooling/vulnerability feedback with stock assets. The exact visual audit is in `prelaunch/stormwright-visual-audit.md`; 62186 is not an approved harmless spell. Direct visual-kit packets provide a source-supported alternative, but no client rendering or effect lifetime has been proved.
- Bound and clean every owned actor/marker on death, logout, leave, map change, timeout and failed summon. Record an assisted encounter outcome exactly once.

Remaining later manual questions: client legibility, in-combat interaction feel, route timing, class/gear balance, and ordinary bot combat behavior. These are distinct from the source-supported fact that the design assigns every special mechanic to one human.

## Holdfast — evaluated complete path

**Qualifying path:** one level-80 human with no bots, using the complete solo wave table; ordinary bot fighting/healing is optional.

One central beacon and short converging lanes give the captain a single route. At most one sapper may be armed at a time in every profile. The complete solo table still contains all three roles and eight assaults, with at most two ordinary attackers active and bounded reinforcements. The human makes every preset, target priority, Rally, paid repair, continue/extract, retry and exit choice. Normal bots never need to choose a custom defense post or interpret a sapper mechanic.

Rally occurs only in a cleared intermission and restores living roster resources; it does not repair the beacon. Paid beacon repair still consumes the run's unbanked score. The resulting target-priority/attrition/extraction game remains worthwhile and repeatable. It is not reduced to a tutorial or a passive timer.

Conditions for preserving this pass:

- Verify each seed/preset's live-enemy cap, single armed-sapper invariant, travel/arming budget and complete final extraction path. Sequential human duties must remain feasible even if bots only fight their current ordinary target.
- Do not restart an assault while the sole human is deliberating in a checkpoint. The stated timeout extracts a completed result.
- Prevent ordinary healing **and native regeneration/reset healing** of the beacon. Only guarded paid repair restores objective integrity during the attempt.
- Rally cannot run during combat, revive a player, affect bystanders, repair the beacon or remain available after abort. Protect repeated gossip actions and exactly-once extraction.
- Persist the stated assisted-record semantics; do not claim outsider-proof rankings. Supply public access, natural death/retry flow, full actor cleanup and no GM reset dependency.

Remaining later manual questions: solo class/gear pacing, sapper telegraph/travel readability, beacon targeting and ordinary bot target/support behavior.

## Warband Arena — evaluated complete path

**Qualifying path:** one level-80 human captain with the module's temporary scripted NPC squad and zero participating Playerbots. This is explicitly allowed by the one-human authority's module-owned-helper provision.

The captain sees a lineup, buys/replaces/promotes/repairs, assigns formation pads sequentially, fights personally, carries casualties and purse across six bouts, receives the final result and can retry or abort through the same public marshal. Helpers execute only bounded scripted movement/combat. No ordinary Playerbot is asked to stand at a bespoke coordinate or make a draft decision. A stuck setup must report failure/reset, not require a GM or another client.

The paid-repair economy survives only if between-bout captain rest does not also restore owned allies, medics cannot freely heal the squad between decisions, and native regeneration/reset paths do not erase wounds. In-bout healing remains a deliberate tactical class/roster benefit.

Conditions for preserving this pass:

- Keep exactly the scoped four distinct roles, three slots, bounded opponent table and six bouts; no persistent army or broad tactics framework.
- Restrict ally/enemy targets and medic recipients to the correct owned GUID sets and captain. Validate faction behavior, retargeting, death, failed movement and cleanup rather than trusting a generic friendly scan.
- Disable native regeneration where wounds are meant to persist, guard between-bout healing, and preserve health through evade/reset or movement transitions. Paid repair must be the stated controlled exception.
- Keep all custom decisions sequential and human-only, and complete all outcomes/retry/exit without a bot login, second account or GM.
- Test the casualty/replacement/promotion/repair rules and exactly-once purchases; do not count renamed copies of one melee AI as four working roles.

The API path is feasible, but implementing four reliable roles plus economy and class balance is materially more work than Stormwright's single boss/add state machine. Defer it as first flagship if that workload threatens independent closure; do not weaken its promised strategic game to claim completion.

## Hunt Rhythm — evaluated complete path

**Qualifying path:** one ordinary leveling character, no bots, on normal hostile non-elite outdoor XP-bearing creatures. Level-capped/XP-locked play is explicitly outside the feature.

The same character uses `.rhythm start/status/stop`, chooses routes and ordinary pulls, receives the 0/2/4/6/8/10% current-kill sequence, sustains the cap, naturally loses a chain through timeout/death/map change, retries, and exits. No party leader, NPC operator, shared reward collector, account-specific setting or additional client is required. Botless solo is the entire feature, not a fallback demonstration. Optional bots only contribute ordinary combat/support and existing core shared-XP credit.

Independent source inspection confirms `PlayerScript::OnPlayerGiveXP`, death/logout/map hooks, the normal kill-XP call chain and `SEC_PLAYER` command support. `KillRewarder::_RewardXP` invokes the hook after group/gray/aura adjustments and before `Player::GiveXP` and pet XP, matching the proposal's explicit base-XP scope. The pinned Playerbots target-attack path supports the limited optional combat role; no special cognition is assumed.

Conditions for preserving this pass: strict eligibility and reset rules, exact `elapsed >= window` boundary, bounded config and wide-intermediate integer arithmetic, safe state lifetime/thread access, ordinary-player command permissions, clear status/expiry feedback, and no refresh from ineligible events or repeated Start. Pet/rested/RAF derivation must remain documented and source-reviewed. One-account primary use does not require exercising optional RAF behavior with another human/client.

Remaining later manual questions: class/route pacing, readable bonus/rounding feedback, pet/rested behavior and actual ordinary bot group-credit/pathfinding. A missed chain is normal failure, not evidence that another participant is needed.

## Additional pinned finding shared with Wildcard

Pinned [Creature.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Creature/Creature.h#L327) exposes `SetRegeneratingHealth(bool)`. [Creature.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Creature/Creature.cpp#L896) runs native regeneration outside combat and in some unreachable-target cases; `RegenerateHealth` checks that flag at lines 1037–1040. Template `RegenHealth` initializes it at line 588. Therefore `HealReceived` alone cannot preserve beacon integrity or squad wounds. The needed correction is available through owned templates/creatures and does not require a core change. Wildcard acknowledged this implementation condition.

## Integrity and next checkpoint

The existing judge's positive path allowlist already rejects changes to root `ONE_HUMAN_PLAYABILITY.md`, independently reproduced in `prelaunch/one-human-scope-check.md`. This proposal review does not alter the workflow, pins, warning policy or runtime gates. Final selection belongs to Wildcard among the options passing both independent floors, and substantive gameplay implementation still waits for the proven prelaunch judge and Director's timestamped launch.
