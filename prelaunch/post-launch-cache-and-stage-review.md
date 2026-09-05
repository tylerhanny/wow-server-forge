# Bounded post-launch cache and existing-stage review

The successful complete control `33947235843` is preserved. Both gameplay
builders are active; this review introduces no implementation prerequisite.

## Concrete cache defect and focused correction

The successful run installed ccache `4.9.1-1`. The old workflow exported
`CCACHE_DIR=$GITHUB_WORKSPACE/.ccache` only in the configure shell and set its
size there. Compilation happened in a subsequent shell through the protected
Python wrapper, so that export did not reach the actual compiler launcher.
No cache action persisted either directory. The run did not capture statistics,
so there is no claim that any previous run obtained useful cache hits.

The focused workflow change puts cache, temporary and configuration paths in
job environment variables used by every step. An existing GitHub cache action
restores compiler results and saves them only after job success. Keys include
the exact pins, OS/architecture and protected validation/workflow content;
per-run/candidate suffixes permit a new immutable snapshot, with restoration
from the matching policy prefix. Configure, source/command provenance, complete
compiler-log capture, linking, installation, runtime and tests still execute.
No step skips on a cache hit and no prior verdict is reused.

The fresh runner-local configuration hashes compiler contents, uses actual
preprocessing output for lookup, compiles original source on misses, and
enables no sloppiness or path rewriting. Cached diagnostics remain visible to
the unchanged full-log verifier. Preprocessing temporary files reside under
the runner temporary directory, outside the sole persisted cache directory;
source/build trees and the corrected WorldMock header are not cached. The
existing exact fixture application, compiled identity, verification and
restoration remain unchanged. Configuration and hit/miss statistics are saved
with the existing evidence artifact.

The [ccache 4.9.1 manual](https://ccache.dev/manual/4.9.1.html) documents compiler
content checking, preprocessing lookup, original-source compilation on misses,
temporary directories and diagnostic behavior. The
[GitHub cache action](https://github.com/actions/cache) documents restore-key
matching and saving after successful jobs. The cache remains subject to the
existing independently reviewed build-hook trust boundary; it does not sandbox
arbitrary candidate build hooks.

## Existing remaining stages considered together

The actual successful control exercised configuration and native module
discovery, full warning/provenance enforcement, the exact WorldMock delta,
restoration, install, empty-SQL handling, disposable DB/config initialization,
both dry-runs, the unfiltered native unit command and final integrity. No
remaining contradictory setting was identified for that verified smoke path.

For the two active candidates, the existing independent review still needs to
inspect their actual config/data/SQL and lifecycle. Static SQL screening alone
does not establish module data semantics. Dry-run exits before OnStartup and
world updates, and the zero-population fixture does not validate bot gameplay.
These are existing evidence limits, not newly added stages or gates. Native
parameter skips and the pre-existing disabled ASan-only unit test remain fully
disclosed in the clean-control record; no test-selection change is proposed.

Local verification: YAML parsing and the existing 17 shell syntax checks pass,
exact dependency pins and global `-Werror` flags remain unchanged, and the
full post-build acceptance sequence is unchanged apart from recording ccache
statistics. No local Linux compiler or ccache execution was available. Actual
warm-cache hit rate, warning replay and timing remain to be observed on the
next needed candidate run; no duplicate full control is requested.
