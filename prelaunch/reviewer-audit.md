# Reviewer prelaunch gate audit

Status: PRELAUNCH. No sprint timestamp is initialized by this audit.

Reviewer lane: `lane/reviewer`. Audit base: `5160975`.

## Evidence-backed correction, revision 1

The exact AzerothCore pin is `47960183bb03b83e8943eb2f0f39c16df9710c9d` and the exact Playerbots pin is `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. No dependency source or compiler warning policy is changed.

- [Playerbots sample config](https://github.com/mod-playerbots/mod-playerbots/blob/2f7d9f774987d0157c6a0d0cc08c40bec3db3945/conf/playerbots.conf.dist#L2492) sets a separate `PlayerbotsDatabaseInfo` connection using the `acore` account. The original workflow only overrides the three core databases with the disposable runner's `root` fixture. It must override the fourth database as well. The revision explicitly installs MySQL and verifies the local fixture before startup.
- [Pinned module discovery](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/cmake/macros/ConfigureModules.cmake#L20) requires `src/`. [The loader generator](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/modules/CMakeLists.txt#L159) turns hyphens into underscores and invokes `Add<module-name>Scripts()`. The revision requires the candidate's generated loader call; a README-only directory cannot silently validate a build without its candidate.
- [Worldserver initialization](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/apps/worldserver/Main.cpp#L264) loads module configurations and initializes scripts before databases. [The dry-run exit](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/World/World.cpp#L1056) follows world initialization. Thus dry-run is real module/config/DB/world initialization evidence; it is **not** `WorldScript::OnStartup`, network, update-loop, shutdown-hook, or gameplay evidence. `OnStartup` is later at Main.cpp line 390. The revision requires actual completion log sentinels and preserves logs. Candidates whose scope requires later callbacks need additional runtime evidence.
- [Pinned unit test CMake](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/test/CMakeLists.txt) creates `unit_tests`; the root CMake uses `BUILD_TESTING`. The original optional executable check permits missing mandatory tests. The revision fails if the requested executable is absent.
- The original scope baseline fetches moving `main` after checkout and the report describes a judge without a hash. The revision records `GITHUB_WORKFLOW_SHA`, hashes the exact workflow checked out at that SHA, requires execution from the default branch, and compares candidate changes against that exact judge commit. Evidence is uploaded even after a failing step.
- The original dependency diff excludes all core `modules/`, including tracked loader/build authority. The revision compares all tracked core/Playerbots files to their pinned commit, including staged changes, and repeats the checks after install/runtime.
- Handoff changes now must match the selected project. Compiler flags remain `-Werror -ferror-limit=0`; configure/build/install/startup/test failures remain fatal via `set -euo pipefail`.

## Validation performed

Exact public source files were retrieved by commit SHA into ignored `.forge-local/` and read independently. This is authoritative source reproduction, not a full local compile or runtime test. `git diff --check` passed. PyYAML parsed the workflow and Git Bash `bash -n` passed for all 16 shell run blocks; assertions confirmed the two exact dependency pins and both `-Werror -ferror-limit=0` flags remain. Official disposable CI must still validate the revision and clean control before launch. No live-server interaction occurred.

Clean control `87b822fd41bb6013358aa6f5e16ca252ad79761c` was independently source-inspected: its explicit `WORLDHOOK_ON_AFTER_CONFIG_LOAD` registration reads `ForgeSmoke.Enable`/`ForgeSmoke.ControlValue` with false/zero fallbacks. The judge now requires `FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159` for `mod-forge-smoke`, which proves the shipped configuration overrides those fallbacks in the actual hook. This is a prelaunch control assertion, not an arbitrary substitute test supplied by a gameplay candidate.

## Additional gaps under review

- Candidate `mod-<slug>.cmake` / `CMakeLists.txt` hooks can execute during configure and alter official flags/tests or the dependency tree. Native modules need no custom hook, but a blanket ban affects valid optional integration patterns. Any policy change must be a separate justified Reviewer revision; this revision does not silently impose it.
- `Errors.log` only receives selected SQL/spell categories with the stock logger definitions. Empty `Errors.log` does not prove all runtime categories were error-free. The pinned baseline must be measured before choosing stricter all-category logging or any evidence-based baseline.
- SQL grep/newline checks alone do not prove module ownership, syntax, data references, or application. The pinned automatic updater can provide real application evidence for recognized paths. Other layouts must fail or have separately reviewed explicit validation.
- Runtime data is currently fetched from mutable ac-data `master`; the resolved SHA is now recorded, but a reproducible data pin should be established from a successful control.
- A default-branch workflow and hash identify the accepted judge; candidates remain untrusted compiled code on disposable runners. A green run from a different workflow SHA is not acceptance, even if its display name matches.
