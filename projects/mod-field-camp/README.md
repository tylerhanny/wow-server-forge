# Field Camp

Save one personal outdoor camp, take a normal same-continent supply trip, and request
a return when you are safe. Field Camp is a small travel convenience for ordinary
players, with no gold charge, database rows, shared portals or persistent travel network.

**Candidate under development/review. Compilation, installation and disposable startup
are NOT_RUN. Actual client arrival and gameplay are PENDING LIVE/IN-GAME VALIDATION.**

Exact target: WoW 3.3.5a build 12340; Ubuntu Server 24.04 x86-64;
AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and mod-playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. Neither dependency needs a source change.

## Using your camp

| Command | Effect |
|---|---|
| `.camp` or `.camp status` | Show your camp coordinates/map/phase, remaining cooldown and current safety restriction. |
| `.camp set` | Save or replace your camp at your own safe position. Preserve any running cooldown. |
| `.camp return` | Recheck your state and saved ground, then request a same-map return. |
| `.camp clear` | Remove your camp. Preserve any running cooldown; no return happens automatically. |

Stand outdoors on dry, stable ground to set or return. You must be alive, out of
combat, free of PvP flags/duels and normal control restrictions. Flight, taxi,
falling/jumping, hovering, swimming, transports, vehicles, casts/channels, pending
teleports and logout are rejected. Instances, battlegrounds and arenas are excluded.
Ground mounts are allowed. A normal player account can use every command; bots and
the server console do not operate the feature.

Set a camp near your questing/gathering route. Travel normally to town, sell or repair,
step back outdoors and use `.camp return`. Return requires the same world map and
**exact phase mask** as the saved camp. A continent change or quest phase change does
not silently relocate the anchor: travel back normally, replace it or clear it.

The default return cooldown is ten minutes. It begins when the core **accepts the
teleport request**. Acceptance can precede the client's actual arrival; the success
message says "return requested". An accepted request consumes the cooldown even if
the client later disconnects or fails to acknowledge the transfer. There is no automatic
retry or promised arrival. A safety rejection or `TeleportTo` returning false does not
consume the cooldown. Clear/replacement within the session cannot reset it.

Death retains your camp/cooldown but cannot be escaped with a resurrection or return:
recover normally first. Login, logout, server restart and successful server configuration
reload remove all session camps and cooldowns. These deliberately temporary limits mean
relogging starts a new session; this is not a persistent travel restriction or anticheat.

## Installation and configuration

1. In a disposable installation of the exact pinned server, copy this directory to
   `modules/mod-field-camp`. Keep the directory name: native loader discovery uses it.
2. Reconfigure and build with modules and pinned Playerbots enabled, then install using
   the normal server procedure. Native discovery reads `src/` and installs `conf/`.
   No CMake overrides, custom loader edits or SQL imports are needed.
3. Optionally copy installed `etc/modules/mod_field_camp.conf.dist` to
   `etc/modules/mod_field_camp.conf` and adjust the two settings below.
4. Start the disposable worldserver. With the existing `Logger.module` severity at INFO
   (`3`), retaining its appenders, look for `FIELD_CAMP_CONFIG reload=0 enabled=1 cooldown=600`.
   The ordinary module logger's default warning threshold may hide this INFO record.
   The configuration marker proves script/config loading, not a successful player teleport.
5. For travel validation, supply correctly extracted maps/vmaps/mmaps and use the manual
   checklist below. A DBC-only dry-run cannot prove landing or client behavior.

| Setting | Default | Behavior |
|---|---:|---|
| `FieldCamp.Enable` | `1` | Disable with `0`; successful config reload also clears all sessions. |
| `FieldCamp.CooldownSeconds` | `600` | Clamped to `60..3600`; effective value is logged. |

Removing the module means stopping the disposable server, removing its module directory
and installed module config, then rebuilding/installing. There are no database changes
or persistent player records to undo. Existing ordinary character positions remain core data.

## Ground and teleport limits

Both the current position and saved destination must have a finite, valid coordinate and
a phase-aware floor found by the pinned map query. The search begins two yards above
the stored position with a six-yard search distance; the position must be within 1.5 yards
of the floor. At return, the floor must also remain within 0.5 yards of the floor recorded
at set time. Liquid contact, including water-walking contact, rejects the position. The
module preserves the original position/orientation; it never guesses or substitutes a Z.
Missing terrain data and some unusual platforms/terrain therefore reject otherwise
plausible camps. Move to a simple open dry surface and retry.

