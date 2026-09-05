# Clean control 33937007702 — build/install pass, empty-SQL judge defect

Independent Reviewer disposition: **overall gate FAIL; full build, authorized fixture
verification and disposable install PASS**. Runtime initialization and unit-test execution
did not run. This result does not start the sprint or pass the smoke candidate.

## Exact run and observed failure

- [Run 33937007702](https://github.com/tylerhanny/wow-server-forge/actions/runs/33937007702),
  validation job `101226804121`, failed after 1h39m16s on 2026-09-05.
- Candidate `87b822fd41bb6013358aa6f5e16ca252ad79761c`, `project/forge-smoke-clean`.
- Judge `60953d65185a231650c8c1050dbd6a182016ef66`.
- Workflow SHA-256 `9c123f8039aa53ebd76dc3025f98b9192ba7bf1818afb549409c4cb6492f93fd`.
- Both required AC/Playerbots pins remained unchanged.
- [Artifact 9962025709](https://github.com/tylerhanny/wow-server-forge/actions/runs/33937007702/artifacts/9962025709),
  642075 bytes; GitHub ZIP SHA-256
  `e42d7d5220d259d0d64f0e669cd2bbc829d138f7280ba4a30045243547189d3a`.

At `03:22:47.4139884Z`, the SQL stage printed its destructive-SQL rejection without any
matching SQL line. The exact smoke candidate has no SQL files. The original pipeline used
`find ... -print0 | xargs -0 -r grep ...` as an `if` condition: on no input, `xargs -r`
executes nothing and returns success, incorrectly entering the rejection branch.

The Reviewer reproduced this behavior with the actual old workflow fragment locally.
The candidate does not contain destructive SQL, and no new owner exception is needed
for this diagnosed judge defect.

## Independent build/fixture/install evidence

The downloaded 203042-byte raw build log has SHA-256
`13353067ff6de418feabee838703177d8ba60ef8b5bc1861ebcb3a41af7fdb3c`, equal to both receipt
stream and persisted hashes. Capture completed; build exit code was zero. The real log
records `[100%] Built target unit_tests` at `03:22:33.0123334Z`; the protected build verdict
passed at `03:22:46Z`. All four unchanged Playerbots unused-parameter warnings remain
visible and match the verdict, source inventory and compiler warning summaries. No actual
compiler error appears. The complete test executable compiled; this does not claim its tests ran.

The Reviewer independently matched all nine protected artifact hashes against raw Git
blobs at the exact judge. The 1829-entry compile inventory preserves `-Werror` everywhere;
only its 1822 verified upstream inputs receive the existing source demotion. The original
3634-file source inventory is identical before the build and after disclosed restoration.

The exact WorldMock patch hash is
`ccb5de156d833f050764a086260d3603f459932872974e5a85dd36e5c8c93bc5`.
The receipt records original/restored hash
`0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1`, applied/post-compile hash
`f8bd0eb555aab8ab93369f47f662b65cb7d78b3a87800d243bbd1ed109d426e6`, exact-delta verification,
all-other-tracked-files unchanged, and restoration before install. The modified header is
explicitly labeled an authorized corrected test fixture, not unchanged upstream source.
The artifact exports only its approved patch and metadata; no complete WorldMock header exists
in the artifact. Install output contains the server binaries and no WorldMock or unit-test installation.

Additional raw evidence hashes:

| Evidence | SHA-256 |
|---|---|
| Build receipt | `a2d7b589408ed77b85acfc9d44c7f8074d1cddf57817212e08de24f6f849d901` |
| Build warning verdict | `0d2840c8eea008aa7a65f1d2e641e4019e53c61318d760373a82bea125f8f125` |
| Install log, 7713 bytes | `7f5ddb3ebdf67bc478969b9ac2352575cbf4b29e257e410d87ad43fdaf312965` |
| Compile commands | `6d7caaede652ff90161c2761a4efd15b2a1a3c9b8e92af05d652a5f425bd2683` |

## Minimal correction and remaining work

Reviewer commit `6caa073b8b10d1716d130894076193431db5a83e` changes only SQL list handling:
enumerate once, run the identical destructive regex only when files exist, retain nonempty
and final-newline checks, and fail on scanner errors. Existing stages, source/pins,
warning policy and unit tests are unchanged. Practical independently approved that exact diff.

Bounded local shell checks reproduced the old empty-list failure and confirmed the revised
empty/benign/repeat-safe cases pass while destructive SQL, empty files, missing newlines
and grep errors fail. YAML and all 17 existing shell steps parse. These checks were not
added to the published suite or introduced as new prelaunch gates.

The existing authority-tamper control `33937008812` independently passed its required
rejection before dependencies/build. Fresh controls must use the corrected judge. Preserve
this run's overall failure and skipped runtime/unit outcomes; archival work must not delay
that continuation or the immediate launch following a complete reviewed clean pass.
