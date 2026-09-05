# Field Repairs — independent final acceptance

**READY FOR LIVE TEST. Independent review PASS; ONE_HUMAN_REVIEW=PASS.**
Reviewer disposition: 2026-09-05. The exact implementation and full official evidence
pass independent review. Actual logged-in repair behavior remains for owner testing.

## Exact accepted checkpoint

- Candidate: `1450d92f8bcf3a8282526120753ed5f750939722`, `project/field-repairs`.
- Reviewed source: `e560e72a09ed99c4d3391c90a242f9b8f5a9b277`.
  Final candidate changes only three review-status documents. Source, configuration and
  compile-time checks remain byte-identical; exact diff, scope and whitespace passed.
- Official run: [33970121674](https://github.com/tylerhanny/wow-server-forge/actions/runs/33970121674), **SUCCESS**.
- Default-branch judge: `8d21e8b1b4920b4966760ba621751725bd411444`.
- Workflow SHA-256: `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Artifact: `9970803705`, 877,388 bytes. GitHub API archive digest:
  `81710133c5ab281f38e8f15d3440a8ee6beefe801b5bf45de9936c19bdb8e4cd`.
  This digest is API metadata; the extracted evidence below was independently hashed.
- Validation job completed `2026-09-05T14:02:41Z`.

All applicable steps succeeded: native discovery/configure/full compilation, fixture
restoration and dependency integrity, install, SQL applicability, disposable data/config,
authserver and worldserver dry-runs, unfiltered native units, final source integrity,
evidence publication and cache save. Only the project-specific Stormwright normal-startup
step was skipped, correctly: Field Repairs has no OnStartup actor or encounter requirement.

## Build, warnings and source identity

The 203,155-byte complete build capture returned 0. Its raw SHA-256 matches both captured
stream and persisted-log hashes in the receipt:
`cdb19217d6b0b89bdcd848ada158a01a8b78d38abb1697fa2a5c07378af2e055`.
Receipt SHA-256 is `11a372b79e4a3dfaa605c26a0440d09a0f145a42a7c752fa48ae62ad04eb6209`;
warning verdict SHA-256 is `ac22b60a205825956f7158e08b0548745c9d3ceb4dbdb61e36f8eae8f23935b1`.

Exactly four visible warnings are exclusively verified unchanged Playerbots source:
unused `botAI` in BTHelpers.cpp:107, HyjalHelpers.cpp:168 and :209, and HyjalScripts.cpp:39.
The complete headers, contexts and compiler summaries of 1 + 2 + 1 remain captured.
There is no project warning or compiler error. All 1,830 compile commands retain literal
`-Werror`; the 1,822 upstream demotions match the protected source inventory. The command
database hashes to `103143c3fbf4ca52e4a150b8e4278533e85a0e77c67f72c813814eb334252d76`.
Field Repairs' actual-helper static assertions compiled as part of this complete build.

All ten protected validation/authority hashes match raw Git blobs at the recorded judge.
The pre/post inventory has 3,634 tracked source files, unchanged SHA-256
`c0a0a00c908bd7ac8e7063021360b32fb7b9c32c023590ae343b98e33980fec9`.
Exact pins remain AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, on Ubuntu 24.04 x86-64 / client 12340.

The authorized disposable WorldMock correction is explicitly recorded as corrected test
source, never as unchanged upstream. Original/restored SHA-256 is
`0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1`;
applied/post-compile SHA-256 is `f8bd0eb555aab8ab93369f47f662b65cb7d78b3a87800d243bbd1ed109d426e6`.
Patch SHA-256 is `ccb5de156d833f050764a086260d3603f459932872974e5a85dd36e5c8c93bc5`.
The exact delta and every other tracked file were verified before restoration, which
completed before install. No full WorldMock header/source tree is exported in the artifact;
the install log contains neither the fixture nor the native test executable.

## Actual runtime and tests

Native module discovery generated `Addmod_field_repairsScripts();`; install staged
`mod_field_repairs.conf.dist`, and the effective module config was loaded. The actual
worldserver dry-run contains `FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`,
Playerbots initialization, world initialization and successful dry-run termination.
Authserver also completed its dry-run. The single preserved Errors.log is zero bytes.
The recorded DBC checkout is `74643b700b1cd806845a1dfd926a2c46e7890dbe`.
No module-owned SQL exists; the normal empty-SQL applicability check succeeded.

The unfiltered native executable selected 11,395 tests from 83 suites: **5,909 passed,
5,486 native conditional skips, one native disabled test**, no failure. The protected
16-test suite and real CMake/compiler provenance probe also passed. These are actual
execution results, distinct from prior source-only inspection.

Selected independently recomputed evidence SHA-256 values:

| Evidence | SHA-256 |
|---|---|
| authserver-dry-run.log | `dd2b8ed83ab4f1634bfeb802e059f6c04a25decced1ac717ae1aa343701a9993` |
| worldserver-dry-run.log | `e51be776025ab11229db88d1fb2391c78aabbbd19e3926b3948f7eebbdb8297e` |
| unit-tests.log | `78eeab8bc35b5d6ede597809eec4e0f6573031b08c642b767b121c043045168d` |
| install.log | `3c6b0c7b64226860cb091adeaa90c89ec9c1879923c15b9063645bca48b2496d` |

## Observed compiler-cache reuse

The actual restore log names the prior successful Stormwright cache from run33960843535,
candidate60c6a91925eed80049bec47994f87df739ac7725, under the identical pins and protected
content namespace `03b1a431940f268581189b395c9d58f2070a5a34eb0fbda2cb982340dd67e987`.
Recorded statistics: **1,826 preprocessed hits, four misses, zero direct hits**, from 1,830
cacheable calls. The complete compile step ran 13:54:09Z–14:01:11Z: **422 seconds (7m02s)**.
The successful job saved the current candidate's cache at 14:02:39Z.

Effective configuration retains content-based compiler identity, disabled direct mode,
second preprocessing, no sloppiness/remote storage/debug, a 1.5 GB limit and temporary
files outside the persisted cache in RUNNER_TEMP. Current candidate compilation, physical
source provenance, fixture and runtime checks all still ran. All four upstream warnings
remain fully visible; aggregate hit statistics do not establish which individual warning
was replayed. No cache-only control or timing-based assumption is used as acceptance.

## One-human disposition and remaining manual checks

The independently reviewed solo path is complete: inspect damaged gear/balance, request,
read native personal-gold and possible partial-repair terms, confirm within 30 seconds,
observe wallet/durability outcomes, earn gold and retry, or cancel/expire/exit. All current
damaged carried items are preflighted before the single native repair call. No second
human, bot-specific action, guild money, GM command, persistent state or custom price is
required. README and handoff document the exact path and independent one-human PASS.

CI does not log in a player or execute a repair. Actual native prices/partial order,
durability/stat updates, other modules' callbacks, consent usability and normal bot-party
coexistence remain **PENDING LIVE/IN-GAME VALIDATION**. The observed wallet delta is not
promised to isolate unrelated callback effects. No critical source or official-gate
finding remains; the exact frozen candidate is eligible for early owner delivery.
