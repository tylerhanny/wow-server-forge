# Validation record

State: **IMPLEMENTED CANDIDATE; acceptance and actual gameplay pending.**

## First official build and repair

Official run `33952393192` for candidate
`a1558178ceee2b92e020928ecb8fd3f59c3c34a2` failed full compilation.
`build.log:1829–1833` reported Stormwright.cpp:277 calling
`SendPlaySpellImpact` with one argument; exact Unit.h:2034 requires
`SendPlaySpellImpact(ObjectGuid guid, uint32 id)`.
All three impact calls now supply the corresponding owned rod, boss or marker GUID.
Pinned Unit.cpp:15210–15219 confirms the first value is the packet's target.
The repair changes no gameplay rule, damage, timing, SQL, configuration, dependency
or judge input. Independent SOURCE_REVIEW=PASS and ONE_HUMAN_REVIEW=PASS were received
for repair commit `a65f162419c8d0c0cc1ddbad2f35b7b4450018c8`. The subsequent
docs-only candidate was `bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc`.
The failed candidate and its evidence are preserved.

The failed run did not reach install, SQL/startup, unit execution or supplemental
normal-world checks. Those outcomes must not be inferred from configure/discovery
or the partial build.

## Second official run: successful stages and supplemental failure

Run `33955586542` for exact candidate
`bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc` passed full compilation, installation,
the authserver/worldserver dry-runs, native unit execution and the existing standalone
Stormwright rules test. `stormwright-installed-sql.tsv` contains the expected five
script-bound templates, five exact model rows and npc_text 910900. The build-stage
warning verdict is PASS with four disclosed, verified upstream warnings; project
warnings remain fatal. The source and exact pins were not changed to obtain these results.

The required normal-startup supplement timed out after five minutes: the real
worldserver reached ready and world updates, but neither STORMWRIGHT_REGISTRAR nor
STORMWRIGHT_SITE_UNAVAILABLE appeared. The independent Reviewer established a fixture
defect: pinned `LogCommon.h` defines WARN=3 and INFO=4, but the helper changed
`Logger.module` to 3, suppressing the registrar's INFO line. Native logger default 4
already permits INFO. The README's corresponding incorrect logger guidance is corrected
in this docs-only checkpoint. The supplemental fixture correction belongs to the
independent judge owner, not this candidate.

**No registrar spawn or complete normal-startup check is claimed from the missing log.**
Absence of a site-error line does not prove success. The complete official rerun must
observe the required evidence using the corrected fixture. All source, configuration,
SQL, rules and tests remain byte-identical to the successfully compiled bde390e3.

Evidence is in run `33955586542` artifact
`official-gate-bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc-1`: build/install logs,
authserver/worldserver dry-run logs, `unit-tests.log`, `stormwright-rules-test.log`,
`stormwright-installed-sql.tsv`, `stormwright-worldserver-running.log` and
`stormwright-runtime-fixture.conf`.

| Check | Current evidence |
|---|---|
| Exact pinned API/source inspection | PASS: independent Reviewer inspected implementation c1f3926dcc8988d6f1461affeee0c817c97f911d, including API/state, ownership, charge, cleanup and complete solo flow. Prior terminal victory precedence finding fixed. Practical's bounded exact-schema SQL review also PASS. |
| Static stock references | Exact DBC/schema/model references and hashes in REFERENCES.md; invisible Tesla/Spike models rejected. |
| Source isolation | Only projects/mod-stormwright and its handoff changed from launch base. No dependency or judge changes. |
| Compile / native discovery | PASS for bde390e3 in run 33955586542, after the preserved first-build failure. This checkpoint changes docs only. |
| Compile-time rules checks | PASS during actual module compilation in 33955586542; src/StormwrightRulesChecks.cpp is unchanged. |
| Executable developer rules tests | PASS in stormwright-rules-test.log for 33955586542: all presets, recovery, duplicate input, retry, lag and time cap. |
| Native units | Runner PASS in 33955586542: 11,395 tests considered, 5,909 passed, 5,486 native skips, one disabled test. The approved disposable WorldMock fixture exception remains disclosed in official evidence; no module test/assertion change. |
| Install / SQL import / dry-run startup | PASS for bde390e3 in 33955586542. Expected installed SQL rows verified; authserver/worldserver dry-runs completed. |
| Official independent gate | FAILED for a1558178 at compilation in 33952393192, and for bde390e3 at required supplemental observation in 33955586542. Complete corrected-fixture rerun pending. |
| Independent implementation review | PASS for repaired source a65f162419c8d0c0cc1ddbad2f35b7b4450018c8. Reviewer verified all three target-GUID fixes against pinned packet semantics, unchanged rules/SQL/config/tests and diff --check. |
| ONE_HUMAN_REVIEW | PASS at source level for repaired implementation a65f162419c8d0c0cc1ddbad2f35b7b4450018c8: one human controls every special action; no-bots recovery, success/failure, outcome, retry and exit are complete in source. Actual execution/feel remains pending. |
| Terrain/public access/navmesh/LOS | PENDING applicable validation. Runtime height guards and offline coordinate/ground projections do not prove walking access, collision, navigation or client safety. |
| Normal world update lifecycle | Real worldserver reached ready/updates, but required registrar observation FAILED in 33955586542 under the incorrect WARN logger fixture. Corrected observation, continued run and clean shutdown evidence remain required. |
| Client visuals/class tuning/bots | PENDING IN-GAME VALIDATION, never implied by DBC references or CI. |

Developer assertions cover all three presets, invalid start/input, charge consumption,
full-ward injured-pilot Ground, full-health waste prevention, duplicate activation,
cooling, armor expiry, ward failure, reset/retry, delayed ticks and the time cap.
They do not exercise AzerothCore actor lifecycle, interactions or client rendering.

The independent review dispositions were received from the Reviewer for the exact source
SHA above, with Practical's separate SQL disposition. They are source-level results.
The repaired candidate SHA will be bound by the official dispatch and its immutable
evidence. Prior source approval and successful stages do not turn the failed overall
gate or unobserved registrar into passes.

Do not mark this module READY FOR LIVE TEST until exact-candidate official gate evidence
and applicable runtime closure are recorded, with all remaining uncertainty limited to
the explicitly documented later in-game checks.
