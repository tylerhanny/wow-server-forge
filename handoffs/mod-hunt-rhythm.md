# Hunt Rhythm — final independent acceptance and early handoff

```text
PROJECT=mod-hunt-rhythm
OWNER=Practical
BRANCH=project/hunt-rhythm
CANDIDATE_SHA=4aaa3ae188e7bcdba2569676911e14142ac378e2
STATE=READY_FOR_HARVEST
OWNER_DELIVERY=READY FOR LIVE TEST; delivered early on2026-09-05
BUILD_RESULT=PASS_REAL_FULL_PINNED_BUILD
OFFICIAL_GATE=PASS
ONE_HUMAN_REVIEW=PASS
REVIEWER=Independent Reviewer/Closer; source and actual artifact review PASS
NEXT_ACTION=Owner one-human installation/playtesting; diagnose reported bugs without expanding scope
```

This main-branch final attestation supersedes the frozen candidate's honestly pending
pre-run handoff and README validation status. The tested project tree remains exactly
unchanged. No live server was accessed or modified. No client gameplay is certified.

## Feature and installation

Opt-in outdoor leveling streak: choose a route and make eligible ordinary kills within
60 seconds to progress through 0/2/4/6/8/10% capped base kill-XP bonuses. Timeout/death
resets the chain; opting out, relogging or successful config reload clears opt-in.
State is session-only. There is no SQL, custom NPC or reward inventory.

[Exact install/configuration/rollback and ordered manual tests](../deliveries/mod-hunt-rhythm-install.md).
Source ZIP: `mod-hunt-rhythm-4aaa3ae.zip`, six module files, all Git blobs matched against
the frozen candidate; SHA256 `72f4b97e6ad9c2b59c7cbc8c666e07ba43de5090c27ae76d4e269db5b53af6fb`.
The source is also integrated under `projects/mod-hunt-rhythm/` on main. The archive's
pre-run documents are preserved as tested; this external attestation supplies final status.

## Exact independent evidence

- Candidate: `4aaa3ae188e7bcdba2569676911e14142ac378e2`.
- [Official run33951428776](https://github.com/tylerhanny/wow-server-forge/actions/runs/33951428776):
  all mandatory stages SUCCESS; candidate job completed2026-09-05T08:05:00Z.
- Judge: `e35e85a787d7576d58cb691f6335b638ee8bc342`; workflow SHA256
  `8bc95aa73c0418b601e980529d13fb4f5fb414d33f3a0ba308dfa3333f092542`.
- AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu24.04 x86-64,
  stock client target3.3.5a build12340.
- Artifact9965830223,876416bytes; API SHA256
  `dc40e9e3b6ade2dd32a0c56ba2cd45111165a223eea9518253e668f33b78342c`.
- [Machine-readable independent audit](../deliveries/evidence/mod-hunt-rhythm-33951428776.json)
  and [final Reviewer report](../reviews/mod-hunt-rhythm-final-review.md).

The exact judge's configure command uses Clang18, Release, all applications, static
scripts/modules, WITH_WARNINGS=ON, BUILD_TESTING=ON, NOPCH=true, both compiler launchers
ccache, both language flags `-Werror -ferror-limit=0`, and its protected file-scoped
upstream-warning hook/inventory. Full configure command is preserved in the exact judge
workflow and run log. The protected wrapper executed `cmake --build ac/build --config
Release -j 5` and captured the entire stream with return0; build SHA256
`d56170889744b545e68eb5be07af0fb43639780f254093f7221363e684a28e45` matches receipt and log.
`cmake --install ac/build --config Release` succeeded into the disposable prefix.

All1830 compiler commands retain Werror, with1822 verified upstream-only demotions;
both project translation units remain strict. Exactly four unchanged pinned Playerbots
warnings are visibly retained with source provenance. No project warning or build error
was accepted. This is the standing owner-authorized upstream baseline, not a repaired dependency.
All nine protected validation file hashes match the exact judge. The authorized two-method
WorldMock correction was hash-verified, used only in disposable CI, restored before install,
and never exported as corrected source. The3634-source inventory matches before/after
restoration; dependency pins and Git-clean checks passed through final runtime integrity.

Install/module discovery/config/SQL-data gate PASS (no module SQL is shipped). The native
loader contains the correct module registration. Authserver and worldserver completed
both required dry-runs; Errors.log is empty. Actual world log evidence includes config
`mod_hunt_rhythm.conf` and `HUNT_RHYTHM_CONFIG reload=0 enabled=1 window=60 step=2 cap=10;
all sessions opted out`. The16 protected judge tests and real compiler scope probe passed.
The unchanged, unfiltered upstream unit executable selected11395 tests from83 suites:
5909 passed,5486 native conditional skips, and one pre-existing disabled test. Forge removed
or weakened no test. These native skips are disclosed, not counted as passes.

## One-Human Playability

Independent ONE_HUMAN_REVIEW=PASS for the complete solo design, source and applicable
disposable evidence. One ordinary level10–30 character, one stock client and no bots
can access `.rhythm status`, opt in with `.rhythm start`, select a safe outdoor route,
kill eligible creatures, earn the capped outcome, recover from failure, retry and stop
with `.rhythm stop`. No second real person, second client or second operated account is
required. No enemy scaling or helper requirement is added.

Ordered primary manual test: opt in outdoors; make six eligible kills less than60seconds
apart and inspect0/2/4/6/8/10%; let the chain expire and retry; recover after death;
stop, restart, then relog and confirm opt-out. Test exclusions and config lifecycle from
the linked guide and full frozen README. No module-created gold/items or permanent
progression requires rollback; earned ordinary XP is never subtracted on removal.

Optional ordinary pinned bots fight/tank/heal/follow only; the human owns every Rhythm
command, target and route decision. Bots need no custom cognition and never enroll
implicitly. Native shared XP credit remains authoritative. The entire loop remains
available without bots. Additional XP-changing modules are outside the validated combination.

**PENDING LIVE/IN-GAME VALIDATION:** real kill-XP amounts and rounding, class/pet/rested/RAF
interactions, route pacing, exclusions in real gameplay, lifecycle/player feedback and
ordinary bot behavior/feel. Dry-run loading and source arithmetic checks do not establish
those outcomes. Report actual observations against this exact SHA; any source/config/SQL
or installation-behavior correction becomes a new candidate requiring full revalidation.
