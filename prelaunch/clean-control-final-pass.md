# Final independent clean-control disposition

**INDEPENDENT_REVIEW=PASS** for the complete existing startup smoke gate.
Reviewer reported this disposition to the Director immediately after artifact
inspection; this note is a durable record, not an additional launch condition.

| Identity | Exact value |
| --- | --- |
| Clean run | `33947235843` |
| Candidate | `87b822fd41bb6013358aa6f5e16ca252ad79761c` |
| Judge | `dd283819da03e9ccbebdf9378b5fe3f1cf016380` |
| Judge workflow SHA256 | `8bc95aa73c0418b601e980529d13fb4f5fb414d33f3a0ba308dfa3333f092542` |
| Completed | `2026-09-05T06:37:33Z` |
| Artifact | `9964597892`, 876,014 bytes |
| API-reported artifact SHA256 | `0230e4792e57aecbf5fafd8a491563e08cb5d389f33b77c3119776105426df45` |
| AzerothCore | `47960183bb03b83e8943eb2f0f39c16df9710c9d` |
| Playerbots | `2f7d9f774987d0157c6a0d0cc08c40bec3db3945` |
| Runtime data | `74643b700b1cd806845a1dfd926a2c46e7890dbe` |

Reviewer downloaded the actual artifact and complete job logs. All existing
steps succeeded, including protected selftests and the real Ubuntu compiler
scope probe, discovery/configuration, full build, disclosed fixture restoration,
installation, SQL/configuration checks, disposable database initialization,
both dry-runs, unfiltered unit-test execution and final dependency integrity.
All nine protected artifact hashes match raw Git blobs at the exact judge.

## Build, fixture and installation

The complete merged build capture is 203,042 bytes with SHA256
`b5ffb3c01439803eedaad9f38f7b40181408d51c3907f8318e62cef0229e1c3c`.
It matches both the incoming-stream and persisted-file receipt; the compiler
process returned zero. All four visible upstream warnings match the verified
pinned source inventory and compiler summaries. No project warning or actual
compiler error is present. All 1,829 commands retain `-Werror`; exactly 1,822
verified upstream commands receive the owner-authorized demotion.

The 3,634-file original source inventories match before/after build. The exact
authorized WorldMock correction has separately recorded original, applied,
post-build and restored hashes; all-other-tracked-file verification succeeds.
It was restored before install and never classified as unchanged upstream.
No full corrected header or source tree appears in the artifact. Installation
contains both server binaries; the unit-test binary was built and then directly
executed from the build tree, without being installed.

## Actual runtime and tests

- Authserver emitted `Dry run completed, terminating.` and closed its pools.
- Worldserver emitted `WORLD: World Initialized In ` and
  `AzerothCore Dry Run Completed, Terminating.`.
- The candidate emitted the independently required configuration sentinel:
  `FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159`.
- Playerbots emitted `mod-playerbots initialized`; its supported disposable
  zero-population profile reported zero random accounts and zero characters.
  Playerbots remained enabled. The six effective fixture settings are captured
  in `playerbots-runtime-fixture.conf`; the generated random/addclass pools are
  omitted only from this disposable startup profile.
- `Errors.log` is present and empty.
- The unfiltered pinned unit command returned zero: 11,395 selected cases from
  83 suites, 5,909 passed and 5,486 native conditional skips. All skip records
  originate from the pinned `SpellProcFullCoverageTest.cpp` cases whose input
  lacks the tested property, such as a cooldown or proc flag. One existing
  `DISABLED_StaleIteratorAfterCascade_AsanOnly` test remains disabled upstream.
  No Forge filter, assertion removal or additional skip was introduced.

| Captured log/config | SHA256 |
| --- | --- |
| authserver-dry-run.log | `dd2b8ed83ab4f1634bfeb802e059f6c04a25decced1ac717ae1aa343701a9993` |
| worldserver-dry-run.log | `18e787127c50e065e79fb07e288a8dff4a14f1f7af2613dfd6bdb3cf6fa91807` |
| unit-tests.log | `89fcdde942f41705b75410ef195117cbd3f349235e67e02d289d60bc4d8250cc` |
| playerbots-runtime-fixture.conf | `f3201d5e1da6d9880d9edf4075abfa80651e70c00289036f28f48db8e2c1e958` |

## Independent negative control

Run `33947239092` tested tamper candidate
`2d74a0b1599313a9b09c7baf5b961d3744f48ed6` against the same judge.
Its actual scope output identifies `VALIDATION_INTEGRITY.md` at
`2026-09-05T05:27:24.5543642Z` and exits one before dependency checkout or
build. Reviewer independently matched candidate/judge/pins and all nine
protected hashes from artifact `9963710915`.
**NEGATIVE_CONTROL_REVIEW=PASS**: the tampered candidate was rejected.

This proves the complete disposable smoke path and independent judge controls.
It does not prove a gameplay loop, client visuals, terrain/pathing, the running
world-update loop, OnStartup-dependent behavior, bot competence or any live
server behavior. Hunt Rhythm and Stormwright still need their own exact-source
implementation review and applicable official candidate evidence. Historical
failed/cancelled runs remain unsuccessful. No further prelaunch run or gate is
required before beginning the already-approved implementation assignments.
