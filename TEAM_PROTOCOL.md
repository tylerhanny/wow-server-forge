# WoW Server Forge — Team Protocol

**Status: ACTIVE AUTHORITY**

This file defines how the persistent Codex threads work as one autonomous team without relying on shared chat history.

## Team topology

The Forge uses four persistent top-level Codex threads:

1. **Director / Producer** — owns mission, clock, priorities, assignment, scope cuts, and final harvest.
2. **Practical Builder** — builds high-value, high-probability complete modules.
3. **Wildcard Designer / Builder** — independently invents and builds surprising systems within the hard technical envelope.
4. **Reviewer / Closer** — independently evaluates, breaks, fixes, validates, and closes candidates.

Top-level threads may spawn bounded subagents when useful. Subagents do not become new project owners unless the Director explicitly changes ownership.

## How the agents communicate

Separate Codex chats do **not** share private conversational history. Repository state is the durable team memory.

Every resumed thread must begin by fetching current repository state and rereading the authority/state files relevant to its lane.

Durable communication occurs through:

- `RUN_STATE.md` — sprint clock, phase, and lane ownership;
- `BACKLOG.md` — prioritized/claimed work;
- `handoffs/` — project-specific implementation/review handoffs;
- project branches and commits — actual implementation evidence;
- `BLOCKED.md` — genuine blockers;
- `IDEA_VAULT.md` — worthwhile deferred research;
- `HARVEST.md` — only finish-gate-approved candidates.

Never rely on a statement like "another agent said it passed" when source, commits, CI, or review evidence can be inspected directly.

## Local parallelism and worktrees

The four persistent chats must not edit the same working tree concurrently.

Use separate Git worktrees/branches. Recommended lane layout:

```text
main                         Director coordination only
lane/practical               Practical lane staging
lane/wildcard                Wildcard lane staging
lane/reviewer                Reviewer/Closer staging
project/<slug>               Candidate implementation/review branch
```

A persistent lane may create or switch into project-specific worktrees as needed. It must never reset, clean, overwrite, or discard another lane's unexplained work.

## Main branch ownership

Normal builders do not push directly to `main`.

`main` is reserved for:

- Director coordination/state commits;
- pre-sprint/Reviewer validation-authority changes;
- accepted administrative merge/integration changes.

Practical and Wildcard submit implementation on project branches. Reviewer performs independent review on those candidate commits/branches and does not weaken the official gate.

## Candidate handoff format

Each active candidate should have:

```text
handoffs/<project-slug>.md
```

Minimum content:

```text
PROJECT=<slug>
OWNER=<lane>
BRANCH=<branch>
CANDIDATE_SHA=<sha or UNSET>
STATE=BUILDING|READY_FOR_REVIEW|CHANGES_REQUESTED|VALIDATING|READY_FOR_HARVEST|BLOCKED
CLAIMED_SCOPE=<short exact scope>
BUILD_RESULT=<actual evidence or NOT_RUN>
OFFICIAL_GATE=<PASS|FAIL|NOT_RUN>
REVIEWER=<reviewer state>
NEXT_ACTION=<single highest-leverage next action>
```

The body should also list known limitations, exact validation already performed, and unresolved risk.

## Assignment behavior

The Director may assign explicit projects through `RUN_STATE.md`/`BACKLOG.md`.

When a builder becomes idle and BUILD phase still permits new work, it may claim an unclaimed high-priority project consistent with its lane, record that claim durably, and proceed rather than waiting for Tyler.

Wildcard retains independent idea-generation authority and is not required to pick from the seeded practical backlog.

## Handoff behavior

When a builder believes a candidate is ready:

1. Commit all intended candidate changes.
2. Push the project branch.
3. Record exact candidate SHA in its handoff.
4. Mark `STATE=READY_FOR_REVIEW`.
5. Stop self-certifying and move the candidate to Reviewer ownership for official disposition.
6. While BUILD phase permits, the builder may begin another Director-approved/claimed project without waiting for review, provided project ownership remains isolated.

Reviewer then:

1. fetches the exact candidate SHA;
2. inspects source/diff;
3. runs or examines the independent official gate;
4. makes project-code fixes on a review/project branch when appropriate;
5. records new candidate SHA after any fix;
6. reruns the official gate;
7. marks the candidate `READY_FOR_HARVEST` only after all mandatory evidence is real.

## Collision prevention

Before substantive work, every lane must:

1. `git fetch` current remote state;
2. inspect `RUN_STATE.md`, `BACKLOG.md`, and active handoffs;
3. confirm nobody else owns the same project;
4. operate only in its own worktree/project branch.

If a collision is discovered, preserve both branches and let the Director choose the canonical path. Never erase one to make the tree look clean.

## Phase behavior

### BUILD

Parallel invention/implementation/review is encouraged. Practical and Wildcard may continuously hand completed candidates to Reviewer and start another credible project.

### CONVERGENCE

New ambitious projects stop. Director reallocates lanes toward the strongest closable candidates. Scope may be reduced to coherent V1s.

### HARVEST

No new projects. Practical, Wildcard, Reviewer, and Director all become closers: fix, validate, document, and truthfully classify existing work only.

### COMPLETE

No feature work. Finalize `HARVEST.md` and preserve blocked/research state.

## Autonomous behavior

Do not stop for ordinary design choices, routine compilation failures, review findings, or project reprioritization. Resolve them using the authority hierarchy and repository evidence.

A genuine blocker in one project is not a blocker for the Forge. Park it and redirect capacity.

The team objective is a clean shelf of complete, runnable candidates at the deadline, not a large number of started branches.
