# Director recovery and launch procedure

## Current resume and prelaunch blocker

Owner explicitly resumed; reconciled 2026-09-05T01:06:37.050300Z. The prior safe pause is lifted.
The existing continuity heartbeat is ACTIVE and stays quiet while this blocker is unchanged.
Practical Hunt Rhythm and Wildcard Stormwright ownership/selections are preserved; neither
implementation nor the 36-hour clock has started. All sprint timestamps remain UNSET.

Tamper run 33929247980 was rejected as required. Clean 33929246418 failed on actual
pinned upstream WorldMock compile errors: missing GetPlayerbotsDBRevision and
AddQueryHolderCallback overrides. Both server targets built, but the required whole build
failed and install/SQL/runtime/unit-test execution were skipped. The standing upstream-warning
policy worked and remains authorized. No additional warning approval is required.

Evidence: `prelaunch/clean-control-pinned-unit-test-blocker.md`, Reviewer source e892081.
The Director independently checked the saved raw build hash/diagnostics and reconciled
GitHub completion at the exact judge SHA. Reviewer found no supported configuration fix preserving the suite. The exact unapplied
two-method proposal is `prelaunch/worldmock-test-fixture-proposal.md` with adjacent patch
(Reviewer source b4724d4); it requires explicit owner authorization for that test-only delta. No dependency/test
source, judge, pin or acceptance requirement has been changed. No identical retry is justified.
Earlier pause/active instructions below are historical; this current disposition controls.

The durable user mandate is in the repository authorities and this task. Internal workers
are approved and preferred; never wait for Tyler to create separate lane tasks.

## Resume

The owner resumed the safe pause and has now supplied standing authorization in
`UPSTREAM_WARNING_POLICY.md`. Warnings exclusively from verified-unchanged pinned
AzerothCore/Playerbots source are non-fatal and fully visible; every project-owned warning
remains fatal. Additional qualifying upstream warnings require no further approval.
The previous full clean runs `33911646203` and `33922537362` remain failed under their
then-current judges. Their evidence is preserved; neither reached install/runtime/unit
success. The owner-decision conflict is resolved, and revised validation is executable.

Complete the already-required independent check of the revised judge, rerun tamper and
complete clean controls immediately, and start the clock as soon as the existing minimum
pre-start gate passes. Do not add prelaunch review, cleanup, hardening, test expansion or
policy gates. Resolve other ordinary in-scope blockers autonomously. Stop only for a real
blocker requiring a new prohibited action, dependency/source modification, destructive
operation, credentials/human intervention or material scope/policy change. The selected
Practical and Wildcard projects are unchanged; implementation begins at formal launch.

1. Stay inside this project boundary. Fetch origin without overwriting unexplained work.
2. Read `AGENTS.md`, `VALIDATION_INTEGRITY.md`, `TEAM_PROTOCOL.md`, `RUN_STATE.md`,
   `ONE_HUMAN_PLAYABILITY.md`, `UPSTREAM_WARNING_POLICY.md`, `prelaunch/STATUS.md`,
   and applicable handoffs.
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
- Disposable smoke branches are not harvest projects. Record their exact identities;
  archival housekeeping must not delay launch and can follow the clock start.

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
