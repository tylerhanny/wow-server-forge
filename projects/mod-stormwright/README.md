# Stormwright

**Turn the boss's storm into your weapon before it tears the arena apart.**

Status: **COMPILER REPAIR — full rerun and acceptance pending.**
Source, stock model references, owned SQL/configuration, recovery/offense decisions,
terminal cleanup and developer rules checks are present. This is not yet approved
for installation on a live server. See [validation status](docs/VALIDATION.md).
The first official build (`33952393192`, candidate `a1558178`) failed because
impact visual packets require an explicit target GUID. The three calls are repaired;
installation, runtime and executable tests were not reached in that failed run.

One human pilot leads tracking lightning into three capacitor rods, moves after the mark
locks, then chooses what the stored charge buys: Ground restores pilot health and ward;
Discharge damages the armored boss, opens an eight-second damage window, and destroys
nearby pursuers. Cooling rods force new routes. Three missed catches shatter the ward;
every attempt has a twelve-minute cap. Normal, Surge and Tempest retain the same solo loop.

## One-Human Playability

The qualifying path is one level-80 human at one client/account. Solo Pilot has at most
one live pursuing add and a human-operated recovery choice that remains usable at full
ward when injured. Optional ordinary bots may tank, heal, attack and follow; they never
operate rods, make custom decisions or require an exact tank position. The starting
nearby roster is frozen, with at most five participants. Party play changes ordinary
combat pressure, not the number of custom operators.

The registrar owns every attempt, checks pilot/roster/actor identities, and exposes normal
player gossip. Death, leaving, disconnect, timeout, missing actors, disablement and evade
end the attempt; all owned actors are bounded and cleaned. Outcomes are assisted encounter
results, never an outsider-proof ranking. V1 holds the last result in memory
at its registrar and records terminal outcomes in the module log; it has no persistent
economy or character-power reward.

The public venue validation target is the northern Mirage Raceway apron, map 1, center
XY (-6250, -3750). The implementation derives Z from installed extracted terrain, validates
a bounded ground footprint and refuses to substitute a guessed height. Neither those
source checks nor DBC-only startup prove public walking access, collision/navmesh safety,
visual readability or competent bot traversal. These remain explicit site/client checks.
There is no GM teleport or second account in the intended access/start/outcome/retry/exit loop.

### Complete ordinary-player loop

1. Use normal world travel to Thousand Needles and Mirage Raceway in the Shimmering
   Flats. Walk north from the raceway staging area toward the apron. Nix Stormwright
   is placed south of the encounter footprint when extracted terrain passes the
   startup checks. This route still needs the explicit manual access check below;
   a GM teleport is not a substitute.
2. Be alive, level 80, out of combat, beside Nix. For Solo Pilot, use no group or bots.
   For companions, lead a party of at most five; nearby living level-80 members
   within 50 yards are frozen into the starting roster. Ineligible or distant
   members do not count toward scaling. Other humans may assist but are unnecessary.
3. Choose Normal, Surge or Tempest in ordinary gossip. A first mark arrives after
   12 seconds. Move close to a ready crystal capacitor during tracking; its center
   must be within 4.5 yards of the final mark. At LOCKED, move more than 3.5 yards
   away before impact. The marker follows only the pilot; bots need no dodging.
4. Click the charged, enlarged capacitor. **Discharge** immediately removes 6% of
   boss maximum health, opens normal damage for eight seconds, and destroys owned
   pursuers within eight yards of that capacitor. **Ground** restores one ward and
   30%/28%/26% of pilot maximum health. Full ward plus an injured pilot can Ground;
   full health and full ward does not waste a charge. No currency or item is required.
5. Route toward a different ready capacitor while the used one cools. Fight normally
   between storm marks. Decide whether to lure the pursuer into the blast, kill it
   directly, or spend a charge on recovery. Armor reduces ordinary boss damage to
   5% outside the discharge window; environmental play remains valuable.
6. Break the boss while alive and in the arena to win. Pilot death, disconnect,
   leaving the 45-yard radius, abort, missing actors, enemy evade, ward depletion,
   module disablement, or twelve minutes ends the attempt and despawns owned actors.
   A simultaneous pilot failure takes precedence over a pending boss kill.
7. Read the result in chat, at Nix, or in the module log. Recover through ordinary
   class/food/rest/death recovery as needed, return to Nix, and start again. Attempts
   do not consume an entry fee or award loot/XP/persistent power. Walk back toward
   the raceway to leave. A restart clears the last in-memory result.

