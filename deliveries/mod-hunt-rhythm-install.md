# Hunt Rhythm — owner install, testing and rollback

Prepared external installation guide, 2026-09-05. Source candidate:
`4aaa3ae188e7bcdba2569676911e14142ac378e2` (`project/hunt-rhythm`).
Independent source/one-human review passed; official run `33951428776` is pending at
preparation. This guide is not acceptance. The final exact-candidate attestation in
`HARVEST.md` controls readiness and supersedes the frozen package's pre-run status.
The commands below are instructions, **not executed evidence**.

This note uses an existing **disposable Ubuntu 24.04 x86-64 checkout and databases**.
It installs into a new prefix and changes no running installation/service. The Forge
does not connect to or operate the owner's live server. No SQL is shipped by Hunt Rhythm.

## Prepare a distinct build and installation

Prerequisites: normal pinned AzerothCore build dependencies, CMake, Git, make, Clang 18,
an existing exact-pin Playerbots checkout, disposable auth/characters/world/playerbots
databases, and correctly extracted 3.3.5a map/vmap/mmap/DBC data for actual gameplay.
Additional XP-changing modules are outside this reviewed combination.

Replace the three `/path/to/...` values. Use a new work directory and keep the selected
checkout's existing build directory and previous installation untouched.

```bash
set -euo pipefail
AC=/path/to/disposable/azerothcore
FORGE=/path/to/wow-server-forge
WORK=/path/to/new/hunt-rhythm-4aaa3ae-test
PB="$AC/modules/mod-playerbots"
CANDIDATE=4aaa3ae188e7bcdba2569676911e14142ac378e2
AC_PIN=47960183bb03b83e8943eb2f0f39c16df9710c9d
PB_PIN=2f7d9f774987d0157c6a0d0cc08c40bec3db3945
BUILD="$WORK/build-with-rhythm"
STAGE="$WORK/stage-with-rhythm"

test "$(git -C "$AC" rev-parse HEAD)" = "$AC_PIN"
test "$(git -C "$PB" rev-parse HEAD)" = "$PB_PIN"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
git -C "$FORGE" cat-file -e "$CANDIDATE^{commit}"
test ! -e "$AC/modules/mod-hunt-rhythm"
test ! -e "$WORK"
command -v cmake
command -v clang-18
command -v clang++-18

mkdir -p "$WORK/export" "$STAGE"
git -C "$FORGE" archive "$CANDIDATE" projects/mod-hunt-rhythm |
  tar -x -C "$WORK/export"
cp -a "$WORK/export/projects/mod-hunt-rhythm" "$AC/modules/mod-hunt-rhythm"

COMMON_CMAKE=(
  -DCMAKE_C_COMPILER=clang-18
  -DCMAKE_CXX_COMPILER=clang++-18
  -DCMAKE_BUILD_TYPE=Release
  -DAPPS_BUILD=all
  -DTOOLS_BUILD=none
  -DSCRIPTS=static
  -DMODULES=static
  -DWITH_WARNINGS=ON
  -DBUILD_TESTING=OFF
)
cmake -S "$AC" -B "$BUILD" "${COMMON_CMAKE[@]}" \
  -DCMAKE_INSTALL_PREFIX="$STAGE" 2>&1 | tee "$WORK/configure.log"
cmake --build "$BUILD" --parallel 2 2>&1 | tee "$WORK/build.log"
cmake --install "$BUILD" 2>&1 | tee "$WORK/install.log"

# Verify both pins and tracked dependency source again; no checkout/reset/patch is used.
test "$(git -C "$AC" rev-parse HEAD)" = "$AC_PIN"
test "$(git -C "$PB" rev-parse HEAD)" = "$PB_PIN"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
```

