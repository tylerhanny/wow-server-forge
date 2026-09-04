# Smoke control evidence

This record describes builder evidence only. It does not self-certify the
official gate or independent review.

| Check | Result |
| --- | --- |
| Pinned API and discovery source inspection | PASS: exact public source listed below |
| Developer whitespace check | PASS: `git diff --cached --check` on staged candidate files |
| Module configure/discovery execution | NOT_RUN |
| Full pinned compilation | NOT_RUN |
| Disposable install/staging | NOT_RUN |
| SQL/data | NOT_APPLICABLE: no SQL or data files |
| Disposable worldserver startup/module load | NOT_RUN |
| Official candidate gate | NOT_RUN |
| Independent review | PENDING |
| Live/in-game validation | NOT_RUN; not a gameplay candidate |

## Pinned source basis

All sources below are from AzerothCore commit
`47960183bb03b83e8943eb2f0f39c16df9710c9d`:

- [WorldScript.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Scripting/ScriptDefines/WorldScript.h):
  hook-selecting constructor and the `OnAfterConfigLoad(bool)` / `OnStartup()`
  virtual signatures.
- [Config.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/common/Configuration/Config.h):
  `ConfigMgr::GetOption<T>`.
- [Log.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/common/Logging/Log.h):
  `LOG_INFO`.
- [modules/CMakeLists.txt](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/modules/CMakeLists.txt):
  automatic source collection, directory-derived loader name, and config
  discovery. No builder-controlled CMake logic is supplied.

## Remaining evidence required

The Director/Reviewer must record the exact submitted candidate SHA, default-
branch gate SHA/hash, official run URL, configure/build/install results, and
actual module config-hook output. A startup record must distinguish the pinned
dry-run path from a regular startup reaching `OnStartup`.

Until that evidence exists, this control is ready for independent validation,
not validated.
