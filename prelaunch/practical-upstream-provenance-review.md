# Independent upstream-provenance review

Disposition: **APPROVE — source, parser and command-provenance scope**.
Reviewer: Practical Builder, 2026-09-04.

- Implementation: `e7afa692992b2fcaaef885d1c4473e9fa4352616`.
- Workflow: `d31e425a3fa6bd731a180c171727730219d8760a`.
- Director-published combined judge: `6f0582572ceb1c0a16c4234fd6b97e896d3cf0ed`.
- Tested verifier SHA-256:
  `8461d5b3ffb4d05962ed39e8ae41a203bd3fac1f1d6d3594a6c572ed49bd6259`.

Exact committed validation files were exported with `git show`. All **35 existing
independent cases produced their expected outcomes**, with zero mismatches;
`practical-upstream-provenance-results.json` preserves the results. The original
source-directory junction and generated-project-header suppression reproductions
were also repeated against those bytes and correctly rejected. One local fixture
was corrected to write its Unicode include path as UTF-8 rather than Windows'
default encoding; expected outcomes were unchanged.

The bounded cases cover multiple/zero verified upstream warnings, project and
unknown source/header warnings, modified source bytes, macro-definition notes,
physical-path attribution, project/generated demotion, aliasing, generated-header
suppression, input metadata, complete capture, summary counts and actual errors.
The existing committed selftests also completed locally: 15 passed; the real
Ubuntu compiler integration probe was explicitly skipped on this Windows host.
No new prelaunch gate or additional control was introduced.

The exact policy, source inventory, CMake hook, verifier, tests, README and workflow
were reviewed. Demotion applies to individually verified unchanged upstream source
files. Project translation units retain Werror. Source aliases and reachable
generated project headers cannot inherit the upstream allowance in the exercised
cases. Warnings remain visible with provenance; errors and incomplete captures
remain fatal. `git diff --check` passed. Workflow changes preserve global Werror
and all later build/install/config/SQL/runtime/unit/integrity stages.

The upstream-header/project-TU compiler boundary and same-user build-hook trust
limits are documented in the validation README. They are not represented as new
owner-approval blockers or as complete hostile-code isolation.

This review does **not** establish real Clang integration, a full pinned build,
installation, startup or gameplay success. Those remain the existing official
control evidence and Reviewer responsibilities. Historical failed runs remain
failed. No gameplay implementation, dependency edit or clock change occurred.
