# Stormwright owner install / rollback / first test

Prepared for Director delivery from frozen candidate
`bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc` on `project/stormwright`.
This external installation guide does not change the candidate or the official judge.
The final exact-candidate attestation in `HARVEST.md` controls readiness and supersedes
the frozen package's honestly pending pre-run status. This guide is not acceptance.

**Release status at preparation:** independent source review and source-level
ONE_HUMAN_REVIEW passed for the minimal three-call impact GUID repair. Corrected candidate
`bde390e` is pending official run `33955586542`. Original a155817 failed compilation in
`33952393192`; its install/runtime/unit/supplemental stages did not run and the failure
remains preserved. Neither source review nor these prepared instructions are acceptance. Director must
attach the terminal exact-SHA gate and applicable normal-startup evidence before
calling this READY FOR LIVE TEST. No client gameplay, public walking route, visual
readability, class balance or bot competence has been tested by this note.

All commands below are for a local disposable Ubuntu staging environment first.
Tyler controls any later owner installation; Forge agents do not access the live server.

## Exact checkout and staging

Target: stock client 3.3.5a build 12340; Ubuntu 24.04 x86-64;
AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`;
Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.

Example for a fresh, empty disposable staging directory, with ordinary pinned build
prerequisites already installed. Replace the first path with an actual staging path.
These commands do not select or modify an existing live checkout.

```bash
set -euo pipefail
STORM_STAGE=/absolute/path/to/disposable-stormwright-stage
mkdir -p "$STORM_STAGE"
AC_SRC="$STORM_STAGE/ac"
CANDIDATE_SRC="$STORM_STAGE/candidate"
INSTALL_ROOT="$STORM_STAGE/install"
WORLD_DB=acore_world
test ! -e "$AC_SRC"
test ! -e "$CANDIDATE_SRC"
test ! -e "$INSTALL_ROOT"
git clone https://github.com/mod-playerbots/azerothcore-wotlk.git "$AC_SRC"
git -C "$AC_SRC" checkout --detach 47960183bb03b83e8943eb2f0f39c16df9710c9d
git -C "$AC_SRC" submodule update --init --recursive
test ! -e "$AC_SRC/modules/mod-playerbots"
git clone https://github.com/mod-playerbots/mod-playerbots.git "$AC_SRC/modules/mod-playerbots"
git -C "$AC_SRC/modules/mod-playerbots" checkout --detach 2f7d9f774987d0157c6a0d0cc08c40bec3db3945
git clone --no-checkout https://github.com/tylerhanny/wow-server-forge.git "$CANDIDATE_SRC"
git -C "$CANDIDATE_SRC" checkout --detach bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc
test "$(git -C "$AC_SRC" rev-parse HEAD)" = 47960183bb03b83e8943eb2f0f39c16df9710c9d
test "$(git -C "$AC_SRC/modules/mod-playerbots" rev-parse HEAD)" = 2f7d9f774987d0157c6a0d0cc08c40bec3db3945
test "$(git -C "$CANDIDATE_SRC" rev-parse HEAD)" = bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc
test ! -e "$AC_SRC/modules/mod-stormwright"
cp -a "$CANDIDATE_SRC/projects/mod-stormwright" "$AC_SRC/modules/mod-stormwright"
```

For an existing disposable checkout already at the exact pins, use its paths and run
the three identity checks and absent-destination check before copying. Do not pull a
new dependency revision or merge this directory into an occupied module directory.
Keep the previous working server binary/config and a normal database backup before
any owner installation. No core/PB source changes are part of this module.

Example installation build (not an acceptance run):

```bash
cmake -S "$AC_SRC" -B "$AC_SRC/build-stormwright" \
  -DCMAKE_C_COMPILER=clang-18 -DCMAKE_CXX_COMPILER=clang++-18 \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$INSTALL_ROOT" \
  -DAPPS_BUILD=all -DTOOLS_BUILD=none -DSCRIPTS=static -DMODULES=static \
  -DWITH_WARNINGS=ON -DBUILD_TESTING=OFF
