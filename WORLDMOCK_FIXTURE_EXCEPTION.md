# WorldMock test-fixture exception — explicit owner authority

The owner explicitly authorized only the reviewed two-method correction in
`prelaunch/worldmock-test-fixture-proposal.patch` on 2026-09-05. This is a narrow
disposable-CI test-fixture exception to unchanged-source requirements, not a warning
waiver, dependency update, production repair, test exclusion, or candidate success.

## Exact authorized input and delta

- AzerothCore pin: `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots pin: `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- Sole permitted fixture: `src/test/mocks/WorldMock.h` in disposable AzerothCore.
- Original Git blob: `23cc8998295ad6ec70fc1264e193185ed50c9322`.
- Original SHA-256: `0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1`.
- Exact patch SHA-256: `ccb5de156d833f050764a086260d3603f459932872974e5a85dd36e5c8c93bc5`.
- Corrected Git blob: `78df3ce2cfb77e03db6c78c063955ca81d4c7816`.
- Corrected SHA-256: `f8bd0eb555aab8ab93369f47f662b65cb7d78b3a87800d243bbd1ed109d426e6`.

Only the reviewed GoogleMock declarations for `GetPlayerbotsDBRevision` (with the
existing interface's `MOD_PLAYERBOTS` guard) and `AddQueryHolderCallback` may be added.
The full reviewed patch, including insertion locations, controls the exact bytes.

## Mandatory limits

The protected default-branch judge must verify the original exact identity before
patching and the exact authorized result afterward. Verify both dependency pins and
every other tracked dependency file unchanged. Production source and Playerbots source
remain untouched. No test, assertion, coverage, test selection or later validation stage
may be removed, skipped, weakened or rewritten under this exception.

The modified fixture may exist only inside the disposable CI control environment.
Never commit, install, cache, upload as a full source file, or otherwise persist that
modified fixture outside that environment. The exact patch and original/corrected
hashes must be preserved in validation evidence. Explicitly disclose that the unit-test
fixture was corrected; never classify it as verified-unchanged upstream source.

If the judge restores original bytes before install or runner disposal, record that
restoration separately. It must not hide which fixture was compiled. The fixture's
modified state is the sole exception; all other integrity checks remain strict.

Standing `UPSTREAM_WARNING_POLICY.md` continues to cover exclusively verified-unchanged
upstream diagnostics. All project-owned warnings and actual compiler errors remain fatal.
This exception authorizes no other upstream source change and no additional warning
suppression. An unrelated upstream error is not covered.

## Immediate continuation

Rerun the existing authority-tamper and legitimate clean controls under the revised
immutable default-branch judge. Preserve exact candidate/judge/patch identities and the
complete existing configure/build/install/config/SQL/integrity/dry-run/unit-test evidence.
After both controls satisfy their required outcomes and the existing minimum evidence
review passes, record the actual 36-hour clock and launch immediately. Add no prelaunch
review, cleanup, hardening, test expansion or additional policy gate. All isolation,
deadline, One-Human Playability and Wildcard Auteur rules remain binding.
