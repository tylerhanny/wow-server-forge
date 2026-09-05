# Hunt Rhythm final independent review

**READY FOR LIVE TEST. INDEPENDENT_REVIEW=PASS. ONE_HUMAN_REVIEW=PASS.**
This disposition applies only to candidate
`4aaa3ae188e7bcdba2569676911e14142ac378e2` on `project/hunt-rhythm`.
Actual player XP/chat behavior, class pacing and ordinary bot competence remain
PENDING LIVE/IN-GAME VALIDATION under the candidate's manual checklist.

Official [run 33951428776](https://github.com/tylerhanny/wow-server-forge/actions/runs/33951428776)
succeeded; the validation job completed at `2026-09-05T08:05:00Z`. Every required
stage passed. Judge `e35e85a787d7576d58cb691f6335b638ee8bc342` used workflow SHA256
`8bc95aa73c0418b601e980529d13fb4f5fb414d33f3a0ba308dfa3333f092542`.
Both pinned dependencies remain unchanged except the exact disclosed, temporary
owner-authorized WorldMock test fixture correction inside disposable CI.

## Independently inspected evidence

- Artifact `9965830223`, `official-gate-4aaa3ae188e7bcdba2569676911e14142ac378e2-1`,
  876,416 bytes. GitHub reports archive digest
  `dc40e9e3b6ade2dd32a0c56ba2cd45111165a223eea9518253e668f33b78342c`.
  Extracted evidence file hashes were recomputed independently; this is not a
  claim that the archive digest itself was recomputed.
- Full 203,147-byte build log SHA256
  `d56170889744b545e68eb5be07af0fb43639780f254093f7221363e684a28e45`
  matches both captured-stream and persisted-log receipt hashes. Capture completed
  with build exit 0. All nine protected file hashes match exact judge Git blobs.
- The 1,830 compile commands retain `-Werror`; exactly 1,822 verified upstream
  translations have the authorized demotion. Both candidate translations remain
  strict, including the actual compile-time boundary checks. Command inventory hash:
  `1845a85de1f442987ad20b65c9867fcfd919bdd23ecbe33e6d842947d5dea9d1`.
- Exactly four unchanged pinned Playerbots warnings remain fully visible:
  BTHelpers.cpp:107, HyjalHelpers.cpp:168 and 209, HyjalScripts.cpp:39. Raw headers,
  compiler warning summaries and the provenance verdict agree. No project warning
  or compilation error appears.
- Before/after inventories match across 3,634 tracked source files, with inventory
  digest `c0a0a00c908bd7ac8e7063021360b32fb7b9c32c023590ae343b98e33980fec9`.
  The exact WorldMock original/applied/post-compile/restored hashes and patch hash
  match authority; all other tracked files are verified unchanged. Restoration
  occurred before install. No full corrected header was exported or installed.
- Native generated loader calls `Addmod_hunt_rhythmScripts`. Installation contains
  the module configuration and server binaries. No module SQL is required.
- Actual world dry-run loads `mod_hunt_rhythm.conf` and prints
  `HUNT_RHYTHM_CONFIG reload=0 enabled=1 window=60 step=2 cap=10; all sessions opted out`.
  Both complete dry-run markers and Playerbots initialization appear; Errors.log is
  present and empty. An earlier concern about the default INFO logger hiding this
  marker is superseded by this direct observation.
- The protected 16-test suite and real CMake/compiler provenance probe passed.
  The unfiltered pinned unit binary selected 11,395 tests: **5,909 passed**,
  **5,486 native conditional skips**, plus **one pre-existing disabled test**.
  This does not claim all 11,395 passed. The skip/disabled behavior matches the
  unchanged baseline documented in `prelaunch/clean-control-final-pass.md`; no
  Forge filtering, assertion removal or newly skipped test was used.
- Final post-install/runtime dependency and protected-judge integrity checks passed.

## Acceptance scope

The earlier actual-source review and corrected pet-XP overflow guard are recorded
in `reviews/mod-hunt-rhythm-source-review.md`. The final SHA differs from reviewed
source `fa31ee9713d634ed1cddde75ed62c9aa71607125` only in truthful review-status
documentation. Source/config remain identical and whitespace hygiene passed.

The complete one-human source path and applicable disposable validation now pass.
The human opts in, makes route/target decisions, observes the bounded kill-chain
bonus, experiences timeout/death reset, retries and stops. Optional bots need only
ordinary combat/follow behavior; the same primary loop works solo.

CI validates compilation, configuration/module loading and server startup, not
actual kill awards, client messages, pet/group behavior or gameplay feel. Those
remaining uncertainties reasonably require the documented later in-game checklist.
The immutable candidate is not edited to insert its own final SHA or this later
attestation; Director records acceptance externally on main.
