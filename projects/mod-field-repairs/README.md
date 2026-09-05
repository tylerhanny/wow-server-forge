# Field Repairs

Buy ordinary personal-gold repairs for your equipped and carried gear while safely
outdoors. Review the service notice, confirm once, and see the actual gear and wallet
changes. Field Repairs saves a vendor detour without adding free repairs, a surcharge,
guild-bank spending or an automatic payment mode.

**Independent source and one-human implementation review passed. Official compilation,
installation and startup are PENDING. Not ready for live testing. Actual gameplay and
client inventory/stat behavior are PENDING LIVE/IN-GAME VALIDATION.**

Exact target: WoW 3.3.5a build 12340; Ubuntu Server 24.04 x86-64;
AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and mod-playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. Neither dependency requires a source change.

## Commands and payment

| Command | Effect |
|---|---|
| `.fieldrepair` or `.fieldrepair status` | Show damaged-item count, personal balance, remaining consent and current restrictions. |
| `.fieldrepair request` | Inspect current gear/pricing and explain current personal-gold charges and possible partial repair; grant 30 seconds to confirm. |
| `.fieldrepair confirm` | Consume consent, recheck all current conditions, then perform one native paid repair attempt. |
| `.fieldrepair cancel` | Clear consent without payment. Nothing happens automatically. |

Ordinary player accounts can use every command. Bots and the server console cannot
operate the service. You must be alive, outdoors on a normal world map, out of combat,
unflagged for PvP/FFA and outside a duel. Trades, taxi flight, transports, vehicles,
pending teleports, casts/channels, control impairments and logout reject service.
Instances, raids, battlegrounds and arenas are excluded. No character is moved.

The request explicitly authorizes **current native prices for all carried/equipped
gear**. It is not a price quote or an inventory reservation: confirmation inspects your
then-current items and rate again. Vendor reputation discounts do not apply. The native
`Rate.RepairCost` applies; the module adds no fee or discount. Its zero-price rounding
still has the core's one-copper minimum per damaged item.

The core repairs affordable items individually, skips unaffordable ones and continues.
**Partial repair is possible.** There is no repair-all transaction or refund promise.
Equipment, backpack and carried-bag contents are included; bank, buyback and key slots
are excluded. The result reports how many previously damaged items became fully repaired,
how many carried items remain damaged, and the observed wallet change. Native item changes,
broken-item stat restoration and payment remain entirely owned by the core.

An unsuccessful or expired confirmation consumes any remaining consent. Earn more gold,
leave the restricted state, or fix unsafe server item/pricing data, then request again.
Repeating service with healthy gear charges nothing. Login, logout, death, map changes,
server restart and successful config reload discard pending consent. There is no persistent
module record or delayed repair task. Simply cancel or stop interacting to exit.

## Installation and configuration

Use an existing disposable installation of the exact pinned server. Copy this directory
to `modules/mod-field-repairs`, keeping that directory name. Native module discovery
collects `src/` and installs `conf/`; no loader/CMake changes or SQL import are needed.
Reconfigure, build and install into a separate prefix using the normal server procedure.
For an ordinary installation, this example leaves existing build/install directories alone:

```bash
# Set these to existing disposable paths and a new, unused work directory.
set -euo pipefail
AC=/path/to/disposable/azerothcore
WORK=/path/to/new/field-repairs-test
test "$(git -C "$AC" rev-parse HEAD)" = 47960183bb03b83e8943eb2f0f39c16df9710c9d
test "$(git -C "$AC/modules/mod-playerbots" rev-parse HEAD)" = 2f7d9f774987d0157c6a0d0cc08c40bec3db3945
git -C "$AC" diff --exit-code HEAD --
git -C "$AC/modules/mod-playerbots" diff --exit-code HEAD --
test ! -e "$WORK"
cmake -S "$AC" -B "$WORK/build" -DCMAKE_INSTALL_PREFIX="$WORK/stage" \
  -DCMAKE_C_COMPILER=clang-18 -DCMAKE_CXX_COMPILER=clang++-18 \
  -DCMAKE_BUILD_TYPE=Release -DAPPS_BUILD=all -DTOOLS_BUILD=none \
  -DSCRIPTS=static -DMODULES=static -DWITH_WARNINGS=ON -DBUILD_TESTING=OFF
cmake --build "$WORK/build" --parallel 2
cmake --install "$WORK/build"
```

These commands have not been executed. `BUILD_TESTING=OFF` is an ordinary installation
setting, distinct from official acceptance with its full upstream test build/run. Never
apply the CI-only WorldMock fixture correction or official warning adapter outside CI.
Do not change pins or dependency source to make an installation build pass.

Prepare the new prefix's normal server configs for disposable databases, local test realm
and extracted client data. Use its installed module config as the optional override:
`etc/modules/mod_field_repairs.conf.dist` to `etc/modules/mod_field_repairs.conf`.

