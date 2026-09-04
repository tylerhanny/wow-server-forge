# Clean control 33922537362 — additional upstream compile blockers

Independent Reviewer disposition: **FAIL / fresh owner-decision blocker**. The single
authorized warning remained visible and nonfatal. Two different immutable Playerbots
diagnostics correctly remained fatal. No allowance expansion, dependency change, retry,
runtime success, or sprint launch is authorized by this result.

## Exact run and evidence

- [Official run 33922537362](https://github.com/tylerhanny/wow-server-forge/actions/runs/33922537362),
  validation job 101183866585, failed after 47m45s; completed 2026-09-04T22:33:18Z.
- Candidate: `87b822fd41bb6013358aa6f5e16ca252ad79761c`, `project/forge-smoke-clean`.
- Judge: `78a5da6d5aed19a932fae53e74226ac5afc2e204`.
- Workflow SHA-256: `5c792e61941d16578567499891d46047bab5248bee2bc5bd8962eb6c5c21a7a2`.
- AC: `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots: `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- [Artifact 9956799024](https://github.com/tylerhanny/wow-server-forge/actions/runs/33922537362/artifacts/9956799024),
  `official-gate-87b822fd41bb6013358aa6f5e16ca252ad79761c-1`, 355433 bytes.
  GitHub's recorded ZIP SHA-256 is
  `de1036ce3788e5613ed34b8eb438b06d551462466350e83ef2406811b2e2486f`.
- Independently downloaded raw `evidence/build.log`: 179453 bytes, SHA-256
  `7f5b632de2e4532218fc907542b4ca2832d5e46a701e2761cbd0186096598fcf`.
- Build receipt SHA-256: `d7c9daaddddfaa8d6a24edd9b24dd73f5c60c096117efa5e74c5e645347d3bd8`.
- Failure verdict SHA-256: `e285e31b380d42ead88adcde0e8c04ffce9597d52dbdaebe73e2772be69fda89`.

The Reviewer independently compared all six entries in `protected-validation.sha256`
against raw Git blobs at the exact judge SHA. All matched. The receipt records completed
merged output capture, build exit code 2, equal pre/post source identities, and the same
raw-log SHA-256 for the incoming byte stream and persisted file. The raw downloaded log
reproduces both hashes. This proves capture of a failed build, not successful compilation.

## Actual diagnostics

Paths below are relative to `ac/modules/mod-playerbots/` in the disposable runner.

| Log line | UTC | Source | Actual result |
|---|---|---|---|
| 1558 | 22:30:11.802 | `src/Ai/Raid/BT/BTHelpers.cpp:107:60` | One warning: unused `botAI` in `GetShahrazTankPositionState`; authorized |
| 1606 | 22:31:31.980 | `src/Ai/Raid/Hyjal/Util/HyjalHelpers.cpp:168:61` | Fatal unused `botAI` in `GetKazrogalTankPositionState`; unauthorized |
| 1614 | 22:31:37.505 | `src/Ai/Raid/Hyjal/Util/HyjalScripts.cpp:39:63` | Fatal unused `botAI` in `ShouldInterruptForArchimondeAirBurst`; unauthorized |

All three have category `[-Wunused-parameter]`; each header has its real source excerpt
and caret in the untouched raw log. The single warning has `1 warning generated.`.
The two fatal diagnostics each have `1 error generated.`. Make exits 2 at
22:33:05.677Z; the verifier rejects the unsuccessful build at 22:33:12.933Z.

Reviewer and Practical independently retrieved both failing files from the exact public
Playerbots commit. Reviewer recomputed Git blob identities from raw bytes:

| Pinned file | Git blob | Raw SHA-256 |
|---|---|---|
| `src/Ai/Raid/Hyjal/Util/HyjalHelpers.cpp` | `536841de39ab91846b531df111be1a9171ec3acf` | `3e77fd578d0f064ba729084e19830939d6e78e1a2b352a41ddb159238f63ae0f` |
| `src/Ai/Raid/Hyjal/Util/HyjalScripts.cpp` | `64d2a328d0d2cd52773a34ed7c564a80690ee528` | `0f812e2a2f7686a3acd1dc1e7311d02ddf795ba9e942b220ad320227ca62758c` |

`GetKazrogalTankPositionState` at lines 168–179 uses `bot`, group tank lookup and stored
tank state, but never `botAI`. `ShouldInterruptForArchimondeAirBurst` at lines 39–52
uses the three players, group tank and distance, but never `botAI`. These are defects in
the immutable baseline under the required warning policy, not smoke-module changes.

The same Helpers blob also contains an unused `botAI` parameter in
`GetAzgalorTankPositionState` at lines 209–220. That is **source-review evidence only**;
this run did not emit a diagnostic for it. Pinned compile commands retain `-Wfatal-errors`
as well as `-ferror-limit=0`, so the first fatal error can stop a translation unit before
later defects are diagnosed. These two observed failures are not an exhaustive baseline
inventory, and allowing them would not establish that a subsequent full build will pass.

## What the gate actually established

- Scope and exact dependency checkouts passed.
- All 17 protected tests passed in actual Ubuntu CI, including the real Clang/CMake
  file-scope probe and fatal candidate-warning probe. The self-test log hash is
  `ac46271bed41cf20b8aeb7dec2bd955cfe8a2ffc88a3f491b82aa69b5a3b60e9`.
- Full target configuration and generated module loader passed.
- The 1829-entry compile inventory has SHA-256
  `ecd9e8a0ab4cddee2dc67ff4d49f8c6e3fe61187cc2593eb2277fb48578ef02e`, equal to the
  receipt. Exactly one actual input, `BTHelpers.cpp`, has the demotion. Both failing
  Hyjal inputs and `ForgeSmoke.cpp` retain `-Werror`, `-Wall`, `-Wextra` and
  `-Wfatal-errors` without a demotion. The actual `-c` inputs match those entries.
- The build wrapper verified tracked AC/Playerbots trees and the authorized source
  identity before and after compilation. The later standalone integrity steps were
  skipped, as were install, SQL/data checks, runtime data/MySQL preparation, both
  server dry-runs, pinned unit tests and final runtime integrity. No later result exists.
- Both negative controls at this judge rejected tampering: authority run 33922543117
  and allowlist run 33922549107. Their success as negative tests cannot pass this clean run.

The complete smoke candidate has only its previously reviewed five project/handoff files;
it supplies no build hook, diagnostic pragma, dependency edit or compiler option. Candidate
source review and command provenance provide no mechanism by which it causes these errors.

## Evidence presentation and next decision

The authorized warning and new errors are visible in the official raw build artifact and
step log. The failed verdict currently contains only `Complete build did not succeed`,
and the generated job summary repeats the allowance policy rather than the observed
diagnostic. Thus observed-warning visibility in the **failed-build summary** is incomplete.
A separately reviewed reporting-only fix may add observed headers/context and explicit
capture-integrity status to a FAIL verdict. It must not change acceptance, counts, hashes,
source identities, compiler flags or the allowlist. Invalid capture observations must be
labelled non-authoritative. Such a fix cannot pass this failed run or justify another
known-failing full build.

Under current authority the Forge remains prelaunch with all phase timestamps unset.
The owner may preserve the existing warning policy and hold the Forge, or explicitly
authorize a further precisely bounded baseline investigation/exception policy. The current
single-warning authorization does not cover either new error or the source-only finding.
No dependency edit/update, warning suppression, broader exception or identical retry may
be inferred. Actual full build/install/runtime/unit validation remains pending.
