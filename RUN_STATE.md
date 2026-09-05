# WoW Server Forge — Run State

Implementation started at 2026-09-05T06:40:42Z after control33947235843 reached terminal
SUCCESS. Required artifact review also passed independently. The fixed provisional
deadline remains2026-09-06T18:34:32Z; it was not reset at implementation start.

```text
STATUS=RUNNING
EXECUTION_STATUS=AUTONOMOUS_IMPLEMENTATION_AND_VALIDATION
CURRENT_PHASE=BUILD
IMPLEMENTATION_PERMISSION=GRANTED_OWNER_TERMINAL_RESULT_DIRECTIVE
IMPLEMENTATION_STATUS=ACTIVE
DIRECTIVE_RECEIVED_UTC=2026-09-05T06:34:32Z
DIRECTIVE_RECEIVED_AMERICA_NEW_YORK=2026-09-05T02:34:32-04:00
DEADLINE_BASIS=PROVISIONAL_OWNER_RECEIPT_PLUS_36H
CONFIRMED_ACCESS_CUTOFF_UTC=UNKNOWN
START_UTC=2026-09-05T06:40:42Z
START_AMERICA_NEW_YORK=2026-09-05T02:40:42-04:00
FEATURE_FREEZE_UTC=2026-09-06T06:34:32Z
FEATURE_FREEZE_AMERICA_NEW_YORK=2026-09-06T02:34:32-04:00
CANDIDATE_HANDOFF_UTC=2026-09-06T12:34:32Z
CANDIDATE_HANDOFF_AMERICA_NEW_YORK=2026-09-06T08:34:32-04:00
OWNER_TESTING_START_UTC=2026-09-06T12:34:32Z
OWNER_TESTING_END_UTC=2026-09-06T18:34:32Z
PRIMARY_MODULES_INDEPENDENTLY_ACCEPTED=NO
ADDITIONAL_PROJECT_WINDOW_REVIEW=NOT_GRANTED
HARD_DEADLINE_UTC=2026-09-06T18:34:32Z
HARD_DEADLINE_AMERICA_NEW_YORK=2026-09-06T14:34:32-04:00
HEARTBEAT_STATUS=ACTIVE
REVIEWED_JUDGE_SHA=dd283819da03e9ccbebdf9378b5fe3f1cf016380
CLEAN_CONTROL_RUN=33947235843
AUTHORITY_TAMPER_RUN=33947239092
TAMPER_CONTROL_REVIEW=PASS_REJECTED_BEFORE_BUILD
CLEAN_CONTROL_REVIEW=PASS_COMPLETE_EXISTING_GATE
VALIDATION_STATUS=HUNT_RHYTHM_AND_FIELD_CAMP_ACCEPTED_STORMWRIGHT_PENDING
STANDING_WARNING_POLICY=UPSTREAM_WARNING_POLICY.md
WORLDMOCK_FIXTURE_EXCEPTION=WORLDMOCK_FIXTURE_EXCEPTION.md
```

## Recorded implementation transition

Current run33947235843 is terminal SUCCESS. Both approved builders begin
actual module source now. Prelaunch evidence review passed; candidate review and validation continue
concurrently. No new full control may idle both lanes. Preserve existing start and deadlines.

| Lane | Project | Branch/worktree | State |
|---|---|---|---|
| Director | Fixed deadline and persistent orchestration | main | Active orchestration and independent closure |
| Practical | Hunt Rhythm / mod-hunt-rhythm | project/hunt-rhythm / .worktrees/practical | READY FOR LIVE TEST at4aaa3ae; delivered early; available for owner feedback |
| Practical | Field Camp / mod-field-camp | project/field-camp / .worktrees/field-camp | READY FOR LIVE TEST at796e27e; delivered early; remains subordinate |
| Wildcard | Stormwright / mod-stormwright | project/stormwright / .worktrees/wildcard | Correcting logger documentation after runtime-fixture failure; source remains frozen; primary priority |
| Reviewer | Official harness and independent candidate review | lane/reviewer / .worktrees/reviewer | Independent evidence/source review and concurrent validation |

The completed selection, creative ownership and one-human approvals are in
`decisions/initial-project-selection.md`, `prelaunch/wildcard-final-choice.md` and
`prelaunch/reviewer-one-human-dispositions.md`. No new tournament is needed for these scopes.

## Fixed calendar and acceptance

The latest owner schedule amendment supersedes the old internal convergence/harvest split.
Keep all current builders/runs active. Hunt Rhythm is the primary Practical candidate;
Stormwright is the primary Wildcard candidate. Field Camp proceeds only while it does not
threaten either primary's completion, validation, documentation or early delivery. No project
beyond this active set starts unless both primaries are independently accepted and Director
records that it cannot threaten the protected owner window.

