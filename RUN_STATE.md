# WoW Server Forge — Run State

## Current controls after the empty-SQL judge correction

Clean `33937007702` passed the complete pinned build, exact authorized WorldMock
correction/restoration, dependency integrity and install. It remains overall FAIL: the
existing SQL scanner incorrectly rejected a candidate with no SQL files, leaving runtime
and unit-test execution unrun. Independent evidence and the reproduced defect are in
`prelaunch/clean-control-empty-sql-judge-defect.md`; original artifact identities remain in
`prelaunch/evidence/fixture-exception-controls.json`.

Reviewer SQL-only correction `6caa073b8b10d1716d130894076193431db5a83e`, independently
approved by Practical and Director, is published as judge
`04f15bd01c7d49813053a5737f9141885c000ce6`. It preserves the existing destructive regex,
file checks and all other stages, treating an empty SQL list as inapplicable and scanner
errors as fatal. No source/pin/warning-policy change or additional gate was introduced.

Fresh clean `33941967266` and authority-tamper `33941974575` were dispatched immediately
at 2026-09-05T03:29 UTC against the same frozen candidates. Current exact evidence is
`prelaunch/evidence/sql-repair-controls.json`. Review the complete existing controls, then
record the actual 36-hour clock and start both selected lanes immediately. All sprint
timestamps remain UNSET until that complete evidence passes. Earlier controls below are
historical and must not be repeated or mistaken for the current pair.


Status: `ARMED_NOT_STARTED`

The 36-hour sprint has NOT started yet.

The Director must record the launch timestamps immediately before sprint implementation begins.

## Current authorized fixture correction and controls

At 2026-09-05T01:36:02.615039Z, the Director reconciled the owner's explicit authorization in
`WORLDMOCK_FIXTURE_EXCEPTION.md`. The exact reviewed WorldMock two-method delta may be
applied only inside disposable CI after verifying its original hash. No other upstream
source change is authorized; production source, pins, tests/assertions/coverage and all
remaining gate requirements are preserved. Record the exact patch and before/after hashes;
the modified full fixture must never be committed, installed or persisted outside CI.

The prior clean run 33929246418 remains FAIL, with both server targets built and the
required unit-test target failing. Tamper 33929247980 was rejected as required. The
source-policy blocker is now resolved by this exact owner exception. Reviewed adapter source `ff0e5807` is published as judge `60953d65185a231650c8c1050dbd6a182016ef66`.
Clean `33937007702` and tamper `33937008812` are dispatched. Practical and Director
approved the exact adapter; Reviewer now inspects actual complete control evidence.
Exact identities and outcomes: `prelaunch/evidence/fixture-exception-controls.json`. No new prelaunch gate or test expansion is authorized.

The heartbeat is ACTIVE. Hunt Rhythm and Stormwright selections/ownership are preserved.
All sprint timestamps remain UNSET until complete reviewed prelaunch success, then record
the actual clock and launch both lanes immediately. Earlier blocker/pause instructions
below are historical and do not override the current explicit authorization.

## Launch record

