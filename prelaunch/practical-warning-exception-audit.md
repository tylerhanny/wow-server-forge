# Practical independent warning-exception audit

Reviewed commit: `2e73998349c65dc442b7fed3008d0df0e007bb29`.
Disposition: **APPROVE at source, parser and command-provenance review scope**.
Completed: 2026-09-04 21:45 UTC. Reviewer: Practical Builder, independently of
the Reviewer lane's implementation and selftests.

The exact committed verifier, policy and hook were exported with `git show` into
an ignored disposable directory, then exercised by the independent harness.
All **73 cases produced their expected outcomes; zero mismatches**. The report
does not claim Linux compiler integration, a complete pinned dependency build,
install, worldserver startup, in-game validation, or launch permission.

## Exact tested identities

| File | SHA-256 |
| --- | --- |
| `validation/verify_build.py` | `2b3adb4328f5a1ce356b734b3b31a168efe2f021e3320cfd12eed9b70b2c161c` |
| `validation/upstream-warning-allowlist.json` | `9d79d5b080c0087dd0f144a89e7363e4e524e2a09dbb2e828173acb1dd315dc5` |
| `validation/upstream-warning-hook.cmake` | `16b42cd5a7aba52049aa4d623765a8764ac2e3e85367c9fbabdf67cbf42683f6` |
| Independent harness | `630111e6d18c164544a894c307f8f1552de68d29fd88360a95eeb7ffd786f42b` |

Evidence is in `practical-warning-exception-results.json`; the independent
exerciser is `practical-warning-exception-cases.py`. The raw result includes
disposable local fixture paths. The harness takes a fresh directory containing
the three exact validation files as its sole argument and requires Python and
Git. It creates a tiny local Git inventory solely to distinguish tracked and
untracked dependency paths. That fixture commit is explicitly substituted only
for command-inventory cases and is never claimed to be the AzerothCore pin.
These files are review evidence, not a replacement official acceptance judge.

## Exercised behavior

- The exact complete allowed diagnostic, CRLF output and ordinary interposed
  parallel progress pass. The permitted source filename containing `Warning`
  also passes when its object exists in the compile inventory.
- Missing or duplicate warnings, wrong path/line/column/parameter/function/
  category, unrelated compiler/driver/linker warnings and errors, missing or
  incorrect summaries, absent source context, and invented progress fail.
- Empty, truncated, non-UTF-8, ANSI/control/overwrite output, bad persisted or
  streaming hashes, incomplete capture and unsuccessful or invalid exit-status
  receipts fail.
- Actual `-c` input must match inventory metadata; candidate compilation must
  exist. Duplicate or out-of-build outputs, response files, absent Werror,
  extra demotion and core/candidate warning suppression fail.
- A real disposable Git inventory proves native `-w` for tracked dependency
  input passes, while `-w` for an untracked dependency input fails. Added blanket
  suppression, a second demotion or missing Werror still fail on tracked deps.
- Native `src/test` compilation without private Wall/Wextra inheritance passes;
  added test suppression fails. A game source missing native Wall fails.
- An absent/mismatched pinned dependency checkout fails identity validation.
  Successful complete real-pin checkout verification was not exercised locally.

## Independent source and integration review

Reviewed the complete six-file committed change, including the protected policy,
hook, capture implementation, selftest source, workflow and validation README.
`git diff --check` for the reviewed commit passed. Scope/source-binding,
candidate-coverage, suppression and forged-progress defects found in earlier
drafts were fixed before this exact-commit rerun.

The pinned AC `ConfigureBaseTargets.cmake` creates warning-enabled core and
warning-disabled third-party interfaces. Exact pinned fmt, g3dlite and SFMT
targets use the latter; common/game/database/shared use the former. Pinned
`src/test/CMakeLists.txt` does not directly inherit the private core warning
interface. The final verifier preserves these native distinctions while keeping
global Werror and strict candidate checks. This avoids misclassifying an
unchanged upstream build setting as the newly authorized exception.

Policy values match the independently retrieved pinned Playerbots file:
commit `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, blob
`7688e6d4c04f246c87bf80881c238ba2c6bb0a3c`, SHA-256
`6ad2a48db1f191b2ce6008fbd6d9b2c2f492438965a5211c38ab2b348f2d693c`,
physical line 107, column 60, `GetShahrazTankPositionState`, unused `botAI`.

The hook changes a source compile property and does not rewrite dependency
files. The build capture independently hashes received process bytes and the
persisted log. The workflow invokes default-branch protected files, hashes them
into evidence, runs the mandatory real Clang integration preflight, and retains
the later complete build/install/SQL/config/startup/unit-test/integrity stages.
The README explicitly retains independent source review for executable module
build hooks and does not claim hostile same-user build logic is sandboxed.

## Required external evidence remains pending

The actual Ubuntu Clang 18 integration probe must pass in the new official run.
The tamper control must fail for the intended integrity reason, and the unchanged
clean control must pass every applicable stage at its exact candidate SHA.
The previously failed run remains failed. No clock or gameplay implementation
was changed by this audit.
