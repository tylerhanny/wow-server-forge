# Stormwright implementation handoff

```text
PROJECT=mod-stormwright
OWNER=Wildcard
BRANCH=project/stormwright
CANDIDATE_SHA=UNSET; building checkpoint, not a frozen acceptance candidate
STATE=BUILDING
CLAIMED_SCOPE=One public environmental encounter; complete Solo Pilot; three rods; optional ordinary bots
BUILD_RESULT=NOT_RUN
OFFICIAL_GATE=NOT_RUN
ONE_HUMAN_REVIEW=Proposal PASS at 0aa6e58; implementation PENDING
REVIEWER=PENDING_IMPLEMENTATION_REVIEW
NEXT_ACTION=Complete owned template/model SQL and compile the actual module against exact pins
```

First source checkpoint implements the registrar controller, owned AI roles, explicit
tracking/lock/impact transitions, charged/cooling rods, Ground/Discharge, fixed roster,
bounded adds, outcome/cleanup paths and terrain-derived placement guards. It includes
no production dependency edits, judge edits or claim of completed runtime validation.

## One-Human Playability

The human chooses preset/start, baits every mark, dodges after lock, operates every rod,
chooses offense or recovery, and retries/aborts. No bots are required; Solo Pilot caps
pursuers at one and Ground restores the living pilot's health as well as ward. Optional
bots perform ordinary combat/follow only. No second human, client or operated account
is part of the full intended experience. Full implementation review and manual tests
through ordinary access, victory/failure, result, retry and exit remain pending.

This is not yet an installable candidate: module-owned SQL/model selection and final
package docs remain incomplete. All official compile/install/startup/test evidence is
NOT_RUN. Public venue safety, client effects, class/gear tuning and bot competence remain
unproven; nearby pinned spawn coordinates are not being represented as terrain validation.
