# Stormwright compilation failure and impact-packet repair

Independent Reviewer, 2026-09-05. The failed candidate is not harvest-ready.
The correction below passes source review only and requires the complete official gate.

## Actual failed execution

- Candidate: `a1558178ceee2b92e020928ecb8fd3f59c3c34a2`.
- Official run: [33952393192](https://github.com/tylerhanny/wow-server-forge/actions/runs/33952393192), **FAILURE**.
- Judge: `aea0f034d9e4767e96891fdf24c6260cd959218f`.
- Artifact: `9966139884`, 642,376 bytes; GitHub API archive digest
  `3e764cadb180d350235f53eb280b73b6732e2b97047ea0ac2aa9be39f87e5f89`.
  This archive digest is API metadata; extracted evidence was independently hashed.
- Complete build log: 197,686 bytes, SHA-256
  `4f0835874725e26d1c63943e0b9a4034955f2a2ec9a69f11e903c5f4bce151e2`.
  Capture is complete, stream/persisted hashes match, compiler process returned 2.
- All ten protected file hashes match raw Git blobs at the recorded judge. Exact pins
  are retained. The disclosed WorldMock correction's precise delta, all-other-source
  integrity and original-byte restoration are verified in the receipt. No full modified
  fixture header was exported. Both project translation units retain literal `-Werror`
  without upstream demotion in the 1,830-entry compiler inventory.

Actual build-log lines 1829–1833 report:

```text
Stormwright.cpp:277:56: fatal error: too few arguments to function call, expected 2, have 1
277 | rod->SendPlaySpellImpact(LightningImpactKit);
Unit.h:2034:10: note: 'SendPlaySpellImpact' declared here
2034 | void SendPlaySpellImpact(ObjectGuid guid, uint32 id);
```

This project API misuse was missed by source review. It is not a judge defect or an
authorized upstream warning. The four known Playerbots unused-parameter warnings are
also visible: BTHelpers:107, HyjalHelpers:168/209 and HyjalScripts:39. The retained native
fatal-error behavior reports the first bad project call; bounded source follow-through
identified the same missing argument at lines 285 and 388.

Configure/provenance passed. Full compilation failed. Install, SQL application, dry-runs,
unit execution, supplemental normal-world evidence and final stage checks were skipped.
None of those outcomes is inferred from partial compilation or fixture cleanup.

## Exact minimal correction

`a65f162419c8d0c0cc1ddbad2f35b7b4450018c8`: **SOURCE_REVIEW=PASS** and
**ONE_HUMAN_REVIEW=PASS**, for the complete source-level Solo Pilot path.

All three calls explicitly pass their intended owned actor's GUID: rod, boss and marker.
Exact pinned `Unit.cpp:15210–15219` writes that target GUID and visual-kit ID to the impact
packet. This retains packet-only feedback; it introduces no cast, aura or other spell effect.
Only those call arguments change executable source. Rules, SQL, configuration, tests,
human/bot roles, recovery/offense decisions, cleanup and retry/exit remain unchanged.
The remaining edits preserve the failed SHA/run and mark new execution pending.
Independent `git diff --check` passes. Actual full build and all applicable runtime gates
remain required; client visuals, approach/navigation, encounter balance and bot competence
remain unperformed manual checks.

Final candidate `bde390e3ec1d9df764b5d4e6b0b0e00c40e0d7cc` changes only README,
validation notes and handoff review status from that repaired source. Source, SQL,
configuration and test byte identity and whitespace were independently checked.
One complete official run was dispatched: `33955586542`, judge
`8b87494de0261cd82c48c4a0dc11895611fb9d39`. Its execution result is pending.
