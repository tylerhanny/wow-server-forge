# Field Repairs — independent source and one-human review

**SOURCE_REVIEW=PASS; ONE_HUMAN_REVIEW=PASS (implementation source).**
Reviewer disposition: 2026-09-05. Official execution and actual client behavior are
separate, pending evidence; this report does not mark the project ready for live testing.

## Exact scope and candidate binding

- Complete reviewed implementation: `e560e72a09ed99c4d3391c90a242f9b8f5a9b277`.
- Final frozen candidate: `1450d92f8bcf3a8282526120753ed5f750939722`, `project/field-repairs`.
- The final commit changes only README, VALIDATION and matching handoff review status.
  Source, config and actual-helper compile-time checks remain byte-identical. The Reviewer
  inspected the final documentation diff, seven-path scope and `git diff --check`.
- One required full official run dispatched:
  [33970121674](https://github.com/tylerhanny/wow-server-forge/actions/runs/33970121674).
- Actual default-branch judge: `8d21e8b1b4920b4966760ba621751725bd411444`. Protected workflow
  and validation bytes match the previously successful judge `e5fd277de515dbda983993e6f8a52b48cb0816b4`.
  No stale Reviewer-lane workflow, new framework or extra control was used. Scope passed;
  all later execution and final acceptance are pending at this source-review checkpoint.

The change contains one isolated project plus its handoff, native `src/` and
`conf/mod_field_repairs.conf.dist`, no SQL, custom CMake, warning suppression, dependency
modification, persistent state, spawn, item grant or external runtime service.
Pins remain AC `47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu 24.04 x86-64 / client 12340.

## Native repair and arithmetic review

The Reviewer inspected actual implementation against exact `Player.cpp:4900-4990`,
public `Player.h:2084-2085`, Item/Bag headers, durability stores and the raw-index helper
in `ItemTemplate.h:557-567`. Carried-slot iteration matches the native repair routine;
bank, buyback and key slots are excluded. Personal native payment returns zero rather
than paid cost, so actual wallet and item-condition snapshots supply honest outcomes.

All visited damaged items are preflighted before the sole
`DurabilityRepairAll(true, 1.0f, false)` call. The guard checks durability consistency,
quality/class/subclass and DBC presence, raw multiplier index before uint8 narrowing,
uint32 product bounds, the exact native double quality conversion, and the subsequent
float rate conversion against the signed debit bound. Comparing through double avoids
admitting 2^31 after float rounding of INT32_MAX. Nonfinite/negative inputs are declined;
the native zero-cost-to-one-copper minimum remains intact. There is no custom debit,
clamp, surcharge, guild spending, fake atomicity or refund path.

The existing project-local compile-time assertions exercise the actual helpers, including
expiry, fractional/zero costs, product/conversion boundaries and nonfinite inputs. They
have not been executed locally; their compiler result must come from the official build.

## Consent, lifecycle and complete solo path

An ordinary player can inspect status, request, explicitly consent within 30 seconds,
observe complete/partial native repair and wallet changes, earn gold and retry, or cancel
and exit. The request discloses current undiscounted native personal-gold prices for all
then-current carried/equipped gear, possible partial repair and the absence of a binding
quote. Confirmation consumes the request once, rechecks eligibility and all current
prices/items, and rejects changed configuration before the native operation.

The mutex protects shared consent/config state without crossing native repair callbacks.
Login/logout/death/map change and successful config reload clear consent; expired or
rejected confirmation does not retain authorization. No action occurs automatically.
Alive/outdoor world-map, no-combat/PvP/duel/trade/transport/vehicle/taxi/queued teleport/
cast/control/logout checks use pinned public interfaces, including the already verified
public near/far teleport-state predicate. No private delayed-teleport API is called.

This is a complete level 1-80 solo service with durable gear, one human/client/account and
no class spell, second participant, GM operation or bot cognition. Optional normal bots
only fight/follow while the human earns money and receive no repair. No group scaling is
needed. No-money and partial-result paths explicitly lead back to earning/retrying;
healthy gear costs nothing. README and handoff include installation, disable/removal,
configuration and the full ordered one-human manual checklist.

The final config log accurately reports both enabled and disabled values:
`FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30` is the expected default marker under
native INFO level 4. No OnStartup actor path requires a separate normal-startup fixture.

## Remaining validation

No blocking source finding remains. Complete pinned configure/build/install, native config
loading, both dry-runs, unfiltered native units, source/fixture integrity and independent
artifact review remain required. A startup marker cannot execute a player repair.
Actual prices and partial ordering, client durability/stat updates, other modules' normal
callbacks and bot-party coexistence remain PENDING LIVE/IN-GAME VALIDATION. Observed wallet
delta is not promised to be an isolated transaction ledger when other callbacks exist.
