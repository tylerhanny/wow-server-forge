# Protected upstream warning provenance

UPSTREAM_WARNING_POLICY.md is the current standing owner authority. The former single
BTHelpers warning limit is superseded; its historical runs remain failed. Only protected
default-branch policy, source-inventory construction, compiler integration and verifier
files are authoritative. Candidate changes to these paths fail the existing scope gate.

Before configure, the verifier checks exact AC/Playerbots HEADs and clean tracked trees,
enumerates source/header files from the pinned Git trees, and verifies each working file's
raw Git blob and SHA-256. The resulting inventory records repository, commit, relative
path, blob and raw hash. Untracked, copied, generated or aliased files acquire no upstream
trust. The same identity checks run before/after compilation and in existing later checks.

The CMake hook adds -Wno-error only to verified upstream SOURCE properties in each target's
defining directory. It never demotes the combined modules target. General -Werror and
WITH_WARNINGS remain; project/generated translation units retain strict flags. Existing
pinned third-party -w conventions are preserved without adding suppression. All actual
compiler inputs/outputs and option scope are verified from compile_commands.json.

Compile-only Clang physical-location flags ignore #line aliases and retain complete macro
and template backtraces. Each warning's physical file/line must resolve to verified raw
upstream bytes. Project/unknown diagnostic notes make macro provenance ambiguous and fail.
Project headers included by an upstream translation unit therefore cannot inherit warning
acceptance. Candidate includes are checked for reachable generated headers that use warning
pragmas or GNU system linemarkers to hide diagnostics. Input remapping and non-native system
include options fail closed. Native vendor directories are not labelled project code merely
because they live in the build tree.

A warning in an upstream header included by a strict project translation unit may still be
promoted to a compiler error. This conservative compiler behavior is not an owner-approval
blocker: if encountered, resolve it within the standing authorization while retaining every
project warning failure. No error is silently waived and no retry/demotion is implicit here.

The entire merged compiler output, independently streamed byte hash, persisted log hash,
exit code and pre/post source identities are retained. Successful full capture may contain
zero or multiple exclusively verified upstream warnings; observed counts must match Clang
summary totals. Every authorized warning is listed with provenance/context in the JSON
verdict displayed by the existing job summary. Every other warning/error, ambiguous origin,
missing/incomplete capture or changed identity fails. Failed verdicts retain the original
reason and observational diagnostics; invalid captures are explicitly non-authoritative.

Run local regressions with `python3 -B validation/test_verify_build.py`. The official Ubuntu
workflow runs `--integration` before the full build: actual Clang/CMake source scope, project
warning failure, project headers under upstream compilation, #line spoofing, mixed macro
origin and the conservative upstream-header/project-TU boundary. A local machine without
CMake/Clang must not claim this probe ran. No separate full control or extra launch gate is
introduced. Install, config/SQL/data, runtime, unit-test and tamper requirements remain.

These checks do not sandbox malicious same-user CMake/build hooks that rewrite the compiler,
verifier, native vendor material or the runner itself. Independent candidate source review
remains necessary. Dynamic/computed project includes require explicit provenance rather
than assumed ownership. This limitation does not authorize hidden project warnings.

The exact owner-authorized `WORLDMOCK_FIXTURE_EXCEPTION.md` is the sole test-source
exception. `worldmock-fixture.json` and `worldmock-fixture.patch` bind the original and
corrected header hashes and the exact two mock declarations. Before configuration, the
original complete pinned inventory is verified and the correction is checked only in
memory. Immediately before the existing full build, the protected wrapper writes the
corrected header only inside the disposable Linux GitHub Actions job. No complete corrected
header is copied to evidence, installed, committed, or exported in artifacts/cache.

After the build, the wrapper verifies the exact corrected header and every other tracked
dependency file before restoring the original header for the existing install/runtime
stages. The receipt and visible verdict separately record application, whether the build
started, the verified compiled delta, and restoration. Restored clean bytes never imply
that the unmodified fixture was compiled. Every build-log recheck excludes WorldMock from
unchanged-upstream warning eligibility even after restoration. Original source inventory
identities remain complete; the diagnostic-eligible inventory omits this corrected fixture.

Only the small approved patch and identity metadata are exported. The complete upstream
unit-test executable, direct unfiltered test invocation, production code, Playerbots,
both pins, assertions, coverage and all later checks remain unchanged. The fixture exception
is not a warning waiver or an exception for any other source modification or actual error.
