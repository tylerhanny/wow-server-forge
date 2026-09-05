# Field Repairs — owner installation, testing and rollback

**READY FOR LIVE TEST — accepted for early delivery on 2026-09-05.** Frozen candidate
`1450d92f8bcf3a8282526120753ed5f750939722` passed full official run
[33970121674](https://github.com/tylerhanny/wow-server-forge/actions/runs/33970121674)
under judge `8d21e8b1b4920b4966760ba621751725bd411444`, plus independent source,
one-human and actual-artifact review. Build/install/config, both server dry-runs, native
units and final source integrity passed. Actual player repairs remain PENDING LIVE/IN-GAME
VALIDATION. This external final status supersedes the frozen source's truthful pre-run status.
No commands in this guide have been executed by the Forge against an owner's server.

Field Repairs provides explicitly confirmed paid repair of the human character's
carried/equipped gear. It uses current native personal-gold prices, without a reputation
discount. Native repair may skip unaffordable items and repair later affordable items;
partial repair is possible. No free repairs, guild funds, NPC, SQL or persistent module
record is added. Only the human requesting service receives repairs.

## Exact target and separate staging install

Stock WoW3.3.5a build12340; Ubuntu24.04x86-64; AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`; Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.

Use an already working disposable checkout at these pins, ordinary build dependencies,
local disposable databases and extracted stock-client data. The Forge does not operate
the live installation. Keep the previous working binaries/configuration and normal backup.
Replace the path placeholders. Use the exact accepted candidate below.

```bash
set -euo pipefail
AC=/absolute/path/to/disposable/azerothcore
FORGE=/absolute/path/to/wow-server-forge
WORK=/absolute/path/to/new/field-repairs-test
CANDIDATE=1450d92f8bcf3a8282526120753ed5f750939722
PB="$AC/modules/mod-playerbots"
AC_PIN=47960183bb03b83e8943eb2f0f39c16df9710c9d
PB_PIN=2f7d9f774987d0157c6a0d0cc08c40bec3db3945
BUILD="$WORK/build"
STAGE="$WORK/stage"
test "$(git -C "$AC" rev-parse HEAD)" = "$AC_PIN"
test "$(git -C "$PB" rev-parse HEAD)" = "$PB_PIN"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
git -C "$FORGE" cat-file -e "$CANDIDATE^{commit}"
test ! -e "$AC/modules/mod-field-repairs"
test ! -e "$WORK"
command -v cmake
command -v clang-18
command -v clang++-18
mkdir -p "$WORK/export" "$STAGE"
git -C "$FORGE" archive "$CANDIDATE" projects/mod-field-repairs |
  tar -x -C "$WORK/export"
cp -a "$WORK/export/projects/mod-field-repairs" "$AC/modules/mod-field-repairs"
cmake -S "$AC" -B "$BUILD" \
  -DCMAKE_C_COMPILER=clang-18 -DCMAKE_CXX_COMPILER=clang++-18 \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$STAGE" \
  -DAPPS_BUILD=all -DTOOLS_BUILD=none -DSCRIPTS=static -DMODULES=static \
  -DWITH_WARNINGS=ON -DBUILD_TESTING=OFF 2>&1 | tee "$WORK/configure.log"
cmake --build "$BUILD" --parallel 2 2>&1 | tee "$WORK/build.log"
cmake --install "$BUILD" 2>&1 | tee "$WORK/install.log"
test "$(git -C "$AC" rev-parse HEAD)" = "$AC_PIN"
test "$(git -C "$PB" rev-parse HEAD)" = "$PB_PIN"
git -C "$AC" diff --exit-code HEAD --
git -C "$PB" diff --exit-code HEAD --
```

An occupied destination stops the procedure. Inspect it instead of merging files into
another module installation. If the exact frozen commit is missing, fetch the published
project branch in the Forge clone and recheck its SHA; never update either dependency.

This is an ordinary installation build, not the official acceptance run. BUILD_TESTING=OFF
omits the upstream unit target for installation; the independent judge still builds/runs
it and enforces strict project warnings, visible verified-upstream warnings and all other
checks. Do not copy the CI-only WorldMock correction or warning hook into this checkout.

## Configuration and useful logs

Keep the existing disposable auth/world and Playerbots settings, databases and data paths.
Create the module configuration from the installed distribution if it does not exist:

```bash
test ! -e "$STAGE/etc/modules/mod_field_repairs.conf"
cp "$STAGE/etc/modules/mod_field_repairs.conf.dist" \
   "$STAGE/etc/modules/mod_field_repairs.conf"
```

The V1 default is:

```ini
FieldRepairs.Enable = 1
```

No SQL import or account/database migration is part of this module. Consent lasts30seconds;
there is no automatic repair mode. Keep native module INFO logging enabled, preserving
your configured appenders. At the pinned defaults:

```ini
Logger.module=4,Console Server
```

INFO is4 and WARN is3; lowering the logger to3 suppresses INFO. Start only the newly staged
server through the owner's normal disposable procedure, with the proper existing local
database/data configuration. The source-defined configuration marker is:
`FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`.
Inspect normal startup logs and Errors.log, then perform the ordinary-player tests below.
No in-game result is proven by a config marker alone.

## Commands and complete one-human loop

An ordinary character with durable gear uses:

| Command | Effect |
|---|---|
| `.fieldrepair status` | Inspect damaged gear count, personal balance and restrictions |
| `.fieldrepair request` | Read current-price/partial-repair disclosure and open30second consent |
| `.fieldrepair confirm` | Recheck consent, eligibility and all costs/items; perform native paid repairs once |
| `.fieldrepair cancel` | Clear consent without repair or payment |

The module does not promise a binding price quote. Current native costs apply at confirmation.
Report actual wallet/durability outcomes, including zero or partial repair. Fully repaired
gear incurs no charge. Unaffordable items remain damaged; earn gold through normal solo
play, then request and confirm again. Native repair order and affordability remain in use.
The current `Rate.RepairCost` and native one-copper minimum apply. Bank, buyback and key
slots are excluded. Unsafe item/pricing data refuses the entire service before payment.

Eligibility requires alive/in-world, outdoors on a normal-world/non-instance map,
out-of-combat/non-PvP/non-duel state, with no trade, taxi, vehicle, transport, pending
teleport, active cast/control impairment or logout. Confirmation rechecks the current
state. Death/map change/logout/config reload clears pending consent.

## One-Human Playability

The complete qualifying path is solo: inspect damaged gear, request/confirm repairs,
observe equipment and personal gold, earn more money if needed, retry, and cancel or
let consent expire. Any ordinary class/level with durable gear can use it. One human,
one client and one operated account suffice. There are no enemies, helper roles or scaling.
Zero bots retains the whole feature. Optional bots only perform ordinary combat/follow
while the human earns gold; they operate no custom action and receive no repairs.

Exact manual sequence, **PENDING LIVE/IN-GAME VALIDATION**:

1. On one ordinary character in a safe outdoor normal-world area, inspect damaged durable gear
   and personal gold, then `.fieldrepair status`.
2. Request service and read its native-price/possible-partial notice. Cancel; verify
   gear and gold did not change. No second character or GM action is needed.
3. Request and confirm; compare actual durability, wallet delta, reported repaired/
   remaining counts and any restored broken-item stats. This is the success/outcome loop.
4. Repeat on repaired gear: no charge. When naturally low on gold, verify honest no-repair
   or partial repair. Earn money normally and retry; no refund or atomic-repair promise.
5. Request then let consent expire. Request again and confirm while ordinary combat or
   a cast is active: refusal consumes consent without payment. Merely entering and leaving
   combat before an unexpired confirmation does not cancel consent. Map change, death or
   logout clears consent; recover normally and request again. No delayed charge occurs.
6. Cancel to exit. Test owner-admin disable/reload/re-enable in disposable staging and
   require a fresh request. Optionally repeat with normal bots; only the human is serviced.

Record candidate SHA, command, initial/final gold and item durability, reported outcome,
class/level and relevant logs if behavior differs. Actual inventory/stat updates, pricing
feel and party coexistence remain manual tests; proposal review and CI are not a playthrough.

## Disable and rollback

Set `FieldRepairs.Enable = 0` and use the normal administrator `reload config` command,
or restart the disposable server. New repair requests must reject and pending consent
must clear; re-enabling requires a new request. This maintenance action is not part of
the ordinary player's required loop.

For full removal, stop the disposable server normally. Archive this module and its config,
move only `mod-field-repairs` out of the AC modules directory, then reconfigure/rebuild
and install the server without it into a new separate prefix; retire the old module config.
Keep Playerbots and unrelated modules intact. Use the
owner's prior working binaries/configuration if reverting an installation failure.

There is no module SQL or persistent record to delete. Actual native repairs and spent
gold are normal character state; disabling/removing this service does not undo them.
Do not edit character data or invent refunds as part of module rollback.
