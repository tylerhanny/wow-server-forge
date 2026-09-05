# WorldMock compatibility correction — unapplied owner proposal

**Status: PROPOSED ONLY. No dependency, judge, or CI run has been changed.**

This is the smallest source correction identified for the actual unit-test compilation
failure in [run 33929246418](https://github.com/tylerhanny/wow-server-forge/actions/runs/33929246418).
The original failed result and complete evidence remain in
`clean-control-pinned-unit-test-blocker.md` (Reviewer commit `e8920811e79fa5bc5a40801a533647c2844887be`).

## Supported configuration assessment

The Reviewer read the exact pinned root `CMakeLists.txt`, `src/test/CMakeLists.txt`,
`src/server/game/World/IWorld.h`, and `src/test/mocks/WorldMock.h`.
The root enables the suite through `BUILD_TESTING AND BUILD_APPLICATION_WORLDSERVER`.
The test CMake file collects the test sources into `unit_tests` and links the existing
game, module and GoogleTest/GoogleMock targets. It supplies no alternate WorldMock
implementation or compatibility option.

`WorldMock` directly inherits `IWorld` and lacks two required pure virtual overrides.
Disabling Playerbots removes only the conditional revision method; the callback method
remains pure virtual. Disabling tests/worldserver, excluding failing sources, or applying
a GoogleTest runtime filter cannot preserve and successfully compile the complete required
suite. The actual upstream compile commands already contain `-Wno-error`; this error is
not a warning. Different warning flags cannot provide a missing class member. Compiler
macros, forced headers, or a shadow mock that alter class definitions would substitute a
test fixture, not constitute a supported non-mutating build option.

**No supported non-mutating configuration repair was found that preserves both pinned
dependency sources and the complete required upstream unit-test suite.**

## Exact proposed correction

The adjacent `worldmock-test-fixture-proposal.patch` changes only
`src/test/mocks/WorldMock.h` at AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`:

```cpp
#ifdef MOD_PLAYERBOTS
    MOCK_METHOD(char const*, GetPlayerbotsDBRevision, (), (const, override));
#endif
    MOCK_METHOD(SQLQueryHolderCallback&, AddQueryHolderCallback, (SQLQueryHolderCallback&& callback), (override));
```

The patch places each declaration beside its corresponding existing interface neighbors.
It adds normal GoogleMock declarations, with no fabricated return values, relaxed
assertions, excluded tests, runtime implementation edits, or Playerbots edits.
`IWorld.h` already includes `QueryHolder.h`; no new include or forward declaration is
needed. The revision declaration preserves the interface's `MOD_PLAYERBOTS` condition.

| Identity | Value |
|---|---|
| Original header Git blob | `23cc8998295ad6ec70fc1264e193185ed50c9322` |
| Original header SHA-256 | `0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1` |
| Proposed header Git blob | `78df3ce2cfb77e03db6c78c063955ca81d4c7816` |
| Proposed header SHA-256 | `f8bd0eb555aab8ab93369f47f662b65cb7d78b3a87800d243bbd1ed109d426e6` |
| Unapplied patch SHA-256 | `ccb5de156d833f050764a086260d3603f459932872974e5a85dd36e5c8c93bc5` |

The proposal was generated from independently fetched, hash-verified original bytes and
checked for exactly the two uniquely anchored insertions. This is source-level proposal
validation, not a compile or unit-test pass. Subsequent tests may reveal further failures;
no success or blanket permission for additional changes is implied.

## Specific authorization required

Current `UPSTREAM_WARNING_POLICY.md` requirement 2 states: “Neither dependency source nor
either pin may be changed.” Requirement 6 requires both dependency trees to remain
“byte-for-byte Git-clean,” and requirement 7 preserves every unit-test requirement.
`AGENTS.md` also says the standing warning policy authorizes no dependency edit or other
finish requirement change. `VALIDATION_INTEGRITY.md` prohibits altering validation inputs
to make compilation easier or bypassing failing tests. Therefore this fixture correction
cannot be inferred from the already-authorized upstream warning treatment.

The proposed owner exception would authorize only this exact test-fixture delta in the
disposable judge, under independent default-branch control. Both dependency commit pins,
all production source, Playerbots source, candidate source, existing tests/assertions,
warning requirements and later gate stages would remain unchanged. Evidence must identify
the original blob, exact patch and resulting header hash before and after validation, and
verify every other tracked dependency file unchanged. The modified fixture must be labeled
as an authorized test-only correction, never as verified-unchanged upstream source or a
fully Git-clean unmodified dependency tree. Any judge accommodation must be separate and
reviewed under that explicit exception. Restoring the original header after compilation
must never be used to hide the fact that the tested fixture was modified. This proposal
adds no prelaunch gate. Until the owner grants the precise test-fixture exception, leave
the patch unapplied and do not repeat the known-failing full run.

## Independent proposal review

Practical independently APPROVED the exact proposal at Reviewer commit
`b4724d425e9710a5a96e15bf155ec1d1a8556d0d`: both method signatures and the conditional
Playerbots guard match pinned IWorld; its QueryHolder include supplies the callback type.
The diff adds only the two GoogleMock overrides, with no runtime source, test assertion,
test selection or fabricated return change. Director inspected the same exact patch and
pinned headers and concurs. This is source review only, not a compilation or unit-test pass.
The patch remains unapplied pending explicit owner authorization.