| Setting | Default | Behavior |
|---|---:|---|
| `FieldRepairs.Enable` | `1` | Set to `0` to disable; successful reload clears all pending consent. |

The 30-second consent lifetime is fixed. Retain native `Logger.module=4,Console Server`
or an existing equivalent INFO-level (`4`) configuration with its appenders. On disposable
startup look for `FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`. This marker proves
script/config loading, not a player repair. Other effective values are logged truthfully.

To disable, set `FieldRepairs.Enable = 0` and perform the authorized operator's normal
successful config reload or clean restart. Confirm `enabled=0` in the marker. Re-enable
with `1` and reload/restart; every player needs a fresh request. Prior completed native
repairs and gold payments are not reversed.

For full removal, cleanly stop the disposable worldserver, move this module directory
out of `modules/`, then reconfigure/build/install to a new separate prefix. Retire the old
prefix and its module config from use; prepare the new prefix's ordinary disposable server
configs. The command should no longer exist. No SQL cleanup or player-record rollback is
needed. Keep the old stage/module for deliberate rollback rather than overwriting a running
installation or deleting unrelated files.

## Safety and known limits

Before the native call, the module inspects every item the pinned repair routine can visit.
Each damaged item must have consistent durability, a valid template/quality/class/subclass,
valid durability DBC rows and a multiplier index within the actual 29-element array.
Arithmetic follows the pinned uint32 product, double quality calculation and float rate
conversion, rejecting costs outside the native unsigned and signed-debit ranges. An unsafe
item or active pricing input refuses the entire operation before any repair/payment.
These checks protect this entry point; they do not patch or saturate baseline core arithmetic.
Malformed custom durable items can be conservatively refused even if ordinary vendors
attempt to process them.

The native personal-payment function returns zero rather than money spent. Field Repairs
therefore compares actual wallet/item snapshots and does not label that return as a charge.
Other modules' normal callbacks may affect wallet/item state; the displayed delta is an
observation, not an isolated transaction ledger. If resulting item data cannot be verified,
the module reports that limitation and does not retry automatically. Prices/partial ordering,
inventory updates, restored stats and coexistence with other modules require real client
testing. The feature supplies no new economy, repair insurance or bot repair.

## One-Human Playability

The complete qualifying loop is **solo**, using one ordinary level 1–80 character with
durable equipment. No second human, client or operated account is required. The human
inspects gear, requests, confirms/cancels, reads the outcome, earns more gold through normal
solo play if necessary and retries or exits. No class-specific spell, GM command or helper
is needed. On PvP realms choose a state/location without native PvP flags.

Zero bots leaves the complete feature available. Optional ordinary pinned Playerbots can
fight/follow while the human earns repair money; they receive no repairs and issue no custom
commands or menu actions. No bespoke bot cognition, precise choreography or second participant
is assumed. There are no added enemies, encounters or group/difficulty scaling.

Director and independent Reviewer approved the complete proposal before implementation
in `decisions/field-repairs-selection.md` and `reviews/additional-project-proposal-review.md`.
Independent Reviewer also inspected the complete implementation at
`e560e72a09ed99c4d3391c90a242f9b8f5a9b277`: **SOURCE_REVIEW=PASS; ONE_HUMAN_REVIEW=PASS
(source-level complete solo path)**. The final freeze changes only review-status documentation.
Source review does not prove in-game behavior. All manual steps below are
**PENDING LIVE/IN-GAME VALIDATION**:

1. Log in alone with an ordinary character and damaged durable gear in a safe outdoor
   normal-world area. Use `.fieldrepair status`; compare damaged count and wallet to the client.
2. Use `.fieldrepair request`. Read the current-price/personal-gold/partial-repair notice.
   Cancel once; confirm neither gold nor gear changed and direct confirm now refuses.
3. Request again and confirm within 30 seconds. Compare the reported wallet delta and
   repaired/remaining counts with actual inventory durability, including a broken equipped
   item's restored stats. Repeat with healthy gear and verify no charge.
4. With insufficient personal funds, request/confirm and observe native no-repair or partial
   repair. Confirm that unaffordable earlier items can remain while cheaper later items repair.
   Earn gold through ordinary solo play, then request/confirm again. No second player is needed.
5. Let consent expire and confirm: no payment. Request and enter ordinary PvE combat or cast
   before confirming: refusal, no payment and fresh request required. Recover normally and retry.
   Death, relog and map changes clear consent; confirm after recovery must require a new request.
6. Cancel or stop interacting to exit. In disposable operator testing, successful config reload
   clears consent, disable blocks repairs and re-enable requires a new request. No payment happens
   automatically. Record unavailable edge cases as untested rather than inventing a pass.
7. Optionally repeat with normal bots after completing the solo loop. Only the human's gear
   and wallet should change. Record actual client/stat updates, party coexistence and price feel
   separately from source and CI results.

Validation status, pinned source evidence and arithmetic checks are in [VALIDATION.md](VALIDATION.md).
