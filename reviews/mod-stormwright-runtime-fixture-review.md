# Stormwright normal-startup observation and logger repair

Independent Reviewer, 2026-09-05. **Overall gate remains FAILED** for candidate
`bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc`, run
[33955586542](https://github.com/tylerhanny/wow-server-forge/actions/runs/33955586542).
Successful earlier stages are retained, but no registrar-spawn or complete normal-runtime
acceptance is inferred from missing output.

## Exact failed evidence

- Judge: `8b87494de0261cd82c48c4a0dc11895611fb9d39`.
- Artifact: `9967727355`, 880,795 bytes; GitHub API archive digest
  `c134b7537bfec72c375d972b0eb7ff43696b9ab76802b1da28eb9769d38276fc`.
  The archive digest is API metadata; extracted evidence was independently hashed.
- Complete build log: 203,150 bytes, SHA-256
  `65df7fe4525279a619e40e0ee3dd24fdf7a42221e7171382013cf4c000bf3fc1`.
  Stream and persisted hashes agree; capture is complete and build process returned 0.
- All ten protected hashes match raw Git blobs at the judge. Exact pins, 3,634-source
  pre/post-build identity, 1,830 compiler commands, strict project warnings and the precise
  disclosed WorldMock correction/restoration were independently verified. Four known
  unchanged Playerbots warnings remain visible; no project warning is accepted.
- Full compilation/install, both dry-runs and required native units passed. Unit results
  are 5,909 passed, 5,486 native conditional skips and one pre-existing disabled test
  from 11,395 selected tests. Compiled module rules assertions and the existing standalone
  rules executable also passed.
- The expected five owned script templates, five exact display rows and npc_text 910900
  are present in actual MySQL query output. SQL evidence SHA-256:
  `dc59712a34f02283a1b8e6a25440a36fc53f9601cc5d7b774da6a50fc10770d1`.
- Actual data download matches archive SHA-256
  `a3d4df635ae6c2c8f08052c32a79e0f806955150ad36b014a823dd08a32a4610`.
  The helper records 22,018 extracted maps/vmaps/mmaps files; original recorded DBC data
  is retained. This is data identity evidence, not a client navigation test.

The real worldserver initialized in 13 seconds, logged enabled Stormwright configuration,
reached `ready...` and world updates, but emitted neither required registrar nor site-error
marker. After five minutes the helper timed out and terminated it. `Halting process...`
and database shutdown appear after that intervention; this is not the required successful
marker-triggered console exit. `Errors.log` is empty. No runtime PASS verdict exists.
Final post-runtime integrity and cache saving were skipped because the required step failed.

Raw normal-server log SHA-256:
`48e23498bf5758adeef6a60c3277ea3ec73e060bf0a07c9049d8c8be0b70d104`.
This raw runtime log contains interleaved non-ASCII banner bytes; ASCII observations above
were checked against original bytes. It is not the strict compiler capture, whose independent
UTF-8/integrity checks passed.

## Confirmed fixture defect and exact correction

Pinned `LogCommon.h` defines **WARNING=3, INFO=4**. `Logger.cpp` and `Appender.cpp`
drop a message when the configured level is lower than the message's level. Native
configuration is `Logger.module=4,Console Server`, Console appender level 4 and Server
appender level 5. The supplemental fixture incorrectly changed the module logger to 3,
so it suppressed the required INFO registrar marker. This was missed by fixture review;
the source-level diagnosis is not a retroactive runtime PASS.

Cached LogCommon/Logger/Appender raw hashes were rechecked against the exact pinned
inventory. The repair is commit `0340f0c`: only `Logger.module` changes from
`3,Console Server` to `4,Console Server`. Exact helper SHA-256 becomes
`980804f2e54e32550d1f9329935bf71987e97336265163c5b027a60397c1493a`.
Exact one-value diff, Python AST and whitespace checks pass. Required marker, SQL/data,
five-minute deadline, exit, Errors.log and all other stage requirements are unchanged.
Director independently reviewed and published it in judge
`e5fd277de515dbda983993e6f8a52b48cb0816b4`.

Candidate `60c6a91925eed80049bec47994f87df739ac7725` changes only README, validation
notes and handoff from bde390e3: correct INFO/default guidance and honest completed/failed
stage history. Source/SQL/config/rules/tests remain byte-identical. Independent docs review,
SOURCE_REVIEW and ONE_HUMAN source disposition PASS. It is frozen for the one required
full run [33960843535](https://github.com/tylerhanny/wow-server-forge/actions/runs/33960843535),
whose result is pending. Both previous failed Stormwright runs remain failed.

## Cache facts

The failed run was a cold restore miss. Effective approved configuration is unchanged;
all 1,830 cacheable calls missed, zero hit, and cache size was reported as 0.1 GB / 1.5 GB
(5.08%). Saving was skipped with the failed runtime step. Full compile ran
`08:35:52–10:12:31Z`, **96m39s**, versus Hunt's **58m54s** and Field Camp's **95m05s**.
These observations do not establish acceleration or a cause for the timing difference.
The protected runtime-helper change also changes the existing cache namespace, so the
saved Field Camp cache is not assumed reusable for the corrected run. No cache-key change
or extra control was introduced.
