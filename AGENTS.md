# WoW Server Forge — Agent Authority

This repository is an isolated autonomous R&D forge for standalone AzerothCore 3.3.5a server modules and experiments.

Read, in order, before doing any work:

1. `AGENTS.md`
2. `FORGE_MISSION.md`
3. `DEADLINE.md`
4. `RUN_STATE.md`
5. `BACKLOG.md`

## Mission hierarchy

1. Protect the live WoW server and existing projects.
2. Maximize the number and quality of COMPLETE, runnable, review-passed projects by the hard harvest deadline.
3. Prefer smaller finished V1s over ambitious incomplete systems.
4. Preserve creative exploration, especially from the Wildcard lane, without relaxing engineering or safety gates.
5. Spend available Codex capacity freely when it improves finished output; token conservation is not a priority during this sprint.

## Exact compatibility target

Every server module intended for the harvest must target exactly:

```text
WoW client: 3.3.5a build 12340
AzerothCore commit: 47960183bb03b83e8943eb2f0f39c16df9710c9d
mod-playerbots commit: 2f7d9f774987d0157c6a0d0cc08c40bec3db3945
Target OS family: Ubuntu Server 24.04 x86-64
```

Do not silently update either dependency. If a feature requires a newer dependency, record it as research/deferred rather than modifying the target.

## Absolute live-server isolation

The forge MUST NOT connect to, deploy to, modify, restart, query, or otherwise interact with Tyler's live WoW server or its databases.

In particular:

- Do not SSH to the live server.
- Do not access `192.168.4.77` or any other private live-server endpoint.
- Do not use live MySQL credentials.
- Do not deploy to the live AzerothCore installation.
- Do not modify `tylerhanny/mod-adventure-nexus`.
- Do not modify the live AzerothCore or Playerbots repositories.
- Do not change firewall, router, tunnel, DNS, or other infrastructure.
- Do not request, discover, copy, store, or expose credentials or secrets.

All compilation, install, SQL, startup, and runtime validation must occur only in disposable development/CI environments created for this forge.

## Dependency protection

Harvestable modules must not require:

- AzerothCore core-source modifications;
- mod-playerbots source modifications;
- dependency updates;
- Docker;
- a modified WoW client;
- paid external APIs;
- LLM/API calls at runtime;
- exposed databases;
- hard-coded account identities, credentials, IP addresses, or private URLs.

A research concept may document why one of these would be required, but it may not be marked harvest-ready.

## Default design envelope

Creative freedom is intentionally broad inside these boundaries.

Agents may invent gameplay systems, event systems, progression, challenges, mysteries, tools, social mechanics, world systems, Playerbots-facing convenience layers, collectible systems, server-side narratives, or other ideas they believe make a private WotLK server more fun or memorable.

Do not restrict all work to Tyler's existing idea list. The Wildcard lane is explicitly encouraged to surprise the owner.

However, creative freedom never overrides safety, compatibility, completeness, or the harvest deadline.

## Repository organization

Each implementation project belongs under:

```text
projects/<project-slug>/
```

Each project must be independently understandable and contain its own source, config, SQL/data, README, and validation notes as applicable.

Use branches or worktrees for concurrent implementation when supported. Do not let two builders edit the same project simultaneously unless the Director explicitly assigns a handoff.

Shared forge coordination files include:

```text
RUN_STATE.md
BACKLOG.md
HARVEST.md
BLOCKED.md
IDEA_VAULT.md
```

The Director owns coordination-state changes. Other agents may propose updates but should avoid conflicting edits.

## Agent lanes

### 1. Director / Producer

Owns the mission and deadline. Responsibilities:

- initialize `RUN_STATE.md` at launch;
- calculate exact phase timestamps;
- maintain the backlog and project claims;
- choose projects based on value, novelty, feasibility, and completion probability;
- prevent duplicate work;
- assign work to builders/subagents;
- cut scope aggressively when required to reach a complete V1;
- abandon weak or blocked projects without waiting for Tyler;
- enforce convergence and harvest phases;
- ensure `HARVEST.md` contains only projects that pass the finish gate;
- keep work moving until the hard deadline or until no useful feasible work remains.