The human performs every menu, route choice, capture, spend and abort. Optional
pinned bots perform ordinary tank/heal/DPS/follow only; no custom item use, gossip,
object interaction, damage stopping or precise positioning is expected. No second
client, operated account or human is required for success, recovery, outcome or retry.
**ONE_HUMAN_REVIEW=PASS at source level** for implementation
`c1f3926dcc8988d6f1461affeee0c817c97f911d`, independently inspected by the Reviewer.
Actual solo/client/bot execution remains pending; this is not runtime validation.
The three-call compiler repair is awaiting independent review; custom human roles
and the complete solo mechanics are unchanged.

### Scaling and difficulty

| Setting | Normal | Surge | Tempest |
|---|---:|---:|---:|
| Tracking / locked warning | 4 / 2 sec | 3.5 / 2 sec | 3 / 1.8 sec |
| Recovery before next mark | 18 sec | 16.5 sec | 15.2 sec |
| Spent capacitor cooldown | 30 sec | 31 sec | 32 sec |
| Ground healing | 30% | 28% | 26% |

For starting roster size `n`, boss health is `1,200,000 × (n+1)/2`, pursuer health
is `9,000 × (n+1)/2`, with integer rounding. Solo has at most one living pursuer;
parties have at most two. Base weapon damage starts at 0.4%/0.3% of pilot maximum
health for boss/pursuer, multiplied by `(n+1)/2`, at a two-second attack interval.
Normal combat armor/avoidance still applies. These are initial tuning values;
actual class, gear and bot feel require in-game validation. The no-bots case uses
the same charge/ward mechanic and Ground recovery, not an empty demonstration mode.

## Exact target and current checks

- Stock WoW 3.3.5a build 12340.
- AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- Ubuntu Server 24.04 x86-64; no production dependency/source edits or client modification.
- Selected C++ method signatures were checked against those exact source files.
- First full compilation: **FAILED**, official run `33952393192` for `a1558178`.
  Repaired candidate full compilation: **NOT RUN**. Installation, startup and executable
  tests were skipped in the failed run; compile-time rules checks run during compilation.
- Independent implementation review: **PASS** for source
  `c1f3926dcc8988d6f1461affeee0c817c97f911d`; the Reviewer inspected API/state,
  owned actors, charge/cleanup logic and the full solo recovery/retry/exit path.
  Practical's separate exact-schema SQL review also passed. This final checkpoint
  had documentation changes only. The subsequent impact-GUID repair requires review
  and a full rerun; no compilation or runtime success is claimed.
- Actual gameplay, terrain, visuals, class balance and bot feel: **PENDING IN-GAME VALIDATION**.

## Install and configuration

Use a disposable development server targeting the exact source commits above. Keep
Playerbots installed at its pin; Stormwright does not require an active bot for Solo Pilot.
Stock client 3.3.5a and properly extracted map/vmap/mmap data are required for meaningful
world testing. The DBC-only official dry-run cannot exercise the encounter.

1. Copy this directory to `<azerothcore>/modules/mod-stormwright`.
2. Before database work, verify creature template/model IDs **910900–910904** and
   npc_text ID **910900** are unoccupied by another custom module. Never use REPLACE
   or a forced import to hide a collision.
3. Reconfigure and build the pinned server with modules and Playerbots enabled, using
   the normal pinned build instructions. Install into the disposable server tree.
   `src/` and `conf/` use native module discovery; no core/PB source changes are needed.
4. Copy installed `etc/modules/mod_stormwright.conf.dist` to
   `etc/modules/mod_stormwright.conf` if you want an explicit local override.
5. With the native database updater enabled, first startup applies
   `data/sql/db-world/2026_09_05_00_stormwright.sql` once to the world database.
   It contains owned templates/models/text only, no permanent spawns or existing
   quest/race edits. Without the updater, import that file once using the disposable
   database's normal local administration procedure; do not use `--force`.
6. Start the worldserver normally and inspect `STORMWRIGHT_CONFIG` and
   `STORMWRIGHT_REGISTRAR`. `STORMWRIGHT_SITE_UNAVAILABLE` means no registrar was
   spawned; resolve missing/unsuitable extracted ground data before gameplay testing.
   No invented Z or GM-only substitute is supported.

For registrar/outcome log evidence, set the existing `Logger.module` severity in
the disposable `worldserver.conf` to INFO (`3`), retaining its configured appenders.
The pinned default warning threshold hides these INFO records. Chat and registrar
results remain available without changing logger settings.

`Stormwright.Enable = 1` enables the encounter at startup. Reloading it to `0`
ends an active attempt on its next controller update and rejects new attempts.
If disabled at initial startup, enabling it requires a worldserver restart to create
the registrar. One attempt runs at a time at the public registrar. No teleport,
global player aura, addon, external API, character DB migration or runtime payment exists.

For removal, stop the server, remove the module, rebuild/install, then optionally run
`sql/uninstall_world.sql` against the disposable world database. That script is outside
the updater path and deletes only matching owned identities. The updater's application
history is preserved; reinstall after removal requires an explicit one-time import of
the install SQL once the owned IDs are free.

