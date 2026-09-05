# Triage Night — independent final acceptance

**READY FOR LIVE TEST. Independent review PASS; ONE_HUMAN_REVIEW=PASS.**
Reviewer disposition: 2026-09-05. Actual source and the full official artifact pass review.
Logged-in priest gameplay remains for the owner's in-game validation.

## Exact accepted checkpoint

- Candidate: `b404a1bd4614a8b956187f17baf585eee6d16cf6`, `project/triage-night`.
- Reviewed source: `e8907bd72940628148150621d7c8143624c47045`.
  The frozen candidate changes only README, VALIDATION and handoff review status. Source,
  SQL, configuration and actual-helper compile-time checks are byte-identical; scope,
  final documentation equivalence and whitespace passed independent inspection.
- Official run: [33971943070](https://github.com/tylerhanny/wow-server-forge/actions/runs/33971943070), **SUCCESS**.
- Default-branch judge: `8070cf87ba160d08c507e98dc809a949c573f986`.
- Workflow SHA-256: `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Artifact: `9971337715`, 878,092 bytes; GitHub API archive digest
  `e33d00961ae2bc4b37d163d3910def2e00c5c1df1d1c4822cf180b351f4010bd`.
  This archive digest is API metadata; extracted evidence was independently hashed.
- Validation job completed `2026-09-05T14:40:41Z`.

The Director published only the exact owner-authorized frozen SHA and verified the remote
branch before the Reviewer dispatched this single required run. Earlier rejected publication
attempts created no official run and were not bypassed. This review does not alter the
candidate, expand the owner's publication scope or infer permission for another version.

All applicable steps succeeded: native discovery/configure/full compilation, restored
dependency integrity, install, SQL checks, disposable data/config, authserver/worldserver
dry-runs, unfiltered native units, final integrity, artifact publication and cache save.
Only the Stormwright-specific normal-startup supplement was correctly skipped. Triage
creates actors through a logged-in player's start command, with no OnStartup actor hook.

## Complete build and immutable provenance

The raw build log is 203,152 bytes, returned 0 and matches both receipt stream and persisted
hashes: `6e55eaa6a2bf9ec59608952f16d9f83361c6dcc31846e63f8818dba2ba9c7a42`.
Receipt SHA-256 is `d2a7bc972461119ef4c7cac4748d8632671ff73693007ee619173a98b4c220f2`;
warning verdict SHA-256 is `2cf28613ce68e1bcbb207618fd8a8e8884f72125a2c7d94df501cad4be2a60f5`.

Exactly four warnings remain fully visible with context and matching compiler summaries
of 1 + 2 + 1: unchanged Playerbots unused `botAI` in BTHelpers.cpp:107,
HyjalHelpers.cpp:168 and :209, and HyjalScripts.cpp:39. No project warning or compiler error
appears. All 1,830 commands retain literal `-Werror`; the 1,822 source demotions match the
verified upstream inventory. Compile-command SHA-256 is
`38e493bdb5fb8138701faaf4994d54917f302ad3d0f6e87dfc5855ec2a043120`.
The project-local schedule/stabilization/terminal-state static assertions compiled in
the complete target; no separate local execution is claimed.

All ten protected validation/authority hashes match raw Git blobs at the actual judge.
Before/after source inventories contain the same 3,634 tracked files, SHA-256
`c0a0a00c908bd7ac8e7063021360b32fb7b9c32c023590ae343b98e33980fec9`.
Exact pins remain AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu24.04 x86-64 / client12340.

The precise authorized test-only WorldMock correction is disclosed as the fixture actually
used during compilation, not unchanged upstream. Original/restored SHA-256 is
`0908566bb6f2ec3875992c73e28204d4c0a1271624b2b75fa99357f30b579ce1`;
applied/post-compile SHA-256 is `f8bd0eb555aab8ab93369f47f662b65cb7d78b3a87800d243bbd1ed109d426e6`.
The exact delta, patch SHA-256 `ccb5de156d833f050764a086260d3603f459932872974e5a85dd36e5c8c93bc5`
and all other tracked files were verified before restoration, which completed before install.
No full WorldMock header/source tree appears in the artifact; neither the fixture nor the
native test executable is installed. Production source and both pins remain unchanged.

## Actual SQL, configuration and startup

Native discovery generated `Addmod_triage_nightScripts();`. Install staged the module's
configuration, and the worldserver dry-run explicitly loads `mod_triage_night.conf` and logs:

```text
TRIAGE_NIGHT_CONFIG reload=false enabled=true; priest solo, no OnStartup actors, active shifts end on reload
```

The native world updater reports applying `2026_09_05_00_triage_night.sql` with checksum
`98F6E4C`. Independent raw Git-byte hashing of the exact candidate SQL gives SHA-1
`98f6e4ca90839004c164834926357495234805e9` and SHA-256
`4ca8db5f7efd3caf4afb00557b189323f5f61009d2bd596627cdef0649342bfa`.
The update is followed by successful world-data loading, Playerbots initialization and
complete worldserver dry-run termination. Authserver also completes successfully; the
single preserved Errors.log is zero bytes. Recorded DBC checkout:
`74643b700b1cd806845a1dfd926a2c46e7890dbe`.

This establishes actual native application during disposable startup, alongside independent
schema/model/ScriptName source review. No separate post-import row query or uninstall
execution was performed. The source review verifies the four owned templates and four
model rows, plain INSERT behavior, no permanent spawns, reserved identity rollback and
retained updater history. Owner custom-database collision checks remain necessary.

## Native tests and cache facts

The unfiltered native executable selected 11,395 tests from 83 suites: **5,909 passed,
5,486 native conditional skips, one native disabled test**, no failure. The existing
16 protected tests and real CMake/compiler provenance probe also passed.

The full compile step ran `14:31:38Z`–`14:39:01Z`, **443 seconds (7m23s)**. Actual cache
statistics report **1,826 preprocessed hits, four misses and zero direct hits** out of
1,830 cacheable calls. The restore log names run33970361200 and Field Repairs candidate
1450d92f8bcf3a8282526120753ed5f750939722 under the identical pins/protected-content namespace
`03b1a431940f268581189b395c9d58f2070a5a34eb0fbda2cb982340dd67e987`.
That is the observed cache source, not a substitute candidate acceptance verdict. The
current Triage cache was saved successfully at14:40:37Z.

Effective cache configuration retains content compiler hashing, disabled direct mode,
second preprocessing, no sloppiness/remote storage/debug, a 1.5 GB limit and transient files
in RUNNER_TEMP outside persisted objects/results. Current-candidate source/command/fixture
and full runtime checks still ran. All four permitted warnings remain in the complete log;
aggregate hit statistics do not identify which individual diagnostic was replayed.

Selected independently recomputed evidence SHA-256 values:

| Evidence | SHA-256 |
|---|---|
| authserver-dry-run.log | `dd2b8ed83ab4f1634bfeb802e059f6c04a25decced1ac717ae1aa343701a9993` |
| worldserver-dry-run.log | `6c979488b84bdd741b4ab57d668ef5f206b39a9c1d0b211640d32c05ce66f307` |
| unit-tests.log | `f56475b583bc59ddcc009f1932cd500616286d25a55fab321b0287411a85b502` |
| install.log | `b68de30278544241210fcf71f5d8050a509fd2d50f9ca73063a28af9824cbf0a` |

## One-human acceptance and manual limits

The complete source-reviewed path is one level80 priest using ordinary direct heals and
mana: public help/start/preset, three persistent patients across five injury rounds,
warned burst priorities, two human-targeted stabilization charges, success/failure result,
normal rest/retry or stop. No second operator, bot-healing assumption, GM venue, custom
client, player resource refill or permanent reward is required. Actual healing casts and
channels are allowed during the encounter. Ownership, lease limits, outside-effect filters,
preserved wounds, finite lifetimes and failure cleanup passed independent source review.
README and handoff contain the full one-human path and independent PASS disposition.

CI did not log in a priest, start a shift or operate healing spells. Native patient assist
targetability in the client, stock health bars/poses, terrain suitability, gear/mana pressure,
stabilization feel, fun/replayability and optional normal bot coexistence remain
**PENDING LIVE/IN-GAME VALIDATION**. The narrow priest path does not claim other healer
classes or party-AoE support. No critical source or applicable official-gate finding remains.
The exact frozen candidate is eligible for immediate owner delivery without a further cycle.
