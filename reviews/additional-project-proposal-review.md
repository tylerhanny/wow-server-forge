# Independent additional-project proposal review

Reviewer/Closer disposition, 2026-09-05. This records the completed read-only comparison
already delivered to Director and builders. It adds no research, test or acceptance gate.
The Director reports direct owner authorization at 13:27Z for exactly one Field Repairs
project and one Triage Night project, resolving the earlier additional-scope mutation block.
Existing Hunt Rhythm, Field Camp and Stormwright accepted checkpoints remain frozen unless
owner feedback requires a fix. Owner feedback takes priority over additional projects.

## Review level and schedule

These are **proposal quality, one-human design and pinned-source feasibility** judgments.
They are not reviews of implementation that does not yet exist, and do not claim compilation,
SQL application, runtime gameplay or client validation. Actual source review and every
applicable existing official gate remain required for each exact candidate.

- Exact target: client 3.3.5a build 12340, Ubuntu 24.04 x86-64; AzerothCore
  `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- Source candidate cutoff: **2026-09-05T22:34:32Z**.
- Feature freeze: **2026-09-06T06:34:32Z**; owner testing begins
  **2026-09-06T12:34:32Z**; hard deadline **2026-09-06T18:34:32Z**.
- Proposal estimates allow <=3h Field Repairs or <=4h Triage source/docs, plus two
  approximately two-hour full candidate runs and bounded fixes before freeze. These are
  feasibility estimates, not guaranteed timing or reasons to relax acceptance.
- No new judge framework, cache-only control, dependency change, live-server access or
  accepted-project expansion is included. Dispatch must use the current default-branch
  judge; the historical Reviewer-lane workflow is not the acceptance authority.

## Practical comparison: Field Repairs

**QUALITY/INSTALLATION VALUE=PASS; ONE_HUMAN_REVIEW=PASS at proposal scope;
PINNED FEASIBILITY=PASS.** Recommended over daily supply Work Orders.

Field Repairs is a modest but repeatedly useful personal paid repair service. It complements
Field Camp, whose return trip still supports selling/restocking. Work Orders offers new
profession content, but quest/item/reward/access data and reference-validation work make
that alternative a poorer completion risk for the <=3h source/docs envelope; **DEFER**.

One ordinary human of any level/class with damaged durable gear can inspect condition and
balance, request service, consent within 30 seconds, observe actual repairs/charges, earn
more gold after an unaffordable or partial result, retry, cancel or let consent expire.
One client/account suffices. No bots are required; optional bots only provide ordinary
combat while earning gold, receive no repairs and perform no special interaction. There
are no enemies or roster scaling in the feature, and zero bots is the complete primary path.

The independently inspected exact `Player.cpp:4900-4990` confirms
`DurabilityRepairAll(true, 1.0f, false)` iterates equipped/backpack/bag items, excludes
bank/buyback/keys, uses personal native gold, and continues after unaffordable items.
Its personal-payment return value is zero, so it cannot be reported as the price paid.
The module must report observed wallet and durability changes instead.

Essential bounded conditions already agreed:

- Commands cover status/request/confirm/cancel. Consent clearly explains current native
  undiscounted prices and possible partial repairs before any effect. Any displayed
  estimate is re-evaluated at confirmation; it is not silently treated as a binding quote.
- Confirmation rechecks the proposed alive/in-world, safe outdoor/non-instance,
  out-of-combat, non-PvP/non-duel, no trade/taxi/vehicle/transport/teleport/control/cast/logout
  eligibility, consumes consent, and performs complete preflight before one native repair call.
- All carried items/rate inputs must be safe before any effect: current durability <= max;
  valid quality/DBC data; raw class/subclass index validated before the uint8 helper;
  multiplier index <29; wide lost-durability product within uint32; finite nonnegative
  quality and initial double cost within uint32; the native second float/rate conversion
  within signed debit range. Preserve native minimum one-copper cost. Unsafe inputs decline
  the whole request rather than saturate, partially preflight or alter native source.
- Record actual repaired/remaining condition counts and wallet delta. No fake atomicity,
  refunds, surcharge, guild funds, item grants, SQL, persistent state or new economy.
- Logout/death/map change/config reload clear pending consent. Already-repaired requests
  charge nothing. Normal client inventory updates, pricing feel and bot-party coexistence
  remain manual validation items; no execution is inferred from this source analysis.

## Wildcard five-concept comparison

The full read-only tournament supplied five mechanically distinct concepts, all mandatory
concept and one-human fields, three shortlisted alternatives, creator rationale and
60-90-second future demonstration framing. The following is the independent comparison;
Wildcard retains authorship and selection among concepts passing both review floors.

| Concept | Gameplay and installation judgment | One-human design | Completion disposition |
|---|---|---|---|
| Triage Night | Distinct support-role challenge using persistent wounds, real healing/mana and finite rescue choices; worthwhile repeated practice | PASS for explicit level-80 priest/direct-heal solo path | PASS within bounded V1 |
| Blindside | Promising non-Rogue patrol infiltration with route/distraction decisions | Plausible solo observation, two caches, extraction, failure/retry | DEFER: facing/path/LOS fairness and stock warning readability need uncertain client iteration |
| Kill Switch | Player-authored mine chains offer tangible spatial choices, but lure/discharge overlaps Stormwright and reduces second-install value | Plausible solo mine planting/detonation; ordinary combat bots optional | DEFER: chain readability, ammunition outcome, chase and any-class sustain/bot threat increase closure risk |
| Switchback | Movement-route mastery could repeat, but tiny player-anchored course value and visible hazards are unproven | Solo route is conceivable | DEFER: traversability/collision and class movement make worthwhile fair timing uncertain |
| Borrowed Body | Possession changes the playable role and has strong demonstration potential | Intended solo control/return path | DEFER: action-bar initialization, spell targeting, body safety and every possession cleanup path exceed the bounded window |

## Triage Night: independent qualifying scope

**QUALITY/INSTALLATION VALUE=PASS; ONE_HUMAN_REVIEW=PASS at proposal scope;
PINNED FEASIBILITY=PASS.** This is the only shortlisted concept that independently passes
all eight mandatory decision tests within this particular window: install, repeat,
gameplay decisions, short demonstration, visible moment, post-surprise value, deadline
credibility and authentic creator judgment. This is not a claim of global novelty or
executed gameplay; stock First Aid triage exists, while this V1 uses real healing spells,
three persistent patients and cumulative resource decisions across five rounds.

The coherent V1 is one level-80 priest with ordinary learned direct single-target heals
and healing gear, three owned patients and a controller, five authored 45-second injury
rounds separated by finite 10-second recovery breaks, two pressure presets, and two total
human-operated stabilization charges that pause one patient's deterioration for six seconds.
Patient health carries between rounds; normal player mana is never refilled by the module.
The player chooses efficient versus quick healing and rescue timing under overlapping
burst/sustained pressure. Native resource recovery is allowed. This is a complete solo
support challenge, not a partial raid role requiring a second healer or client.

The complete lifecycle is public help/start/preset selection, safe eligible ground checks,
briefing, all five rounds and breaks, all-patients-alive success or explicit patient/pilot/
departure/time failure, result, ordinary rest/retry and stop. Human actions include every
targeted heal and stabilization choice. No bot helper heals patients or operates a menu;
zero bots is the primary path. Presets change injury pressure, not party scaling.

Essential bounded conditions already agreed:

- Ordinary selectable living friendly patients with `CREATURE_TYPE_FLAG_CAN_ASSIST`;
  do not use NON_ATTACKABLE/immune-PC flags as damage protection. Independent inspection
  of exact `Unit.cpp:10920-10975` confirms those flags can block ordinary player assistance.
  Filter outside damage through owned AI, instead of invalidating legitimate heal targets.
- `HealReceived` is invoked before native health modification in the inspected pinned
  path. Only the owning pilot's intended healing can affect the challenge. Disable native
  patient regeneration and prevent evade/reset paths from restoring persistent wounds.
- Scripted deterioration is explicitly health loss, not shield-preventable combat damage.
  Party-targeted/AoE compatibility, other healer classes and helpful bot healing are not
  promised. Normal priest direct-heal feasibility must not be generalized into proven
  all-healer balance. No free player mana/health is granted by the module.
- Three named patients in a compact semicircle use stock health bars, ordinary healing
  animations, low-health/recovery poses and concise upcoming-injury warnings. Real client
  targeting, poses/readability, gear pressure and tuning remain manual checks.
- Player-triggered temporary actors avoid introducing an untested OnStartup registrar.
  Start rejects unsuitable/missing nearby height/LOS samples rather than guessing ground.
  Height sampling is not represented as client navigation proof. Owned actors, runs and
  lifetime are bounded; death/logout/map departure/abort/disable/spawn failure clean up.
- No stock-world damage, economic rewards, fair ranking, permanent progression, custom UI,
  injury-dispel framework, gear normalization or possession system. Results remain bounded
  session records; every terminal outcome permits a clean retry/exit.
- Existing full candidate build/install/SQL/config/dry-run/native-unit and source-integrity
  requirements still apply. Native updater/module-load evidence does not execute a logged-in
  encounter. No Stormwright-only helper reuse or new runtime framework is assumed.

These limits preserve the interesting mechanic and one-human completeness while keeping
scope credible. Actual implementation findings must be fixed and independently reviewed;
none of these proposal dispositions pre-accepts code, successful execution or owner gameplay.