`BUILD_TESTING=OFF` is an **ordinary installation setting only**. It leaves the pinned
test source unchanged and does not build the unrelated upstream unit-test executable.
Never apply/copy the CI WorldMock fixture patch here. Never copy the judge's fixture
adapter or warning hook into this checkout. This owner build uses ordinary native warning
settings, retains its logs, and does **not** replace official acceptance: the independent
gate retains its full unit build/execution, fixture containment, source provenance and
fatal project-warning rules. Do not describe this install command as that gate passing.
Investigate/report any new module warning or build failure rather than patching dependencies.

If a destination already exists, the checks stop; inspect it instead of overwriting it.
If the frozen commit is missing from the local Forge clone, fetch the already-published
`project/hunt-rhythm` branch in that clone, then rerun the exact `cat-file` check.

## Configure and run the staged server

Use the staged `etc/authserver.conf.dist` and `etc/worldserver.conf.dist` as templates,
or separately prepared **disposable-only** configs. Configure only the local disposable
databases, its realm/listen ports and extracted data path. Do not copy live credentials
or point staged binaries at live databases. Do not alter network infrastructure.

For a fresh stage:

```bash
cp -n "$STAGE/etc/authserver.conf.dist" "$STAGE/etc/authserver.conf"
cp -n "$STAGE/etc/worldserver.conf.dist" "$STAGE/etc/worldserver.conf"
cp -n "$STAGE/etc/modules/mod_hunt_rhythm.conf.dist" \
  "$STAGE/etc/modules/mod_hunt_rhythm.conf"
mkdir -p "$STAGE/logs"
```

Edit the two server configs for the existing disposable environment before starting.
Set `DataDir` in worldserver.conf to the fully extracted test-data directory, and `LogsDir`
to the new stage's absolute `logs` path. For local-only testing bind the disposable servers
to the local interface and use that disposable realm's matching port/address configuration.
No account/database setup or infrastructure change is part of this module install.
Keep Playerbots enabled with the owner's already-working ordinary test configuration;
random bot population and addclass-generated accounts are not requirements of Hunt Rhythm.

The four module defaults are exactly:

```ini
HuntRhythm.Enable = 1
HuntRhythm.WindowSeconds = 60
HuntRhythm.StepPercent = 2
HuntRhythm.MaxBonusPercent = 10
```

For visible INFO evidence, change the existing `Logger.module` severity in worldserver.conf
from `4` to `3`, preserving its appenders. The pinned default is
`Logger.module=4,Console Server`; with unchanged appenders use:

```ini
Logger.module=3,Console Server
```

Start each staged executable in its own terminal. Set `STAGE` to the same absolute prefix
in each terminal; do not use an existing system service or replace running binaries.

```bash
# Terminal 1, after its configuration is prepared:
cd "$STAGE/bin"
./authserver -c "$STAGE/etc/authserver.conf"
```

```bash
# Terminal 2, after its configuration is prepared:
cd "$STAGE/bin"
./worldserver -c "$STAGE/etc/worldserver.conf"
```

Confirm normal world startup and inspect its configured logs for
`HUNT_RHYTHM_CONFIG reload=0 enabled=1 window=60 step=2 cap=10`.
The marker proves registration/config loading only. Use normal running worldserver for
the client test; `--dry-run` exits before world updates and cannot exercise a kill streak.
There is **no Hunt Rhythm SQL migration, SQL import, custom NPC or spawned encounter**.

## One-Human Playability — test in this order

One stock 3.3.5a client, one ordinary level 10–30 character and no bots are sufficient.
No second human/client/operated account is required. Retain the candidate README's full
checklist; this order gives a short primary demonstration before optional edge cases.

1. **Access/start:** stand outdoors among hostile non-elite XP-bearing creatures. Use
   `.rhythm status` (opted out), then `.rhythm start`. No GM permissions are needed.
2. **Success/outcome:** kill six eligible creatures with less than 60 seconds between
   each. Applied bonuses progress 0/2/4/6/8/10%; the seventh stays capped without another
   cap notice. Status after the first kill shows streak 1 and next bonus +2%.