Ground queries are conservative checks, not a navigation, collision-clearance or client
arrival proof. Geometry, moving platforms, changing world objects and other modules can
still affect the destination. Transport/vehicle anchors are unsupported. The module does
not check nearby enemies or promise immunity after arrival; choose a sensible camp.

The native `TeleportTo` call uses default options, preserving native map restrictions,
script vetoes, acknowledgements and pet handling. Some core aura/movement cleanup occurs
before its veto hook; a rejected request is not a guarantee that unrelated core effects
were untouched. The module rejects control impairments and active casts before calling it.
Distant pets may be temporarily unsummoned by the normal core path. No Playerbot is
transported by Field Camp and no bot-follow/teleport behavior is assumed.

## One-Human Playability

The complete qualifying path is **solo**, with one ordinary level 1–80 character of any
class. One human, one client and one operated account can access, set, travel, return,
observe the outcome, retry and exit. No second human/client/account, GM command, paid API,
custom client, enemy scaling or helper is required. On PvP realms, choose a location/state
where native PvP flags are absent; the restriction is not bypassed for convenience.

No bots are needed. The human alone issues all four commands and makes every camp/travel
decision. A human with ordinary pinned bots can still use the full feature, but only the
human is moved; manage the party normally before travel. Optional bot regrouping, pet
handling and travel feel are **PENDING LIVE/IN-GAME VALIDATION** and do not qualify the
primary solo loop. There is no party-size or difficulty scaling because no encounter is added.

Director and independent Reviewer approved this solo proposal before implementation in
`decisions/field-camp-selection.md`. **ONE_HUMAN_REVIEW=PENDING for this implementation**;
proposal PASS does not certify the completed source or official gate.

Exact one-human manual smoke checklist (not yet performed):

1. Log in as one ordinary character on a normal outdoor world map, with no bots required.
   Use `.camp`. Confirm no camp exists and the default cooldown is 600 seconds.
2. On dry stable outdoor ground, out of combat and unflagged for PvP, use `.camp set`.
   Confirm the saved map/coordinates/phase. No money, items or quest state should change.
3. Travel normally to a nearby town on the same world map, sell/repair through ordinary
   NPCs, step outdoors and use `.camp return`. Confirm "return requested", then verify
   actual client arrival at the original camp and orientation.
4. Use `.camp return` again immediately. Confirm the cooldown message. Use `.camp clear`,
   then `.camp set`: the remaining cooldown must persist. After it expires, repeat a
   supply trip and return. This is the repeatable utility outcome; no extra reward is paid.
5. With a camp set, attempt return while jumping/swimming and during ordinary hostile-creature
   combat or a cast. Each should reject without spending a cooldown or moving you. Wait for
   safe state, then retry. Do not involve another human for these failure cases.
6. Travel normally to another world map and try return. It must reject; the anchor stays
   visible. Return normally to its original map/phase and retry. If a normal quest changes
   your phase, confirm exact mismatch rejects and a safe `.camp set` replaces the anchor.
7. Die through normal solo gameplay with a camp set. Return must reject while dead; recover
   normally. Confirm the session anchor remains, with the cooldown continuing to elapse.
8. Use `.camp clear` to exit. Status must show no camp; no automatic teleport occurs.
   Set again and relog: camp and cooldown must be gone. Restart and successful operator
   config reload have the same documented cleanup; verify those only in disposable testing.
9. Optional: with your ordinary bot party or hunter pet, repeat the primary trip. Confirm
   the human loop works; separately record actual pet/bot regroup behavior. Bot arrival
   is not promised, and no custom bot command/menu is required by the module.

## Design decision

Practical's approved small V1 adds sustained supply-trip convenience without duplicating
Hunt Rhythm's XP chain or Stormwright's encounter. The one-anchor/session/same-map limits
keep installation simple and completion credible; no persistence or travel-network framework
is deferred inside a supposedly complete core loop. Exact pinned `Player::TeleportTo`,
`Map::GetHeight`, movement/state getters, `CommandScript`, login/logout and config hooks
provide the whole feature. Main residual risks are terrain/client arrival and coexistence
with other teleport scripts; source/CI/manual evidence is tracked in [VALIDATION.md](VALIDATION.md).