cmake --build "$AC_SRC/build-stormwright" --parallel 2
cmake --install "$AC_SRC/build-stormwright"
```

Retain normal site-specific compiler/build settings where appropriate. Playerbots is
discovered from its module directory. The staging installation build above omits
unit-test targets; it does not replace the independently reviewed official gate.
Do not ship the Forge's CI-only WorldMock fixture correction into this checkout.
Point the disposable configuration at properly initialized disposable databases and
valid extracted 3.3.5a DBC/maps/vmaps/mmaps using the ordinary AzerothCore setup.
No credentials or private endpoints are supplied here.

## Reserved data and collision preflight

The installer writes only these world database identities:

| Creature entry | Name / script role | Display ID | DBC model path |
|---:|---|---:|---|
| 910900 | Nix Stormwright / registrar | 5443 | Character/Gnome/Male/GnomeMale.mdx |
| 910901 | Stormwright Capacitor / rod | 17856 | Creature/QuestObjects/Creature_PowerCrystal.mdx |
| 910902 | The Unbound Storm / enemy | 26382 | Creature/RevenantAir/RevenantAir.mdx |
| 910903 | Stormwright Pursuer / enemy | 23349 | Creature/ElementalEarth/ElementalEarth.mdx |
| 910904 | Stormwright Mark / marker | 26753 | Creature/PowerSparkCreature/PowerSparkCreature.mdx |

Each has `creature_template_model.Idx=0`. `npc_text.ID=910900` supplies instructions.
There are no persistent creature/gameobject spawns, character/auth migrations, loot,
XP rewards, modified stock quests, spells or race paths. NPC display names are not
proof of assets: the invisible stock Tesla Coil/Crystal Spike models were rejected.

Before a first installation, run these **read-only** queries through the owner's
normal local MySQL authentication against the disposable world database:

```sql
SELECT entry, name, ScriptName
FROM creature_template WHERE entry BETWEEN 910900 AND 910904;
SELECT CreatureID, Idx, CreatureDisplayID
FROM creature_template_model WHERE CreatureID BETWEEN 910900 AND 910904;
SELECT ID, LEFT(text0_0, 80) AS text_prefix
FROM npc_text WHERE ID = 910900;
SELECT name, hash, state FROM updates
WHERE name = '2026_09_05_00_stormwright.sql';
```

For a fresh install, all four queries should return no rows. Any row requires
identifying whether this is an existing Stormwright installation, a removed module's
retained updater record, or a collision. Do not overwrite or delete another module's
IDs, use `REPLACE`, use `INSERT IGNORE`, or import with `mysql --force` to make it pass.
Check any existing custom data that also refers to this reserved creature range.

### Choose exactly one SQL installation method

**Native updater (recommended):** leave world updates enabled in the disposable
`worldserver.conf`; `Updates.EnableDatabases = 7` is the pinned default (world flag
is 4). Keep `SourceDirectory` empty when the built-in source path remains valid, or
set it to the real `AC_SRC` directory. Start normally. The native updater discovers:

```text
modules/mod-stormwright/data/sql/db-world/2026_09_05_00_stormwright.sql
```

It applies that file once and records it in the world database `updates` table.
Afterward, repeat the queries: expect five templates, five model rows, one text row,
and one tracked update. Do not manually import the same SQL before this first start.

**One-time manual import:** use only for an already initialized disposable world
database whose updates are intentionally managed manually. The world updater flag
must remain disabled (for example `Updates.EnableDatabases = 3` preserves auth/character
updates but excludes world). With the worldserver stopped, after the empty-ID checks:

```bash
WORLD_DB=acore_world
mysql --database="$WORLD_DB" < "$AC_SRC/modules/mod-stormwright/data/sql/db-world/2026_09_05_00_stormwright.sql"
```

Use the existing normal local client authentication if extra connection options are
needed. The file is a transaction with plain INSERTs; an occupied key is a failure.
A manual import does **not** create native updater history. Do not later turn on the
world updater over that untracked installed SQL: it would attempt a duplicate import.
Use the native method unless the owner already manages that database lifecycle.

## Installed configuration and first start

From the installed distribution, create an explicit module configuration:

```bash
test ! -e "$INSTALL_ROOT/etc/modules/mod_stormwright.conf"
cp "$INSTALL_ROOT/etc/modules/mod_stormwright.conf.dist" \
   "$INSTALL_ROOT/etc/modules/mod_stormwright.conf"