```text
STATUS=ARMED_NOT_STARTED
EXECUTION_STATUS=ACTIVE_PRELAUNCH_SQL_JUDGE_REPAIR
BLOCKER_IDENTIFIED_UTC=2026-09-05T00:47:37Z
OWNER_EXCEPTION_RECONCILED_UTC=2026-09-04T21:16:15Z
OWNER_EXCEPTION_POLICY=UPSTREAM_WARNING_EXCEPTION.md
STANDING_WARNING_POLICY=UPSTREAM_WARNING_POLICY.md
WORLDMOCK_FIXTURE_EXCEPTION=WORLDMOCK_FIXTURE_EXCEPTION.md
FIXTURE_EXCEPTION_RECONCILED_UTC=2026-09-05T01:36:02.615039Z
STANDING_WARNING_POLICY_RECONCILED_UTC=2026-09-04T23:07:16Z
CURRENT_POLICY_CONTROLS=RUNNING_SQL_CORRECTED_JUDGE
REVIEWED_JUDGE_SHA=04f15bd01c7d49813053a5737f9141885c000ce6
LAST_FULL_CLEAN_JUDGE_SHA=60953d65185a231650c8c1050dbd6a182016ef66
CLEAN_CONTROL_RUN=33941967266
AUTHORITY_TAMPER_RUN=33941974575
ALLOWLIST_TAMPER_RUN=33927019176
TAMPER_CONTROL_REVIEW=PASS_REJECTED_BEFORE_BUILD
CLEAN_CONTROL_REVIEW=PENDING_CURRENT_CONTROLS
PAUSE_UTC=2026-09-05T00:55:39.347769Z
RESUME_UTC=2026-09-05T01:06:37.050300Z
RESUME_POLICY=AUTONOMOUS_WITHIN_EXISTING_AUTHORITY
HEARTBEAT_STATUS=ACTIVE
START_UTC=UNSET
CONVERGENCE_START_UTC=UNSET
HARVEST_START_UTC=UNSET
HARD_DEADLINE_UTC=UNSET

START_AMERICA_NEW_YORK=UNSET
CONVERGENCE_START_AMERICA_NEW_YORK=UNSET
HARVEST_START_AMERICA_NEW_YORK=UNSET
HARD_DEADLINE_AMERICA_NEW_YORK=UNSET

CURRENT_PHASE=SETUP
```

## Active ownership

| Lane | Agent role | Current project | Branch/worktree | State |
|---|---|---|---|---|
| Director | Persistent orchestrator | Apply standing upstream policy, rerun controls and launch immediately on existing gate success | main | PRELAUNCH |
| Practical | Internal Practical Builder | Hunt Rhythm selected; complete solo design approved; awaits launch | lane/practical / .worktrees/practical | PRELAUNCH |
| Wildcard | Internal AI Auteur / Flagship Gameplay | Stormwright chosen after both floors; complete Solo Pilot mandatory; awaits launch | lane/wildcard / .worktrees/wildcard | PRELAUNCH |
| Reviewer | Independent internal Reviewer / Closer | Implement provenance warning policy and review complete control evidence | lane/reviewer / .worktrees/reviewer | PRELAUNCH |

Prelaunch evidence and next actions are recorded in `prelaunch/STATUS.md`.
Internal worker lanes are managed by the Director; Tyler need not create worker tasks.

## Pause and explicit resume record

At `2026-09-04T19:56:13Z`, the owner requested a safe temporary pause. Internal workers
and local monitoring were stopped, and heartbeat `wow-forge-director-continuity` was paused.
The already-running external clean-control run `33911646203` is left to finish and preserve
its evidence. All sprint timestamps remain UNSET.

The owner explicitly resumed on 2026-09-04; current state was reconciled at
`2026-09-04T20:10:30Z`. Run `33911646203` was still in full compilation. One-human
playability is now mandatory across every lane under `ONE_HUMAN_PLAYABILITY.md`.
Workers have resumed prelaunch only. Reconcile real CI results, finish any legitimate repair,
complete independent one-human/Auteur review and choice, then reactivate the existing
heartbeat and launch only after all prelaunch requirements pass. The bounded selection is now
complete: Practical `mod-hunt-rhythm`, Wildcard `mod-stormwright`. Both have independent
one-human proposal approval. Substantive implementation remains forbidden until formal launch.
The existing 15-minute Director continuity heartbeat has been reactivated with the mandatory
one-human policy. This does not start the sprint clock.

## Historical warning failures and earlier owner resolution

This section records the policies and dispositions at the time of those runs. The current
standing authorization below supersedes every earlier restriction on additional verified
upstream warnings; historical failures and evidence remain unchanged.

Clean run `33911646203` failed full compilation at `2026-09-04T20:56:03Z`.
The exact pinned Playerbots source has an unused `botAI` parameter in
`src/Ai/Raid/BT/BTHelpers.cpp:107`, fatal under the unchanged warnings-as-errors gate.
Independent Reviewer and Practical source audits found no smoke-induced flags or source
mutation and no evidenced supported-toolchain repair. The owner has now explicitly authorized
only the exact mechanically enforced allowance in `UPSTREAM_WARNING_EXCEPTION.md`.
Implement/review that protected policy and rerun both controls; no dependency edit, additional
warning waiver, identical failing rerun or gameplay implementation is authorized.
Full independent evidence and owner alternatives are recorded in
`prelaunch/clean-control-compile-blocker.md` (Reviewer source commit `ec81c2e`).

