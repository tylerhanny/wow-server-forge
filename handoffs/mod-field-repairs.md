# Field Repairs — implementation checkpoint

```text
PROJECT=mod-field-repairs
OWNER=Practical
BRANCH=project/field-repairs
STATE=IMPLEMENTED_AWAITING_REVIEW
BUILD_RESULT=NOT_RUN
OFFICIAL_GATE=NOT_RUN
SOURCE_REVIEW=PENDING
ONE_HUMAN_REVIEW=PASS_PROPOSAL_ONLY; IMPLEMENTATION_PENDING
NEXT_ACTION=Independent exact-source review, then freeze and dispatch one full official gate
```

This is a complete source/docs checkpoint, not READY FOR LIVE TEST. No compiler, install,
runtime or client result is claimed. The final exact candidate SHA is supplied externally
after the local source checkpoint and subsequent review-status freeze.

## Scope and installation

Ordinary players can inspect damaged carried/equipped gear and wallet, request explicitly
paid service, confirm within 30 seconds, observe the actual complete/partial repair and
wallet change, earn more gold and retry, or cancel/expire without a charge.

Commands: `.fieldrepair` / `.fieldrepair status`, `request`, `confirm`, `cancel`.
Only setting: `FieldRepairs.Enable = 1`; consent lifetime is fixed at 30 seconds.
Install the project directory as `modules/mod-field-repairs`, reconfigure/build/install
the exact pinned server to a disposable prefix, and optionally copy installed
`etc/modules/mod_field_repairs.conf.dist` to `.conf`. Native discovery needs no CMake or
loader edits. No SQL, persistence, item grants, NPC spawns or external service is involved.
Use INFO (`4`) on the module logger to observe
`FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`.

Compatibility: WoW 3.3.5a build 12340; Ubuntu 24.04 x86-64; AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`, mod-playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. No dependency changes are required. The official
judge, source protections and CI-only WorldMock exception remain untouched.

Confirm checks safe outdoor/non-instance/alive/non-PvP/no-combat/no-trade/control/cast/
transport/teleport/logout state and preflights every current damaged item before one
`DurabilityRepairAll(true, 1.0f, false)`. The core alone calculates charges, checks each
item's affordability, debits personal gold and restores durability/stats. The module uses
current undiscounted native prices and preserves `Rate.RepairCost` and the one-copper minimum.
It adds no fee, free-repair mode, guild spending, refund or transaction atomicity.

Native repair can skip unaffordable items and repair later cheaper items; the consent
notice discloses this. No price quote or inventory reservation is promised. Its returned
TotalCost is not personal spending; the module reports observed before/after wallet and
gear instead. All data/index/uint32-product/double-conversion/float-rate/signed-debit checks
precede repair. Unsafe input refuses the whole attempt without altering baseline arithmetic.

## One-Human Playability

Director and independent Reviewer approved the proposal's complete solo path before code:
**ONE_HUMAN_REVIEW=PASS at proposal scope; implementation review PENDING**. One ordinary
level 1–80 character with durable gear, one human, one client and one operated account
can perform the entire useful loop. No second human/account/client or GM action is needed.
Zero bots is complete; optional ordinary bots only fight/follow during normal gold earning,
receive no repairs and perform no custom commands. No new enemies or difficulty/roster
scaling exists.

Exact manual order, all **PENDING LIVE/IN-GAME VALIDATION**:

1. Safely outdoors, inspect damaged gear and balance with `.fieldrepair status`.
2. Request, read the current-price/personal-gold/partial-result notice and cancel; verify
   no gear or gold change and no valid direct confirmation afterward.
3. Request again and confirm within 30 seconds; compare actual wallet delta, item durability,
   restored broken-item stats and repaired/remaining counts. Healthy gear should cost nothing.
4. With insufficient gold, observe native zero or partial repairs. Earn gold solo and repeat
   the same request/confirm loop successfully; no helper economy is needed.
5. Test expiry, ordinary PvE combat/casts and death/map/logout cleanup. Refusals must not pay;
   recover normally and request anew. Cancel or stop interacting to exit.
6. In disposable operator testing, successful config reload/disable clears consent; re-enable
   requires a fresh request. Optionally repeat with normal bots and verify only human gear/wallet.

Disable with `FieldRepairs.Enable=0` and successful operator config reload or clean restart.
Remove by stopping the disposable server, moving the module out and rebuilding/installing
to a separate prefix without its config. No SQL rollback exists; completed native repairs
and payments are ordinary core data and are not undone.

The [README](../projects/mod-field-repairs/README.md) supplies installation/removal details,
the complete manual checklist and restrictions. [VALIDATION](../projects/mod-field-repairs/VALIDATION.md)
records exact pinned source evidence and actual-helper compile-time checks, currently NOT_RUN.
Remaining uncertainty includes real pricing/partial ordering, client inventory/stat updates
and ordinary module callbacks/bot-party coexistence. Source review or startup will not be
represented as those manual tests.
