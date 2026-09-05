# WoW Server Forge — Blocked / Abandoned Work

This file preserves honest non-harvest outcomes so blocked work does not consume the whole sprint or masquerade as complete.

## Current disposition

Implementation is active from2026-09-05T06:40:42Z under the fixed provisional deadline
2026-09-06T18:34:32Z. Clean33947235843 and tamper33947239092 passed complete independent
review; see `prelaunch/clean-control-final-pass.md`. Earlier infrastructure failures below
remain historical and do not block the two active gameplay projects.

### Optional cache publication — approval block resolved

Reviewer revision `03002fb6c347925e10d08b6c741194f8569174dc` was independently
reviewed. Automatic approval review initially rejected the exact
`git cherry-pick` twice, including a direct retry after rereading the owner's explicit cache
authorization and verifying the repository is PUBLIC. Its stated reason is that the attached
authorization is not trusted for a sensitive official-workflow/cache change. Direct approval
was requested asynchronously. The owner then directly authorized publication of this exact
commit in the conversation, preserving all checks and exception boundaries. The unchanged
cherry-pick succeeded as `332eece`. This approval block is resolved; no workaround was used.
Hunt Rhythm's already-running run33951428776 continues under its original judge. Observe
cache behavior on the next required real-candidate run; no cache-only smoke cycle is needed.

## Historical authorized fixture correction and controls

At 2026-09-05T01:36:02.615039Z, the Director reconciled the owner's explicit authorization in
`WORLDMOCK_FIXTURE_EXCEPTION.md`. The exact reviewed WorldMock two-method delta may be
applied only inside disposable CI after verifying its original hash. No other upstream
source change is authorized; production source, pins, tests/assertions/coverage and all
remaining gate requirements are preserved. Record the exact patch and before/after hashes;
the modified full fixture must never be committed, installed or persisted outside CI.

The prior clean run 33929246418 remains FAIL, with both server targets built and the
required unit-test target failing. Tamper 33929247980 was rejected as required. The
source-policy blocker is now resolved by this exact owner exception. Reviewed adapter source `ff0e5807` is published as judge `60953d65185a231650c8c1050dbd6a182016ef66`.
Clean `33937007702` and tamper `33937008812` are dispatched. Practical and Director
approved the exact adapter; Reviewer now inspects actual complete control evidence.
Exact identities and outcomes: `prelaunch/evidence/fixture-exception-controls.json`. No new prelaunch gate or test expansion is authorized.

The heartbeat is ACTIVE. Hunt Rhythm and Stormwright selections/ownership are preserved.
All sprint timestamps remain UNSET until complete reviewed prelaunch success, then record
the actual clock and launch both lanes immediately. Earlier blocker/pause instructions
below are historical and do not override the current explicit authorization.


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