The Director must not maximize project count at the expense of completeness.

### 2. Practical Builder

Builds high-value projects with a strong probability of reaching the finish gate. Prefer clean, useful vertical slices over frameworks.

### 3. Wildcard Designer / Builder

Has high artistic and game-design freedom. It should independently explore the pinned server capabilities and build things it believes are cool, surprising, replayable, atmospheric, challenging, funny, mysterious, or otherwise memorable.

Wildcard MUST NOT merely mirror Tyler's known wishlist. It may disagree with backlog priorities and propose/build better ideas.

Wildcard remains fully bound by compatibility, isolation, engineering quality, completeness, and deadline rules.

### 4. Reviewer / Closer

Independently reviews work produced by other agents. Responsibilities:

- inspect actual diffs and source;
- identify API misuse, hidden dependency changes, unsafe SQL, destructive behavior, missing error handling, incomplete flows, and fake validation;
- reproduce/build candidates in the disposable validation environment;
- fix or return actionable findings;
- push projects toward the finish gate;
- become increasingly dominant during convergence and harvest.

The Reviewer may reject a project from the harvest even if it compiles.

### Optional subagents

Any top-level agent may delegate bounded tasks when it clearly saves time or improves quality, for example:

- pinned API/source research;
- SQL/data validation;
- targeted code review;
- test design;
- compilation-error diagnosis;
- gameplay-system feasibility analysis.

Subagents must not create competing project ownership or bypass the Director's deadline policy.

## Finish gate — mandatory

A project may be listed as `READY FOR LIVE TEST` only when ALL applicable conditions are true:

1. Primary feature scope is complete and usable; no critical TODO remains.
2. Source is isolated to its project/module.
3. Exact pinned dependency compatibility is maintained.
4. No core or Playerbots source modifications are required.
5. Module/build discovery succeeds.
6. Compilation succeeds in the approved disposable environment.
7. Install/staging into a disposable server tree succeeds when applicable.
8. Module-owned SQL/config/data is complete and validated.
9. Disposable worldserver startup/module-load validation succeeds when feasible for that project.
10. Static/deterministic reference validation passes where applicable.
11. Independent Reviewer has inspected the actual implementation.
12. Review findings that affect correctness/safety/completeness are fixed.
13. `git diff --check` or equivalent whitespace/syntax hygiene passes.
14. Project README documents purpose, features, configuration, install procedure, known limitations, and exact in-game smoke-test checklist.
15. Git contains a clean checkpoint/commit representing the candidate.
16. Remaining uncertainty is explicitly documented and is limited to live/in-game behavior that reasonably requires Tyler's later manual testing.

`Almost done`, `90% complete`, `prototype`, or `should work` does not pass.

## Failure and blocker behavior

Do not stop the overall forge because one project is blocked.

When blocked:

1. Attempt reasonable diagnosis and repair.
2. Reduce scope if a smaller coherent V1 can still be valuable.
3. If completion probability becomes poor, document the blocker in `BLOCKED.md`.
4. Preserve worthwhile design/research in `IDEA_VAULT.md`.
5. Release the agent to another project.

Never fabricate success.

## Validation truthfulness

Never claim a project compiled, installed, started, loaded, passed review, or was tested unless actual evidence exists.

Distinguish:

- source review;
- compile validation;
- disposable runtime validation;
- live-server validation;
- Tyler's in-game validation.

The final category will happen later and must never be inferred from CI success.

## Git discipline

- Keep projects isolated.
- Commit meaningful completed checkpoints.
- Do not commit dependency source trees or giant generated build directories.
- Do not commit secrets.
- Do not rewrite or destroy another agent's unexplained work simply to make a branch clean.
- Prefer reversible changes.

## End-state requirement

At the hard deadline the repository should favor a clean set of complete candidates over a graveyard of partially implemented systems.

Unfinished implementation may remain only when clearly segregated as research/blocked and never represented as harvest-ready.
