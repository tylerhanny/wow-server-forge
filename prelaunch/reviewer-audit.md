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

## SQL application requirements for later candidates

The exact pinned [UpdateFetcher.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/database/Updater/UpdateFetcher.cpp#L159) automatically discovers `modules/<name>/data/sql/<directory>/` when the immediate directory name contains the target database's module name (`auth`, `world`, or `characters`). Canonical directories should be `data/sql/db-auth/`, `data/sql/db-world/`, and `data/sql/db-characters/` to avoid ambiguous substring matches.

The updater traverses up to ten levels and only accepts files whose extension is exactly lowercase `.sql` (lines 74–102). Basenames must be unique across the database's entire update set, not only within the candidate, or it throws. It applies the `MODULE` updates after ordinary updates, computes SHA-1 from the SQL file bytes on the Ubuntu runner, and stores the basename, hash, and `MODULE` state in that database's `updates` table (lines 297, 379–383, 394–406, and 462–468).

Therefore a later SQL-bearing candidate needs all of the following actual evidence before approval:

1. Every module-owned migration is in a recognized unambiguous directory and is observed in the disposable updater's application log.
2. The disposable database's `updates` row matches each migration basename, SHA-1, and `MODULE` state after startup.
3. Independent review confirms the SQL touches only owned tables or explicitly scoped owned rows and has no unsafe unrelated effects.
4. Candidate-specific reference/row assertions verify gameplay data where relevant. An `updates` record proves execution but does not prove every referenced spell, creature, item, faction, or quest is correct.

The current newline/keyword check is only static hygiene. It is not item 1, 2, 3, or 4. No-SQL smoke is unaffected; no new gate behavior is introduced by this note.

## Build hooks and logging boundaries

Pinned root CMake lines 72–87 executes any module `CMakeLists.txt`; pinned module CMake lines 312–315 optionally includes `<module-name>.cmake`. These are valid upstream conventions and are not blanket-prohibited by revision 1. Reviewer must inspect any such candidate code for test/flag/source mutation, substitute binaries, environment access, or arbitrary commands. No `acore.json` / `include.sh` execution was found on the reviewed direct `cmake -S ac` call chain; installer shell behavior is outside that conclusion.

Pinned `Log::GetLoggerByType` selects the nearest logger and does not bubble a message through every parent appender. Stock world config routes `Logger.server` to `Console Server`, while only selected SQL/spell loggers include `Errors`. Consequently an empty `Errors.log` is insufficient to claim all categories were error-free. Review actual console and Server logs. Do not hide, suppress, or approve a baseline error until its cause and impact are independently established.

## Corrected-control checkpoint

Director integrated revision 1 at judge commit `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b`. Corrected clean run: [33911646203](https://github.com/tylerhanny/wow-server-forge/actions/runs/33911646203), candidate `87b822fd41bb6013358aa6f5e16ca252ad79761c`. Independent API inspection confirmed the actual run's head SHA is that judge version and its default-branch check, exact-judge checkout/recording, candidate checkout, and scope checks passed. At this checkpoint, later compilation/runtime/tests remain pending; this is **not** a clean-control pass or permission to start the sprint.

The prior clean run `33911309528` was cancelled after successful configure and incomplete compilation. It is not a failed candidate, a completed compile, or a passing gate.
