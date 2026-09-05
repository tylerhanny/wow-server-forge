# Field Camp — independent final acceptance

**READY FOR LIVE TEST. Independent review PASS; ONE_HUMAN_REVIEW=PASS.**
Reviewer disposition: 2026-09-05, after inspecting the exact implementation, repaired
candidate and complete official evidence. Actual client/gameplay checks remain pending.

## Exact accepted checkpoint

- Candidate: `796e27e9cfcd05f4c4e4c627e26834ea7be72155`, `project/field-camp`.
- Reviewed repaired source: `6ce52323b96be5dba4f4dfea5668032d17acdc3a`.
  Final candidate differs only in three review/evidence documents; source/configuration
  byte identity and `git diff --check` were independently checked.
- Official run: [33955341216](https://github.com/tylerhanny/wow-server-forge/actions/runs/33955341216), **SUCCESS**.
- Judge: `1ea9a4b3671c763b286f681e983e9499c7cb35af`.
- Judge workflow SHA-256: `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Artifact: `9967556076`, 877,076 bytes; GitHub API archive digest
  `e147d0f4112c7102d2c26b4210041b3170dac6c46b2e38abbf815346c525106a`.
  The archive digest is API metadata; extracted evidence was independently hashed.
- Validation job completed `2026-09-05T10:07:34Z`.

Both exact dependency pins remain unchanged: AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. No production dependency patch is required.
The earlier candidate `ec9eea979c9344853aaf02d46ba9f6632636254b` and run `33952603462`
remain failed, as documented in `mod-field-camp-compile-repair-review.md`.

## Verified execution and integrity

All applicable official stages succeeded: scope, pinned discovery/configuration, complete
compilation, install, SQL/data checks, both dry-runs, required unfiltered upstream units,
final dependency integrity and evidence publication. The Stormwright-specific supplemental
step was correctly inapplicable. The module has no SQL.

- Complete build capture: 203,040 bytes; SHA-256
  `a6343cd280846d62785bfe7f1797432be6c78234622971bb6f8c7f90308a0d59`.
  Stream and persisted hashes agree, capture is complete and process returned 0.
- All ten protected hashes match raw Git blobs at the exact judge. Pre/post source
  identities match: 3,634 tracked sources, inventory SHA-256
  `c0a0a00c908bd7ac8e7063021360b32fb7b9c32c023590ae343b98e33980fec9`.
- All 1,829 compiler commands retain `-Werror`; upstream demotion is confined to the
  1,822 inventoried upstream translation units. The project remains strict.
- Exactly four verified upstream warnings are visible: BTHelpers:107,
  HyjalHelpers:168/209 and HyjalScripts:39. Header/context/source provenance and compiler
  summary counts agree. No project warning or compiler error is accepted.
- Exact authorized WorldMock original/corrected/post-build/restored identities and
  all-other-source integrity are attested and independently verified. The corrected
  fixture is excluded from upstream warning allowance; no full modified header is exported
  or installed, and no assertion/test selection is changed.
- Native loader calls `Addmod_field_campScripts()`. Installation includes the module's
  configuration. Actual world dry-run output contains `mod_field_camp.conf` and
  `FIELD_CAMP_CONFIG reload=0 enabled=1 cooldown=600; session camps and cooldowns cleared`.
  Both dry-runs complete, Playerbots initializes, world initialization completes and
  `Errors.log` is present with zero bytes.
- Required upstream units: **11,395 selected / 83 suites; 5,909 passed; 5,486 native
  conditional skips; one pre-existing disabled test**. This does not mean 11,395 passed.
  Protected selftests and the real compiler provenance probe also passed.

## Actual cache observations

The Actions log explicitly reports a restore miss. Effective ccache configuration matches
the approved policy: compiler content hashing, `direct_mode=false`, `run_second_cpp=true`,
no sloppiness/remote storage/debug, and temporary files outside the persisted cache.
Statistics show 1,829 cacheable calls, **zero hits and 1,829 misses**; stored size is reported
as 0.1 GB / 1.5 GB (5.08%). A successful cache save is logged at `10:07:31Z`.

The compile step ran `08:30:53–10:05:58Z`: **95m05s**, versus Hunt Rhythm's **58m54s**.
This cold run proves actual cache use and saving, not acceleration or cached-warning replay.
No causal claim or separate cache-only control follows from this timing difference.

## One-human and remaining manual checks

One ordinary player can set a safe session camp, take a normal same-map supply trip,
request return, inspect status, retry after cooldown and clear/replace the anchor. No bot,
second client or operated account is required. The repaired public teleport-state check
preserves delayed-transfer exclusion; all other safety and cooldown rules are unchanged.

CI does not simulate client teleport acknowledgement or arrival. Actual landing, terrain,
phase/PvP changes, coexisting teleport hooks and pet/bot regrouping remain explicitly
pending in the README's in-game checklist. The accepted source and evidence support owner
installation/testing; they do not claim those manual behaviors were exercised.
