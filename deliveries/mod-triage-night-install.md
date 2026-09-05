# Triage Night — owner installation, SQL, testing and rollback

**PREPARED, NOT RELEASED.** Candidate SHA/run and final source details are pending.
Director and independent Reviewer approved the proposal and Wildcard chose it; that is
not implementation acceptance. This guide will be bound to the exact reviewed candidate
and its own complete official evidence before READY FOR LIVE TEST.

Triage Night is a solo level80 priest healing challenge. Three patients retain their
health through five45second injury rounds and finite10second breaks. Ordinary spells,
real mana and two six-second stabilization charges create repeated priority decisions.
The module supplies no player health/mana, economic reward or permanent progression.
Scripted deterioration is health loss and bypasses shields. Other healer classes and
party-targeted/AoE compatibility are not part of the qualifying claim.

## Exact target and separate staging install

Stock WoW3.3.5a build12340; Ubuntu24.04x86-64; AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`; Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.

Use an already working disposable checkout at these pins, ordinary build dependencies,
local disposable databases and extracted stock-client data. The Forge does not operate
the live installation. Keep the previous working binaries/configuration and normal backup.
Replace the path placeholders. The UNSET candidate deliberately stops this draft.

```bash
set -euo pipefail
AC=/absolute/path/to/disposable/azerothcore
FORGE=/absolute/path/to/wow-server-forge
WORK=/absolute/path/to/new/triage-night-test
CANDIDATE=UNSET
test "$CANDIDATE" != UNSET
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
test ! -e "$AC/modules/mod-triage-night"
test ! -e "$WORK"
command -v cmake
command -v clang-18
command -v clang++-18
mkdir -p "$WORK/export" "$STAGE"
git -C "$FORGE" archive "$CANDIDATE" projects/mod-triage-night |
  tar -x -C "$WORK/export"
cp -a "$WORK/export/projects/mod-triage-night" "$AC/modules/mod-triage-night"
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

## Owned SQL and collision preflight

The reserved world identities are creature/template-model entries911100–911103:
one controller and three patients. Their current source/SQL bindings are:

| Entry | Name | ScriptName | CreatureDisplayID |
|---|---|---|---:|
| 911100 | Triage Night Controller | npc_triage_night_controller | 13069 |
| 911101 | Patient One | npc_triage_night_patient | 6570 |
| 911102 | Patient Two | npc_triage_night_patient | 2588 |
| 911103 | Patient Three | npc_triage_night_patient | 1027 |

Patients are friendly faction35, selectable, with CAN_ASSIST and no native health
regeneration. Only the controller is invisible/not selectable. There are no permanent creature
spawns, npc_text rows, character/auth migrations or stock-world modifications.

Before a first install, use the owner's normal local MySQL authentication against the
**disposable world database** and inspect:

```sql
SELECT entry, name, ScriptName, type_flags, unit_flags
FROM creature_template WHERE entry BETWEEN 911100 AND 911103;
SELECT CreatureID, Idx, CreatureDisplayID
FROM creature_template_model WHERE CreatureID BETWEEN 911100 AND 911103;
SELECT name, hash, state FROM updates
WHERE name = '2026_09_05_00_triage_night.sql';
```

For a fresh installation all three queries should return no rows. Any existing row
requires identifying a prior installation or foreign collision. Do not overwrite it,
use REPLACE/INSERT IGNORE, import with mysql --force, or broaden deletion ranges.

Choose exactly one installation method:

**Native updater:** keep world updates enabled (native Updates.EnableDatabases=7 includes
world flag4), and keep SourceDirectory empty if the compiled source path is still valid,
or set it to the actual disposable AC directory. Normal startup should discover:

```text
modules/mod-triage-night/data/sql/db-world/2026_09_05_00_triage_night.sql
```

It applies once and records its history. Expect four templates, four model rows and one
tracked update afterward. Do not manually import the same SQL before that first start.

**One-time manual import:** only for an initialized disposable database whose world
updates are intentionally managed manually. Keep world updates disabled (for example
Updates.EnableDatabases=3 retains auth/character updates but excludes world). With the
worldserver stopped, after the empty-ID checks:

```bash
WORLD_DB=acore_world
mysql --database="$WORLD_DB" < "$AC/modules/mod-triage-night/data/sql/db-world/2026_09_05_00_triage_night.sql"
```

Use existing local authentication options as needed. Manual import does not create native
updater history. Do not later enable the world updater over that untracked installed SQL;
it would attempt a duplicate import. Use the native method unless already managing that
lifecycle yourself.

## Configuration, commands and logs

Use the already working local disposable auth/world and Playerbots configuration and
extracted DBC/maps/vmaps/mmaps. Copy the installed configuration if no override exists:

```bash
test ! -e "$STAGE/etc/modules/mod_triage_night.conf"
cp "$STAGE/etc/modules/mod_triage_night.conf.dist" \
   "$STAGE/etc/modules/mod_triage_night.conf"
```

The default is:

```ini
TriageNight.Enable = 1
```

Keep native `Logger.module=4,Console Server` for INFO (WARN is3 and suppresses INFO).
The source-defined prefix `TRIAGE_NIGHT_CONFIG` reports reload/enabled booleans and proves
config load only. Player starts use `TRIAGE_NIGHT_START`; outcomes use `TRIAGE_NIGHT_RESULT`.
Check Errors.log and ordinary startup logs. This feature creates
its actors on a player start command, not at server startup. No registrar or NPC travel
route is required; dry-run/config-load evidence does not play the healing challenge.

