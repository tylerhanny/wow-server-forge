# Stormwright implementation handoff

```text
PROJECT=mod-stormwright
OWNER=Wildcard
BRANCH=project/stormwright
CANDIDATE_SHA=Docs-only logger correction to be bound by the next official dispatch and immutable evidence
SOURCE_REVIEW_SHA=a65f162419c8d0c0cc1ddbad2f35b7b4450018c8
STATE=BUILT_AND_REVIEWED_PENDING_CORRECTED_SUPPLEMENTAL_RERUN
CLAIMED_SCOPE=One public environmental encounter; complete Solo Pilot; three rods; optional ordinary bots
BUILD_RESULT=PASS for bde390e3 in33955586542; first a1558178 compilation failure preserved
OFFICIAL_GATE=33955586542 FAILED required supplemental observation; complete corrected-fixture rerun pending
SOURCE_REVIEW=PASS; exact repaired source a65f162419c8d0c0cc1ddbad2f35b7b4450018c8
SQL_SCHEMA_REVIEW=PASS; Practical independent exact-schema inspection
ONE_HUMAN_REVIEW=PASS; independent implementation source review, runtime/client execution pending
REVIEWER=Independent Reviewer; a65f162419c8d0c0cc1ddbad2f35b7b4450018c8
NEXT_ACTION=Official exact-candidate compile/install/SQL/startup gate and applicable normal-world runtime evidence
```

The source implements the registrar controller, owned AI roles, explicit
tracking/lock/impact transitions, charged/cooling rods, Ground/Discharge, fixed roster,
bounded adds, outcome/cleanup paths and terrain-derived placement guards. It includes
no production dependency edits or judge edits. Full gameplay runtime validation is not claimed.
Owned SQL/model/config packaging is complete. Exact DBC inspection rejected invisible
Tesla Coil/Crystal Spike models and selected a real PowerCrystal asset. Compile-time
rules assertions and executable developer tests passed in run33955586542.
The Reviewer-identified terminal-order defect is fixed: pilot failure is checked before
pending victory. Visual packets are feedback only; no existing encounter spell is cast.

The first official run33952393192 failed full compilation at a one-argument
SendPlaySpellImpact call. All three impact calls now provide the corresponding owned
actor's GUID, matching exact Unit.h:2034 and Unit.cpp:15210–15219. No gameplay, SQL,
configuration, dependency or judge changes were made. Independent repair SOURCE_REVIEW
and ONE_HUMAN_REVIEW passed for a65f162419c8d0c0cc1ddbad2f35b7b4450018c8. The required
rerun33955586542 passed full compile/install, both dry-runs and native units, then failed
the required supplemental normal-startup observation. Failed a1558178 history/evidence
is preserved alongside that second run's successful and failed stages.

The second run verified all expected installed SQL rows and the standalone rules test.
Its real worldserver reached ready/updates, but no registrar/site-outcome line was observed
before the five-minute timeout. Reviewer confirmed the helper's Logger.module=3 setting
was WARN, suppressing INFO=4; native default4 already permits INFO. This candidate fixes
only the corresponding README guidance and records actual evidence. The independent
judge owner corrects the helper separately. No registrar spawn is inferred from absent
logs; a complete official rerun must produce the required observation.

## One-Human Playability

The human chooses preset/start, baits every mark, dodges after lock, operates every rod,
chooses offense or recovery, and retries/aborts. No bots are required; Solo Pilot caps
pursuers at one and Ground restores the living pilot's health as well as ward. Optional
bots perform ordinary combat/follow only. No second human, client or operated account
is part of the full intended experience. Independent implementation inspection passed
the full one-human path. Actual manual tests through ordinary access, victory/failure,
result, retry and exit remain pending.

README contains full ordinary access, start, rules, recovery/offense, outcome, retry and
exit steps; all custom actions belong to the human. It also includes the exact 75-second
demo and later capture checklist. Independent ONE_HUMAN_REVIEW=PASS applies to the
actual implementation at c1f3926dcc8988d6f1461affeee0c817c97f911d, with no remaining
actionable source finding at that review. The later compiler repair changes three
impact-call arguments only; SQL, config, tests and gameplay rules remain unchanged.
Independent source/one-human carry-forward passed for that repair. This final frozen
checkpoint updates only README/validation/handoff after bde390e3; source, SQL, config,
rules and tests remain byte-identical to the successfully compiled candidate.

Full build/install, auth/world dry-runs, native units, installed SQL and developer rules
tests PASS for bde390e3 do not constitute overall acceptance. Corrected supplemental
registrar observation/continued run/shutdown remain pending, as do public access,
client effects, class/gear tuning and bot competence. Nearby spawn coordinates and
offline terrain projections are not being represented as gameplay validation.
