# WoW Server Forge — Blocked / Abandoned Work

This file preserves honest non-harvest outcomes so blocked work does not consume the whole sprint or masquerade as complete.

## PRELAUNCH infrastructure — fresh upstream diagnostics require owner resolution

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

Current action: preserve the failure report and independently review the bounded improvement
that displays observed diagnostics in failed-job summaries without changing acceptance.
Then await explicit owner resolution; no unchanged rerun, broader waiver, source/pin edit,
gameplay implementation or clock start is authorized.
See `prelaunch/clean-control-compile-blocker.md` for the exact judge/hash, artifact, diagnostic,
supported-toolchain audit, skipped stages and concrete owner alternatives.
Until the complete clean gate and tamper control pass independent review, preserve both
selected projects without implementation and keep every sprint timestamp UNSET. The
active continuity heartbeat stays quiet while this owner-required blocker is unchanged.

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
