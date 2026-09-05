# Triage Night — final independent acceptance and owner handoff

```text
PROJECT=mod-triage-night
OWNER=Wildcard
BRANCH=project/triage-night
CANDIDATE_SHA=b404a1bd4614a8b956187f17baf585eee6d16cf6
STATE=READY_FOR_HARVEST
OWNER_DELIVERY=READY FOR LIVE TEST; delivered early 2026-09-05 after owner safe pause
BUILD_RESULT=PASS_REAL_FULL_PINNED_BUILD
OFFICIAL_GATE=PASS
ONE_HUMAN_REVIEW=PASS
REVIEWER=Independent source, SQL/reference and actual-artifact review PASS
NEXT_ACTION=Owner installation and one-human playtesting; report actual findings
```

This external main-branch attestation records acceptance of the unchanged candidate on its
owner-authorized public project branch. It supersedes that candidate's truthful pending
pre-run status; no different implementation is represented as tested. The owner paused
after final review passed, then explicitly resumed at2026-09-05T16:37:25Z. No repeat gate,
candidate alteration, new project or additional source publication was needed for delivery.

## Feature and exact delivery

One level-80 priest keeps three persistent patients alive through five authored injury
rounds. Ordinary healing spells, real mana, warned bursts and two finite stabilization
charges create target, spell and timing decisions. Training and Veteran vary pressure.
Results, normal rest/retry and clean abort complete the loop; there are no player resource
refills, permanent rewards, helper bots or additional operators.

