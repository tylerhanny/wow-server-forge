# Field Camp — owner install, testing and rollback

Prepared external installation guide, 2026-09-05, for exact candidate
`ec9eea979c9344853aaf02d46ba9f6632636254b` (`project/field-camp`).
Independent source and source-level one-human review passed; official run `33952603462`
is pending at preparation. The final exact-candidate attestation in `HARVEST.md` controls
readiness and supersedes the frozen package's pre-run status. This guide is not acceptance.
**These commands have not been executed.**

Use a disposable Ubuntu 24.04 x86-64 checkout/database setup and stock WoW 3.3.5a build
12340 client. The Forge never operates the live server. Field Camp adds no SQL, payment,
NPCs, persistent player records or bot transport. Hunt Rhythm and Stormwright remain the
primary delivery priorities; this guide introduces no new feature or acceptance shortcut.

## Install to a separate prefix

Prerequisites: the existing exact pinned checkout, normal build dependencies including
Clang 18/CMake/make, already-working disposable databases/Playerbots config, and extracted
DBC/maps/vmaps/mmaps for actual travel testing. Keep the existing installation and build
untouched. Replace the three path placeholders with local disposable paths.

```bash
set -euo pipefail
AC=/path/to/disposable/azerothcore
FORGE=/path/to/wow-server-forge
WORK=/path/to/new/field-camp-ec9eea9-test
PB="$AC/modules/mod-playerbots"
CANDIDATE=ec9eea979c9344853aaf02d46ba9f6632636254b
AC_PIN=47960183bb03b83e8943eb2f0f39c16df9710c9d
PB_PIN=2f7d9f774987d0157c6a0d0cc08c40bec3db3945
BUILD="$WORK/build-with-camp"
STAGE="$WORK/stage-with-camp"
test "$(git -C "$AC" rev-parse HEAD)" = "$AC_PIN"
test "$(git -C "$PB" rev-parse HEAD)" = "$PB_PIN"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
git -C "$FORGE" cat-file -e "$CANDIDATE^{commit}"
test ! -e "$AC/modules/mod-field-camp"
test ! -e "$WORK"
command -v cmake
command -v clang-18
command -v clang++-18
mkdir -p "$WORK/export" "$STAGE"
git -C "$FORGE" archive "$CANDIDATE" projects/mod-field-camp |
  tar -x -C "$WORK/export"
cp -a "$WORK/export/projects/mod-field-camp" "$AC/modules/mod-field-camp"
COMMON_CMAKE=(
  -DCMAKE_C_COMPILER=clang-18 -DCMAKE_CXX_COMPILER=clang++-18
  -DCMAKE_BUILD_TYPE=Release -DAPPS_BUILD=all -DTOOLS_BUILD=none
  -DSCRIPTS=static -DMODULES=static -DWITH_WARNINGS=ON -DBUILD_TESTING=OFF
)
cmake -S "$AC" -B "$BUILD" "${COMMON_CMAKE[@]}" \
  -DCMAKE_INSTALL_PREFIX="$STAGE" 2>&1 | tee "$WORK/configure.log"
cmake --build "$BUILD" --parallel 2 2>&1 | tee "$WORK/build.log"
cmake --install "$BUILD" 2>&1 | tee "$WORK/install.log"
test "$(git -C "$AC" rev-parse HEAD)" = "$AC_PIN"
test "$(git -C "$PB" rev-parse HEAD)" = "$PB_PIN"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
```

An occupied destination stops the instructions; inspect it rather than overwrite it.
If the candidate is missing, fetch published `project/field-camp` in the Forge clone,
then verify the exact SHA again. Never update either dependency pin.

`BUILD_TESTING=OFF` is an **ordinary installation setting**, distinct from official
acceptance. It does not run the upstream unit executable. Never apply the CI WorldMock
patch or bring its adapter/warning hook outside CI. Ordinary native compiler settings and
these install logs are not an official-gate verdict. The independent gate still requires
the full test build/run, exact fixture containment, provenance and fatal project warnings.
Report module warnings/build errors; do not patch dependencies or change acceptance rules.

## Configure and run

```bash
cp -n "$STAGE/etc/authserver.conf.dist" "$STAGE/etc/authserver.conf"
cp -n "$STAGE/etc/worldserver.conf.dist" "$STAGE/etc/worldserver.conf"
cp -n "$STAGE/etc/modules/mod_field_camp.conf.dist" \
  "$STAGE/etc/modules/mod_field_camp.conf"
mkdir -p "$STAGE/logs"
```

Prepare those server configs for existing **local disposable databases and realm/ports**,
with worldserver `DataDir` pointing to the fully extracted test data and `LogsDir` to the
new stage's absolute logs path. Do not copy live credentials or point staged binaries at
live databases. Keep the already-working test Playerbots configuration; random population
is not required. No SQL import or account/network setup is part of this module install.

The exact defaults in `etc/modules/mod_field_camp.conf` are:

```ini
FieldCamp.Enable = 1
FieldCamp.CooldownSeconds = 600
```

Cooldown is clamped to 60–3600 seconds. Set the existing `Logger.module` severity to
INFO (`3`), preserving its appenders. With the pinned default appenders:

```ini
Logger.module=3,Console Server
```

Start the staged binaries in two terminals, each with `STAGE` assigned to the same
absolute prefix. Do not start an existing service or replace running binaries.

```bash
# Terminal 1:
cd "$STAGE/bin"
./authserver -c "$STAGE/etc/authserver.conf"
```

