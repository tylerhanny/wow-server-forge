# Field Camp candidate handoff

PROJECT=mod-field-camp
OWNER=Practical
BRANCH=project/field-camp
CANDIDATE_SHA=UNSET
STATE=VALIDATING
CLAIMED_SCOPE=One safe same-map/exact-phase session camp, normal-player set/status/return/clear, bounded session cooldown, no SQL/payment/bot transport
BUILD_RESULT=Previous ec9eea9 FAIL in run33952603462; minimal API repair NOT_RUN
OFFICIAL_GATE=Previous ec9eea9 FAIL in run33952603462; repaired candidate NOT_RUN
ONE_HUMAN_REVIEW=PASS for repaired complete solo source path at6ce52323b96be5dba4f4dfea5668032d17acdc3a; actual execution/client evidence pending
REVIEWER=SOURCE_REVIEW PASS for exact repair6ce52323b96be5dba4f4dfea5668032d17acdc3a; new official execution pending
NEXT_ACTION=Dispatch one full official gate for the frozen final repaired candidate

Official run `33952603462` attempted to compile candidate `ec9eea979c9344853aaf02d46ba9f6632636254b`
far enough to diagnose private `Player::HasDelayedTeleport` access. Configure/provenance
passed; install/runtime/unit execution did not run. The minimal correction removes only
that redundant private call: public `IsBeingTeleported()` covers the near/far semaphores
set by both delayed teleport branches. Dependencies, pins and official judge are unchanged.
Failed history stays preserved; the repaired source is not yet compiled.

The commit containing this handoff cannot contain its own SHA. Director records its frozen
SHA and exact independent judge/run/evidence in a later external main attestation. This
pre-run handoff remains honestly pending and cannot certify acceptance.

Complete source/config/docs are isolated to `projects/mod-field-camp/`; the branch starts
at Director main `4587658`. No dependency, authority, validation, build-hook or SQL changes.
No local compiler is available; source inspection is not compile evidence. Native module
registration/config emits `FIELD_CAMP_CONFIG` when the module logger is at INFO.

## One-Human Playability

The qualifying complete path is solo: one ordinary level 1–80 character of any class sets
a safe dry outdoor camp, travels normally to a same-map town for supplies, steps outdoors,
requests return, observes arrival/cooldown, retries after a restriction expires, and clears
the camp to exit. No second human, second client or second operated account is required.
No enemy scaling or helper is needed. All custom actions are `.camp set`, `.camp status`,
`.camp return` and `.camp clear`, performed by the human.

One human with normal pinned bots can use the feature, but it transports only the human.
No bot count/type is required, no bot menu/action is assumed, and regrouping/pet handling
remain PENDING LIVE/IN-GAME VALIDATION. Solo delivers the full useful loop with no bots.
Director and independent Reviewer approved the design in `decisions/field-camp-selection.md`;
independent ONE_HUMAN_REVIEW for the implementation's complete solo source path is PASS
at `b1b84172b96b41e230bae5f8c6564b3195eb61a7`. The later compiler exposed an inaccessible
API; independent Reviewer approved the minimal public-predicate correction at
`6ce52323b96be5dba4f4dfea5668032d17acdc3a` with SOURCE_REVIEW=PASS and ONE_HUMAN_REVIEW=PASS
for the complete solo source path. Final changes record only review/source evidence.
Actual execution and client evidence remain pending.

Exact manual steps, not yet performed:

1. One ordinary character uses `.camp status`, then `.camp set` on dry safe outdoor ground.
2. Travel normally to town on the same map, sell/repair, step outdoors and `.camp return`.
   Confirm the accepted-request message and actual client arrival separately.
3. Immediate repeat rejects on cooldown. Clear/set must preserve its remaining time;
   wait, then repeat the full supply-trip loop successfully.
4. Try jumping/swimming, ordinary solo PvE combat, casting, death or a different map/phase.
   Return rejects without spending cooldown; recover or travel normally and retry.
5. `.camp clear` removes the anchor with no automatic travel. Set/relog clears anchor and
   cooldown. Optional normal bots/pets require separate behavior observations.

README includes the full detailed checklist, config/install/removal and terrain/veto caveats.

## Limits and pending evidence

No persistent/cross-map/shared camp. Logout/restart/successful config reload clears session
state. An accepted default TeleportTo request consumes cooldown before proven client arrival;
core rejection refunds it, but native core cleanup may already have occurred before a veto.
Ground/phase checks reject unavailable or changed surfaces instead of inventing a destination.
Gameplay feel, terrain/client arrival and optional bot regrouping remain pending.

Compile/install/config/SQL-applicability/startup, full official gate, independent source and
one-human implementation review must all be independently recorded before harvest. See
`projects/mod-field-camp/VALIDATION.md` for exact pinned references and current evidence.
