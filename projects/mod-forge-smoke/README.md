# Forge smoke control

This minimal module is a disposable validation control for the WoW Server Forge.
It proves that the pinned core can discover and link a module, install its config,
register its world hooks, and read the installed configuration. It provides no
gameplay feature and is not a harvest project.

## Exact target

- WoW client: 3.3.5a build 12340.
- AzerothCore: `mod-playerbots/azerothcore-wotlk` at
  `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots: `mod-playerbots/mod-playerbots` at
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- Validation OS: Ubuntu Server 24.04 x86-64.

Neither dependency needs source changes. The module does not call Playerbots
APIs, but the official control must be built with the exact pinned Playerbots
module present.

## Installation in a disposable development tree

1. Prepare a disposable checkout of each exact dependency above, with Playerbots
   under `modules/mod-playerbots`.
2. Copy this entire directory to `modules/mod-forge-smoke`.
3. Configure the core with `-DMODULES=static`, then build and install through the
   official candidate gate. No module-specific CMake script is needed: the pinned
   loader expects `Addmod_forge_smokeScripts()` and automatically discovers
   `conf/*.conf.dist`.
4. Copy the installed `etc/modules/mod_forge_smoke.conf.dist` to
   `etc/modules/mod_forge_smoke.conf`, preserving the two control values.
5. Start the disposable worldserver with its disposable data and databases.
   Never use this control against the live server.

The official default-branch workflow is the acceptance authority. See
`VALIDATION.md` for the actual evidence status; these instructions are not a
claim that a build or startup has passed.

## Configuration and observable behavior

| Key | Distributed value | Missing-key default | Purpose |
| --- | --- | --- | --- |
| `ForgeSmoke.Enable` | `1` | `0` | Demonstrates a boolean config value was loaded. |
| `ForgeSmoke.ControlValue` | `314159` | `0` | Demonstrates an integer config value was loaded. |

These options affect only the reported diagnostic values. Logging remains active
when `Enable` is zero so a missing or intentionally disabled configuration is
visible. The module never changes players, creatures, items, world state,
databases, or networking.

With the distributed configuration, the initial config hook must log:

```text
FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159
```

The marker is emitted by a registered `WorldScript` callback. The non-default
values additionally demonstrate configuration acceptance. Compilation or a source
text search alone does not demonstrate either callback execution or config load.

A regular disposable startup that reaches `WorldScript::OnStartup` also logs:

```text
FORGE_SMOKE_STARTUP enabled=1 control=314159
```

The pinned core's `--dry-run` intentionally exits after world initialization and
before `OnStartup`; absence of the second marker is expected for that mode.
An ordinary config reload logs the first marker with `reload=1`.

## SQL, removal, and limitations

There is no SQL, persistent state, timer, player hook, client modification,
external service, or runtime dependency beyond the pinned core. Remove the
module directory and rebuild to remove the control; remove its installed config
files from the disposable tree if desired.

This is a build and module-load control only. It does not prove any gameplay
module works, and it must not be counted as a completed gameplay project.

## Manual smoke checklist

Use only a disposable development server:

- Confirm the configure log lists `mod-forge-smoke` and its config.
- Confirm the installed config preserves `Enable = 1` and `ControlValue = 314159`.
- Confirm the initial `FORGE_SMOKE_CONFIG` record matches the exact line above.
- For a regular startup, confirm the `FORGE_SMOKE_STARTUP` record as well.
- For an optional reload check, change `ControlValue` to `271828`, reload config,
  and confirm `FORGE_SMOKE_CONFIG reload=1 enabled=1 control=271828`; then restore
  the canonical control value.

There is no in-game interaction to test. No live-server or WoW-client validation
has been performed or is required for this prelaunch control.
