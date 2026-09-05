# Field Camp — final independent acceptance and early handoff

```text
PROJECT=mod-field-camp
OWNER=Practical
BRANCH=project/field-camp
CANDIDATE_SHA=796e27e9cfcd05f4c4e4c627e26834ea7be72155
STATE=READY_FOR_HARVEST
OWNER_DELIVERY=READY FOR LIVE TEST; delivered early on 2026-09-05
BUILD_RESULT=PASS_REAL_FULL_PINNED_BUILD
OFFICIAL_GATE=PASS
ONE_HUMAN_REVIEW=PASS
REVIEWER=Independent Reviewer/Closer; source and actual artifact review PASS
NEXT_ACTION=Owner one-human installation/playtesting; preserve primary Stormwright priority
```

This external main-branch attestation supersedes the frozen candidate's pending pre-run
status without changing its tested project tree. The original ec9eea9 compilation failure
in run 33952603462 remains failed; its install/runtime/unit stages never ran. The accepted
candidate removes the private API call while retaining the public predicate that rejects
both delayed-teleport paths. No dependency or judge change was used to repair the module.

## Feature and installation

Set a personal camp on dry outdoor ground, make a normal same-map supply trip, step
outdoors and request return. Commands are `.camp set`, `.camp status` (or `.camp`),
`.camp return` and `.camp clear`. Default cooldown is 600 seconds. There is no module
SQL, payment, custom NPC, persistent record or bot transport.

[Exact install/configuration/rollback and ordered one-human tests](../deliveries/mod-field-camp-install.md).
Source package `mod-field-camp-796e27e.zip` has four module files, each matching its frozen
Git blob; SHA256 `0afa0e660d14a247776dad777d1ada8e7d4ecfa780b8b5885f7d4388d56bf8bf`.
The exact tested source is integrated at `projects/mod-field-camp/` on main. Its archived
pre-run documents remain preserved; this final attestation supplies the later acceptance.

Logging erratum: the frozen README incorrectly calls the native module logger's default
a warning threshold. At this exact pin, WARN=3 and INFO=4; native `Logger.module=4,Console Server`
already permits INFO. Retain level4 as used in the successful official run. The corrected
external guide supersedes that documentation claim without altering the accepted project tree.

## Exact independent evidence

- Candidate `796e27e9cfcd05f4c4e4c627e26834ea7be72155`.
- [Official run 33955341216](https://github.com/tylerhanny/wow-server-forge/actions/runs/33955341216)
  passed every applicable stage; validation job completed at 2026-09-05T10:07:34Z.
- Judge `1ea9a4b3671c763b286f681e983e9499c7cb35af`; workflow SHA256
  `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Exact AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu 24.04 x86-64,
  stock client target 3.3.5a build 12340.
- Artifact 9967556076, 877,076 bytes; GitHub API archive digest
  `e147d0f4112c7102d2c26b4210041b3170dac6c46b2e38abbf815346c525106a`.
  Extracted file hashes were independently verified; the archive digest is API metadata.
- [Machine-readable audit](../deliveries/evidence/mod-field-camp-33955341216.json),
  [final independent review](../reviews/mod-field-camp-final-review.md), and
  [preserved compiler failure/repair](../reviews/mod-field-camp-compile-repair-review.md).

The exact judge configures Clang 18, Release, all applications, static scripts/modules,
WITH_WARNINGS=ON, BUILD_TESTING=ON, NOPCH=true, ccache launchers and both language flags
`-Werror -ferror-limit=0`, with protected source-provenance/warning enforcement. Its exact
configure command remains in the immutable workflow/run. The protected build wrapper ran
`cmake --build ac/build --config Release -j 5`; complete captured log and stream match
SHA256 `a6343cd280846d62785bfe7f1797432be6c78234622971bb6f8c7f90308a0d59`, return 0.
`cmake --install ac/build --config Release` succeeded into the disposable server prefix.

All 1,829 compile commands retain Werror, with 1,822 verified upstream-only demotions;
project compilation remained strict. Four verified unchanged Playerbots warnings are
visible; no project warning or error was accepted. All ten protected judge hashes match
exact Git blobs. The owner-authorized WorldMock two-method patch was verified, confined
to disposable CI and restored before install, without exporting its corrected header.
The 3,634-source before/after inventory matches; dependency pins and final Git-clean checks
passed. No production dependency was repaired or changed.

Native loader registration and installed module config are verified. The actual world
log loads `mod_field_camp.conf` and prints `FIELD_CAMP_CONFIG reload=0 enabled=1 cooldown=600;
session camps and cooldowns cleared`. Both auth/world dry-runs completed; Errors.log is
empty. No module SQL exists; the data/SQL applicability check passed. The Stormwright-only
normal-startup step was inapplicable to this separate candidate, not a waived requirement.
The 16 protected tests and real compiler scope probe passed. Unfiltered native units
selected 11,395 tests: 5,909 passed, 5,486 native conditional skips and one pre-existing
disabled test. No Forge filtering, removed assertion or newly skipped test was used.

Cache evidence is a cold restore MISS, 1,829 misses and zero hits, with a successful
object-cache save. Effective configuration matches the reviewed policy. Full compilation
took 95m05s (Hunt took 58m54s); this proves use/save, not acceleration or cached-warning
replay. No additional control was run to measure caching.

## One-Human Playability

Independent ONE_HUMAN_REVIEW=PASS for the complete solo design/source and applicable
disposable evidence. One ordinary level 1–80 character of any class and one stock client
can set a safe camp, make a supply trip, return, observe the cooldown, retry after a normal
restriction ends and clear the camp. No second human, second client or second operated
account is required. No enemy scaling or helper is needed; the human performs all commands.

Ordered primary manual test: `.camp set` on safe dry outdoor ground; travel to a same-map
town, sell/repair, step outdoors and `.camp return`; observe both the request message and
actual arrival; confirm immediate repeat rejects, including after clear/rebind; wait the
cooldown and repeat; check jumping/swimming/combat/casting/death and map/phase mismatch
rejections; recover normally and retry; clear/relog to verify cleanup. Full edge cases,
configuration and removal steps are in the linked guide and exact frozen README.

Bots are optional ordinary companions and are not transported by the module. No custom
bot cognition or menu is required. Native pet handling and bot follow/regroup behavior
remain PENDING LIVE/IN-GAME VALIDATION. The complete useful solo loop needs no bots.

**PENDING LIVE/IN-GAME VALIDATION:** actual ground/phase behavior, arrival, travel feel,
other teleport hooks, pets and bots. Ground checks are not universal collision/navigation
or enemy-avoidance guarantees. The camp is same-map, exact-phase and session-only;
logout/restart/successful config reload clears anchor and cooldown. Native accepted
teleport requests consume cooldown before client acknowledgement; native rejection
refunds the reservation, though core cleanup can precede a veto. Removal stops future
camp actions and never rolls back ordinary saved character positions. No live server or
client was operated by the Forge. Any behavioral correction requires a new full candidate gate.