At FEATURE_FREEZE (2026-09-06 02:34:32 America/New_York), no new projects or optional
features: finish, cut, validate, fix, document and package existing work only. By
CANDIDATE_HANDOFF (08:34:32), deliver every available READY FOR LIVE TEST module with
exact install/config/SQL/rollback, one-human smoke steps, commands/NPCs/flow/logs and honest
verified-versus-pending status. Deliver each ready module early; never hold one for another.
The final six hours, 08:34:32–14:34:32, are OWNER_TESTING: reserve capacity for Tyler's
installation/playtesting feedback, bug diagnosis/fixes, independent re-review and changed-
candidate revalidation. No new projects or optional features. Hard deadline is unchanged.
Actual access cutoff remains unknown; never extend the ceiling or lower acceptance.
Use tools/Get-ForgePhase.ps1 on every resume; preserve actual START and fixed timestamps.

Every exact harvest candidate still needs official real compile/link, install, config/data/SQL,
startup, tests, dependency integrity and independent review. DEVELOPMENT-ONLY checks are
not acceptance. Live gameplay and bot competence remain pending manual validation.
All live-server/Adventure Nexus/source/pin prohibitions, visible upstream warnings,
project-owned warnings-as-errors and exact disposable WorldMock exception remain binding.

## Evidence and continuity

Current exact pair/evidence: `prelaunch/evidence/startup-fixture-controls.json`.
Historical failed/cancelled controls remain preserved in `prelaunch/STATUS.md`, its linked
audits/manifests, and Git history through50ac30e. They are never retroactive successes.
The owner sequencing amendment in AGENTS.md and DEADLINE.md supersedes historical
prelaunch launch-prerequisite language in those records. The existing15-minute heartbeat
remains active; report meaningful transitions/results, not unchanged compile status.

Complete prelaunch evidence and native test-skip disclosure: `prelaunch/clean-control-final-pass.md`.
This certifies only the control. Hunt Rhythm's separate candidate acceptance is recorded below;
Field Camp also has separate candidate acceptance below; Stormwright remains pending its
actual result and independent evidence review.

Hunt Rhythm candidate `4aaa3ae188e7bcdba2569676911e14142ac378e2` is **READY FOR LIVE TEST**.
Official run `33951428776` passed every required stage at2026-09-05T08:05:00Z under judge
`e35e85a787d7576d58cb691f6335b638ee8bc342`; independent source, one-human and actual
artifact review all PASS. Director delivered its exact source ZIP and installation/test/rollback
guide immediately, without waiting for the other candidates. Final attestation is
`handoffs/mod-hunt-rhythm.md`; evidence is `deliveries/evidence/mod-hunt-rhythm-33951428776.json`.
The exact tested project tree is integrated on main without source/config/SQL changes.
The early download is published at GitHub release `mod-hunt-rhythm-v1`, targeting that
exact candidate; uploaded source ZIP SHA256 matches the independently packaged archive.
Gameplay/XP/class/pet/bot behavior remains PENDING LIVE/IN-GAME VALIDATION. Practical is
available for findings; no further project is allowed until both primary modules are accepted
and Director records that it cannot threaten the protected owner testing window.