```bash
# Terminal 2:
cd "$STAGE/bin"
./worldserver -c "$STAGE/etc/worldserver.conf"
```

Confirm normal startup and `FIELD_CAMP_CONFIG reload=0 enabled=1 cooldown=600` in the
configured logs. That marker proves config/script loading, **not a successful teleport**.
Use the normal running server for client tests; a DBC-only dry-run cannot prove landing.

## One-Human Playability — commands and test order

One ordinary level 1–80 character of any class can complete this solo loop. No second
human/client/operated account, bot, custom client or GM action is required. The human
alone operates `.camp set`, `.camp status` (or `.camp`), `.camp return` and `.camp clear`.
There is no enemy/helper scaling. On PvP realms choose a normal state/location without
native PvP flags; Field Camp does not bypass those flags.

1. **Access/start:** on dry, stable outdoor ground, alive/out of combat and unflagged,
   use `.camp`, then `.camp set`. Status should show the saved map, coordinates and phase.
2. **Complete useful loop:** travel normally to a same-map town, sell/repair, step back
   outdoors and `.camp return`. Confirm **"return requested" first, actual client arrival
   separately**. The destination/orientation should match the saved camp.
3. **Cooldown/replay:** immediately repeat return; it should reject until 600 seconds
   elapse. Use `.camp clear`, then `.camp set`: both clear and rebind must preserve the
   running cooldown. After expiry, repeat the supply-trip loop. No gold or extra reward
   is involved, and there is no automatic return.
4. **Safety failures/retry:** jumping/swimming, ordinary PvE combat, casting or dead state
   must reject without moving or spending a cooldown. Recover normally and retry.
   Taxi/flight/hover/vehicle/transport, control impairments, logout and existing teleport
   also reject. Dungeons, raids, battlegrounds and arenas are excluded.
5. **Map/phase:** ordinary travel to another map must block return while retaining the
   anchor. Return normally to the saved map and retry. If a normal quest changes phase,
   exact mismatch must block return; overlapping masks are insufficient. Travel back
   normally, or set a new safe camp. Do not invent a passed phase test if unavailable.
6. **Exit/lifecycle:** clear removes the anchor but preserves cooldown in this session.
   Set again, relog, and confirm both anchor/cooldown are gone. Death retains both while
   preventing resurrection/return. Restart and successful config reload clear both too.
7. **Optional companions:** repeat with an ordinary bot party or hunter pet only after
   the solo loop. Field Camp transports **only the human**. It promises no bot teleport,
   follow/regroup or pet arrival; native pet unsummoning and bot behavior remain pending
   actual observation. No custom bot action/menu is required.

Both current and saved positions must pass finite coordinate, phase-aware nearby floor
and liquid-contact checks. Saved floor drift over 0.5 yards or a position more than
1.5 yards from the verified floor rejects return. Missing/changing ground rejects;
the module never invents a replacement Z. These checks are not collision-clearance,
navigation, enemy-avoidance or universal landing guarantees. Choose simple open dry ground.

The core's default `TeleportTo` may accept a delayed request before client acknowledgement.
Acceptance starts the session cooldown even before confirmed arrival; there is no automatic
retry/refund for an unproven client transfer. Native rejection refunds the reservation,
although core movement/aura cleanup can occur before its veto. Session logout/reload cleanup
still applies. Actual terrain, arrival, travel feel and companion behavior remain
**PENDING LIVE/IN-GAME VALIDATION** until observed; retain results independently from CI.

## Disable, re-enable and full removal

Set `FieldCamp.Enable = 0`, then use the authorized operator's normal `reload config`
console command (`.reload config` for a privileged test character), or cleanly restart
the staged server. Verify `FIELD_CAMP_CONFIG ... enabled=0`. A successful reload clears
all camps/cooldowns; a failed reload does not apply settings. Re-enable with `1` and
reload/restart: each human must set a new camp. This does not reverse a prior teleport
or restore a previously saved character position.

For full removal, first cleanly stop the staged worldserver and wait for exit. Stop its
staged authserver if retiring the instance. Preserve the previous stage/config/logs.
With the same path and `COMMON_CMAKE` assignments from preparation:

```bash
test ! -e "$WORK/removed-mod-field-camp"
mv -- "$AC/modules/mod-field-camp" "$WORK/removed-mod-field-camp"
WITHOUT_BUILD="$WORK/build-without-camp"
WITHOUT_STAGE="$WORK/stage-without-camp"
test ! -e "$WITHOUT_BUILD"
test ! -e "$WITHOUT_STAGE"
cmake -S "$AC" -B "$WITHOUT_BUILD" "${COMMON_CMAKE[@]}" \
  -DCMAKE_INSTALL_PREFIX="$WITHOUT_STAGE" 2>&1 | tee "$WORK/remove-configure.log"
cmake --build "$WITHOUT_BUILD" --parallel 2 2>&1 | tee "$WORK/remove-build.log"
cmake --install "$WITHOUT_BUILD" 2>&1 | tee "$WORK/remove-install.log"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
```

Prepare the without-camp stage's own disposable server configs and data reference, then
start it only after the prior instance exits. It has no installed Field Camp config;
`.camp` should no longer be registered. Keeping the old stage archived also retires its
module config from use. No SQL/character cleanup is required; ordinary saved positions
remain core data. Preserve the saved module/old stage for deliberate rollback, rather
than deleting unrelated paths or using a stale binary as evidence of removal.
