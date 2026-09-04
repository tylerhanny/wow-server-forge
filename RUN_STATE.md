# WoW Server Forge — Run State

Status: `ARMED_NOT_STARTED`

The 36-hour sprint has NOT started yet.

The Director must record the launch timestamps immediately before sprint implementation begins.

## Launch record

```text
STATUS=ARMED_NOT_STARTED
EXECUTION_STATUS=ACTIVE_PRELAUNCH
BLOCKER_IDENTIFIED_UTC=2026-09-04T21:00:08Z
OWNER_EXCEPTION_RECONCILED_UTC=2026-09-04T21:16:15Z
OWNER_EXCEPTION_POLICY=UPSTREAM_WARNING_EXCEPTION.md
PAUSE_UTC=2026-09-04T19:56:13Z
RESUME_UTC=2026-09-04T20:10:30Z
RESUME_POLICY=AUTONOMOUS_CONTINUATION_AUTHORIZED
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
| Director | Persistent orchestrator | Exact owner exception authority, independent audit and fresh controls | main | PRELAUNCH |
| Practical | Internal Practical Builder | Hunt Rhythm selected; complete solo design approved; awaits launch | lane/practical / .worktrees/practical | PRELAUNCH |
| Wildcard | Internal AI Auteur / Flagship Gameplay | Stormwright chosen after both floors; complete Solo Pilot mandatory; awaits launch | lane/wildcard / .worktrees/wildcard | PRELAUNCH |
| Reviewer | Independent internal Reviewer / Closer | Protected exact-warning allowlist and judge revision under explicit owner authorization | lane/reviewer / .worktrees/reviewer | PRELAUNCH |

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

## Previous blocker and explicit owner resolution

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

The heartbeat remains ACTIVE and autonomous PRELAUNCH has resumed. Both launch selections
are preserved, all timestamps remain UNSET, and no live-server work has occurred. The old
run remains failed. Launch waits for the new complete reviewed evidence, not the policy edit.

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
