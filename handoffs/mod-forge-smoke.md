PROJECT=mod-forge-smoke
OWNER=Practical
BRANCH=project/forge-smoke-clean
CANDIDATE_SHA=UNSET
STATE=READY_FOR_REVIEW
CLAIMED_SCOPE=Minimal prelaunch module discovery/config-load control; no gameplay feature
BUILD_RESULT=NOT_RUN
OFFICIAL_GATE=NOT_RUN
REVIEWER=PENDING
NEXT_ACTION=Dispatch the official default-branch gate against the exact pushed candidate SHA

The control registers only `WorldScript::OnAfterConfigLoad` and `OnStartup`.
Canonical initial config evidence is
`FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159`. The compiled defaults are
zero, so the non-default values distinguish configuration acceptance from hook
execution alone. The second `FORGE_SMOKE_STARTUP` marker is expected only for a
regular startup; pinned `--dry-run` exits before that hook.

Exact dependency pins, installation instructions, source references, limitations,
and honest validation status are in the project README and VALIDATION.md.
No SQL, custom CMake, authority files, workflow changes, dependency changes, or
live-server access form part of this candidate. This is a disposable prelaunch
control, not a harvestable gameplay project.

The exact immutable submission SHA will be reported to the Director after the
commit; the Director/Reviewer must bind external gate evidence to that SHA.