3. **Fail/retry:** repeat `.rhythm start` during a streak and ensure it does not refresh
   the timer. Wait at least 60 seconds after the previous eligible kill; status/next kill
   resets the chain. The next eligible kill begins again at 0%, without losing earned XP.
4. **Recovery:** die in ordinary solo PvE, recover and retry. Death and entering a map
   reset the streak but preserve opt-in; same-map zone travel does not reset it.
5. **Exit:** `.rhythm stop` removes the bonus immediately. Start again and relog; status
   returns to opted out. Earned XP remains unchanged.
6. **Exclusions:** check quest/exploration XP, gray/non-hostile targets, pets/summons,
   elites/dungeon enemies and normal XP-locked/capped states against README. None may
   advance or refresh the chain. Normal core rewards are not replaced.
7. **Optional components:** observe rested/hunter-pet awards and normal `Rate.XP.Pet`;
   rounding/group/pet/rested/RAF caveats are in README. RAF may remain untested and is
   not a reason to operate a second account. Then optionally repeat with normal Playerbots;
   only the human issues Rhythm commands. Bot combat/follow/shared-credit feel is pending
   real observation, not proven by CI or the source review.
8. **Operator lifecycle:** try disable/re-enable below and one bounded timer change.
   Successful reload clears everyone's opt-in; each human must start again. Keep logs
   and observed results separately from the existing exact-candidate CI evidence.

## Disable, re-enable and remove

**Immediate feature disable:** in the staged module config set `HuntRhythm.Enable = 0`.
Use the normal authorized operator config reload (`reload config` in the test server's
console; `.reload config` from an appropriately privileged test character), or cleanly
stop/restart the staged server. Check `HUNT_RHYTHM_CONFIG ... enabled=0`; successful
reload clears all opt-ins/chains. Subsequent awards use ordinary XP. A failed reload
does not apply settings: inspect its error and use a clean restart if needed.

**Re-enable:** restore `HuntRhythm.Enable = 1`, reload or restart, verify the enabled
marker and opt in again. Timer accepts 15–300, step 1–5 and cap 1–20; out-of-range
numbers are clamped and logged. The four defaults above are the baseline demonstration.

**Full removal:** first stop the staged worldserver cleanly with its ordinary shutdown
procedure and wait for exit. Stop its staged authserver if retiring this test instance.
Never overwrite running binaries. Keep previous binaries/config/logs as rollback material;
no SQL cleanup or XP rollback is necessary. To create an installation without the feature:

```bash
# Reuse the same path/pin/COMMON_CMAKE assignments from the preparation shell.
test ! -e "$WORK/removed-mod-hunt-rhythm"
mv -- "$AC/modules/mod-hunt-rhythm" "$WORK/removed-mod-hunt-rhythm"
WITHOUT_BUILD="$WORK/build-without-rhythm"
WITHOUT_STAGE="$WORK/stage-without-rhythm"
test ! -e "$WITHOUT_BUILD"
test ! -e "$WITHOUT_STAGE"
cmake -S "$AC" -B "$WITHOUT_BUILD" "${COMMON_CMAKE[@]}" \
  -DCMAKE_INSTALL_PREFIX="$WITHOUT_STAGE" 2>&1 | tee "$WORK/remove-configure.log"
cmake --build "$WITHOUT_BUILD" --parallel 2 2>&1 | tee "$WORK/remove-build.log"
cmake --install "$WITHOUT_BUILD" 2>&1 | tee "$WORK/remove-install.log"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
```

Prepare the without-feature stage's own disposable server configs/data reference as above.
It has no Hunt Rhythm module config to load. Start it only after the prior instance exits;
`.rhythm` should no longer be a registered module command. The saved module and old stage
can be restored deliberately if desired. Do not reuse a stale binary and call that removal.
Archiving the old stage also removes its installed module config from active use; nothing
needs to be deleted from unrelated paths or the world/character databases.

Rollback limits: disabling/removal stops future added XP; it never subtracts already earned
XP or reverses ordinary saved character progress. No Hunt Rhythm persistent state exists.
