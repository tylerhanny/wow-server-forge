# Stormwright — independent final acceptance

**READY FOR LIVE TEST. Independent review PASS; ONE_HUMAN_REVIEW=PASS.**
Reviewer disposition: 2026-09-05, after inspecting the actual implementation, bounded
repairs and complete official evidence. Client encounter and gameplay checks remain pending.

## Exact accepted checkpoint

- Candidate: `60c6a91925eed80049bec47994f87df739ac7725`, `project/stormwright`.
- Reviewed repaired source: `a65f162419c8d0c0cc1ddbad2f35b7b4450018c8`.
  Final candidate source, rules, developer tests, SQL and configuration are unchanged from
  the reviewed repair and `bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc`. Later changes only
  correct logging guidance and preserve actual validation history. Byte equivalence and
  `git diff --check` were independently checked before dispatch.
- Official run: [33960843535](https://github.com/tylerhanny/wow-server-forge/actions/runs/33960843535), **SUCCESS**.
- Judge: `e5fd277de515dbda983993e6f8a52b48cb0816b4`.
- Workflow SHA-256: `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Runtime helper SHA-256: `980804f2e54e32550d1f9329935bf71987e97336265163c5b027a60397c1493a`.
- Artifact: `9969242731`, 881,458 bytes; GitHub API archive digest
  `8d61fd451b39c751d13410a4074424bda8a40e262794b4967e5567c95ccab8d1`.
  This archive digest is API metadata; extracted evidence was independently hashed.
- Validation job completed `2026-09-05T12:12:24Z`.

Exact dependency pins remain AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`
and Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. No production dependency
source modification is required. Earlier runs `33952393192` and `33955586542` remain
failed; their respective compiler and runtime-fixture records are preserved in
`mod-stormwright-compile-repair-review.md` and `mod-stormwright-runtime-fixture-review.md`.

## Verified build, warning and fixture evidence

All required official stages succeeded, including complete compilation, install,
SQL/data validation, both dry-runs, unfiltered native units, required normal-startup
supplement, final dependency integrity and evidence publication.

- Build capture: 203,150 bytes; SHA-256
  `627dd74393987f3eabb26c6efa6510ceda82d88df903af0e59b6f1a04820818b`.
  Capture is complete, process returned 0 and stream/persisted hashes agree.
- Receipt SHA-256: `28d96bdebdaacc61ee37b52a8ea4fe14865124a484739e2cb73db17b72a7c28c`.
  Warning verdict SHA-256: `f543d033498fe7af0018337fd107dfdb00add3dcc4c3392e7cd116d05f6d3fdf`.
- All ten protected hashes match raw Git bytes at the exact judge. Pre/post inventory
  identities agree across 3,634 tracked sources, inventory SHA-256
  `c0a0a00c908bd7ac8e7063021360b32fb7b9c32c023590ae343b98e33980fec9`.
- All 1,830 compiler commands retain `-Werror`; demotion is limited to 1,822 inventoried
  upstream translation units. Both project translation units remain strict.
- Exactly four unchanged pinned Playerbots warnings are visible: BTHelpers:107,
  HyjalHelpers:168/209 and HyjalScripts:39. Physical diagnostic/context provenance and
  compiler summary counts match the verdict. No project warning or compiler error occurs.
- The exact authorized WorldMock correction is separately identified as compiled,
  verified after build, and restored before installation. Original SHA-256
  `0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1`, corrected/post-build
  SHA-256 `f8bd0eb555aab8ab93369f47f662b65cb7d78b3a87800d243bbd1ed109d426e6`, and patch
  SHA-256 `ccb5de156d833f050764a086260d3603f459932872974e5a85dd36e5c8c93bc5` match.
  All other tracked files remain unchanged. The corrected fixture never receives
  upstream warning allowance; no modified full header is exported or installed.
- Native loader calls `Addmod_stormwrightScripts()`. Module configuration is installed
  and actual dry-run output records `STORMWRIGHT_CONFIG reload=false enabled=true`.
  Both server dry-runs complete, including Playerbots and world initialization.
- Native units: **11,395 selected / 83 suites; 5,909 passed; 5,486 native conditional
  skips; one pre-existing disabled test**. No failure or test-selection change occurred.
  The existing protected selftests and actual compiler provenance probe passed.
- Existing standalone rules tests compiled under strict warnings and ran successfully,
  reporting presets, recovery, duplicate input, retry, lag and time-cap checks. This is
  deterministic rules evidence, not a simulated encounter or client playthrough.

## Actual installed SQL and normal startup

The installed database contains exactly the expected five owned creature/script rows,
five model mappings and owned NPC text row. SQL evidence SHA-256:
`dc59712a34f02283a1b8e6a25440a36fc53f9601cc5d7b774da6a50fc10770d1`.
The official terrain archive was fully hashed in CI as
`a3d4df635ae6c2c8f08052c32a79e0f806955150ad36b014a823dd08a32a4610`, and 22,018 terrain
files were extracted from maps/vmaps/mmaps only. Original recorded ac-data DBC checkout
`74643b700b1cd806845a1dfd926a2c46e7890dbe` remained in use.

The installed disposable fixture uses loopback binding, console enabled, remote admin,
SOAP and cluster disabled, and the pinned correct `Logger.module = 4,Console Server`.
Normal startup initialized the world in 13 seconds and reached its update loop. Actual
normal-server log line 893 records:

```text
STORMWRIGHT_REGISTRAR spawned=true map=1 x=-6250 y=-3790 derived_z=-58.700077; client/path validation remains separate
```

After observation and the required five-second interval, the helper sent console info/exit
commands; the server logged `Halting process...` and returned 0. `Errors.log` is present
and empty. The normal-runtime verdict explicitly records startup, registrar observation,
owned SQL and clean console shutdown as PASS, and client/gameplay/navigation/bot competence
as NOT_TESTED. Normal log SHA-256:
`90b560097d1a3a72c902d376083cb59e4d5c0532b485e5f30adc7bf26ceeb6ba`;
runtime verdict SHA-256:
`cf9dda83c7163a84f0100514d1fe63636a9f780c9062e7e40f40698fac166a94`.
Final post-runtime dependency integrity also succeeded.

## Actual cache observations

The Actions log explicitly records a cold restore miss. Effective ccache configuration
matches the reviewed policy: compiler-content identity, direct mode false, second
preprocessing true, no sloppiness/remote storage/debug, and temporary files outside the
persisted cache. All 1,830 calls are cacheable misses, with **zero hits**; reported stored
size is 0.1 GB / 1.5 GB (5.08%). Cache save succeeded at `12:12:22Z`.

Full compilation ran `10:32:57–12:10:08Z`: **97m11s**. Prior Stormwright compilation was
96m39s and Hunt Rhythm was 58m54s. These are observations, not proof of acceleration or
cached-warning replay. The protected namespace remained unchanged in design; changing the
runtime helper changed its content fingerprint. No extra cache control was run.

## One-Human Playability and remaining manual evidence

**ONE_HUMAN_REVIEW=PASS.** One level-80 human can travel to the registrar, choose Solo
Pilot, start, bait and evade lightning, select Ground for personal/ward recovery or
Discharge for damage, win or fail, inspect the outcome, retry and exit. Solo Pilot retains
the complete mechanic with one-add cap and human-operated recovery. Optional normal bots
only fight; they need no custom rod decisions, exact positioning or second operated client.

Actual client access and return route, rod clickability, visual timing/readability, chase
and navigation, class balance, encounter feel and normal bot behavior remain pending the
README's manual checklist. Runtime terrain-derived spawning proves neither those client
behaviors nor a completed encounter. This exact candidate is ready for owner installation
and live/in-game testing with those limitations explicit.
