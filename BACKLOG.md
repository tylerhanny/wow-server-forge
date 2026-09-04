# WoW Server Forge — Backlog

This file is a living Director-owned queue, not a locked product specification.

Do not treat example ideas as mandatory. The forge is allowed to discover better ideas.

## Status vocabulary

```text
IDEA
SCOUTING
CLAIMED
BUILDING
BUILD_FAILED
REVIEW
FIXING
READY_FOR_HARVEST
BLOCKED
ABANDONED
RESEARCH_ONLY
```

## Initial practical candidates

These are seed ideas only. Score feasibility before claiming them.

| Candidate | Intent | Initial lane | Status |
|---|---|---|---|
| World Director | Dynamic server/world events using existing client assets and clean module hooks | Practical | IDEA |
| Adventure Contracts | Repeatable bounties/contracts/challenges with server-side tracking and rewards | Practical | IDEA |
| Dungeon Challenge | Replayable WotLK dungeon challenge mode with scalable difficulty/timers/affixes if cleanly feasible | Practical | IDEA |
| Event Master | Native GM/event orchestration tools for waves, hunts, races, scavenger events, or similar activities | Practical | IDEA |
| Challenge Modes | Opt-in rulesets/records such as Ironman or other constrained play challenges | Practical | IDEA |
| Rare / Treasure Hunts | Server-side exploration, clues, hunts, rotating treasures or rare encounters | Practical | IDEA |

## Wildcard allocation

At least one substantial project-selection cycle belongs to the Wildcard lane with NO requirement to choose from the table above.

Wildcard independently inspects feasible pinned hooks/mechanics and generates at least five
mechanically distinct concepts under `WILDCARD_AUTEUR.md`, shortlists three for Director
and Reviewer evaluation, and chooses among passing options. The comparison, dispositions,
selected concept and final rationale must be recorded before substantive
implementation. If none clears the bar, repeat fresh ideation. Creative independence remains;
flavor-first novelty is insufficient.

Do not contaminate every Wildcard cycle with the practical seed list. Periodically allow a fresh conceptual pass from the technical constraints alone.

Current Wildcard disposition: **SCOUTING — fresh comparative pass required**.
The Small Council is **NOT APPROVED** and is retained only in `IDEA_VAULT.md`.

Wildcard selection records must cover all five concepts and eleven fields, compare the
shortlisted three against the quality dimensions and mandatory YES tests, record Director and
Reviewer dispositions, and preserve Wildcard's own final choice/rationale. Use
SELECT / REJECT / FRESH_PASS. No Wildcard implementation is currently approved.
The first flagship must pass independent review and the official gate before Wildcard begins
another project, and BUILD must still permit it.

## Claimed projects

| Project | Owner | Branch/worktree | Claim time | Finish-gate target | Status |
|---|---|---|---|---|---|
| — | — | — | — | — | — |

## Project decision template

Before substantial implementation, record a compact decision note in the project README or coordination commit:

```text
Project:
Lane:
Gameplay value:
Novelty:
Pinned-API feasibility:
Technical risk:
Smallest worthwhile V1:
Estimated completion confidence before current deadline boundary:
Decision: BUILD / SCOUT / DEFER
```

## Queue discipline

- Do not duplicate an actively claimed concept without a Director decision.
- Prefer one owner per project.
- Builders should hand completed candidates to Reviewer rather than endlessly polishing their own work.
- If blocked, either cut to a coherent smaller V1 or move to `BLOCKED.md`/`IDEA_VAULT.md` and release the worker.
- During CONVERGENCE, the queue should shrink.
- During HARVEST, this file must receive no newly started implementation project.
