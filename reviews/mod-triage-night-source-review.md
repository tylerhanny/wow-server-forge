# Triage Night — independent implementation review

**SOURCE_REVIEW=PASS; ONE_HUMAN_REVIEW=PASS (implementation source);
owned SQL/reference SOURCE_REVIEW=PASS.** Reviewer disposition: 2026-09-05.
Official compilation/runtime and actual logged-in encounter behavior remain pending.

## Exact reviewed scope

Complete reviewed source: `e8907bd72940628148150621d7c8143624c47045`.
The preceding complete checkpoint `f629a44f3c8d49166669580636367103f8f6a010`
includes the exact pinned `getClass()` spelling, 12,000 patient health and retention of
the global actor lease until actual controller destruction. The final source correction
adds only the explicit pinned `CommandScript.h` include, avoiding an unproven transitive
definition. These bounded deltas were inspected against the initial coherent source
`fb5abd8f3a369ea92adef4842064405d48ee366f`.

Final local freeze: `b404a1bd4614a8b956187f17baf585eee6d16cf6`, `project/triage-night`.
Only README, VALIDATION and handoff review-status text differs from the reviewed source;
source, SQL, configuration and rule checks remain byte-identical. Exact documentation
equivalence and `git diff --check` passed. The eleven files are confined to one module
and its matching handoff, with no custom build hook, dependency edit or warning suppression.

At this record's checkpoint, remote publication was rejected by automatic approval
review, including the builder's evidence-backed retry. The Director is resolving that
specific publication approval. No remote publication or official dispatch is claimed,
and this review does not authorize bypassing the block through another route.

Subsequent authorized publication and dispatch: the owner directly approved the exact
frozen SHA for the specified public repository and branch. The Director performed that
push and verified remote `refs/heads/project/triage-night` equals
`b404a1bd4614a8b956187f17baf585eee6d16cf6`; no source or documentation changed. Only then
the Reviewer dispatched [33971943070](https://github.com/tylerhanny/wow-server-forge/actions/runs/33971943070)
at `2026-09-05T14:29:03Z`, using actual default-branch judge
`8070cf87ba160d08c507e98dc809a949c573f986`. Protected workflow/validation bytes match the
accepted judge `e5fd277de515dbda983993e6f8a52b48cb0816b4`. Scope and pinned checkout passed;
the full build/runtime and independent artifact disposition remain pending at this update.
The earlier publication block is resolved, with no alternate-route bypass or extra control.

Exact compatibility remains AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`,
Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu 24.04 x86-64 and client12340.

## Actual gameplay and one-human implementation

The qualifying path is one level-80 priest with ordinary learned direct single-target
heals and healing gear, one human/client, and no bots. Three persistent patients face
five authored 45-second injury rounds, four 10-second breaks and a 10-second briefing.
The human chooses efficient versus fast healing, priorities after four-second burst
warnings, and the target/timing of two six-second stabilization charges. Stabilization
pauses that patient's scripted injury; it does not heal or overlap another pause.
Patient health and the player's native mana carry between rounds. No free player health,
mana, item, gold, permanent power or equal-conditions ranking is granted.

Public SEC_PLAYER commands provide help, preset selection/start, status, stabilization,
stop, result history and retry. Commands enqueue bounded requests; OnPlayerUpdate performs
map-owned operations. Start-only casting restrictions are separate from active eligibility:
ordinary healing casts and channels are explicitly allowed during the encounter. The
complete loop supports success, patient loss, death/departure, timeout, abort and normal
rest/retry without a second operator, special bot cognition or GM venue setup.

Training and Veteran share the mechanics; Veteran scales authored injury to 135 percent.
Role rotation and carrying patient health give repeat attempts different priorities.
The 12,000-health capacity and pressure values are source-based starting estimates,
not measured class/gear balance. Other healer classes, party AoE and bot healing are
unclaimed. Shields do not prevent the explicitly documented scripted health loss.

## Targetability, ownership and lifecycle

Exact pinned assist logic requires friendly, selectable, living patients with CAN_ASSIST;
NON_ATTACKABLE/immune-PC protection would reject ordinary healing. Patient templates
therefore use faction35, type_flags4096, unit_flags0 and RegenHealth0. Runtime additionally
disables native regeneration and checks the pilot's native assist/LOS targetability after
creation. AI DamageTaken filters outside damage; HealReceived permits only the exact pilot
on an active bound patient. The pinned hook runs before native health modification.
The invisible controller's separate non-attackable/not-selectable flags do not leak to patients.

Health persists through breaks and the AI never refills it on reset/evade; those paths abort.
Low-health collapse is a stand pose rather than a dead unit, preserving heal targetability.
A lethal scheduled injury explicitly fails the shift. The last round's injury is applied
before success, so victory cannot suppress its final required damage. Visible ticks are
not compressed to catch up after lag; a separate six-minute real-time cap remains active.

Commands and controller identity are bound to the current session. Bounded queues/results,
one active run per human and a four-controller global limit constrain ownership. Completed
sessions detach and save results, while their lease stays counted through the actual
controller destructor and short result-pose cleanup. Logout does not refund an actor lease
before destruction or let a stale controller clear a new run. Death, map/phase departure,
configuration generation changes, disable, reset/evade, partial spawn and timeout reach
owned cleanup. Actor lifetime is 390 seconds, exceeding the separate 360-second run cap.

The encounter is player-triggered at validated nearby outdoor ground. Bounded phase-aware
height, liquid and LOS checks reject unsuitable starts instead of guessing coordinates.
The normal course is a tight patient semicircle, with no hostile pathing or required bot
movement. No OnStartup actor/helper is registered. Actual client terrain, heal targeting,
poses, visibility and command responsiveness remain distinct from these source checks.

## SQL and static reference review

Independent Practical SQL/reference inspection and Reviewer source inspection found no
actionable SQL defect. Install blob `66786f463f202e8c8a3bd87f29ab008041c5f7e7` and uninstall
blob `1cc7d0df1b89cf0100f2b8ae4d0ccc31d4e78d53` remain unchanged at the final freeze.
The transaction adds only four reserved templates911100–911103 and four Idx0 model rows,
using plain INSERT against valid pinned InnoDB schemas. No stock rows, permanent spawns,
rewards or player records are modified. Rollback removes model rows before templates,
restricted by reserved identities and matching Triage ScriptNames; updater history remains.

Pinned DBC references independently resolve controller display13069 to InvisibleStalker,
and patient displays6570,2588,1027 to OrcMale, TrollMale and ScourgeMale respectively.
The reserved IDs are absent from inspected pinned base tables. This is static reference
inspection, not proof of SQL execution, a user's custom-module collision check or client
rendering. Native SQL discovery/install and disposable startup remain required evidence.

## Remaining official and manual evidence

The full README, reference notes, validation matrix, handoff and 90-second ordinary-priest
demo checklist are complete. The actual-helper compile-time checks cover schedule,
stabilization, terminal transitions and bounded arithmetic; no local C++ execution was
claimed. Source review leaves no critical finding requiring another implementation change.

After authorized publication, the exact frozen SHA still requires one full current-default-
branch official gate and independent artifact review. Native module/config/SQL loading and
unfiltered tests must pass; a dry-run is not an executed logged-in shift. Actual direct-heal
targetability, stock bars/poses, gear/mana pressure, fun/replayability and optional bot-party
coexistence remain **PENDING LIVE/IN-GAME VALIDATION**. No additional judge framework or
bespoke logged-in test fixture is proposed or inferred from this source disposition.
