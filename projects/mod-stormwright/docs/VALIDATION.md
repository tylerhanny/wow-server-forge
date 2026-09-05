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
or judge input. Independent repair review and the new full official rerun are pending.
The failed candidate and its evidence are preserved.

The failed run did not reach install, SQL/startup, unit execution or supplemental
normal-world checks. Those outcomes must not be inferred from configure/discovery
or the partial build. The table below describes the repaired candidate's remaining
validation, while prior source-review results retain their exact reviewed SHA.

| Check | Current evidence |
|---|---|
| Exact pinned API/source inspection | PASS: independent Reviewer inspected implementation c1f3926dcc8988d6f1461affeee0c817c97f911d, including API/state, ownership, charge, cleanup and complete solo flow. Prior terminal victory precedence finding fixed. Practical's bounded exact-schema SQL review also PASS. |
| Static stock references | Exact DBC/schema/model references and hashes in REFERENCES.md; invisible Tesla/Spike models rejected. |
| Source isolation | Only projects/mod-stormwright and its handoff changed from launch base. No dependency or judge changes. |
| Compile / native discovery | First candidate configured/discovered, then FAILED compilation in 33952393192. Repaired candidate full compile NOT_RUN. |
| Compile-time rules checks | Present in src/StormwrightRulesChecks.cpp; execute by constant evaluation during real module compilation. NOT_RUN until compiler evidence exists. |
| Executable developer rules tests | tests/rules_test.cpp; NOT_RUN. In an available C++17 toolchain: `c++ -std=c++17 -Wall -Wextra -Werror tests/rules_test.cpp -o /tmp/stormwright-rules && /tmp/stormwright-rules`. |
| Install / SQL import / startup | NOT_RUN. Exact-pin native updater location inspected; no claim of execution. |
| Official independent gate | FAILED for a1558178 in run 33952393192; repaired candidate rerun pending. |
| Independent implementation review | Prior PASS for c1f3926dcc8988d6f1461affeee0c817c97f911d carried to docs-only a1558178. Three-call compiler repair review PENDING. |
| ONE_HUMAN_REVIEW | PASS at source level for implementation c1f3926dcc8988d6f1461affeee0c817c97f911d: one human controls every special action; no-bots recovery, success/failure, outcome, retry and exit are complete in source. Actual execution/feel remains pending. |
| Terrain/public access/navmesh/LOS | PENDING applicable validation. Runtime height guards and offline coordinate/ground projections do not prove walking access, collision, navigation or client safety. |
| Normal world update lifecycle | PENDING; official dry-run exits before OnStartup and world updates. Registrar/controller need additional applicable runtime evidence. |
| Client visuals/class tuning/bots | PENDING IN-GAME VALIDATION, never implied by DBC references or CI. |

Developer assertions cover all three presets, invalid start/input, charge consumption,
full-ward injured-pilot Ground, full-health waste prevention, duplicate activation,
cooling, armor expiry, ward failure, reset/retry, delayed ticks and the time cap.
They do not exercise AzerothCore actor lifecycle, interactions or client rendering.

The independent review dispositions were received from the Reviewer for the exact source
SHA above, with Practical's separate SQL disposition. They are source-level results.
The repaired candidate SHA will be bound by the official dispatch and its immutable
evidence. Prior source approval does not turn the failed compile or unrun checks into passes.

Do not mark this module READY FOR LIVE TEST until exact-candidate official gate evidence
and applicable runtime closure are recorded, with all remaining uncertainty limited to
the explicitly documented later in-game checks.
