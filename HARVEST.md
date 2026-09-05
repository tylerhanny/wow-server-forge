# WoW Server Forge — Final Harvest

Only projects that pass the mandatory finish gate in `AGENTS.md` may appear in the READY section.

`Almost done`, prototypes, ideas, and unverified implementations belong elsewhere.

## READY FOR LIVE TEST

### Hunt Rhythm — Practical

**Delivered early on 2026-09-05.** Opt-in outdoor leveling streaks reward choosing routes
and sustaining ordinary eligible kills, with a modest base kill-XP bonus capped at 10%
by default. It provides a repeatable solo leveling loop without custom SQL, NPCs or economy.

[Download the accepted module, owner guide and evidence](https://github.com/tylerhanny/wow-server-forge/releases/tag/mod-hunt-rhythm-v1).
Release tag targets the exact accepted SHA; the uploaded ZIP digest matches the source package below.

- Exact candidate: `4aaa3ae188e7bcdba2569676911e14142ac378e2`, branch `project/hunt-rhythm`;
  its unchanged project tree is integrated on main.
- Exact target: AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu 24.04 x86-64, client 3.3.5a build 12340.
- [Official run 33951428776](https://github.com/tylerhanny/wow-server-forge/actions/runs/33951428776)
  PASS under judge `e35e85a787d7576d58cb691f6335b638ee8bc342`: full compilation,
  installation, config/data/SQL checks, auth/world dry-runs, native unit tests and final
  dependency integrity. Actual native module loader/config marker observed; Errors.log empty.
- Independent source, actual artifact and **ONE_HUMAN_REVIEW=PASS**.
- [Final attestation](handoffs/mod-hunt-rhythm.md), [independent review](reviews/mod-hunt-rhythm-final-review.md),
  [machine-readable evidence](deliveries/evidence/mod-hunt-rhythm-33951428776.json),
  [exact install/config/rollback and one-human smoke guide](deliveries/mod-hunt-rhythm-install.md).
- Source package: `mod-hunt-rhythm-4aaa3ae.zip`; SHA256
  `72f4b97e6ad9c2b59c7cbc8c666e07ba43de5090c27ae76d4e269db5b53af6fb`.

One human can start with `.rhythm start`, reach the six-kill default cap, fail by timeout
or death, retry and exit with `.rhythm stop`, using one ordinary character and stock client.
Bots are optional ordinary combat companions; they operate no custom mechanics.
The linked guide covers exact ordered steps and lifecycle/exclusion checks.

Remaining **PENDING LIVE/IN-GAME VALIDATION**: real XP/class/pet/rested/RAF interactions,
route pacing and bot behavior/feel. Other XP-modifying modules were not part of this
validated combination. State is session-only; disabling/removing never subtracts earned XP.
The gate retained four visible verified upstream warnings and no project warnings. Native
tests selected 11,395: 5,909 passed, 5,486 native conditional skips, one pre-existing disabled
test; no Forge test was removed or weakened. See final evidence for exact identities.

### Field Camp — Practical, subordinate

**Delivered early on 2026-09-05.** A personal session camp completes a solo supply-trip
loop: set a camp, travel normally to a same-map town, sell/repair, step outdoors and return
with a bounded cooldown. It requires no SQL, payment, custom NPC or companion.

[Download Field Camp, owner guide and evidence](https://github.com/tylerhanny/wow-server-forge/releases/tag/mod-field-camp-v1).
The release targets the exact accepted SHA; its uploaded source digest matches the package below.

- Exact candidate `796e27e9cfcd05f4c4e4c627e26834ea7be72155`, branch `project/field-camp`;
  tested project source is integrated unchanged on main. Same exact AC/Playerbots/client/
  Ubuntu target as Hunt Rhythm above.
- [Official run33955341216](https://github.com/tylerhanny/wow-server-forge/actions/runs/33955341216)
  PASS under judge `1ea9a4b3671c763b286f681e983e9499c7cb35af`: complete compilation,
  installation, config/data/SQL applicability, auth/world dry-runs, units and final integrity.
  Native loader/config marker observed; Errors.log empty.
- Independent source, artifact and **ONE_HUMAN_REVIEW=PASS**.
- [Final attestation](handoffs/mod-field-camp.md), [independent review](reviews/mod-field-camp-final-review.md),
  [evidence](deliveries/evidence/mod-field-camp-33955341216.json), and
  [exact install/config/rollback and one-human smoke guide](deliveries/mod-field-camp-install.md).
- Source package `mod-field-camp-796e27e.zip`; SHA256
  `0afa0e660d14a247776dad777d1ada8e7d4ecfa780b8b5885f7d4388d56bf8bf`.

One ordinary character uses `.camp set`, makes the supply trip, `.camp return`, observes
actual arrival separately from the request message, waits the default 600-second cooldown,
retries, and `.camp clear` to exit. The guide covers restriction failures and lifecycle.
No second human/client/operated account is needed. Bots are optional and are not transported.

Remaining **PENDING LIVE/IN-GAME VALIDATION**: actual landing/terrain/phase behavior,
other teleport hooks, pets, bots and travel feel. Same-map/exact-phase/session-only;
accepted requests consume cooldown before client acknowledgement. Ground checks do not
guarantee universal collision/navigation safety. No SQL or saved-position rollback exists.
The earlier failed private API call is preserved in its review record; the accepted repair
retains equivalent public delayed-teleport rejection. Four upstream warnings remain visible,
project warnings remain fatal, and native unit counts are 5,909 pass / 5,486 native skip /
one pre-existing disabled, with no Forge weakening. See exact evidence for full scope.

### Stormwright — Wildcard flagship

**Delivered early on 2026-09-05.** A repeatable level80 encounter where one human pilot
routes tracking lightning into capacitors, dodges the locked strike, and chooses healing/
ward repair or an offensive discharge and armor opening. Three presets change the cadence.
Optional ordinary bots fight; the human operates every custom mechanic.

[Download Stormwright, owner guide and evidence](https://github.com/tylerhanny/wow-server-forge/releases/tag/mod-stormwright-v1).
The tag targets exact60c6a91 and all uploaded asset digests match the reviewed local files.

- Exact candidate `60c6a91925eed80049bec47994f87df739ac7725`, branch `project/stormwright`;
  its tested project tree is integrated unchanged. Same exact target pins/client/OS as above.
- [Official run33960843535](https://github.com/tylerhanny/wow-server-forge/actions/runs/33960843535)
  PASS under judge `e5fd277de515dbda983993e6f8a52b48cb0816b4`: full build/install/config/SQL,
  both dry-runs, native units, executable rules, normal startup and final dependency integrity.
- Actual registrar spawn observed at map1 XY(-6250,-3790), derived Z=-58.700077;
  owned SQL identities verified, clean console shutdown exit0, Errors.log empty.
- Independent source, actual artifact and **ONE_HUMAN_REVIEW=PASS**.
- [Final attestation](handoffs/mod-stormwright.md), [independent review](reviews/mod-stormwright-final-review.md),
  [evidence](deliveries/evidence/mod-stormwright-33960843535.json), and
  [exact install/config/SQL/rollback and one-human tests](deliveries/mod-stormwright-install.md).
- Source package `mod-stormwright-60c6a91.zip`, SHA256
  `2b773f50d90f926194b0be5e6f04ba3274bd8aee7c8ab3b178cff9d46d0efac9`.

Travel normally to Nix Stormwright north of Mirage Raceway. Start Normal Solo Pilot
without bots, catch/evade lightning, choose Ground or Discharge, defeat the storm, read
the result, retry and abort through ordinary gossip. No second human/client/account is
needed. Optional party scaling never assigns custom decisions to bots. No persistent
power, economy or ranking reward is added; results are session-only.

**PENDING LIVE/IN-GAME VALIDATION:** the complete player encounter, ordinary access and
navigation, visual readability, class/gear balance and bot competence/feel. Server startup
is not a client playthrough. Both prior failures remain preserved. Four verified upstream
warnings remain visible; project warnings remain fatal. Native units:5909 passed,
5486 native conditional skips, one pre-existing disabled test. Current cache restore was
a MISS with1830 misses/0hits and successful save; no acceleration is claimed.

### Field Repairs — additional Practical

**Delivered early on 2026-09-05.** Explicitly confirmed native personal-gold
repairs save a vendor detour while preserving real repair costs and possible partial
results. One ordinary human operates the full request/confirm/outcome/retry/cancel loop.
No SQL, NPC, free repair, guild spending, automatic payment or bot repair is added.

[Download Field Repairs, owner guide and evidence](https://github.com/tylerhanny/wow-server-forge/releases/tag/mod-field-repairs-v1).
The tag targets the exact accepted SHA and all three uploaded asset digests match local files.

- Exact candidate `1450d92f8bcf3a8282526120753ed5f750939722`, branch `project/field-repairs`;
  tested project source is integrated unchanged. Same exact target pins/client/OS as above.
- [Official run33970121674](https://github.com/tylerhanny/wow-server-forge/actions/runs/33970121674)
  PASS under judge `8d21e8b1b4920b4966760ba621751725bd411444`: full configure/build/install,
  config/SQL applicability, auth/world dry-runs, native units and final source integrity.
- Actual marker `FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`; Errors.log empty.
  Independent source, actual artifact and **ONE_HUMAN_REVIEW=PASS**.
- [Final attestation](handoffs/mod-field-repairs.md),
  [independent review](reviews/mod-field-repairs-final-review.md),
  [evidence](deliveries/evidence/mod-field-repairs-33970121674.json), and
  [exact install/config/rollback and one-human guide](deliveries/mod-field-repairs-install.md).
- Source ZIP `mod-field-repairs-1450d92.zip`, six exact Git-blob files; SHA256
  `6e266bc2dd1becb1ae0b036e521f4f3d31d5e8a13a8c8fb862bb4732215372d3`.

Use `.fieldrepair status`, request, confirm within 30 seconds and compare real gear/gold.
Cancel or let consent expire without payment; earn gold normally and retry partial/no-fund
results. Safely outdoors, alive, out of combat/PvP and without active casts or travel/control
restrictions; the guide lists the exact conditions. No second human/client/account needed.

**PENDING LIVE/IN-GAME VALIDATION:** native pricing/partial ordering, actual durability/stat
updates, consent usability, other modules' callbacks and bot-party coexistence. No quote,
atomic repair-all transaction or refund is promised. Disabling/removing does not reverse
completed native repairs/payments. Four upstream warnings remain visible and project
warnings remain fatal. Native units: 5909 pass / 5486 native skip / one pre-existing disabled.
The existing cache produced 1826 preprocessed hits / 4 misses and a 7m02s full compile;
all current-candidate validation still ran. No per-warning cache-hit attribution is claimed.

### Triage Night — additional Wildcard

**READY FOR LIVE TEST — delivered early on 2026-09-05 after the owner's safe pause.**
One level-80 priest uses ordinary healing spells, real mana and two finite stabilization
charges to keep three persistent patients alive through five injury rounds. Warned bursts,
rotating priorities and Training/Veteran pressure support repeat practice, with normal
success/failure, per-login results, recovery/retry and abort. No bot or second human is needed.

- Exact candidate `b404a1bd4614a8b956187f17baf585eee6d16cf6`, on its unchanged authorized
  public branch `project/triage-night`.
  [Browse the exact module source](https://github.com/tylerhanny/wow-server-forge/tree/b404a1bd4614a8b956187f17baf585eee6d16cf6/projects/mod-triage-night).
- [Official run33971943070](https://github.com/tylerhanny/wow-server-forge/actions/runs/33971943070)
  PASS under judge `8070cf87ba160d08c507e98dc809a949c573f986`: complete pinned
  configure/build/install, native SQL application/config loading, auth/world dry-runs,
  native tests and final dependency integrity. Same exact pins/client/OS as the other modules.
- Independent source, SQL/reference, actual artifact and **ONE_HUMAN_REVIEW=PASS**.
- [Final handoff](handoffs/mod-triage-night.md),
  [independent final review](reviews/mod-triage-night-final-review.md),
  [evidence](deliveries/evidence/mod-triage-night-33971943070.json), and
  [exact install/config/SQL/rollback and one-human guide](deliveries/mod-triage-night-install.md).
- Local source ZIP `mod-triage-night-b404a1b.zip`, ten exact candidate files; SHA256
  `e3f550732ae110f6e2f37a01ae56a86de8b23650b341613cde2ba83d92b08e68`.
  The guide can also export the module directly from the already-published exact commit.

Use `.triage help`, then `.triage start` on suitable outdoor ground with one ordinary
level-80 priest. Heal the numbered patients, react to warnings and use `.triage stabilize
1`, `2` or `3`. Keep all patients alive for five45second rounds, observe the result, rest
normally and retry. `.triage status` shows state/results and `.triage stop` aborts.
The guide contains the complete ordered test and source package has a90second capture plan.

The native world log applied `2026_09_05_00_triage_night.sql` (checksum98F6E4C), observed
the enabled config marker and finished startup with Errors.log empty. Four owned templates
and model rows use911100–911103; no permanent spawns or player/economy records are added.
Rollback SQL is identity-bound and source-reviewed, not executed in CI. Owner database
collision checks remain required. Four upstream warnings remain visible and project
warnings remain fatal. Native units:5909 pass /5486 native skip /one pre-existing disabled.

**PENDING LIVE/IN-GAME VALIDATION:** actual direct-heal targetability, stock UI/poses,
terrain, gear/mana pressure, stabilization feel and replay value. Scripted loss bypasses
shields; other healer classes, party/AoE support and bot assistance are unclaimed. The
official run did not log in a priest or jointly validate all five Forge modules together.
The earlier pause and publication rejections are resolved; no unchanged source was rerun.

All five authorized modules are independently accepted and available for owner testing.
No project slots remain. Existing source stays frozen except actual owner-reported fixes.
The fixed handoff remains2026-09-06T12:34:32Z, followed by the protected six-hour owner window.

## Current run totals (not final)

```text
Attempted: 5
Ready for live test: 5
Blocked: 0
Under official validation: 0
Final handoff pending: 0
Abandoned: 0
Research only: 0
Wildcard-ready projects: 2
Live server changes: 0 (must remain 0)
```

## Integrity rule

No project enters READY without satisfying locked `ONE_HUMAN_PLAYABILITY.md`, including
an explicit independent PASS and required README/final-handoff section. Optional human
multiplayer cannot conceal an incomplete one-human primary loop.

The final report must not inflate completed-project counts by splitting one coherent module into trivial subprojects.
