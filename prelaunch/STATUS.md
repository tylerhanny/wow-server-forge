# Prelaunch validation record

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

The sprint remains **ARMED_NOT_STARTED**. No timestamps have been started.

**Current disposition: ACTIVE PRELAUNCH.** The exact fixture correction is explicitly
authorized; the existing controls must rerun against the revised protected judge.

The records below describe earlier judges and their then-current warning policies.
Those failed runs remain failed; the standing policy supersedes their warning restrictions.

## Current standing-policy controls

Judge `6f0582572ceb1c0a16c4234fd6b97e896d3cf0ed` integrates Reviewer implementation
`e7afa692992b2fcaaef885d1c4473e9fa4352616` and independently approved workflow
`d31e425a3fa6bd731a180c171727730219d8760a`. Local regressions: 15 passed;
the real Ubuntu compiler probe passed in the completed clean workflow.
Practical APPROVED the exact committed implementation/workflow: all 35 existing independent
cases passed, including the alias/generated-header checks. No outstanding source finding.

- Clean: [33929246418](https://github.com/tylerhanny/wow-server-forge/actions/runs/33929246418),
  frozen candidate `87b822fd41bb6013358aa6f5e16ca252ad79761c`, FAIL at full build;
  pinned WorldMock lacks two overrides. Required later install/runtime/unit stages skipped.
- Authority tamper: [33929247980](https://github.com/tylerhanny/wow-server-forge/actions/runs/33929247980),
  frozen candidate `2d74a0b1599313a9b09c7baf5b961d3744f48ed6`, REJECTED at scope
  before dependency checkout/build. Director verified exact candidate/judge/pins/protected
  artifact hashes and actual rejection log: `prelaunch/evidence/tamper-33929247980.txt`.

Exact protected hashes and dispositions: `prelaunch/evidence/standing-policy-controls.json`.
No new external control or launch gate was added. Start the clock immediately once these
existing controls and required independent evidence review pass. Source review and local
tests do not establish a passing complete build or runtime gate.

## Historical exact-warning policy — controls

Reviewed judge `78a5da6d5aed19a932fae53e74226ac5afc2e204` integrates Reviewer source
`2e73998349c65dc442b7fed3008d0df0e007bb29`. Its workflow Git-blob SHA-256 is
`5c792e61941d16578567499891d46047bab5248bee2bc5bd8962eb6c5c21a7a2`.
Practical independently exported the exact committed bytes and passed all 73 adversarial
cases; Director reviewed preservation of the default-branch scope and later mandatory gates.
Wildcard independently checked owner-requirement traceability. These are source/test reviews,
not full pinned-build or runtime success. The actual Ubuntu compiler-scope probe is mandatory
in CI, followed by the complete pinned configure/build/install/config/SQL/integrity/dry-run/unit gate.

All three explicit dispatches use this same reviewed default-branch judge:

| Control | Exact candidate | Run | Current evidence |
|---|---|---|---|
| Legitimate clean module | `87b822fd41bb6013358aa6f5e16ca252ad79761c` | [33922537362](https://github.com/tylerhanny/wow-server-forge/actions/runs/33922537362) | FAIL at compile 2026-09-04T22:33:12Z on two new upstream diagnostics; later install/runtime/unit stages skipped |
| Existing locked-authority tamper | `2d74a0b1599313a9b09c7baf5b961d3744f48ed6` | [33922543117](https://github.com/tylerhanny/wow-server-forge/actions/runs/33922543117) | REJECTED at scope 2026-09-04T21:45:42Z, before dependency checkout/build |
| Protected warning-allowlist tamper | `697f4d4d0467171fe55036c9de4c3cb5e8cf0912` | [33922549107](https://github.com/tylerhanny/wow-server-forge/actions/runs/33922549107) | REJECTED at scope 2026-09-04T21:45:49Z, before dependency checkout/build |

The new negative control changes only `validation/upstream-warning-allowlist.json` from
expected count 1 to 2 on its disposable candidate branch. Main retains count 1. Both negative
controls were rejected for their intended scope violations. Director downloaded both artifacts
and verified exact candidate/judge/pin/protected-file hash identities; excerpts and metadata are
in `prelaunch/evidence/tamper-33922543117.txt`, `tamper-33922549107.txt`, and
`owner-exception-controls.json`. The old failed clean run below remains failed.
The exact-warning policy is an owner-authorized upstream baseline exception, not a dependency
repair, gameplay candidate, or completed PRELAUNCH. Every sprint timestamp remains UNSET.

The actual Ubuntu preflight passed all 17 tests, including the real compiler probe showing
candidate unused parameters remain fatal. Configure and actual compile-command provenance
passed. During the full build, BTHelpers107 emitted its single authorized warning, then new
fatal unused `botAI` diagnostics appeared in `Hyjal/Util/HyjalHelpers.cpp:168:61`
(`GetKazrogalTankPositionState`) and `Hyjal/Util/HyjalScripts.cpp:39:63`
(`ShouldInterruptForArchimondeAirBurst`). Both sources and command scope were independently
verified by Reviewer and Practical. The complete build capture has exit 2, stream/file SHA-256
`7f5b632de2e4532218fc907542b4ca2832d5e46a701e2761cbd0186096598fcf`, and equal pre/post
dependency identity/Git-clean checks. The wrapper performed those checks even though later
standalone integrity stages were skipped. Artifact `9956799024` and detailed Director audit
are recorded in `prelaunch/evidence/clean-33922537362-director-audit.json`.

The owner explicitly designated every additional warning a fresh blocker. Do not waive these,
rerun the same known-failing build, edit dependencies/pins, or launch. Another unused parameter
at HyjalHelpers209 is source-only evidence, not an observed CI diagnostic; pinned
`-Wfatal-errors` makes this an incomplete inventory. The separately reviewed reporting
correction at validation revision `5269391` preserves observed warning/error text in future
FAIL summaries without changing acceptance. Practical passed 17 independent checks;
Director replayed the real failed artifact without modifying it. Details and evidence limits:
`prelaunch/failure-summary-reporting-review.md`. No identical failed clean run was repeated.
Both final reporting-revision negative controls also rejected scope tampering before build:
`33927009741` at `2026-09-04T22:48:22Z` and `33927019176` at `2026-09-04T22:48:27Z`,
both under exact judge `5269391836586137f983d79122ad9dd8a09fa1fd`. Director verified their
candidate/judge/pin/protected-file hashes and actual rejection logs. Evidence:
`prelaunch/evidence/reporting-revision-negative-controls.json` and matching log excerpts.

## Infrastructure

- Repository cloned into the selected project directory itself.
- `.worktrees/` and `.forge-local/` are ignored on main (`5160975`).
- Isolated lane worktrees created for Practical, Wildcard, and Reviewer.
- GitHub CLI access confirmed; `Official Candidate Gate` is active (workflow ID `350442956`).
- No live server or Adventure Nexus access performed.

## Assigned prelaunch work

| Owner | Assignment | State |
|---|---|---|
| Director | Preserve complete authorized work and new upstream blockers | Owner decision required; clock unset |
| Practical | Hunt Rhythm one-human reassessment | Proposal approved; awaits launch |
| Reviewer | Protected judge, full failed-control evidence and reporting correction | Independent reviews complete; fresh upstream blockers |
| Wildcard | Three-shortlist one-human paths and final creative choice | Stormwright selected; awaits launch |

## Required launch evidence

- New one-human authority control: **REJECTED as required** by the unchanged official judge.
  - Candidate `813e433cfb69b37a7f56e6db55a58a2d410c6add` modified only locked
    `ONE_HUMAN_PLAYABILITY.md`; scope rejected it at `2026-09-04T20:16:57Z` before build.
  - Run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33915425037
  - Judge `7317977b3619e6984f76fb8bcd7c25b0af0610d1`, workflow hash
    `c7ce13faa48f8336b3b3c161e5ab202c717e7eaf4b1308ece56b147542ee6e81`.
  - Evidence: `prelaunch/evidence/one-human-tamper-control.json` and matching run log excerpt.
  - No workflow change or interruption of the clean control was needed.

- Tampering control: **REJECTED as required** by the default-branch judge.
  - Candidate: `2d74a0b1599313a9b09c7baf5b961d3744f48ed6` (`project/forge-smoke-tamper`).
  - Judge commit: `516097591614c2df9c401b3283f60a24e6cb2e05`.
  - Run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33910753708
  - At `2026-09-04T19:21:49Z`, the integrity step rejected the deliberate `VALIDATION_INTEGRITY.md` change with exit code 1, before dependency checkout/build.
  - Log excerpt: `prelaunch/evidence/tamper-33910753708.txt`.
- Tampering control after Reviewer repair: **REJECTED as required**.
  - Same tamper candidate `2d74a0b1599313a9b09c7baf5b961d3744f48ed6`.
  - Judge `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b`.
  - Run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33911649850
  - Actual authority rejection retained in `prelaunch/evidence/tamper-33911649850.txt`.
- Clean control configure/compile/install/immutability/config/runtime: **FAILED AT COMPILE; diagnosis active**.
  - Candidate: `87b822fd41bb6013358aa6f5e16ca252ad79761c` (`project/forge-smoke-clean`).
  - Initial judge: `283b0d4d063458cb4db6f1fa81d314ad8a82f080`.
  - Initial run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33911309528
  - Initial run passed configure, then was **CANCELLED** during compile because the
    independent source audit proved the fourth database fixture was missing. It is
    not accepted as compile/runtime success.
  - Corrected judge: `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b`.
  - Corrected run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33911646203
  - Actual result: compilation failed at `2026-09-04T20:56:03Z` with exit 2.
    The compile step ran from `19:35:06Z` to `20:56:03Z`; configure/discovery passed.
    Post-build immutability, install, SQL/data, DB fixture, dry-runs and unit tests were skipped.
    Log artifacts were preserved. The failure is an unused `botAI` parameter at pinned
    Playerbots `src/Ai/Raid/BT/BTHelpers.cpp:107:60`, fatal under `-Werror`.
    Independent audits found no candidate-induced build change or supported-toolchain fix.
  - Expected dry-run proof: `FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159`.
- Reviewer disposition of run `33911646203`: **FAIL; blocked under the then-current contract**.
  - Full evidence and alternatives: `prelaunch/clean-control-compile-blocker.md`, Reviewer
    source commit `ec81c2e`. Candidate/judge/pins and extracted build-log hash were also
    independently checked by Director against the downloaded official artifact.
  - Practical's frozen smoke-origin audit: **PASS isolation**, five regular project/handoff
    files only, no build hooks, flags, warning pragmas, header shadows or dependency mutation.
    This does not imply a passing build.

The historical execution disposition was BLOCKED_NEW_UPSTREAM_DIAGNOSTICS. That owner
policy conflict is now resolved by `UPSTREAM_WARNING_POLICY.md`; revised control results
are pending. The skipped install/runtime/unit stages from failed run `33922537362` remain
unproven. No dependency repair or candidate success is claimed.

At pause the corrected clean run had passed scope/discovery/configure and was still compiling.
It has now failed compilation. No full compile/install/runtime/unit-test success is claimed.
The earlier proposed missing-schema error-file defect was independently disproved in
`prelaunch/first-start-log-routing-review.md`; no fixture/judge change was made for it.

Reviewer repair rationale and exact source evidence: `prelaunch/reviewer-audit.md`.
The repair preserves both dependency pins and warnings-as-errors, adds the missing
Playerbots disposable DB connection, and strengthens recorded judge, loader, test,
dependency and runtime evidence. No acceptance requirement was weakened.

## Prepared launch choices (research only)

- Practical: `mod-hunt-rhythm`, opt-in outdoor kill-XP rhythm, bounded to a small
  bonus with no SQL or persistent economy. Proposal: `notes/practical-first-project.md`.
- Wildcard: **Stormwright selected for launch after the completed tournament**. The owner rejected The Small Council;
  it is preserved only in `IDEA_VAULT.md`. The AI Auteur tournament requires at least five
  mechanically distinct concepts, a shortlist of three evaluated by Director and Reviewer,
  then Wildcard's choice among passing options. See `WILDCARD_AUTEUR.md`.
  - Completed comparison: `prelaunch/wildcard-quality-pass-1.md` (source lane commit
    `ad264556c8fd688ea462ead3ab7ece753f142819`).
  - Shortlist: Stormwright, Holdfast, Warband Arena. Wildcard preference: Stormwright.
  - Director comparison: `decisions/initial-project-selection.md`.
  - Independent dispositions: `prelaunch/reviewer-one-human-dispositions.md`, source `0aa6e58`.
  - Wildcard final choice: `prelaunch/wildcard-final-choice.md`, source `fded6b8`.
  - All four assessed concepts passed the one-human proposal floor; Stormwright is the
    selected flagship, Holdfast deferred fallback, Warband deferred for comparative closure risk.
  - Independent asset findings: `prelaunch/stormwright-visual-audit.md` (source lane
    commit `e9a5fba`). These are source/data findings, not client gameplay validation.
- These are distinct prospective assignments, not started projects or harvest entries.

Every current/future project must also pass locked `ONE_HUMAN_PLAYABILITY.md`. No current
concept is automatically accepted or rejected. Full human/bot roles, scaling, no-bots behavior
and complete loop have independent proposal dispositions; real bot feel remains pending live tests.

Practical independently audited one-human propagation at main
`2cc3ae60e4607dc0879194a598884128c3e25021`: **PASS, no omissions** across the dedicated
authority, AGENTS, mission, team protocol, Auteur standard, all four role charters, proposal
requirements, finish gate and handoff template. This read-only audit did not change the judge.

Disposable controls are infrastructure tests and do not count as Forge projects.
Launch remains forbidden until the rejected tamper and passing clean control are recorded here with exact SHAs and run URLs.

## Continuity

Task heartbeat: `wow-forge-director-continuity`, **ACTIVE after explicit owner resume**;
15-minute interval, with the mandatory one-human policy included. No duplicate was created.
Recovery procedure: `prelaunch/RECOVERY.md`.

The Director manages internal subagents; separate user-created worker chats are not required.
Every resume must fetch safely and reconcile branch/CI evidence before acting. Any automated
wake-up must preserve the unset clock until both controls are proven, and never extend a
recorded deadline after launch.