## Stock feedback and replay

The storm revenant visibly chases the pilot or ordinary combat targets. A power spark
tracks the pilot, grows on lock, then flashes at impact. A caught capacitor grows;
a spent capacitor shrinks until ready. Discharge plays direct casting/impact kits and
opens the boss's enlarged exposed form. Enemy health and chat/status make results
legible alongside those stock assets. The client appearance is still untested.

[Reference evidence](docs/REFERENCES.md) follows each model through exact DBC rows.
Visuals use packet kits 12201, 321 and 283, never spell casts. Spell 62186 is deliberately
not cast because it has a periodic encounter trigger. No visual determines gameplay state.

Repeated play is about faster, safer charge routes and the cost of recovery: bank a
charge, blast a pursuer while opening armor, or give up that damage to preserve the
ward. Faster presets compress the route/cooldown choices. Solo class toolkits and
ordinary companion compositions change how much normal fighting fits between marks.
The last assisted result records time, discharges, Grounds and misses; V1 deliberately
keeps rewards and rankings out of a public arena that permits outside assistance.

## In-game smoke checklist

Perform in an isolated disposable world; record actual results without inferring them
from build success. Every item below is currently pending.

- Walk from the ordinary raceway approach to Nix and back without GM movement. Check
  terrain, water, collision, stock quest actors/racing paths, reachability and LOS.
- Run **Normal Solo Pilot with no bots**, start out of combat and reach all three rods.
  Confirm mark tracking/lock position, full escape interval, visible impact and reliable
  in-combat rod gossip. Check ready/charged/cooling feedback at normal camera distance.
- Catch and Discharge: verify boss health loss, eight-second armor window, and a lured
  pursuer dying only when within the eight-yard blast. Other creatures remain unaffected.
- Take ordinary damage with full ward, then Ground: verify recovery. Ground with full
  health/full ward must leave charge intact. Miss once, then Ground to repair ward.
- Win a complete solo run; verify one outcome, no loot/XP, complete cleanup, normal
  return to Nix, and a fresh retry. Repeat on Surge/Tempest with the same one-human duties.
- Fail by three misses, death, boundary exit, explicit abort and time cap. Reconnect
  after logout. Verify no pending victory can outrank pilot failure, no lingering
  enemies/markers, no ward/charge carryover, no duplicate outcomes or dead-pilot healing.
- With ordinary pinned bots, verify frozen roster scaling, up to two pursuers, normal
  tank/heal/attack/follow, and the human alone doing every custom action. Repeat without
  bots afterward. Actual bot competence remains **PENDING IN-GAME VALIDATION**.
- Try nonpilot rod clicks, stale/duplicate menu selections, remote roster members,
  config disablement, missing actor/evade, and server restart. No invalid action should
  award recovery or leave an active orphaned encounter. Check module logs for each result.

## A 75-second demonstration

This is a capture script for implemented mechanics, **not a claim that it was filmed**.
Use Normal Solo Pilot; frame the three crystals and boss with the ordinary client UI.

| Time | Capture |
|---|---|
| 0–10 sec | At Nix, show Solo Pilot start with no second human or bots; move into the arena. |
| 10–18 sec | First spark tracks to a crystal; it locks, the pilot moves clear, crystal grows. |
| 18–28 sec | Lure the pursuing elemental to the charged crystal; Discharge; show flash, pursuer death and boss health/window. |
| 28–42 sec | Fight briefly, route to a different ready crystal; show first crystal still cooling. |
| 42–50 sec | Catch the second mark, choose Ground while injured; show health/ward recovery at the cost of offense. |
| 50–66 sec | Reposition toward the third crystal and fight the next pursuer; show the choice to bank or spend charge. |
| 66–75 sec | Catch the next mark and Discharge; end on the boss under a player-created damage window. |

Tyler's capture checklist: wide shot of readable rod states; close shot of tracking then
locked marker; in-combat choice menu; pursuer caught in a discharge; full-ward Ground
healing; separate real victory/result/retry clip after completing the run; normal access
and departure. Hide private account/chat information. Do not substitute GM kills,
teleports or extra human operators for the actual loop.

## Creator's note

I chose Stormwright because the same hazard becomes a resource the player steers.
The interesting moment is committing to a route with an enemy behind you, then deciding
whether the caught storm buys safety or an opening. That stays useful after the first
surprise and looks different from ordinary combat convenience modules. V1 trades a
large progression framework and exclusive competitive scoring for one repeatable,
human-operated encounter with three readable pieces and a complete recovery path.

Source is GPL-2.0-or-later. Stock client assets remain referenced, not redistributed.
