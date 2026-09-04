# WoW Server Forge — Run State

Status: `ARMED_NOT_STARTED`

The 36-hour sprint has NOT started yet.

The Director must replace this template immediately before autonomous work begins.

## Launch record

```text
STATUS=ARMED_NOT_STARTED
EXECUTION_STATUS=ACTIVE_PRELAUNCH
PAUSE_UTC=2026-09-04T19:56:13Z
RESUME_UTC=2026-09-04T20:10:30Z
RESUME_POLICY=AUTONOMOUS_CONTINUATION_AUTHORIZED
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
| Director | Persistent orchestrator | One-human authority, external proof and launch coordination | main | PRELAUNCH |
| Practical | Internal Practical Builder | Hunt Rhythm one-human reassessment; clean control submitted | lane/practical / .worktrees/practical | PRELAUNCH |
| Wildcard | Internal AI Auteur / Flagship Gameplay | One-human reassessment of shortlisted three; final choice pending | lane/wildcard / .worktrees/wildcard | PRELAUNCH |
| Reviewer | Independent internal Reviewer / Closer | Active clean CI; independent one-human and Auteur dispositions | lane/reviewer / .worktrees/reviewer | PRELAUNCH |

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
heartbeat and launch only after all prelaunch requirements pass. No implementation is approved yet.

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
