# Director recovery and launch procedure

The durable user mandate is in the repository authorities and this task. Internal workers
are approved and preferred; never wait for Tyler to create separate lane tasks.

## Resume

The owner explicitly resumed after the `2026-09-04T19:56:13Z` pause. At resume reconciliation
`2026-09-04T20:10:30Z`, clean-control run `33911646203` was still compiling. The clock remains
unstarted. Continue prelaunch and enforce locked `ONE_HUMAN_PLAYABILITY.md` across all lanes.
The run subsequently failed compilation at `2026-09-04T20:56:03Z`; independent diagnosis
found an immutable pinned Playerbots unused-parameter/warnings-as-errors conflict. Later
install/runtime/unit-test steps did not run. Current state is BLOCKED_PRELAUNCH_OWNER_DECISION:
do not repeat the same known-failing build or infer any warning/dependency exception. Resume
validation after an explicit owner decision or new evidence resolves the conflict. Do not
resurrect the disproved first-start log-routing inference.

1. Stay inside this project boundary. Fetch origin without overwriting unexplained work.
2. Read `AGENTS.md`, `VALIDATION_INTEGRITY.md`, `TEAM_PROTOCOL.md`, `RUN_STATE.md`,
   `ONE_HUMAN_PLAYABILITY.md`, `prelaunch/STATUS.md`, and applicable handoffs.
3. Inspect `git worktree list`, worker status/branches and external Actions runs.
   Run `./tools/Get-ForgePhase.ps1` for a read-only phase calculation from recorded
   timestamps. It rejects malformed/reset boundary intervals and never changes state.
4. Reuse or replace internal lane workers with concrete bounded assignments. Do not
   overlap project ownership. Reviewer must remain independent of builders.
   For Wildcard, read `WILDCARD_AUTEUR.md`: five distinct concepts, three shortlisted
   for Director/Reviewer, Wildcard's choice among passing options, and one flagship first.
5. Execute the next repair/build/review action and commit durable evidence.

## Prelaunch exit conditions

- Default-branch `Official Candidate Gate` must reject a deliberately modified authority
  candidate before running candidate code.
- A legitimate `mod-forge-smoke` control must pass the exact applicable configure,
  full compilation, install, immutability, config/data and disposable runtime gates.
- Record full candidate SHA, full judge SHA, run URL, step results and independent
  Reviewer disposition. After judge changes, validate controls against that revision.
- Preserve failure evidence and explain every judge repair separately. Never turn an
  actual candidate failure into green by weakening the judge.
- Archive disposable smoke branches after recording proof; they are not harvest projects.

## Immediate launch

Once all conditions above are actually proven, read the current UTC wall clock and set
START to that time. Derive CONVERGENCE_START at +24 hours, HARVEST_START at +30 hours,
and HARD_DEADLINE at +36 hours. Use ISO-8601 UTC plus America/New_York equivalents.
Set STATUS=RUNNING and CURRENT_PHASE=BUILD, persist distinct initial builder ownership
in `RUN_STATE.md` and `BACKLOG.md`, commit/push main, and dispatch implementation.

Do not reuse prelaunch timestamps, reset the launch later, or delay for user-created chats.
New project branches start from current main, containing only their single project and
matching handoff. Do not carry lane scouting notes or disposable control code into candidates.

## Active sprint

Use actual timestamps to enforce phase. Keep independent Practical and Wildcard work
moving while Reviewer closes candidates. Every final candidate SHA needs an official
gate result and independent review. Gameplay testing remains pending for Tyler.
At +24 hours cut risk and finish winners. At +30 hours start no new projects. At +36 hours
stop feature implementation and classify every attempted project truthfully.

## Scheduled continuity

The task heartbeat `wow-forge-director-continuity` has a configured 15-minute interval.
It was reactivated after the one-human authority and shortlist reviews completed on resume.
Update the existing automation if needed; do not create another. It is a
recovery mechanism, not permission to spend a wake-up only reporting unchanged status.
Pause it after final harvest closure. Never create duplicate continuation automations.