The protected policy is published as judge `78a5da6d5aed19a932fae53e74226ac5afc2e204`.
Practical independently passed all 73 adversarial cases on the exact committed files;
Director and Wildcard reviewed requirement preservation. Fresh authority tamper `33922543117`
and protected-allowlist tamper `33922549107` were rejected at scope before build, with
independent review and exact artifact identities recorded in `prelaunch/STATUS.md`.
Clean run `33922537362` passed the real Ubuntu compiler-scope probe and configure/command
provenance, then failed compilation at `2026-09-04T22:33:12Z`. The authorized BTHelpers warning
appeared once; new fatal unused `botAI` diagnostics occurred in Playerbots
`Hyjal/Util/HyjalHelpers.cpp:168:61` and `Hyjal/Util/HyjalScripts.cpp:39:63`. Reviewer and
Practical independently verified the pinned source and narrow compiler scope. The wrapper
captured the full failed build and checked equal pre/post dependency identity/Git-clean state.
Install, SQL, dry-runs, unit tests and later standalone integrity steps were skipped.
The exact failure evidence is in `prelaunch/evidence/clean-33922537362-director-audit.json`.
Both failed clean runs remain failed. Do not rerun unchanged known-failing validation.

These are fresh owner-required blockers under `UPSTREAM_WARNING_EXCEPTION.md`; no additional
warning or source/pin edit is authorized. A third unused parameter at HyjalHelpers line 209
is a source-only finding, not an observed CI diagnostic. Pinned `-Wfatal-errors` means the
observed failures are not an exhaustive warning inventory. Preserve that distinction.
The bounded failure-summary reporting correction is complete and independently reviewed
at revision `5269391836586137f983d79122ad9dd8a09fa1fd`; acceptance is unchanged. Its actual
failed-artifact replay and tests are in `prelaunch/failure-summary-reporting-review.md`.
Await explicit owner resolution. No gameplay implementation or clock initialization.

The heartbeat remains ACTIVE for continuity, quiet while this owner-required blocker is
unchanged. Both launch selections are preserved, all timestamps remain UNSET, and no
live-server work has occurred. Launch waits for a complete reviewed passing clean control.

## Current standing owner authorization

At reconciliation `2026-09-04T23:07:16Z`, the owner authorized the standing policy in
`UPSTREAM_WARNING_POLICY.md`: all warnings exclusively from verified-unchanged pinned
upstream source are non-fatal and fully visible. Project-owned warnings remain fatal.
This resolves the earlier owner-decision blocker without passing either failed run.
The revised judge `6f0582572ceb1c0a16c4234fd6b97e896d3cf0ed` is published.
Clean `33929246418` and tamper `33929247980` were dispatched at 23:22 UTC.
Practical completes its exact-revision check concurrently; Reviewer inspects the full clean
gate. All required evidence must pass before launch.
No approval is needed for additional qualifying upstream warnings. Resolve ordinary
in-scope defects autonomously. Do not add new prelaunch review, cleanup, hardening,
test expansion or policy gates. Once the existing minimum gate passes with required
reviewed evidence, record actual launch timestamps and begin both selected projects
immediately. Every sprint timestamp remains UNSET until then.

## Director launch instructions

At launch:

1. Determine the current wall-clock time.
2. Record START in UTC and America/New_York.
3. Calculate +24h, +30h, and +36h timestamps.
4. Set `STATUS=RUNNING` and `CURRENT_PHASE=BUILD`.
5. Commit the timestamped state before substantial implementation starts.
6. Keep this file sufficiently current that another agent can recover mission state after interruption.

Do not reset the sprint clock after launch merely because an agent restarts or loses context.

## Phase transitions

At or after each recorded boundary, the Director must change `CURRENT_PHASE` accordingly:

```text
BUILD
CONVERGENCE
HARVEST
COMPLETE
```

The clock, not subjective project readiness, controls the latest permissible phase.
