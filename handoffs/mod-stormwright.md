# Stormwright implementation handoff

```text
PROJECT=mod-stormwright
OWNER=Wildcard
BRANCH=project/stormwright
CANDIDATE_SHA=UNSET; building checkpoint, not a frozen acceptance candidate
STATE=IMPLEMENTED_VALIDATION_PENDING
CLAIMED_SCOPE=One public environmental encounter; complete Solo Pilot; three rods; optional ordinary bots
BUILD_RESULT=NOT_RUN
OFFICIAL_GATE=NOT_RUN
ONE_HUMAN_REVIEW=Proposal PASS at 0aa6e58; implementation PENDING
REVIEWER=PENDING_IMPLEMENTATION_REVIEW
NEXT_ACTION=Compile actual module against exact pins; independent full review and applicable runtime closure
```

The source implements the registrar controller, owned AI roles, explicit
tracking/lock/impact transitions, charged/cooling rods, Ground/Discharge, fixed roster,
bounded adds, outcome/cleanup paths and terrain-derived placement guards. It includes
no production dependency edits, judge edits or claim of completed runtime validation.
Owned SQL/model/config packaging is complete. Exact DBC inspection rejected invisible
Tesla Coil/Crystal Spike models and selected a real PowerCrystal asset. Compile-time
rules assertions and executable developer tests are present but not yet executed.
The Reviewer-identified terminal-order defect is fixed: pilot failure is checked before
pending victory. Visual packets are feedback only; no existing encounter spell is cast.

## One-Human Playability

The human chooses preset/start, baits every mark, dodges after lock, operates every rod,
chooses offense or recovery, and retries/aborts. No bots are required; Solo Pilot caps
pursuers at one and Ground restores the living pilot's health as well as ward. Optional
bots perform ordinary combat/follow only. No second human, client or operated account
is part of the full intended experience. Full implementation review and manual tests
through ordinary access, victory/failure, result, retry and exit remain pending.

README contains full ordinary access, start, rules, recovery/offense, outcome, retry and
exit steps; all custom actions belong to the human. It also includes the exact 75-second
demo and later capture checklist. Source selection approval remains separate from actual
ONE_HUMAN_REVIEW=PASS, which is pending independent implementation inspection.

All official compile/install/startup/test evidence is NOT_RUN. Public venue safety,
normal-world registrar/controller lifecycle, client effects, class/gear tuning and bot competence remain
unproven; nearby pinned spawn coordinates are not being represented as terrain validation.