| Command | Player flow |
|---|---|
| `.triage help` | Explain access, pressure, healing limits and all custom actions |
| `.triage start` | Start Training at a suitable outdoor location |
| `.triage start training` | Explicitly select Training |
| `.triage start veteran` | Select the harder pressure preset |
| `.triage status` | Inspect the current run and result information |
| `.triage stabilize 1`, `2` or `3` | Spend one of two charges on that patient |
| `.triage stop` | End the owned run and clean up |

The qualifying path uses one level80 priest with ordinary learned direct single-target
heals and normal healing gear. Start alive, out of combat and not casting, unflagged for
PvP and outside a duel, unmounted on dry outdoor ground on a normal world map. Face open
ground. Start checks suitable nearby ground/LOS and rejects unavailable samples rather
than guessing Z. Terrain sampling is not a guarantee of client navigation. During the
shift, normal casts and channels are allowed. Remain within20horizontal yards and5vertical
yards of the start, on the same map and exact phase, with normal footing.

Three named patients and their ordinary target/friendly-nameplate health displays show
competing health states, starting at12000health each. Read incoming-injury warnings, choose spells/targets, and spend
stabilization when its six seconds buy time. Health persists between rounds; the module
never refills player mana or health. After a success/failure result, recover through
normal gameplay and retry. There is no extra operator, helper healer, custom UI or addon.
The initial briefing lasts10seconds. Five45second injury rounds have four10second breaks
and a six-minute hard cap. Stabilization works only during injury rounds on a visible
patient who is not already stabilized. It pauses future deterioration without immediate
healing; invalid requests use no charge. Status keeps your last five results this login.

## One-Human Playability

The complete solo loop is public help/start, five healing rounds and breaks,
ordinary win/failure, recorded outcome, normal recovery/retry and stop. One human priest,
one stock client and one operated account suffice. There are exactly three patients and
no enemies; presets change injury pressure rather than bot or party scaling. The human
casts every heal and chooses every stabilization. Patients/controllers execute schedules
only; no bot cognition or healing assistance is required or promised. Zero bots is complete.

Exact manual sequence, **PENDING LIVE/IN-GAME VALIDATION**:

1. On one level80 priest with ordinary direct heals and healing gear, walk to a safe
   open outdoor area. Read `.triage help`; start Training. Confirm all three patients
   are visible, targetable and close enough to heal through normal client controls.
2. Cast ordinary direct single-target heals on each patient. Observe actual native
   health gain, mana cost and wounded/recovered presentation. Do not infer shield or
   party-AoE support; scripted deterioration explicitly bypasses shields.
3. Follow pressure warnings and prioritize efficient versus fast healing. Stabilize
   one numbered patient and verify a six-second deterioration pause consumes one charge;
   verify only two charges exist for the complete shift.
4. Finish all five rounds with patients alive. Observe finite10second breaks, persistent
   wounds, normal player mana and one success/result with owned-actor cleanup.
5. Recover normally and retry. Let injury reach a patient's lethal threshold; observe
   the patient-lost result, SHIFT ENDED and cleanup. The source uses a dead pose at one
   health before cleanup rather than creating a normal corpse. Then restart. Stop explicitly,
   leave the area and test logout/map/death
   interruption as documented. No orphaned patients or retained charge should remain.
6. After the full Training loop, try Veteran. Record gear, spell choices, timing, mana
   and failure point. Friendly nameplate/pose readability and pressure tuning are manual
   evidence; proposal reasoning and CI do not prove that the encounter feels balanced.

Optional bots do not heal patients or operate commands. Other healer classes, group/AoE
healing and bot assistance are outside the qualifying claim. Report patient number,
round/preset, initial/final health and mana, spell/action, candidate SHA and relevant logs
for a mismatch. No second human or GM intervention is needed to complete the primary test.

For a short owner-recorded demonstration, the source package's `docs/DEMO.md` gives a
90-second sequence: start and frame the numbered patients, show direct healing and mana
use during round1, retain wounds through the55–65second recovery break, then show round2's
first warning/impact around73/77seconds and spend one stabilization while healing another
patient. Finish with status and continue the full shift or stop cleanly. Timing assumes
ordinary server updates. This is a future capture plan, not an executed gameplay test.

## Disable and full removal

Set TriageNight.Enable=0 and use ordinary administrator reload config or restart in the
disposable environment. New starts reject while disabled; active shifts end and clean up
on their next update. Any successful config reload ends active shifts, including when
Enable remains1. These maintenance actions are separate from ordinary play.

For full removal, stop the server normally. Preserve the module's uninstall SQL first,
archive its configuration and move only mod-triage-night out of the AC modules directory.
Reconfigure/rebuild/install without it, preserving Playerbots and unrelated modules.
Use the prior working binary/config backup if reverting an installation failure.

After inspecting the four reserved rows for exact Triage Night ownership, apply the
module's `sql/uninstall_world.sql`. It deletes model rows joined to templates in911100–911103
whose ScriptName is `npc_triage_night_controller` or `npc_triage_night_patient`, then deletes
those matching templates. With the stopped disposable world database selected:

```bash
mysql --database="$WORLD_DB" < /path/to/preserved/mod-triage-night/sql/uninstall_world.sql
```

Never broaden cleanup to foreign rows.
There is no character/auth data or permanent world spawn to remove. Native updater
history is retained; reinstall after removal may require an explicit one-time import.
Do not delete unrelated updater history to force reapplication. Temporary session results
and actors are not persistent progression and are not a reason to edit character data.
