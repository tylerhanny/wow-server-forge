# Clean control: pinned dependency warning blocks compilation

Disposition: **BLOCKED under the current immutable target and warnings-as-errors policy**. The clean official gate failed. The sprint remains ARMED; no launch, runtime success, or harvest approval follows from this run. This is an owner-decision blocker, not permission for an agent to alter the gate or dependencies.

## Exact evidence

| Item | Value |
| --- | --- |
| Official run | [33911646203](https://github.com/tylerhanny/wow-server-forge/actions/runs/33911646203), attempt 1, completed with failure |
| Candidate | `87b822fd41bb6013358aa6f5e16ca252ad79761c`, `project/forge-smoke-clean` |
| Judge commit | `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b` |
| Judge workflow SHA-256 | `c7ce13faa48f8336b3b3c161e5ab202c717e7eaf4b1308ece56b147542ee6e81` |
| AzerothCore | `47960183bb03b83e8943eb2f0f39c16df9710c9d` |
| Playerbots | `2f7d9f774987d0157c6a0d0cc08c40bec3db3945` |
| Artifact | [9954127407](https://github.com/tylerhanny/wow-server-forge/actions/runs/33911646203/artifacts/9954127407), 19,906 bytes |
| Published artifact ZIP SHA-256 | `575a567a8a862fabf2feda58cbc6c3b469053b5f07b5c3b7209b08e7d6479be7` |
| Extracted `evidence/build.log` SHA-256 | `a7595fe5d489d80e067e8dff33c8df36b353091bd8752ac40519f304a407225c` |
| Compiler recorded by configure | Clang 18.1.3, `/usr/bin/clang++-18`, Ubuntu 24.04 runner |

The failure at `2026-09-04T20:52:08Z` is:

```text
ac/modules/mod-playerbots/src/Ai/Raid/BT/BTHelpers.cpp:107:60:
fatal error: unused parameter 'botAI' [-Wunused-parameter]
TankPositionState GetShahrazTankPositionState(PlayerbotAI* botAI, Player* bot)
```

The module target failed; remaining already-running core script work then finished before final `gmake` exit 2 at `20:56:03Z`. The validation job duration was 1h23m38s. Discovery, scope, dependency checkout, configure, and generated-loader assertion passed. Compilation did not complete. Post-build dependency checks, install, SQL checks, runtime data/MySQL preparation, both dry-runs, and unit tests were skipped. Artifact upload succeeded. In particular, there is no actual database-fixture result in this run.

## Independent diagnosis

The exact [Playerbots source](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/src/Ai/Raid/BT/BTHelpers.cpp#L107) was independently retrieved and inspected. The function body uses `bot`, but never uses its named `botAI` argument; no compiler-specific conditional surrounds this body. This is an ordinary upstream unused-parameter diagnostic, not a smoke-module diagnostic or evidence of a compiler malfunction. The failed official build includes the smoke candidate; a separate full build without that candidate was not run. The candidate contains no build hook, compiler flag, pragma, or dependency-source edit that explains this diagnostic.

The exact [Clang settings](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/cmake/compiler/clang/settings.cmake) accept versions at least 10.0.0; the actual configure log accepted 18.1.3 and enabled the pinned `WITH_WARNINGS` set including `-Wall`, `-Wextra`, and `-Wfatal-errors`. The judge adds global `-Werror -ferror-limit=0`. No evidence establishes an unsupported toolchain or accidental gate configuration.

The exact [GCC settings](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/cmake/compiler/gcc/settings.cmake) also enable `-Wall` and `-Wextra` when warnings are requested, and contain no unused-parameter exclusion. [GCC's official warning documentation](https://gcc.gnu.org/onlinedocs/gcc-13.4.0/gcc/Warning-Options.html#index-Wunused-parameter) confirms that combination diagnoses unused parameters. Practical independently checked compiler dispatch and reached the same conclusion. Selecting GCC is supported in principle, but is not an evidenced repair of this failure. No full GCC build or GCC baseline pass is claimed.

Disabling `WITH_WARNINGS`, demoting this warning, modifying the dependency, changing a pin, or omitting Playerbots would change the protected contract. None was performed. The first fatal diagnostic also does not establish that this is the only warning in all remaining upstream translation units.

## Smallest owner decisions, if the target must proceed

1. Keep the existing rules: retain this genuine prelaunch blocker and do not start the sprint. The same candidate cannot be declared green under this result.
2. Explicitly revise the warning policy for independently established, immutable upstream baseline diagnostics while keeping candidate warnings fatal. Any such exception would require owner authorization, a precise diagnostic/source scope, visible retained warnings, a separate reviewed judge revision, and fresh complete validation. It is a policy change, not a repair already authorized by existing rules.
3. Explicitly revise the dependency target or source-protection rule to permit an audited upstream correction of the unused argument. That creates a changed validation target, requires new recorded identities and complete validation, and cannot be represented as the original unmodified exact-pin target.

No option has been selected by the Reviewer. The Director owns the owner decision and coordination state. The unrelated missing-schema/Errors.log inference was separately disproved in `first-start-log-routing-review.md`; it is not the reason for this failure.

Validation of this record: actual run metadata, configure/build logs, and the seven-file official artifact were read; artifact identities match the frozen candidate/judge/pins; exact pinned function and compiler settings were inspected; `git diff --check` passed. No live-server access occurred.
