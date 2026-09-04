# WoW Server Forge — Run State

Status: `ARMED_NOT_STARTED`

The 36-hour sprint has NOT started yet.

The Director must replace this template immediately before autonomous work begins.

## Launch record

```text
STATUS=ARMED_NOT_STARTED
EXECUTION_STATUS=PAUSED_BY_OWNER
PAUSE_UTC=2026-09-04T19:56:13Z
RESUME_POLICY=OWNER_REQUEST_REQUIRED
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
| Director | Persistent orchestrator | Prelaunch checkpoint; await owner resume | main | PAUSED |
| Practical | Internal Practical Builder | Clean control submitted; Hunt Rhythm research only | lane/practical / .worktrees/practical | PAUSED |
| Wildcard | Internal AI Auteur / Flagship Gameplay | Five-concept tournament recorded; final reviews/choice pending | lane/wildcard / .worktrees/wildcard | PAUSED |
| Reviewer | Independent internal Reviewer / Closer | Judge repair/visual audit recorded; final shortlist review pending | lane/reviewer / .worktrees/reviewer | PAUSED |

Prelaunch evidence and next actions are recorded in `prelaunch/STATUS.md`.
Internal worker lanes are managed by the Director; Tyler need not create worker tasks.

## Temporary owner-requested pause

At `2026-09-04T19:56:13Z`, the owner requested a safe temporary pause. Internal workers
and local monitoring are stopped. Heartbeat `wow-forge-director-continuity` is PAUSED.
The already-running external clean-control run `33911646203` is left to finish and preserve
its evidence; last observed stage was full compilation. Do not infer success or launch from
its eventual completion while paused. All sprint timestamps remain UNSET.

Resume only on the owner's instruction. Then inspect that exact run first, reconcile its
evidence and any defects, complete final Auteur comparison/review/choice, and continue
prelaunch. No Wildcard project is currently approved for implementation.

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
