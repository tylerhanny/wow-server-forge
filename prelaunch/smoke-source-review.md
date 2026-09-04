# Independent smoke-control source review

```text
REVIEWER=Wildcard internal worker; independent of Practical implementation
CANDIDATE_SHA=87b822fd41bb6013358aa6f5e16ca252ad79761c
CANDIDATE_BRANCH=project/forge-smoke-clean
CANDIDATE_PARENT=7ffa2bdcb4eafe0de63655531dc61f39f5389a9b
SOURCE_REVIEW=PASS_WITH_NO_ACTIONABLE_FINDINGS
OFFICIAL_GATE=NOT_EVALUATED_BY_THIS_REVIEW
BUILD_INSTALL_STARTUP=NOT_EXECUTED_BY_THIS_REVIEW
HARVEST_DISPOSITION=NOT_APPLICABLE; disposable prelaunch control only
```

The reviewed source is suitable for independent validation as a harmless module discovery/configuration control. This disposition covers actual source and pinned API inspection only. It does not claim compilation, install, callback execution, database/data readiness, startup completion, or an official gate pass. The sprint remained `ARMED_NOT_STARTED` during this review.

## Reviewed changes

Inspected the entire immutable commit using `git show` and compared it with its parent. Exactly five files were added:

- `projects/mod-forge-smoke/src/ForgeSmoke.cpp`
- `projects/mod-forge-smoke/conf/mod_forge_smoke.conf.dist`
- `projects/mod-forge-smoke/README.md`
- `projects/mod-forge-smoke/VALIDATION.md`
- `handoffs/mod-forge-smoke.md`

`git diff --check 87b822fd41bb6013358aa6f5e16ca252ad79761c^ 87b822fd41bb6013358aa6f5e16ca252ad79761c` passed with no output. The candidate changed no authority, coordination state, gate/workflow, validation input, or dependency pin. It supplies no custom CMake, scripts for the build to execute, SQL, runtime network access, player/creature hooks, timers, or persistence. The C++ performs only object registration, two configuration reads, assignment to two private scalar fields, and diagnostic logging.

No candidate files or official judge files were edited during this review. All repository inspection was through immutable Git objects in the Wildcard worktree; public upstream source was read at the exact pinned revision.

## Pinned compatibility findings

AzerothCore pin: `47960183bb03b83e8943eb2f0f39c16df9710c9d`, repository `mod-playerbots/azerothcore-wotlk`.
Playerbots pin: `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, repository `mod-playerbots/mod-playerbots`.
Target remains stock WoW 3.3.5a build 12340 and Ubuntu 24.04 x86-64. This module does not use Playerbots APIs; the official build must still include the pinned Playerbots module.

| Aspect | Source inspection result |
|---|---|
| Module discovery | [ConfigureModules.cmake](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/cmake/macros/ConfigureModules.cmake) enumerates module directories that contain `src`; the candidate has the required structure. |
| Source/link discovery | [modules/CMakeLists.txt](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/modules/CMakeLists.txt#L161) converts hyphens to underscores and generates `Add<directory>Scripts()`. `Addmod_forge_smokeScripts()` matches. Lines 202–215 collect the static module source and register the loader. No candidate CMake override is necessary. |
| Config discovery/install | [modules/CMakeLists.txt](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/modules/CMakeLists.txt#L349) collects `conf/*.conf.dist`, invokes `CopyModuleConfig`, and removes `.dist` from the runtime config filename. [ConfigInstall.cmake](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/cmake/macros/ConfigInstall.cmake#L79) installs Unix module configs under `${CONF_DIR}/modules`. The README correctly requires the installed `.conf` copy. |
| Hook selection/signatures | [WorldScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/WorldScript.h) contains both selected enums, the constructor taking `std::vector<uint16>`, `OnAfterConfigLoad(bool)`, and `OnStartup()`. [WorldScript.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/WorldScript.cpp#L87) registers exactly the nonempty hook selection; no all-hooks behavior is accidentally requested. |
| Config read compatibility | [Config.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/common/Configuration/Config.h#L68) declares `GetOption<T>`. [Config.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/common/Configuration/Config.cpp#L655) provides the boolean specialization and line 811 explicitly instantiates `uint32`. Both candidate calls are supported. |
| Logging compatibility | [Log.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/common/Logging/Log.h#L153) provides `LOG_INFO`; format placeholders and supplied scalar values match. Diagnostic output depends on the normal logger filter being enabled. |
| Initialization order | [Main.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/apps/worldserver/Main.cpp#L264) loads module configs, installs the module loader, and initializes scripts before `SetInitialWorldSettings` at line 310. [World.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/World/World.cpp#L301) dispatches `OnAfterConfigLoad`; its initial-world setup calls `LoadConfigSettings` at line 322. The marker is therefore on an actual registered initialization path. |
| Dry-run limitation | [World.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/World/World.cpp#L1061) exits from dry-run after world initialization, returning failure for failed database updates. [Main.cpp](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/apps/worldserver/Main.cpp#L390) dispatches `OnStartup` later. The README correctly says dry-run does not produce the startup marker. |

## Evidence interpretation and remaining work

The expected initial record is `FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159`. Its two non-default values distinguish successful configuration acceptance from a callback running with compiled defaults. Merely finding this text in source is not evidence. A real emitted record alone also does not establish complete world initialization: the official run must separately succeed through the intended full initialization/dry-run path.

`ForgeSmoke.Enable=0` does not suppress diagnostics. That is intentional and accurately documented: enablement is a reported control value, not a gameplay on/off switch. The module has no gameplay behavior to disable.

The handoff's embedded SHA is `UNSET` and explicitly delegates binding the immutable submission SHA to the Director/Reviewer after commit. This review binds the actual reviewed SHA above. External gate evidence must use that exact SHA, and must additionally identify the default-branch gate revision/hash. Any candidate change requires new evidence against the changed SHA.

Required next step: inspect the actual independent official run for exact pins, discovery/configure output, full compilation, install/staging, installed config, config-hook output, successful disposable world initialization, and dependency-tree integrity. No blockers requiring a product change were found. Practical and Reviewer were sent these findings and the dry-run evidence distinction.
