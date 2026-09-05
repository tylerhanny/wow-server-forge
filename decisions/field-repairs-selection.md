# Field Repairs — approved bounded Practical selection

Prepared 2026-09-05 after direct owner authorization received at 13:27Z. This is an
untracked proposal record for Director integration, not an implementation or acceptance
claim. No new ideation is introduced. Substantive code begins only after the Director
records this decision/state on main and releases the isolated project worktree.

Project: `mod-field-repairs`. Lane/owner: Practical, exclusive ownership.
Planned branch: `project/field-repairs`; planned worktree: `.worktrees/field-repairs`,
created from the updated main only after release. At most one additional Practical
project is authorized. Wildcard independently owns Triage Night; neither lane expands
the three accepted modules. Owner-reported fixes preempt this work.

Exact compatibility: WoW 3.3.5a build12340; Ubuntu24.04 x86-64; AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`; Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. No dependency edits/updates, live-server
access, Docker, modified client, runtime API/LLM or private infrastructure is involved.

## Comparison and selection

| Option | Useful complete slice | Feasibility/risk | Decision |
|---|---|---|---|
| Field Repairs | Ordinary players explicitly buy native repairs for carried/equipped gear while safely in the open world; observe complete/partial result and retry or exit. | Public pinned native APIs, no SQL/spawns/assets/new economy. Modest novelty, repeated utility for solo leveling without a repair mount or vendor detour. Credible within three hours source/docs/review. | SELECT |
| Quartermaster Work Orders | Choose a native daily supply quest, gather/craft materials solo, turn them in for bounded gold, then repeat on reset or abandon/retry. | More profession content, but exact quest/item/access/reward rows and reversible ownership remain incomplete. Estimated4–7h source/data plus review and gates exceeds the reliable bounded target. | DEFER |

Field Repairs complements rather than expands the existing candidates. Hunt Rhythm owns
its XP chain; Stormwright owns its encounter; Field Camp remains useful for selling and
restocking trips. Field Repairs provides paid equipment service without teleporting,
replacing ordinary costs or adding a travel network. The installation value is practical
convenience, not a claim of novel gameplay or a reason to maximize project count.

## Coherent V1

- `.fieldrepair status`: show current damaged-item count and personal balance, explain
  native repair charges and any current eligibility restriction.
- `.fieldrepair request`: explicitly disclose **current native undiscounted prices and
  possible partial repair**, then open a thirty-second session consent. No payment or
  item change occurs yet. No binding quote/price-lock promise is made.
- `.fieldrepair confirm`: require unexpired consent, recheck eligibility and all current
  item/cost safety conditions, consume consent, then call the native paid repair once.
  Report actual repaired/remaining damaged-item counts and observed wallet change.
- `.fieldrepair cancel`: remove consent without a charge. Expiry also exits cleanly.
  There is no ongoing auto-repair mode, automatic payment or delayed repair task.
- Proposed module setting: `FieldRepairs.Enable = 1`. The thirty-second confirmation
  lifetime is fixed. No configurable discount, premium or alternate currency.
- Scope is equipped/backpack/carried-bag gear. No bank/buyback/key repair, item selling,
  guild funds, free repair, vendor spawn, persistent records, SQL or custom transaction
  framework. Repeating the service when nothing is damaged charges nothing.
- Login/logout, death, map change and successful config reload clear pending consent.
  Disabling rejects new service and clears consent; re-enable requires a new request.

Eligibility: an ordinary human session, alive and in world, safely outside combat/PvP/
duel on a normal non-instance world map; no trade, taxi, vehicle, transport, pending
teleport, active cast/channel, control impairment or logout. The service moves nobody
and needs no ground extraction/spawn-site query. A refusal performs no module payment
or item modification. Recheck the current state at confirmation rather than trusting
request-time state. No GM privilege is needed for the primary commands.

## Exact pinned API and cost semantics

Verified public `Player.h:2084–2085` provides:

```cpp
uint32 DurabilityRepairAll(bool cost, float discountMod, bool guildBank);
uint32 DurabilityRepair(uint16 pos, bool cost, float discountMod, bool guildBank);
```

Use `DurabilityRepairAll(true, 1.0f, false)` at `Player.cpp:4900–4990`. The core visits
equipment/backpack/bag slots and explicitly excludes bank, buyback and keys. It charges
personal money using its current `Rate.RepairCost`, without a vendor reputation discount.
It repairs affordable items individually, skips unaffordable items and continues. This
can produce a partial result; do not promise atomic repair-all or invent refunds.

The native returned `TotalCost` remains zero for personal payments: it is assigned only
in the guild branch. **Never use that return value as personal money spent.** Compare
actual wallet and durability snapshots instead. Core repair sets durability, marks items
changed and reapplies stats when a broken equipped item becomes repaired. The module
must not reproduce those mutations or debit money itself.

Public `Player.h` also exposes `GetItemByPos`, `GetBagByPos`, `GetTradeData`, `GetMoney`
and `HasEnoughMoney`. Existing native CommandScript, login/logout/death/map/config hooks
are already used by the accepted Practical modules; do not extract a shared framework
or edit those accepted modules. No borrowed private Player method is permitted.

### Mandatory numerical and data guard before any repair

Preflight **every item the native call can visit**, using the same inventory slot range,
before invoking the native repair. Healthy/non-durable items need no charged repair.
If any actual damaged item or active pricing input is unsafe, refuse the entire request
before any repair/payment. These checks guard the new entry point; they do not patch
or saturate baseline core arithmetic.

1. Require current durability no greater than maximum durability; perform loss arithmetic
   only after validating this relationship. Require valid item/template data.
2. Require valid quality before computing `(Quality + 1) * 2`, and require the corresponding
   durability cost/quality DBC rows. Missing or invalid references reject service.
3. Validate the **raw** class/subclass-derived index before the core helper narrows it to
   uint8. Weapon uses subclass; armor uses subclass+21. The index must fit the actual
   29-element multiplier array; reject unsupported/invalid durable-item classifications.
4. Compute lost-durability times multiplier in uint64 and require it `<= UINT32_MAX`.
   This matters because the pinned core multiplies those two uint32 values **before**
   applying its double quality factor.
5. Require the quality factor finite and nonnegative. Check the same resulting initial
   double cost is finite/nonnegative and `<= UINT32_MAX` before the native uint32 cast.
6. Evaluate the native second expression with its float behavior:
   `uint32_base_cost * 1.0f * Rate.RepairCost`. The rate/result must be finite and
   nonnegative; compare the float result through double against `INT32_MAX` before
   the native uint32 conversion and `ModifyMoney(-int32(costs))` debit. Do not compare
   against a rounded float representation of the integer limit.
7. Preserve the native zero-to-one-copper minimum after its rate scaling. Native per-item
   affordability and continuation remain authoritative; there is no artificial gold cap,
   free-repair path, extra fee or baseline correction.

`DBCStructure.h:904–913` declares `uint32 multiplier[29]` and `float quality_mod`.
Its cached raw SHA256 was verified against pinned inventory:
`c8f2d645c0ce4b51d5586aec6ba43143c8ea6fd2ed273efdc5a1528ae6bc3279`;
Git blob `3db5fe364fab348ee3b514c1c85488ee0c3a5c9d`.
Exact public `ItemTemplate.h:557–567` defines the inline uint8 index helper; fields
Class/SubClass/Quality/ItemLevel are public in the struct beginning at618. The expected
pinned header identity is Git blob `2ce1f3195401788d1586e96cf30e4be3d007da41`, raw SHA256
`ba59e1dc1d72e2a0ea855533b9def8295a16493b203686a46cdd8fffcad16402`.
The proposal inspected this header directly from the exact public commit in memory;
no new source tree or dependency change was created.

If any request-time estimate is eventually displayed, confirmation must re-evaluate
current items/prices and explain changes; do not silently treat an old estimate as binding.
The preferred V1 avoids an estimate/quote subsystem and clearly describes current native
pricing before consent. Ordinary native callbacks and actual client/inventory behavior
remain part of later validation, not an assumed custom-money integration contract.

## One-Human Playability

Qualifying path: **complete solo utility**, available to ordinary classes/levels with
durable gear. No second human, second client or second operated account is required.
The human owns every custom action: inspect damage/balance, request, confirm or cancel,
read the outcome, earn more gold through normal solo play when needed and retry.

No bot/helper or enemy is introduced, so no enemy-count/difficulty/group scaling exists.
Zero bots leaves the entire feature available. A human with ordinary pinned Playerbots
may use normal combat/follow/tank/heal behavior while earning repair money; the bots issue
no repair commands, operate no menus and receive no repairs. No bespoke cognition,
precise positioning, timed intervention or second participant is assumed.

Exact planned manual sequence, all **PENDING LIVE/IN-GAME VALIDATION**:

1. Log in with one ordinary character wearing damaged durable gear in a safe normal
   outdoor-world area. Use status to inspect damaged count and personal balance.
2. Request service; verify the personal-gold/current-price/possible-partial-result notice
   and thirty-second consent. Cancel once and verify neither money nor gear changed.
3. Request again and confirm. Observe actual repaired/remaining counts, wallet delta and
   restored durability/broken-item stats. This is the full success/outcome loop.
4. Repeat with fully repaired gear: no charge. With insufficient personal funds, expect
   native no-repair or partial repair, clearly reported. Earn gold through normal solo
   play and request/confirm again; no extra operator or human economy is needed.
5. Let consent expire, or enter ordinary PvE combat, die, change maps or log out before
   confirming. Confirm must refuse/require a new request as documented. Recover normally
   and retry; no dead/combat/trade repair escape or pending automatic charge is allowed.
6. Cancel or stop interacting to exit. Operator disable/reload clears consent; re-enable
   requires a fresh request. No SQL rollback or persistent module record is involved.
7. Optionally repeat with normal bots; only the human is serviced. Record actual party
   coexistence and client inventory/stat behavior separately. Bot behavior and price feel
   are not inferred from source review or CI.

README and final handoff must each retain the exact `One-Human Playability` heading,
supported solo/optional bot roles, no-bots result, manual sequence and independent
ONE_HUMAN_REVIEW disposition. Do not claim manual tests were already performed.

## Dispositions, schedule and stop conditions

- **Practical: SELECT Field Repairs; DEFER Work Orders.** Stronger completion probability
  for this bounded window; useful paid utility with no new world-data surface.
- **Independent Reviewer: QUALITY=PASS; ONE_HUMAN_REVIEW=PASS; PINNED_FEASIBILITY=PASS**
  for the stated design/source-feasibility scope. Reviewer independently read native
  repair iteration, affordability continuation, personal return0 and signed debit, and
  required transparent pre-consent partial-result/current-price wording, actual count/
  wallet reporting and complete preflight before mutation.
- **Director: BUILD proposal decision PASS**, matching those exact bounded conditions.
- **Direct owner authorization received2026-09-05T13:27Z:** only Field Repairs and
  Wildcard-selected Triage Night additional lanes, at most one per lane. The prior
  automatic-review scope block is resolved. Root records durable decision/state first;
  no substantive implementation starts until the subsequent release.
- These dispositions certify selection only. No implementation, compilation, install,
  runtime or acceptance has occurred for Field Repairs.

Target: source/docs plus independent review within **three hours after release**. Budget
two existing full candidate gates of roughly two hours each, including a bounded fix
opportunity. Hard candidate/source cutoff: **2026-09-05T22:34:32Z**. Feature freeze remains
**2026-09-06T06:34:32Z**; ready handoff/owner testing begins **12:34:32Z**, protected through
the unchanged **18:34:32Z** ceiling. Do not extend these dates or consume owner-test capacity.

Use the existing official judge; no bespoke validation framework or infrastructure.
Small project-local deterministic assertions for actual arithmetic helpers may be useful,
but cannot replace real configure/build/install/config/startup/full tests or independent
evidence review. Every project warning remains fatal under official acceptance. Keep exact
pins/source protections and the CI-only WorldMock exception unchanged.

If the required guards, API behavior or review expand beyond a coherent three-hour slice,
defer rather than build a generalized shop/quote framework. Missing/unsafe data should fail
closed with useful feedback. No optional feature, new project or accepted-module expansion
is authorized. Hunt Rhythm4aaa3ae, Field Camp796e27e and Stormwright60c6a91 stay frozen;
**owner-reported fixes to them preempt this work immediately**.
