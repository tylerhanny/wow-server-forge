# Director recovery and launch procedure

## Current controls after disposable Playerbots startup-fixture correction

Clean `33941967266` passed full compile, authorized fixture restoration, dependency
integrity, install, SQL, runtime preparation and authserver dry-run. Worldserver reached
Playerbots startup, generated 100 accounts / 1000 characters, then waited for the character
database queue. It exceeded both nominal five-minute dry-run timeouts. A normal cancellation
preserved its artifacts; world completion, unit execution and final integrity did not pass.
The run remains CANCELLED, with exact evidence in `prelaunch/evidence/sql-repair-controls.json`
and `prelaunch/clean-control-playerbots-population-stall.md`.

Reviewer correction `ed2357393262a97b9bf30ce3b6e6eb3378326e02`, independently approved by
Practical and Director, is published as judge `dd283819da03e9ccbebdf9378b5fe3f1cf016380`.
Only installed disposable `playerbots.conf` gets the supported enabled/zero-population
fixture: Enabled=1, RandomBotAutologin=0, MinRandomBots=0, MaxRandomBots=0,
RandomBotAccountCount=0 (AUTO), AddClassAccountPoolSize=0. Effective settings are retained
in the existing artifact. Both five-minute limits remain, with kill-after=30s to terminate
the observed TERM-resistant startup wait. Production/dependency source, pins, all tests,
initialization/smoke sentinels, error checks and final integrity requirements are unchanged.

Fresh clean `33947235843` and authority-tamper `33947239092` are running against the same
frozen candidates. Current exact evidence is `prelaunch/evidence/startup-fixture-controls.json`.
All sprint timestamps remain UNSET. Complete only these existing controls and required
independent evidence review, then record the actual 36-hour clock and begin both selected
projects immediately. Earlier pairs below are historical, never retroactive successes.


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
