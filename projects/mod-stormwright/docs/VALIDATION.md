# Validation record

State: **IMPLEMENTED CANDIDATE; acceptance and actual gameplay pending.**

| Check | Current evidence |
|---|---|
| Exact pinned API/source inspection | PASS: independent Reviewer inspected implementation c1f3926dcc8988d6f1461affeee0c817c97f911d, including API/state, ownership, charge, cleanup and complete solo flow. Prior terminal victory precedence finding fixed. Practical's bounded exact-schema SQL review also PASS. |
| Static stock references | Exact DBC/schema/model references and hashes in REFERENCES.md; invisible Tesla/Spike models rejected. |
| Source isolation | Only projects/mod-stormwright and its handoff changed from launch base. No dependency or judge changes. |
| Compile / native discovery | NOT_RUN for current candidate. |
| Compile-time rules checks | Present in src/StormwrightRulesChecks.cpp; execute by constant evaluation during real module compilation. NOT_RUN until compiler evidence exists. |
| Executable developer rules tests | tests/rules_test.cpp; NOT_RUN. In an available C++17 toolchain: `c++ -std=c++17 -Wall -Wextra -Werror tests/rules_test.cpp -o /tmp/stormwright-rules && /tmp/stormwright-rules`. |
| Install / SQL import / startup | NOT_RUN. Exact-pin native updater location inspected; no claim of execution. |
| Official independent gate | NOT_RUN for current candidate. |
| Independent implementation review | PASS for c1f3926dcc8988d6f1461affeee0c817c97f911d. This final checkpoint changes review documentation only; source/SQL/config/tests remain identical. No remaining actionable source finding was reported. |
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
The final candidate SHA is bound by the official dispatch and its immutable evidence;
the docs-only status update does not make unrun checks pass.

Do not mark this module READY FOR LIVE TEST until exact-candidate official gate evidence
and applicable runtime closure are recorded, with all remaining uncertainty limited to
the explicitly documented later in-game checks.