- [Exact approved source](https://github.com/tylerhanny/wow-server-forge/tree/b404a1bd4614a8b956187f17baf585eee6d16cf6/projects/mod-triage-night).
- Local source ZIP: `mod-triage-night-b404a1b.zip`, ten files matching the frozen Git blobs.
  SHA256 `e3f550732ae110f6e2f37a01ae56a86de8b23650b341613cde2ba83d92b08e68`.
- [Exact installation/config/SQL/rollback and smoke guide](../deliveries/mod-triage-night-install.md).
- [Independent final review](../reviews/mod-triage-night-final-review.md) and
  [machine-readable evidence](../deliveries/evidence/mod-triage-night-33971943070.json).

Install the complete module as `modules/mod-triage-night` using native discovery, then
reconfigure/build/install the pinned server into a separate disposable prefix. Use installed
`etc/modules/mod_triage_night.conf.dist` as the source for its `.conf` override.
`TriageNight.Enable=1` enables the module; any successful config reload ends active shifts.
Retain native `Logger.module=4,Console Server` to observe INFO configuration, start and result
markers. The guide supplies exact shell commands, failure checks and SQL lifecycle choices.

Owned SQL `data/sql/db-world/2026_09_05_00_triage_night.sql` inserts only templates/models
911100–911103. Before installing, check those IDs and updater history for collisions.
Use native updates or the documented manual-once path, never both over untracked SQL.
There are no permanent spawns or character/auth changes. Disable with Enable0 and reload
or restart. Full removal stops the server, preserves/removes the module and installed
configs, rebuilds into a separate prefix, then uses identity-bound `sql/uninstall_world.sql`.
That rollback was source-reviewed; it was not executed in CI. Updater history is retained.

## Complete official evidence

- Exact candidate `b404a1bd4614a8b956187f17baf585eee6d16cf6`; reviewed source
  `e8907bd72940628148150621d7c8143624c47045`, followed only by review-status documentation.
- [Run33971943070](https://github.com/tylerhanny/wow-server-forge/actions/runs/33971943070)
  SUCCESS; validation job completed2026-09-05T14:40:41Z under default-branch judge
  `8070cf87ba160d08c507e98dc809a949c573f986`.
- Workflow SHA256 `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Exact AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu24.04 x86-64, stock3.3.5a build12340.
- Artifact9971337715,878092bytes; API archive digest
  `e33d00961ae2bc4b37d163d3910def2e00c5c1df1d1c4822cf180b351f4010bd`.
  Extracted files were independently hashed; the archive digest is API metadata.

The unchanged judge configured Clang18, Release, static scripts/modules, all applications,
WITH_WARNINGS=ON and BUILD_TESTING=ON with protected source-provenance warning enforcement.
The exact configure options are in the immutable workflow. The protected build ran
`cmake --build ac/build --config Release -j 5`, then installed with
`cmake --install ac/build --config Release`. Full captured build203152bytes returned0,
matching stream/receipt SHA256
`6e55eaa6a2bf9ec59608952f16d9f83361c6dcc31846e63f8818dba2ba9c7a42`.

All1830 compile commands retain Werror;1822 verified upstream-only demotions leave both
candidate translation units strict. Four unchanged Playerbots warnings remain visible,
with no project/unknown warning or error. All ten protected judge hashes and the3634-source
before/after inventory match. Both dependencies are Git-clean. The exact authorized
WorldMock test-fixture correction was identified, confined to disposable CI and restored
before install; production source/pins are unchanged and no corrected fixture is shipped.

Native loader/configuration and both server dry-runs succeeded, with empty Errors.log.
The world log applies the exact owned SQL with checksum98F6E4C, then completes world
initialization and termination. It observes:

```text
TRIAGE_NIGHT_CONFIG reload=false enabled=true; priest solo, no OnStartup actors, active shifts end on reload
```

Native tests selected11395 from83 suites:5909 passed,5486 native conditional skips and
one pre-existing disabled test. The16 protected tests and real compiler probe also passed.
The project-local schedule assertions compiled. The Stormwright-only normal-startup
supplement was correctly inapplicable; no logged-in Triage shift was simulated.
The cache recorded1826 preprocessed hits and4 misses, with443seconds full compilation;
all current-candidate checks executed. No per-warning cache-hit attribution is claimed.

## One-Human Playability

Independent **ONE_HUMAN_REVIEW=PASS** for the complete solo priest path and applicable
disposable evidence. One level-80 priest with ordinary learned direct single-target heals
and healing gear, one human/client/account and zero bots can perform every action. Other
healer classes and party/AoE compatibility are unclaimed. Bots provide no healing or custom
action; three patients stay fixed and presets change injury pressure, not group scaling.

Exact manual order, entirely **PENDING LIVE/IN-GAME VALIDATION**:

1. Alone on safe dry outdoor ground, alive, unmounted, out of combat/not casting and
   unflagged for PvP, read `.triage help` and `.triage start` (Training). Face open ground;
   no fixed NPC, GM venue, second client or helper is required.
2. Confirm all three numbered patients are visible/selectable/friendly and accept your
   ordinary direct heals. During the shift, normal casts/channels remain allowed. Stay
   within20horizontal/5vertical yards on the same map and exact phase, without mounted,
   flight/taxi/transport/vehicle, pending teleport or charm state.
3. Observe the10second briefing, five45second rounds and four10second breaks. Patient
   wounds and real player mana persist. Prioritize heals and the four-second burst warnings.
4. Use `.triage stabilize 1`, `2` or `3` during an injury round on a visible unstabilized
   patient. Verify a six-second pause without healing, no stacking and only two total
   charges. Invalid requests consume none. Scripted loss deliberately bypasses shields.
5. Keep all three alive through the fifth round; read the result and `.triage status`.
   Rest normally and retry, including Veteran. No mana/health/economic reward is granted.
6. Allow lethal injury to observe patient-lost failure and cleanup, then retry. The module
   uses a dead pose at one health before cleanup, not a normal corpse. Test `.triage stop`,
   radius/map departure, death/logout and config reload/disable cleanup. History retains
   the last five results this login; a six-minute hard cap bounds each shift.

The source package's `docs/DEMO.md` gives a future90second capture sequence and checklist.
Actual targetability, health bars/poses, terrain, gear/mana pressure, replay value, bot
coexistence and other-module interactions remain manual. CI did not play an encounter or
jointly validate Triage with the other Forge modules. No live server was accessed.
