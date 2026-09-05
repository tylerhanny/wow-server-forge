# Stormwright — final independent acceptance and early handoff

```text
PROJECT=mod-stormwright
OWNER=Wildcard
BRANCH=project/stormwright
CANDIDATE_SHA=60c6a91925eed80049bec47994f87df739ac7725
STATE=READY_FOR_HARVEST
OWNER_DELIVERY=READY FOR LIVE TEST; delivered early on 2026-09-05
BUILD_RESULT=PASS_REAL_FULL_PINNED_BUILD
OFFICIAL_GATE=PASS
ONE_HUMAN_REVIEW=PASS
REVIEWER=Independent Reviewer/Closer; source and actual artifact review PASS
NEXT_ACTION=Owner one-human installation/playtesting and feedback fixes
```

This external attestation supersedes the frozen candidate's pending pre-run status.
The tested project tree is integrated unchanged on main. Original a155817 failed full
compilation in33952393192; the reviewed repair adds the intended owned actor GUID to
three impact packet calls. Candidate bde390e failed required normal-startup observation
in33955586542 because fixture logger3 suppressed required INFO4. The protected one-line
fixture correction was independently reviewed; candidate60c6a91 corrects documentation
only. Both prior failures remain failed. No project feature or dependency was waived.

## Feature, installation and rollback

Stormwright is a repeatable level80 encounter north of Mirage Raceway. The pilot routes
tracking lightning into capacitors, dodges the locked strike, and chooses Ground for
healing/ward recovery or Discharge for damage and an eight-second armor opening. Three
presets change the cadence. Optional ordinary bots fight; the human operates all mechanics.

[Exact install/config/SQL/rollback and ordered one-human smoke guide](../deliveries/mod-stormwright-install.md).
Ten source-package files match the frozen Git blobs. `mod-stormwright-60c6a91.zip` SHA256:
`2b773f50d90f926194b0be5e6f04ba3274bd8aee7c8ab3b178cff9d46d0efac9`.
The exact README also contains the creator's rationale,75-second demo and capture checklist.

Travel normally to Nix Stormwright, map1 XY(-6250,-3790), north of Mirage Raceway;
start/preset/abort use ordinary gossip. No special player command/item/addon/GM action.
`Stormwright.Enable=1`; retain native `Logger.module=4,Console Server` for INFO.
Useful evidence includes STORMWRIGHT_CONFIG, STORMWRIGHT_REGISTRAR, STORMWRIGHT_SITE_UNAVAILABLE
and STORMWRIGHT_* outcomes. The guide gives exact collision queries for creature/template-model
entries910900–910904 and npc_text910900, and mutually exclusive native/manual SQL paths.
There are no permanent world spawns, character/auth migrations or persistent rewards.
Disable via config/reload; restart removes the idle registrar. Full removal stops the server,
removes only this module, rebuilds and uses identity-matched owned SQL cleanup. Updater history
remains; reinstall may require explicit one-time import. Follow the linked exact commands.

## Exact independent evidence

- Candidate `60c6a91925eed80049bec47994f87df739ac7725`.
- [Official run33960843535](https://github.com/tylerhanny/wow-server-forge/actions/runs/33960843535)
  passed every required stage; job completed2026-09-05T12:12:24Z.
- Judge `e5fd277de515dbda983993e6f8a52b48cb0816b4`; workflow SHA256
  `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Exact AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu24.04x86-64, client3.3.5a12340.
- Artifact9969242731,881458bytes; API archive digest
  `8d61fd451b39c751d13410a4074424bda8a40e262794b4967e5567c95ccab8d1`.
  Extracted evidence was independently hashed; archive digest is GitHub API metadata.
- [Machine-readable audit](../deliveries/evidence/mod-stormwright-33960843535.json),
  [independent final review](../reviews/mod-stormwright-final-review.md),
  [compile failure/repair](../reviews/mod-stormwright-compile-repair-review.md),
  [runtime failure/fixture correction](../reviews/mod-stormwright-runtime-fixture-review.md).

Exact configure command is preserved in the immutable judge workflow/run: Clang18,
Release, all applications, static scripts/modules, WITH_WARNINGS=ON, BUILD_TESTING=ON,
NOPCH=true, ccache launchers and both language flags `-Werror -ferror-limit=0`, with
protected provenance enforcement. Build: `cmake --build ac/build --config Release -j 5`.
Full captured log/stream SHA256 `627dd74393987f3eabb26c6efa6510ceda82d88df903af0e59b6f1a04820818b`,
203150bytes, return0. `cmake --install ac/build --config Release` passed.

All1830 compiler commands retain Werror;1822 verified upstream-only demotions, both
candidate units strict. Four verified unchanged Playerbots warnings remain visible;
no project warning/error was accepted. All ten protected hashes match exact judge blobs.
The exact authorized WorldMock fixture delta was verified before/after compilation and
restored before install. All3634 tracked source identities/final Git-clean checks agree;
no production dependency edit or corrected full-header export occurred.

Native loader/config, both dry-runs and unfiltered native units passed:11395 selected
in83 suites,5909 passed,5486 native conditional skips, one pre-existing disabled test.
All16 protected selftests, real compiler probe and strict standalone rules tests passed.
Installed SQL has the exact five script rows, five model mappings and owned text row.
Fully hashed public terrain supplied22018 maps/vmaps/mmaps files, retaining original
ac-data DBC commit74643b700b1cd806845a1dfd926a2c46e7890dbe. Normal startup actually observed:
`STORMWRIGHT_REGISTRAR spawned=true map=1 x=-6250 y=-3790 derived_z=-58.700077`.
After the required interval, console info/exit returned0 and logged `Halting process...`.
Errors.log was present/empty; final dependency integrity passed. Exact hashes are in the audit.
Cache restore MISS,1830 misses/0hits, successful save; compile97m11s. No acceleration claimed.

## One-Human Playability

Independent **ONE_HUMAN_REVIEW=PASS** for complete solo design/source and applicable
disposable evidence. One living level80 human and one stock client can start Normal
Solo Pilot without bots, bait/evade lightning, operate all rods, win/fail, inspect the
outcome, retry and abort. No second human/client/operated account is required.
Solo retains the complete mechanic, one pursuing add maximum and personal healing.
Each missed catch removes one ward point; Ground restores one. Three cumulative misses
with recovery need not fail. The no-recovery condition clarifies the frozen README smoke step.

Manual primary test: walk to Nix; start Normal Solo Pilot; the first mark arrives12seconds
after start, then Normal gives4seconds tracking and2seconds locked escape;
route tracking into a ready rod and dodge after lock; Discharge for boss damage, armor
opening and nearby owned-add elimination; catch again and Ground while injured; miss
and repair ward; win, observe one result/cleanup and retry. Then fail by three misses without Ground recovery (ward reaches zero),
exit and abort; test death/logout and12-minute timeout, cleanup and fresh retry. Try
higher presets after the base loop. The linked guide provides exact ordered steps.

Optional pilot-led parties up to five freeze nearby living level80 members into scaling;
boss/add health scales by(roster+1)/2, grouped play caps pursuers at two. Ordinary bots
tank/heal/attack/follow only; the human handles every custom menu/rod/position decision.
No bespoke cognition, precision bot choreography or additional human is assumed.

**PENDING LIVE/IN-GAME VALIDATION:** full encounter playthrough, ordinary access/return,
terrain navigation/collision, rod clickability, visuals, class/gear balance and actual
bot competence/feel. Public assistance is possible; session-only results provide no
persistent reward or fair ranking. Server startup is not a client playthrough. No live
server/client was operated. Behavior fixes require a new candidate, review and full gate.
