# Clean control 33929246418 — pinned unit-test source mismatch

Independent Reviewer disposition: **FAIL**. The standing upstream-warning policy worked:
four unchanged Playerbots diagnostics remained visible warnings. The required full build
then encountered actual C++ errors in AzerothCore's pinned unit-test mock. These are not
warning-promoted errors and are outside the standing warning authorization. No complete
gate pass, disposable runtime pass, or sprint launch follows from this run.

## Exact evidence

- [Official run 33929246418](https://github.com/tylerhanny/wow-server-forge/actions/runs/33929246418),
  validation job `101204315393`, completed with failure at `2026-09-05T00:47:55Z`.
- Candidate: `87b822fd41bb6013358aa6f5e16ca252ad79761c`, `project/forge-smoke-clean`.
- Judge: `6f0582572ceb1c0a16c4234fd6b97e896d3cf0ed`.
- Workflow SHA-256: `95bd45e3c63cdd82ad92404c0ef87770063dffbd91464b53d4c14fcc1ce93ce0`.
- AzerothCore: `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots: `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- [Artifact 9959575021](https://github.com/tylerhanny/wow-server-forge/actions/runs/33929246418/artifacts/9959575021),
  `official-gate-87b822fd41bb6013358aa6f5e16ca252ad79761c-1`, 639493 bytes.
  GitHub records ZIP SHA-256 `f38d4b17868d5c1d386ed0d548ab4f268d756c8e604f392bb24bd57159e30f7e`.
- Downloaded raw `build.log`: 202858 bytes; SHA-256
  `f23af464c26c31c227693da4d3464746d585df9df799569dcc18a4f2244cb538`.
- `build-receipt.json` SHA-256:
  `7e1b32522149560b13d32707360a3a7bfb43b2ceb9e76f98e98197c4ec8f9557`.
- `upstream-warning-verdict.json` SHA-256:
  `7a4a81dba715a3d71febafb3156d1438db7060284b5972f0cb4d3d037e001d7a`.

The Reviewer independently downloaded the artifact, recomputed the raw log hash, and
matched it to both the incoming-stream and persisted-file receipt hashes. Capture is
complete and the build exit code is 2. Pre/post tracked source identities match, covering
3634 source/header files with inventory SHA-256
`c0a0a00c908bd7ac8e7063021360b32fb7b9c32c023590ae343b98e33980fec9`.
All six protected file hashes match raw Git blobs at the exact judge commit. The failure
verdict includes all eight observed warning/error headers and source excerpts with
`VERIFIED_CAPTURE` and `acceptance_authority: false`; it does not reinterpret failure.

## Observed compiler result

The raw log records four `[-Wunused-parameter]` warnings from unchanged Playerbots files:

| Raw log line | Source relative to `ac/modules/mod-playerbots/` |
|---|---|
| 1540 | `src/Ai/Raid/BT/BTHelpers.cpp:107:60` |
| 1609 | `src/Ai/Raid/Hyjal/Util/HyjalHelpers.cpp:168:61` |
| 1612 | `src/Ai/Raid/Hyjal/Util/HyjalHelpers.cpp:209:60` |
| 1617 | `src/Ai/Raid/Hyjal/Util/HyjalScripts.cpp:39:63` |

The third entry is now an actual observed warning, whereas the prior run established it
only through source review. All four are visible in the failed verdict and job summary.

Four test translation units then fail when allocating `testing::NiceMock<WorldMock>`:

| Raw log line | Source relative to `ac/src/test/server/game/Battlegrounds/` |
|---|---|
| 1843 | `ArenaHookDefaultsTest.cpp:49:26` |
| 1855 | `LowLevelsMinPlayersOverrideTest.cpp:44:26` |
| 1867 | `ArenaSeason/ArenaTeamFilterTest.cpp:51:26` |
| 1878 | `ArenaSeason/ArenaSeasonRewardDistributorTest.cpp:37:26` |

Each reports allocation of an abstract class, followed by the same two unimplemented
pure virtual methods in `src/server/game/World/IWorld.h`: `GetPlayerbotsDBRevision`
at 109:39 and `AddQueryHolderCallback` at 117:37. These diagnostics have no warning
category; these upstream inputs already have `-Wno-error`. Changing warning policy
cannot make an abstract class constructible.

The Reviewer independently fetched both headers at the exact AC pin and verified raw
Git blob and SHA-256 identities against the official source inventory:

| File | Git blob | SHA-256 |
|---|---|---|
| `src/server/game/World/IWorld.h` | `d750ee0f51d9318ca422d58b2dd649c28d3eebde` | `b590a879cb1945bf3c8fcc52e6c3d02684d31724f9316d031073a29f6dea543e` |
| `src/test/mocks/WorldMock.h` | `23cc8998295ad6ec70fc1264e193185ed50c9322` | `0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1` |

`WorldMock` inherits `IWorld` directly and supplies neither override. The revision method
is conditional on `MOD_PLAYERBOTS`; the callback method is unconditional. Disabling
Playerbots would violate the compatibility target and would not resolve the unconditional
missing method. The smoke candidate remains its previously reviewed five files and has
no build hook, interface edit, compiler option, or diagnostic pragma causing this mismatch.

## Completed and unexecuted stages

The actual Ubuntu protected tests and real compiler provenance probe passed at 23:23:46Z.
Exact target configuration and command provenance passed at 23:24:43Z. The 1829-entry
compile database has SHA-256
`6d7caaede652ff90161c2761a4efd15b2a1a3c9b8e92af05d652a5f425bd2683`.
The Reviewer checked every entry: all retain `-Werror`; exactly 1822 verified pinned inputs
have the source demotion, while candidate/generated inputs have none.

The log records `Built target authserver`, `Built target modules`, and `Built target
worldserver` (the last at 00:47:34Z). This establishes those build targets, not completion
of the required whole build. Make exits 2 at 00:47:37Z; the official verifier rejects it
at 00:47:52Z. Install, SQL/data validation, runtime preparation, both server dry-runs,
unit-test execution, and final runtime integrity stages were skipped. The build wrapper's
own pre/post source checks did complete; the separate later integrity steps did not run.

The current judge's authority-tamper negative control `33929247980` independently passed
its rejection requirement. It does not convert this clean failure into acceptance.

## Authority boundary

This is a real incompatibility between the immutable pinned test fixture and its interface.
No judge-classification repair or warning allowance addresses it. A test-only fixture
compatibility correction would require explicit authority to change or substitute that
pinned fixture; omitting the required tests would likewise change an existing gate. Neither
has been done or inferred. No identical full-build retry is justified without a concrete
authorized change. The exact pinned baseline and all historical failed results remain intact.
