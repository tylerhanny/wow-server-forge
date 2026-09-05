# WoW Server Forge — Blocked / Abandoned Work

This file preserves honest non-harvest outcomes so blocked work does not consume the whole sprint or masquerade as complete.

## Current resume and prelaunch blocker

Owner explicitly resumed; reconciled 2026-09-05T01:06:37.050300Z. The prior safe pause is lifted.
The existing continuity heartbeat is ACTIVE and stays quiet while this blocker is unchanged.
Practical Hunt Rhythm and Wildcard Stormwright ownership/selections are preserved; neither
implementation nor the 36-hour clock has started. All sprint timestamps remain UNSET.

Tamper run 33929247980 was rejected as required. Clean 33929246418 failed on actual
pinned upstream WorldMock compile errors: missing GetPlayerbotsDBRevision and
AddQueryHolderCallback overrides. Both server targets built, but the required whole build
failed and install/SQL/runtime/unit-test execution were skipped. The standing upstream-warning
policy worked and remains authorized. No additional warning approval is required.

Evidence: `prelaunch/clean-control-pinned-unit-test-blocker.md`, Reviewer source e892081.
The Director independently checked the saved raw build hash/diagnostics and reconciled
GitHub completion at the exact judge SHA. Reviewer found no supported configuration fix preserving the suite. The exact unapplied
two-method proposal is `prelaunch/worldmock-test-fixture-proposal.md` with adjacent patch
(Reviewer source b4724d4); it requires explicit owner authorization for that test-only delta. No dependency/test
source, judge, pin or acceptance requirement has been changed. No identical retry is justified.
Earlier pause/active instructions below are historical; this current disposition controls.


## Historical warning-policy blocker

The earlier warning-policy conflict was resolved by standing `UPSTREAM_WARNING_POLICY.md`.
It does not resolve the distinct current pinned unit-test source error recorded above.

### Historical failure record under the previous policy

The following describes the earlier runs and their then-current restrictions; it does
not override the current standing authorization.

The sprint remains ARMED_NOT_STARTED. This is a Forge infrastructure blocker, not an
attempted gameplay project and not a harvested result.

Clean-control run `33911646203` failed full compilation of exact Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`: unused parameter `botAI` at
`src/Ai/Raid/BT/BTHelpers.cpp:107:60`, made fatal by the unchanged warning policy.
Candidate `87b822fd41bb6013358aa6f5e16ca252ad79761c` adds no compiler flags, build hooks,
warning pragmas or dependency changes. Supported GCC and Clang warning configurations
do not establish an escape from this diagnostic. Install/runtime/unit tests did not run.

The owner subsequently authorized only the exact protected allowance in
`UPSTREAM_WARNING_EXCEPTION.md`. No dependency edit, pin change, unproven compiler
substitution, additional warning or general warning suppression is authorized. The
protected policy has been implemented and independently reviewed at judge
`78a5da6d5aed19a932fae53e74226ac5afc2e204`. Both fresh negative controls were rejected
as required. Clean run `33922537362` passed its real Ubuntu compiler-scope probe and
configure/provenance checks, then failed at `2026-09-04T22:33:12Z` on two new fatal
`unused parameter 'botAI' [-Wunused-parameter]` diagnostics:

- `src/Ai/Raid/Hyjal/Util/HyjalHelpers.cpp:168:61`, `GetKazrogalTankPositionState`.
- `src/Ai/Raid/Hyjal/Util/HyjalScripts.cpp:39:63`, `ShouldInterruptForArchimondeAirBurst`.

Practical and Reviewer independently verified exact pinned source identities and unused
bodies. Only BTHelpers received the authorized demotion; it emitted exactly one visible
warning. The two Hyjal files and candidate retained warnings-as-errors. Complete captured
build output, exit 2, equal pre/post dependency identity/Git-clean checks and exact hashes
are preserved in `prelaunch/evidence/clean-33922537362-director-audit.json`. The later
install/SQL/runtime/dry-run/unit gates did not run. These diagnostics are explicitly outside
the owner's narrow authorization; no additional allowance or dependency repair is inferred.
Another unused `botAI` in `GetAzgalorTankPositionState` at HyjalHelpers line 209 is source-only,
not observed compiler output. Because pinned `-Wfatal-errors` stops each translation unit
at its first error, the two observed errors are not an exhaustive inventory.

The failure report and independently reviewed failure-summary correction are complete:
`prelaunch/clean-control-additional-upstream-blocker.md` and
`prelaunch/failure-summary-reporting-review.md`. Acceptance is unchanged.
At that point another owner decision was required. The standing policy above now resolves
that decision; the failed runs remain failed, and source/pin edits remain prohibited.
See `prelaunch/clean-control-compile-blocker.md` for the exact judge/hash, artifact, diagnostic,
supported-toolchain audit, skipped stages and concrete owner alternatives.
Until the complete clean gate and tamper control pass independent review, preserve both
selected projects without implementation and keep every sprint timestamp UNSET. The
active continuity heartbeat resumes executable validation under the standing policy.

## BLOCKED

None yet.

Use:

```text
Project:
Lane:
Branch/commit:
What works:
Exact blocker:
Attempts made:
Why scope reduction was insufficient:
Smallest plausible future path:
Requires live testing, dependency change, prohibited action, or simply more time?:
```

## ABANDONED

None yet.

Use:

```text
Project:
Reason abandoned:
Useful assets/research preserved:
Branch/commit if retained:
```

## Rules

- A blocker in one project must not stop the overall forge.
- Never modify the pinned dependencies to rescue a candidate.
- Never use the live server to answer a blocker during this sprint.
- Preserve worthwhile findings, then release the worker to a better opportunity.
- During CONVERGENCE and HARVEST, aggressively move low-probability work here rather than starving strong candidates.
