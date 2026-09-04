# Failed-build diagnostic visibility correction

Reviewer source commit: `d9ddae5c5aede205d54278cc18b09b9c34fd7383`.
Integrated validation revision: `5269391836586137f983d79122ad9dd8a09fa1fd`.
Independent Practical disposition: **APPROVE, 17/17 checks** on exact committed bytes.
Director disposition: **APPROVE reporting only**, with independent replay of the actual
retained failed artifact. This does not approve either new upstream diagnostic or pass CI.

The correction adds diagnostic headers and their following source/caret context to FAIL
verdicts. The existing workflow renders that JSON in the job summary. The original FAIL
status and reason remain. Observations never provide acceptance authority; incomplete,
stale, missing, altered or invalid captures are explicitly non-authoritative. No policy,
allowlist, compiler flag, dependency pin, source identity, count check, acceptance-log check,
workflow stage or deadline rule changed.

Practical independently compared syntax trees, removing only the additive FAIL-reporting
attachment/helper, and found existing acceptance/build code unchanged. Its 17 checks covered
actual failed-artifact replay, partial/stale/altered/missing/invalid captures, failed builds,
early identity failures and reporting I/O failures. All preserved the original failure.
Reviewer ran 22 local test methods: 21 passed; the real Linux integration test was not run
locally. The unchanged integration test previously passed in actual run `33922537362`;
that earlier execution must not be described as a fresh test of this reporting revision.

Director separately exported the exact committed verifier, replayed the real failed build
log and receipt, and verified three headers plus context, `VERIFIED_CAPTURE`, and
`acceptance_authority=false`. A changed stream hash became non-authoritative. All original
artifact files remained byte-identical. Evidence:
`prelaunch/evidence/failed-summary-reporting-replay.json`.
This is **local reporting replay, not a CI rerun or a replacement gate**.

Git-blob SHA-256 identities:

- `validation/verify_build.py`: `7de327ef1f1dc534f4bed9e6e76e8ccd53d146ccf5cde8e26aba3da6708c899c`.
- `validation/test_verify_build.py`: `3cdee57e7927569f3760454644c83391867516b058012253ba2a5144a4ee3ffb`.
- Workflow remains `5c792e61941d16578567499891d46047bab5248bee2bc5bd8962eb6c5c21a7a2`.
- The allowlist and CMake hook remain unchanged.

The old run remains bound to judge `78a5da6d5aed19a932fae53e74226ac5afc2e204` and FAIL.
Its historical artifact/summary was not rewritten. The current correction will report actual
diagnostics on future permitted failed builds. Fresh negative controls against revision
`5269391` are `33927009741` (authority) and `33927019176` (allowlist). Both were rejected
at scope before dependency checkout/build, at 22:48:22Z and 22:48:27Z respectively on
2026-09-04. Director downloaded the artifacts and verified exact candidate, judge, dependency
and protected-file hash identities; actual logs show the intended path rejection and exit 1.
Evidence: `prelaunch/evidence/reporting-revision-negative-controls.json` and matching excerpts.
No identical known-failing clean build was rerun.

PRELAUNCH remains blocked on the explicit owner decision described in
`prelaunch/clean-control-additional-upstream-blocker.md`. All sprint timestamps remain UNSET.