```

In `etc/modules/mod_stormwright.conf`:

```ini
Stormwright.Enable = 1
```

For visible registrar/outcome evidence, set the existing line in `worldserver.conf`
to INFO while retaining the configured appenders. At the pinned default appenders:

```ini
Logger.module=3,Console Server
```

The pinned default is `4,Console Server`, which hides the module's INFO outcome lines.
Start auth/world normally using the owner's ordinary local staging procedure. Inspect
`STORMWRIGHT_CONFIG reload=false enabled=true`, then
`STORMWRIGHT_REGISTRAR spawned=true ... derived_z=...`.
`STORMWRIGHT_SITE_UNAVAILABLE` means the registrar was not spawned: do not substitute
guessed Z values, a GM teleport, or forced actor placement. The module derives ground
height from actual loaded map data and rejects unavailable/unsuitable samples.

The official dry-run exits before WorldScript::OnStartup/world updates. A successful
supplemental normal-startup check can demonstrate those server paths, but it still
does not establish player access, navmesh/collision safety, visual legibility or fun.

## Ordinary-player access and the full loop

No player slash command, GM permission, custom item or addon is required. Travel by
normal world routes to Thousand Needles, enter the Shimmering Flats and reach Mirage
Raceway. Walk north of the raceway's staging area toward the apron. The module's
center is map 1 XY(-6250,-3750); Nix Stormwright is 40 yards south at XY(-6250,-3790),
with terrain-derived Z. The access route is a manual validation target, not a claimed
successful walk. Return toward the raceway normally to leave.

At living level 80, out of combat, talk to Nix within ordinary interaction range.
Start Normal Solo Pilot with no group/bots. All custom choices belong to this one
human. Lead a tracking spark into a ready capacitor; when it locks, move away. Click
the charged large crystal: Ground heals the pilot and repairs ward; Discharge removes
6% boss maximum health, opens armor for eight seconds, and kills owned pursuers within
eight yards. Spent small crystals cool, forcing new routes. Fight normally between
marks. Three misses, pilot failure/exit/abort, missing actors/evade or twelve minutes
end the attempt; boss death while the pilot remains valid wins. Read the result, recover
normally, return to Nix, and retry. The latest result is in memory/chat/log, not persistent
economy or fair rankings. One public attempt runs at a time.

Optional ordinary pinned bots may tank, heal, attack and follow. The pilot must lead
a party of at most five; nearby living level-80 members within 50 yards are frozen
into scaling. Solo has at most one pursuing add; party play has at most two. Bots
never use rods, custom menus, items, pressure plates or precision raid choreography.

## Safest disable and full removal

**Feature disable:** set `Stormwright.Enable = 0`. An administrator can use ordinary
server console `reload config` (or permitted in-game `.reload config`) to load it;
an active attempt ends on its next controller update. New attempts are rejected.
The idle registrar can remain until restart. A normal restart while disabled creates
no registrar. If initially started disabled, enabling requires a restart to spawn it.
These are admin maintenance operations, not requirements of the player loop.

**Full removal:** stop the worldserver normally before changing linked binaries or
SQL. Preserve the package and its uninstall script. Move only `mod-stormwright` out
of the AC `modules/` directory into a separate backup directory; reconfigure, rebuild
and install the server without it. Archive the installed Stormwright config. Retain
Playerbots and every unrelated module. No forced process termination is needed.

Then inspect the reserved rows against the names/scripts above. With only the known
Stormwright-owned identities present, run the separate manual cleanup:

```bash
mysql --database="$WORLD_DB" < "$CANDIDATE_SRC/projects/mod-stormwright/sql/uninstall_world.sql"
```

It deletes model rows only through matching owned creature templates, those templates
only with Stormwright script names, and text 910900 only with the expected Stormwright
prefix. It does not delete the updater's history, any character data, or stock spawn.
If identities differ from expected, inspect rather than broadening its DELETEs.
Repeat the reserved-row checks afterward. If reverting an installation failure,
restore the previous working binary/config through the owner's existing backup method.

Reinstall after native-updater removal needs an explicit one-time import because the
matching native update history remains and will otherwise skip the already-recorded
file. Do not delete arbitrary updater history to force reapplication. A prior manual
installation remains subject to the manual-updater distinction above.

## Ordered one-human smoke and feedback

1. Walk in and out normally; inspect nearby racing/quest actors, terrain, water,
   collision and LOS. Confirm Nix and all three capacitor locations are reachable.
2. Start **Normal Solo Pilot, no bots**, using ordinary gossip. Read the first 12-second
   warning and see the moving spark, fixed enlarged lock, impact and charge state.
3. Catch, dodge, and Discharge in combat. Lure the pursuer into the eight-yard blast;
   verify its death, boss health loss and eight-second normal-damage window.
4. While injured at full ward, catch and Ground; verify healing. At full health/full
   ward, Ground must preserve the charge. Miss once, then Ground to repair ward.
5. Win a full solo attempt; verify one result, cleanup, ordinary return/recovery, and
   a fresh retry with no carried ward/charge. Record class, gear, time and deaths.
6. Fail by three misses, exit and abort; test death/logout/reconnect and eventual
   twelve-minute timeout. Verify cleanup, no duplicate result or dead-pilot recovery.
7. Repeat a higher preset; then add normally controllable bots if desired. The human
   must still handle every custom mechanic. Repeat no-bots afterward. Report bots'
   actual tank/heal/attack/follow behavior separately from source-level feasibility.

Capture the failing step, visible rod/marker state, class/gear/roster and relevant
`STORMWRIGHT_*` lines. A 75-second demonstration script and fuller adversarial checklist
are in the exact candidate README. Do not present GM kills/teleports or extra human
operators as a successful one-human run.
