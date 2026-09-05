# Standing upstream-warning policy — explicit owner authority

**Owner-authorized on 2026-09-04. Protected default-branch validation policy.**

The owner explicitly authorized warnings originating exclusively from verified-unchanged
pinned AzerothCore and Playerbots source to be non-fatal and fully visible. This is standing
authorization: additional qualifying upstream warnings do not require another approval.
This policy supersedes the single-diagnostic limit in `UPSTREAM_WARNING_EXCEPTION.md`,
which remains a historical record. Earlier failed runs remain failed.

## Required enforcement

1. The independent default-branch judge owns the policy, provenance checks, compiler
   integration and complete-log classification. Candidates cannot change these inputs.
2. Keep AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots
   `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. Verify exact commits, tracked-file/blob
   identities and unchanged raw bytes before granting upstream warning treatment.
   Neither dependency source nor either pin may be changed.
3. Every project-owned warning remains fatal, including candidate source, headers and
   macro definitions, whether compiled from `candidate/projects/<project>` or the staged
   module. A warning cannot inherit upstream status merely from its translation unit,
   printed path, copied text or location remapping. Unknown or ambiguous provenance fails.
4. Preserve `WITH_WARNINGS=ON` and warnings-as-errors for project code. Compiler demotion
   must be mechanically bounded by verified upstream provenance and independent log
   enforcement. Do not hide warnings or waive actual compiler errors. Existing native
   upstream build conventions remain identifiable; no new warning suppression is authorized.
5. Capture complete build stdout and stderr, process outcome and log integrity. Classify
   every warning against verified source identity, including relevant diagnostic origin
   notes. Preserve every allowed upstream diagnostic visibly in artifacts and the job
   summary, without a one-warning count limit or a category-only global waiver.
6. Verify both dependency trees remain byte-for-byte Git-clean after compilation and
   preserve subsequent integrity checks. A failed or incomplete build cannot pass.
7. Retain every existing configure, full compile, install, config, SQL/data, dependency
   integrity, runtime, authserver/worldserver dry-run, unit-test and tamper-control
   requirement. No candidate success or repaired dependency is implied by this amendment.

The implementation may conservatively fail a compilation when an upstream-header warning
is promoted to an error inside a project translation unit. If encountered, resolve that
warning within this standing authorization while preserving project warning failures;
the upstream warning itself is not grounds to ask the owner for another exception.
Candidate build hooks retain the existing independent source-review requirement.

## Exact owner-authorized WorldMock test-fixture exception

`WORLDMOCK_FIXTURE_EXCEPTION.md` records the owner's 2026-09-05 authorization for only
an exact hash-checked two-method correction to the pinned WorldMock test fixture inside
disposable CI. The modified fixture must never be committed, installed, or persisted
outside that environment. Record the exact patch and before/after identities; all production
source, pins, tests/assertions/coverage and remaining gates stay unchanged. This explicit
exception supersedes unchanged-source language only for that precise temporary fixture
delta. It does not permit any other upstream modification or mislabel modified code as
verified-unchanged upstream. Immediately rerun the two existing controls, then launch on
complete required evidence without additional prelaunch gates.

## Immediate prelaunch completion

Apply this amendment, complete the already-required independent review, and rerun the
tamper and legitimate clean controls against the revised default-branch judge. Tampering
must be rejected and the clean control must pass the complete existing gate with reviewed
candidate, judge, pin and artifact evidence. Then record the actual 36-hour clock and
launch immediately. Do not add new prelaunch review, cleanup, hardening, test expansion
or policy gates. Archival housekeeping must not delay launch.

Resolve other blockers autonomously within already-authorized scope. Stop only when a
genuine blocker requires a new prohibited action, dependency/source modification,
destructive operation, credentials/human intervention or material scope/policy change.
All deadline, isolation, One-Human Playability and AI Auteur requirements remain binding.
