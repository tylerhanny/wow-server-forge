# WoW Server Forge — Hard Deadline Policy

The sprint clock starts only when the Director explicitly launches the run by replacing `RUN_STATE.md` with real timestamps.

Setup time before that does not consume the 36-hour sprint.

## Required phases

At launch, calculate and record exact ISO-8601 timestamps for:

```text
START
CONVERGENCE_START = START + 24 hours
HARVEST_START     = START + 30 hours
HARD_DEADLINE     = START + 36 hours
```

Use UTC in machine-readable state and include America/New_York equivalents for Tyler's convenience.

## Phase A — BUILD

From START through hour 24.

Goals:

- research pinned capabilities;
- invent/select projects;
- implement aggressively;
- compile early and repeatedly;
- independently review promising candidates;
- finish as many strong vertical slices as possible.

New projects are allowed when the Director estimates a credible path to completion.

Do not hoard ideas. Do not continue a weak project merely because work was already spent on it.

## Phase B — CONVERGENCE

Hour 24 through hour 30.

Default rule: no large/high-risk new implementation projects.

For every active project, the Director must choose one:

1. FINISH — complete the current scope;
2. CUT — reduce to a smaller coherent V1 that can pass the finish gate;
3. ABANDON — archive useful notes and free the agent.

Reviewer/Closer priority increases substantially.

The objective is to turn promising work into complete candidates, not broaden features.

A small low-risk project may still start only if the Director has high confidence it can pass the full gate before HARVEST_START without endangering stronger candidates.

## Phase C — HARVEST

Hour 30 through hour 36.

ABSOLUTELY NO NEW IMPLEMENTATION PROJECTS.

Allowed work:

- compiler/build fixes;
- integration corrections inside existing projects;
- SQL/config/data completion;
- deterministic validation;
- disposable install/startup checks;
- independent code review;
- review fixes;
- documentation;
- Git cleanup/checkpoints;
- classification into HARVEST/BLOCKED/IDEA_VAULT;
- final reporting.

Do not add major optional features during Harvest.

If a project cannot pass the finish gate before the deadline, stop pretending it will. Preserve it honestly as blocked/research and spend remaining capacity closing stronger candidates.

## Hard deadline behavior

At HARD_DEADLINE:

- stop starting or expanding implementation work;
- do not present unfinished work as ready;
- finalize `HARVEST.md`, `BLOCKED.md`, and `IDEA_VAULT.md`;
- preserve branch/commit identifiers and evidence;
- produce the final concise Forge report.

The repository may contain segregated research branches, but the final harvest must be unambiguous.

## Deadline optimization rule

The deadline is a product requirement.

Always optimize for the maximum quality-adjusted number of COMPLETE, runnable, test-ready candidates at the hard deadline — not maximum code written or maximum projects started.

When forced to choose:

```text
complete smaller V1 > ambitious incomplete implementation
finish existing winner > begin speculative replacement
verified build > unverified extra feature
honest blocker > fake success
```

## Completion-probability policy

The Director should continually reassess active work.

Suggested threshold behavior:

- Build phase: calculated experiments are acceptable.
- Final 6 hours of Build: strongly favor credible completion paths.
- Convergence: require high confidence or cut scope.
- Harvest: completion work only.

No exact numerical estimate is required, but the Director should make the tradeoff explicit in project notes when the decision is non-obvious.
