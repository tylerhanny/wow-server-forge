# Exact upstream warning exception — explicit owner authority

**HISTORICAL / SUPERSEDED:** The owner subsequently replaced this single-diagnostic
restriction with standing `UPSTREAM_WARNING_POLICY.md` authorization. The text below
records the policy used for earlier runs; it is not the current warning acceptance rule.

**Authorized by the owner on 2026-09-04. Locked default-branch validation policy.**

This is the sole authorized exception to the existing warnings-as-errors policy. It does
not modify a dependency, approve a candidate, retroactively pass a failed run, or authorize
additional warnings. `VALIDATION_INTEGRITY.md` remains controlling everywhere else.

## Exact authorized diagnostic

```text
PLAYERBOTS_COMMIT=2f7d9f774987d0157c6a0d0cc08c40bec3db3945
SOURCE_GIT_BLOB=7688e6d4c04f246c87bf80881c238ba2c6bb0a3c
SOURCE_SHA256=6ad2a48db1f191b2ce6008fbd6d9b2c2f492438965a5211c38ab2b348f2d693c
STAGED_FILE=ac/modules/mod-playerbots/src/Ai/Raid/BT/BTHelpers.cpp
FUNCTION=GetShahrazTankPositionState
SOURCE_LINE=107
PARAMETER=botAI
DIAGNOSTIC=unused parameter 'botAI' [-Wunused-parameter]
ALLOWED_COUNT=1
```

The independent judge must verify this exact commit and the approved source-file Git blob
and raw-byte identity before applying the allowance. Verify the line/function/parameter
against those immutable source bytes; a matching diagnostic string alone is insufficient.
Reviewer and Practical independently obtained the two source identities above from the pin.
The machine allowlist belongs at `validation/upstream-warning-allowlist.json`; only the
protected default-branch copy is authoritative.

## Mechanical enforcement

1. Keep the allowlist, verifier and compiler integration in protected default-branch judge
   files. Candidate changes to any of them must fail scope/integrity validation.
2. Keep both exact dependency pins, `WITH_WARNINGS`, and general `-Werror`. Never modify
   Playerbots or AzerothCore tracked source. Prefer demotion confined to this one verified
   source file; it must not affect Forge candidate translation units.
3. Preserve the complete compiler/build stdout and stderr. Require exactly one warning,
   matching the authorized file, source identity, line, function, parameter and category.
   Reject missing/duplicate matches and every other warning or error, including any warning
   from `candidate/projects/<project>` or the staged Forge module. A newly discovered
   upstream warning is a fresh blocker, never another automatic allowlist entry.
4. A command-line-wide `-Wno-error=unused-parameter` is authorized only if technically
   necessary and the independent full-log checks above fail closed. It must never become
   an unchecked global waiver. Candidate warnings must still fail validation.
5. An incomplete/missing log or unsuccessful build cannot pass the parser or the gate.
   Preserve the allowed warning visibly in official artifacts and the job summary.
6. Verify both dependency trees remain byte-for-byte Git-clean after compilation and
   retain the existing later integrity checks. Preserve exact judge identities/hashes.
7. Keep every configure, compile, install, config, SQL/data, dependency-integrity, runtime,
   authserver/worldserver dry-run, unit-test and tamper-control requirement. Do not replace,
   skip, lower or reinterpret another check to obtain green.

The Reviewer owns implementation and evidence. Independent adversarial review must verify
the exception cannot admit candidate warnings, unrelated upstream warnings, changed source,
wrong paths or absent/duplicate diagnostics. Record compiler flag scope and remaining
build-hook trust limits honestly; candidate build hooks still require source review.

## Prelaunch and continuation

Record this as an **explicit owner-authorized upstream-baseline exception**. Failed clean
run `33911646203` remains failed. The owner-decision blocker for this diagnostic is resolved
only as authorization to implement and test this policy; validation itself is still pending.

Rerun the tamper control and legitimate clean control under the reviewed new judge. Tampering
must be rejected, and the clean candidate must pass the complete gate with exact candidate,
judge and artifact evidence plus independent review. Only then record the actual 36-hour
clock and immediately launch the selected work. Never start or extend the clock based on
the policy change alone. All One-Human Playability and AI Auteur requirements remain intact.
