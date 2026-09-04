# Protected exact-warning validation

This is the **explicit owner-authorized upstream-baseline exception** defined in
UPSTREAM_WARNING_EXCEPTION.md. Failed run 33911646203 remains failed. Only the
protected default-branch copies of these files are authoritative.

The allowlist fixes the Playerbots commit, source Git blob, raw SHA-256, physical
line, function signature, parameter, diagnostic category, and count of one.
The identity command checks pinned checkouts and clean tracked trees before
configure. The external CMake hook changes only that verified source's compile
options in the directory creating the modules target. It edits no dependency
source, disables no warning, and demotes no candidate warning. Global -Werror,
WITH_WARNINGS, and all later gate stages remain.

Generated compile commands bind the actual -c input to source metadata, use the
selected compiler, preserve general -Werror, compile the named candidate, and
place the sole demotion only on the authorized source. Compiler outputs bind
ordinary progress messages to the inventory. Candidate/core warning suppression
is rejected. The pinned acore-dependency-interface intentionally uses -w for
third-party dependencies: only source files actually tracked under the core pin's
deps/ may retain that existing setting. Pinned src/test/ translation units do
not necessarily inherit -Wall/-Wextra; their existing configuration is preserved,
including global -Werror. Candidate translation units still require all three.

The wrapper directly captures complete stdout plus stderr and independently
hashes bytes as they arrive. Log-write/output failures, nonzero build status,
incomplete receipts, altered/truncated logs, changed source/command identity,
absent/duplicate diagnostics, mismatched context or warning summaries, and every
other warning/error fail. Plain output is requested; terminal controls are rejected.
The permitted warning stays visible in the raw log, artifact, JSON verdict, and
official summary. Ordinary parallel progress may interpose between header and
source excerpt; invented compiler outputs are not accepted as progress.

The workflow hashes the policy, parser, CMake hook, tests, owner authority and
workflow into evidence, and checks identities after configure, build and runtime.
Source/log receipts are checked again by later integrity steps.

Run local parser, Git-identity and command-provenance tests with:

    python3 -B validation/test_verify_build.py

The protected Ubuntu preflight must also run:

    python3 -B validation/test_verify_build.py --integration

The integration option requires actual CMake and Clang 18. It configures and
compiles a small disposable fixture with the real hook, verifies option scope,
observes its one warning, then proves a candidate unused-parameter warning stays
fatal. That fixture is not a full pinned-server build. A host without these tools
can run the other tests, but cannot claim the real compiler probe passed. Official
CI runs it before the full pinned build.

Native optional candidate CMake hooks remain supported and require independent
source review. These checks do not sandbox arbitrary malicious same-user hooks
that can rewrite the runner, compiler or verifier. Hashes, source/command binding
and streamed-log checks detect specific tampering; they are not complete isolation
of hostile executable build logic. No new upstream diagnostic is auto-allowlisted.

Failed builds retain their original FAIL status and reason. Their verdict additionally
reports observed diagnostic headers and the next two raw context lines so the existing
job summary displays the actual warning/errors. Capture status is verified only when
capture completion, exit-status presence, raw and streamed hashes, final newline and text
integrity all agree. Missing, stale, partial or invalid captures are explicitly labelled
NON-AUTHORITATIVE. Even verified observations do not establish source identity or acceptance;
the unchanged acceptance checks remain the sole authority. This reporting correction does
not pass failed run 33922537362 or authorize its new upstream diagnostics.
