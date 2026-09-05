# Field Camp compilation failure and minimal repair

Independent Reviewer, 2026-09-05. The failed candidate is not harvest-ready.
The correction below passes source review only and requires a new complete official run.

## Observed failure

- Candidate: `ec9eea979c9344853aaf02d46ba9f6632636254b`.
- Official run: [33952603462](https://github.com/tylerhanny/wow-server-forge/actions/runs/33952603462), **FAILURE**.
- Judge: `e7a37fa17fa9ed0c0afcc4c196ea98526b6044f4`.
- Artifact: `9966045369`, 635,422 bytes; GitHub API archive digest
  `2cf206fa919b01d4f26d1196c08bbb2cdc9567e45efad7ff90534c553896cefb`.
  This archive digest is API metadata; extracted evidence was independently hashed.
- Complete build log: 122,511 bytes, SHA-256
  `573e2b755a37c7b1015ca98c7c83a91591a3f9b4b88d011fbb1bedc94476e27f`.
  Capture is complete, stream/persisted hashes match, compiler process returned 2.
- All ten protected validation hashes match raw Git blobs at the recorded judge.
  Both exact dependency pins are retained. The disclosed WorldMock delta was verified
  and restored; its receipt verifies all other tracked dependency files unchanged.
  No full modified fixture header was exported.

The actual diagnostic at build-log lines 245–249 is:

```text
FieldCamp.cpp:79:48: fatal error: 'HasDelayedTeleport' is a private member of 'Player'
Player.h:3019:24: note: declared private here
```

This is a project API misuse, missed by the earlier source review. It is neither an
authorized upstream warning nor a judge defect. Configure and provenance checks passed;
full compilation failed. Install, runtime, unit execution and final stage checks were
skipped. Their success must not be inferred from receipt cleanup or partial build progress.

## Exact correction reviewed

`6ce52323b96be5dba4f4dfea5668032d17acdc3a`: **SOURCE_REVIEW=PASS** and
**ONE_HUMAN_REVIEW=PASS**, for the complete source-level solo path.

The only executable change removes the inaccessible, redundant private call. Public
`Player::IsBeingTeleported()` at pinned `Player.h:2125` checks both near/far semaphores.
The delayed same-map branch at `Player.cpp:1509–1516` sets its near semaphore before
returning; the far branch at `1574–1581` sets its far semaphore before returning.
The retained public predicate therefore rejects those pending requests at returned call
boundaries. No private-access workaround, core modification or judge change is needed.

All other eligibility, ground/phase, cooldown, lifecycle, normal-player commands and
one-human behavior remain unchanged. Configuration is byte-identical. The remaining
changes honestly document the failed run and pending repaired execution. Independent
`git diff --check` passes. New compilation/install/runtime evidence is still required;
actual client arrival, terrain, coexisting hooks, pets and bots remain manual-test limits.
