# Triage Night

**One priest. Three persistent patients. Five rounds of difficult healing choices.**

Development checkpoint: source review, compilation, installation and official acceptance
are PENDING. No in-client play or live-server validation is claimed.

Triage Night is a repeatable support-role challenge using your normal healing spells and
mana. Choose efficient or fast heals, prioritize bleeding against warned bursts, and spend
two finite stabilization charges. Patient health carries between rounds. No player health,
mana, gold, items or experience are granted. Stock First Aid Triage uses its quest bandage;
this challenge instead exercises spell choice and resource management across a whole shift.

## Exact target and installation

- Stock client 3.3.5a build 12340; Ubuntu Server 24.04 x86-64.
- AzerothCore: 47960183bb03b83e8943eb2f0f39c16df9710c9d.
- mod-playerbots: 2f7d9f774987d0157c6a0d0cc08c40bec3db3945. No bot is required.
- No core/Playerbots changes, client addon, container or external runtime service.

Copy this complete directory to the pinned checkout's modules/mod-triage-night. Native
module discovery finds src files and Addmod_triage_nightScripts; no upstream edits or custom
CMake wrapper are required. Configure/build/install with the checkout's normal module build.
Use an isolated development tree and databases for initial validation.

Before applying SQL, verify that creature_template entries **911100–911103** and all
creature_template_model rows with those CreatureID values are unoccupied. Any result from
either query is a collision to resolve before installation; do not overwrite existing IDs.

```sql
SELECT entry, name, ScriptName FROM creature_template WHERE entry BETWEEN 911100 AND 911103;
SELECT * FROM creature_template_model WHERE CreatureID BETWEEN 911100 AND 911103;
```

The native module updater applies data/sql/db-world/2026_09_05_00_triage_night.sql once.
If an installation explicitly does not use the native updater, import that exact file once
into its world database. Do not combine manual import with an untracked later updater import.
Never use REPLACE, INSERT IGNORE or mysql --force to hide a collision. There are no permanent
creature spawns, npc_text rows, character schema changes or global rewards.

Install conf/mod_triage_night.conf.dist with the native module configuration files and set
TriageNight.Enable = 1. Any world configuration reload ends existing shifts; it never refills
player resources. Setting it to 0 disables new shifts and ends active ones on their next
update. Native INFO is level 4; Logger.module=4,Console Server permits TRIAGE_NIGHT_CONFIG,
TRIAGE_NIGHT_START and TRIAGE_NIGHT_RESULT messages. Logs prove only what was actually executed.

## One-Human Playability

The complete qualifying V1 is **one level-80 priest** with learned ordinary direct
single-target healing spells and healing gear. Use one normal character/account/client.
No second human, operated account, client or bot is required. Other healer classes and
party/AoE healing compatibility are unclaimed; bots do not heal patients or perform actions.

Every custom choice belongs to the human: start/preset, heal target/spell, stabilization
target/timing, status, retry and abort. Three patients are fixed; Training versus Veteran
changes injury pressure, not group size. The player's normal mana costs/regeneration and
ordinary between-round recovery remain intact. No resources are reset for retrying.

Public commands:

```text
.triage help
.triage start
.triage start training
.triage start veteran
.triage status
.triage stabilize 1
.triage stabilize 2
.triage stabilize 3
.triage stop
```

Start alive, out of combat and not casting, unmounted on dry open outdoor ground, away from
stock hostile creatures. Face the open area. Start checks nearby terrain and LOS and can
decline unsuitable positions; no GM teleport or fixed special venue is necessary. These
checks do not prove pathing or client visibility. During the shift, normal casts and channels
are allowed. Stay within 20 yards of the start, on the same map/phase and normal footing.

Patient One, Patient Two and Patient Three appear five yards ahead. Enable friendly
nameplates or target each by name and use ordinary healing spells. Their numbered names
match stabilization commands, which can be bound in normal macros. The first round begins
after a ten-second briefing. Five 45-second rounds have four ten-second recovery breaks.
Roles rotate between rounds; read the round notice and four-second burst warnings.

Two stabilization charges each pause one patient's future deterioration for six seconds;
they do not heal existing wounds. A charge cannot stack on an already stabilized patient
and is only usable during injury rounds. The patient must be visible. Deterioration is
scripted health loss and **bypasses shields/absorbs**. The qualifying path uses direct healing.
Only the pilot's healing is accepted. Patients do not regenerate, attack or refill on evade.

All three surviving the final injury completes the shift. A patient reaching lethal injury,
death/disappearance/displacement, pilot death/departure/logout, configuration reload or the
six-minute hard cap ends it. Stop aborts normally. Owned actors clean up; normal rest and
another start provide replay. Status retains your last five results for this login only:
preset, outcome, reached round, charges used and critical patient-seconds during injury
steps. These are personal practice records, not equal-conditions competitive rankings.

Independent ONE_HUMAN_REVIEW: **PENDING for implementation**. The approved proposal path
passed independent review; that disposition does not pre-accept this source. Actual healing
targetability, stock health bars/poses, gear pressure and optional bot coexistence remain
**PENDING LIVE/IN-GAME VALIDATION**.

## Ordered in-game smoke checklist

1. On one ordinary level-80 priest, read help and start Training outdoors with zero bots.
   Confirm all three numbered patients appear, are selectable/friendly and accept your
   direct healing. Confirm you can cast/channel normally after the shift starts.
2. Observe the full briefing, each of five distinct pressure rounds, four finite breaks,
   carrying patient health and real player mana. Check the announced burst target is hit
   four visible seconds later. Readability and balance are observations, not CI conclusions.
3. Stabilize a threatened patient. Verify the pause, no immediate healing, six-second expiry,
   refusal to stack, two-charge limit and no consumption during briefing/breaks.
4. Complete all five rounds and read the success/result. Confirm no player resources or
   rewards appeared. Rest normally, retry, see changed patient roles and retained results.
5. Let a patient be lost; check failure, cleanup and retry. Separately stop, leave the radius,
   change map, die/log out, or disable/reload config; check clean termination and fresh retry.
6. Confirm no native patient regeneration or evade refill; outside damage and non-pilot
   healing must not improve the objective. Shields do not prevent scripted deterioration.
7. Try Veteran after Training. Record gear/spells and whether priorities, warnings and mana
   create worthwhile pressure. Other healer classes are intentionally declined at start.

## Disable and full removal

For reversible feature disable, set TriageNight.Enable = 0 and reload world configuration
or restart normally. Existing shifts end without resetting player resources. For complete
removal, stop the server, remove modules/mod-triage-night, reconfigure/rebuild/install and
remove its installed module config. Then apply sql/uninstall_world.sql only after verifying
the reserved script identities; it does not delete stock rows or permanent world spawns.
The native updater may retain its applied-file record; follow its normal operator procedure
before a later reinstall, rather than blindly importing twice.

## Known limitations and creator note

This is a narrow priest practice encounter. It does not normalize gear, validate every
healer/AoE spell, supply raid frames or promise fair rankings. Four simultaneous shifts and
128 current-login command sessions bound temporary state. No actor or result survives a
server restart. Player-triggered encounter execution requires actual client testing.

I chose persistent patients to make healing priorities and mana matter without requiring
a party. Finite emergency intervention adds a decision that survives repeated play. The
small class-specific V1 leaves navigation and combat-AI complexity out of that experience.