Stormwright candidate `a1558178ceee2b92e020928ecb8fd3f59c3c34a2` is frozen; independent
source/one-human review passed, with source/SQL/config/tests identical to reviewed `c1f3926`.
Official run `33952393192` uses judge `aea0f034d9e4767e96891fdf24c6260cd959218f`.
It includes the independently approved normal-startup evidence required by Stormwright's
OnStartup hook, on the same already-built disposable server after existing checks.
That run FAILED full compilation: project SendPlaySpellImpact call omitted the required
pinned GUID argument. Install/SQL/runtime/unit/supplemental stages did not run. Wildcard
owns the minimal project API repair and independent re-review; no dependency or judge
change is authorized. Independently reviewed repair
`a65f162419c8d0c0cc1ddbad2f35b7b4450018c8` supplies each intended owned actor's GUID to
the three impact packet calls, with no gameplay/rules/SQL/config/test changes. Final
docs-only freeze `bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc` is under official run
`33955586542`, judge `8b87494de0261cd82c48c4a0dc11895611fb9d39`. It retains the complete
gate and required supplemental normal-startup checks. That second run passed full build,
install, both dry-runs, units, executable rules, owned SQL and terrain preparation, but
FAILED its five-minute supplemental observation: the fixture incorrectly set module
logging to3, suppressing required INFO output. Exact pinned logging defines WARN=3/INFO=4,
with native module default4 already enabling INFO. Normal server ready was observed;
registrar spawning was not observed and cannot be inferred. Final runtime integrity/cache
save were skipped. Reviewer owns a separate one-line fixture3-to4 correction; Wildcard
corrects the same mistaken README advice in a docs-only candidate for one required full
rerun. No source/gameplay/SQL/config change, removed check or extra control is authorized.
Preserve both failed runs/packages as historical and unreleased.
No extra control was launched. Field Camp original `ec9eea979c9344853aaf02d46ba9f6632636254b` had independent
source/one-human PASS with source/config identical to reviewed `b1b8417`. Its official
run `33952603462` used judge `e7a37fa` and FAILED full compilation: FieldCamp.cpp called
private pinned `Player::HasDelayedTeleport`. This is a project API error; install/runtime/
unit stages were skipped and no acceptance is claimed. Independently reviewed repair
`6ce52323b96be5dba4f4dfea5668032d17acdc3a` removes only the redundant private call;
the retained public IsBeingTeleported predicate covers both delayed near/far semaphores.
Final docs-only freeze `796e27e9cfcd05f4c4e4c627e26834ea7be72155` is **READY FOR LIVE TEST**:
official run `33955341216`, judge `1ea9a4b3671c763b286f681e983e9499c7cb35af`, completed
SUCCESS at 2026-09-05T10:07:34Z. Independent source/one-human/actual-artifact review PASS.
The exact source is integrated unchanged and its ZIP/owner guide were delivered early.
GitHub release `mod-field-camp-v1` targets that exact candidate and provides the module,
guide and evidence; the uploaded ZIP digest matches the verified package.
Final attestation/evidence: `handoffs/mod-field-camp.md` and
`deliveries/evidence/mod-field-camp-33955341216.json`. The old failure/package remain
historical and unreleased. Field Camp remains subordinate to both primaries; actual client
landing, terrain, pets and bots remain PENDING LIVE/IN-GAME VALIDATION.

The owner directly authorized publishing reviewed cache revision
`03002fb6c347925e10d08b6c741194f8569174dc`; its unchanged cherry-pick is `332eece`.
The earlier tool-approval block is resolved. Hunt Rhythm run33951428776 completed under
its original judge. Observe cache effectiveness only on required real-candidate runs.
An actual dispatch HTTP422 exposed invalid job-level runner.temp expressions. Independently
reviewed correction `aea0f034` exports the identical paths through GITHUB_ENV at step scope;
the failed request created no run. Stormwright's required run now exercises the cache.
All acceptance checks, source/pin protections and WorldMock exception boundaries remain.
Field Camp's successful repair run observed a cold restore MISS, 1,829 cacheable misses,
zero hits and successful save, with approved effective config. Compile took 95m05s versus
Hunt's58m54s. This demonstrates use/save, not acceleration or cached-warning replay;
do not infer a cause from the timing difference or launch a cache-only control.

Owner installation/config/SQL/rollback and one-human test guides are in `deliveries/`.
Hunt Rhythm and Field Camp guides and exact source ZIPs are delivered; Stormwright remains
pending actual acceptance. Source ZIPs in ignored `.forge-local/deliveries/` have been checked file-by-file
against the frozen Git blobs. The four completed disposable smoke branch refs were archived
under `forge-controls/2026-09-05/*` tags with evidence in
`prelaunch/evidence/control-archive.json`; no active candidate/run was affected.

Current prepared, unreleased repair package: Stormwright `mod-stormwright-bde390e.zip`,
SHA256 `32b64076275458e7467ec418d4d439743ae49443dce41c540272caf46dcb996e`;
Delivered Field Camp `mod-field-camp-796e27e.zip`, SHA256
`0afa0e660d14a247776dad777d1ada8e7d4ecfa780b8b5885f7d4388d56bf8bf`.
Their file blobs match their exact frozen commits; that packaging check is not compilation
or acceptance. Earlier failed archives remain historical and unreleased. The existing
continuity heartbeat now records Hunt's delivery and directs recovery to these current run
bindings, preserving every deadline and avoiding superseded candidate restarts.

Owner guide correction: retain native `Logger.module=4,Console Server` (INFO=4, WARN=3).
Earlier advice to set3 suppressed INFO and was incorrect. All external guides are corrected;
Field Camp's final handoff explicitly supersedes its frozen README's false default-threshold
claim. Independent Reviewer approved this observation-guidance correction: both accepted
project trees remain unchanged and their actual successful runs used the native setting.
