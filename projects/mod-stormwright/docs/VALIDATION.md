# Validation record

State: **IMPLEMENTED CANDIDATE; acceptance and actual gameplay pending.**

| Check | Current evidence |
|---|---|
| Exact pinned API/source inspection | Selected Map, Unit, CreatureAI, gossip, group and module discovery signatures inspected. Reviewer found terminal victory precedence defect; corrected in current source. Not a full implementation approval. |
| Static stock references | Exact DBC/schema/model references and hashes in REFERENCES.md; invisible Tesla/Spike models rejected. |
| Source isolation | Only projects/mod-stormwright and its handoff changed from launch base. No dependency or judge changes. |
| Compile / native discovery | NOT_RUN for current candidate. |
| Compile-time rules checks | Present in src/StormwrightRulesChecks.cpp; execute by constant evaluation during real module compilation. NOT_RUN until compiler evidence exists. |
| Executable developer rules tests | tests/rules_test.cpp; NOT_RUN. In an available C++17 toolchain: `c++ -std=c++17 -Wall -Wextra -Werror tests/rules_test.cpp -o /tmp/stormwright-rules && /tmp/stormwright-rules`. |
| Install / SQL import / startup | NOT_RUN. Exact-pin native updater location inspected; no claim of execution. |
| Official independent gate | NOT_RUN for current candidate. |
| Independent implementation review | PENDING; early API/terminal-order review only. |
| ONE_HUMAN_REVIEW | Proposal PASS at reviewer commit 0aa6e58; actual implementation PENDING. |
| Terrain/public access/navmesh/LOS | PENDING; no extracted map data currently available in Forge. Runtime height guards do not prove pathing/access. |
| Normal world update lifecycle | PENDING; official dry-run exits before OnStartup and world updates. Registrar/controller need additional applicable runtime evidence. |
| Client visuals/class tuning/bots | PENDING IN-GAME VALIDATION, never implied by DBC references or CI. |

Developer assertions cover all three presets, invalid start/input, charge consumption,
full-ward injured-pilot Ground, full-health waste prevention, duplicate activation,
cooling, armor expiry, ward failure, reset/retry, delayed ticks and the time cap.
They do not exercise AzerothCore actor lifecycle, interactions or client rendering.

Do not mark this module READY FOR LIVE TEST until exact-candidate official gate evidence,
independent implementation/one-human review, and applicable runtime closure are recorded.
