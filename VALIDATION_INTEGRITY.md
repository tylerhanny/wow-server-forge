# WoW Server Forge — Validation Integrity Authority

## Controlling owner sequencing amendment — 2026-09-05

Owner directive received **2026-09-05T06:34:32Z**: finish the current clean control
`33947235843` under judge `dd283819da03e9ccbebdf9378b5fe3f1cf016380` (tamper
`33947239092`) with its existing checks/timeouts. Do not cancel a healthy run or restart it.
This is the last serial prelaunch attempt. After ANY terminal result, start isolated
Practical Hunt Rhythm and independent Wildcard Stormwright implementation immediately.
Do not wait for another control, full failure classification or repair. Preserve unsuccessful
results; Reviewer diagnoses/repairs and validates concurrently. The existing approved designs
and one-human dispositions stand; no new tournament is required for these assignments.

Implementation permission is separate from final acceptance. Every exact candidate still
requires the real official compile/install/config/SQL/startup/test/integrity evidence and
independent review before READY FOR LIVE TEST. No tests, assertions, project warning rules,
pins, source protections, isolation or exact disposable WorldMock limits are relaxed.
Separate clearly labeled DEVELOPMENT-ONLY checks may omit the unchanged upstream unit
target; never force them through or weaken the strict official wrapper.

No exact access cutoff or earlier fixed owner deadline was found in the provided conversation
or project records. The **PROVISIONAL fixed ceiling is 2026-09-06T18:34:32Z**
(2026-09-06 14:34:32 America/New_York), 36 hours from directive receipt. Access for that
whole period is not verified. Remaining control time consumes this window. Record actual
implementation start once terminal; preserve the fixed deadline and reserve the final 12h
for convergence (deadline minus 12h), then harvest (deadline minus 6h). Never extend it.
An earlier confirmed owner/access boundary can only shorten it, with handoff time reserved.

Before another expensive validation dispatch, Reviewer checks the remaining existing stages
together for concrete configuration contradictions. Keep this bounded. Safe economical
reuse of the compilation cache is authorized with source/compiler/options identity and
visible diagnostics preserved; never export the corrected fixture source or reuse a verdict
in place of current-candidate validation. Do not retrofit the current run or delay builders.
Report meaningful transitions and actual source/validation results, not unchanged compile
updates. This explicit amendment supersedes conflicting prelaunch/start-plus-36h language
below and in older records, role prompts and scheduling helpers. Historical failures stay failed.


**Status: LOCKED BEFORE SPRINT LAUNCH**

This file defines the anti-gaming and independent-validation rules for the autonomous forge. All Director, Practical, Wildcard, Reviewer, and subagent work is bound by it.

## Core principle

The implementation must pass the judge. The implementation may not rewrite the judge until it passes.

A candidate does not become acceptable because an agent weakened, skipped, deleted, replaced, mocked, bypassed, or reinterpreted a failing validation.

## Standing explicit owner-authorized upstream warning policy

On 2026-09-04, the owner replaced the earlier single-diagnostic exception with standing
`UPSTREAM_WARNING_POLICY.md`: warnings originating exclusively from verified-unchanged
pinned AzerothCore/Playerbots source are non-fatal and fully visible. The independent
default-branch judge must verify source provenance, reject every project-owned warning,
retain both pins and all other gates, and rerun both controls. Additional qualifying
upstream warnings require no owner approval. This is an explicit owner policy amendment,
not a builder waiver or retroactive success. The old `UPSTREAM_WARNING_EXCEPTION.md`
is retained only as history. Complete only the existing minimum prelaunch gate, then
start the clock immediately without additional prelaunch requirements.

## Exact owner-authorized WorldMock test-fixture exception

`WORLDMOCK_FIXTURE_EXCEPTION.md` records the owner's 2026-09-05 authorization for only
an exact hash-checked two-method correction to the pinned WorldMock test fixture inside
disposable CI. The modified fixture must never be committed, installed, or persisted
outside that environment. Record the exact patch and before/after identities; all production
source, pins, tests/assertions/coverage and remaining gates stay unchanged. This explicit
exception supersedes unchanged-source language only for that precise temporary fixture
delta. It does not permit any other upstream modification or mislabel modified code as
verified-unchanged upstream. Immediately rerun the two existing controls, then launch on
complete required evidence without additional prelaunch gates.

## Official gate ownership

Official acceptance tests, validation scripts, reference checks, dependency-pin checks, and disposable startup gates are controlled by the Reviewer/Closer validation lane and must be treated as immutable by builders.

Practical, Wildcard, Director builder subagents, and project-specific implementation agents may:

- add project-local developer tests that improve coverage;
- fix product code in response to a failing official gate;
- propose a test/gate defect with evidence.

They may NOT:

- delete or weaken an official gate;
- change an expected result merely to match current broken behavior;
- skip, xfail, quarantine, mock away, or conditionally bypass a failure;
- reduce test coverage to obtain green status;
- alter dependency pins or validation inputs to make compilation easier;
- disable warnings/errors/checks merely to make the run pass;
- make the official gate call a substitute test under builder control;
- replace real startup/integration validation with a stub or source-only assertion;
- modify a test and its implementation in the same builder change when that test is part of the official acceptance gate.

## Mechanical enforcement requirement

Before the 36-hour sprint clock starts, the official validation gate must be placed outside normal builder write authority or otherwise cryptographically/hash pinned so modification is detected and invalidates the result.

The enforcement remains required for final acceptance. The owner sequencing amendment permits implementation after the current attempt terminates even when validation remains pending or blocked.

The final validation record for every harvested candidate must identify:

- exact candidate commit SHA;
- exact validation-gate version/hash/commit;
- exact AzerothCore pin;
- exact mod-playerbots pin when applicable;
- build/configure command;
- install/staging result;
- SQL/data validation result;
- disposable worldserver startup result when applicable;
- module-load evidence when applicable;
- official gate result;
- independent Reviewer disposition.

## Server-working gate

For a server module, source review and compilation alone are insufficient.

Before `READY FOR LIVE TEST`, all feasible automated/disposable checks must succeed:

1. Exact pinned AzerothCore source is used.
2. Exact pinned Playerbots source is used when required.
3. Core and Playerbots trees remain unmodified by the candidate.
4. Module discovery/configuration succeeds.
5. Full relevant compilation succeeds.
6. Install/staging into a disposable server tree succeeds.
7. Module config is accepted.
8. Module-owned SQL/data can be applied or deterministically validated without destructive unrelated changes.
9. A disposable worldserver starts far enough to prove the module loads without startup crash/error when the environment can support it.
10. Relevant official deterministic/reference tests pass.
11. Reviewer inspects the actual candidate diff and validation evidence.

Manual WoW-client gameplay remains a later Tyler task and must be clearly labeled `PENDING LIVE/IN-GAME VALIDATION`; it must never be represented as already proven.

## Suspected gate defect

If an agent believes the official gate itself is wrong:

1. Do not edit it.
2. Record the exact failure and evidence.
3. Ask the independent Reviewer lane to reproduce it against a known-good control or authoritative pinned source.
4. Only the Reviewer may propose a gate revision.
5. A gate revision must be committed separately with rationale and must not be used retroactively to disguise a candidate failure.

If uncertainty remains, the candidate stays out of `HARVEST.md`.

## Anti-self-certification

The agent primarily responsible for implementing a candidate may not be the sole authority that marks it harvest-ready.

Every harvested candidate requires independent Reviewer/Closer approval against the official immutable gate.

## No false green

A green result produced after test weakening, gate modification, skipped validation, altered pins, or an unverified substitute environment is invalid even if CI reports success.

The correct response to a legitimate failure is to fix the implementation, safely reduce feature scope, or move the candidate to `BLOCKED.md` / `IDEA_VAULT.md`.
