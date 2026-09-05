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

Current Wildcard disposition: **SELECTED FOR LAUNCH — Stormwright (`mod-stormwright`)**.
Five-option tournament, Director comparison, independent Reviewer quality/one-human
dispositions and Wildcard's final creative choice are recorded in
`decisions/initial-project-selection.md` and `prelaunch/wildcard-final-choice.md`.
The complete Solo Pilot/ordinary-bot paths are mandatory. Implementation is active after current clean33947235843 reached a terminal result under the owner sequencing amendment. Hunt Rhythm (`mod-hunt-rhythm`) is the distinct Practical
launch choice with independent solo-path proposal approval. Both approved lanes have been released for actual module implementation.
The Small Council is **NOT APPROVED** and is retained only in `IDEA_VAULT.md`.

Wildcard selection records must cover all five concepts and eleven fields, compare the
shortlisted three against the quality dimensions and mandatory YES tests, record Director and
Reviewer dispositions, and preserve Wildcard's own final choice/rationale. Use
SELECT / REJECT / FRESH_PASS. The approved first assignments begin after the current control terminates, regardless of its outcome; acceptance remains independent.
The first flagship must pass independent review and the official gate before Wildcard begins
another project, and BUILD must still permit it.

## Claimed projects

| Project | Owner | Branch/worktree | Claim time | Finish-gate target | Status |
|---|---|---|---|---|---|
| mod-hunt-rhythm | Practical | project/hunt-rhythm / .worktrees/practical | 2026-09-05T06:40:42Z | Complete solo loop and full independent acceptance | READY_FOR_HARVEST — exact4aaa3ae; official run33951428776 and independent evidence PASS; delivered early |
| mod-stormwright | Wildcard | project/stormwright / .worktrees/wildcard | 2026-09-05T06:40:42Z | Complete Solo Pilot flagship and full independent acceptance | READY_FOR_HARVEST — exact60c6a91; official33960843535 and independent source/artifact/one-human PASS; delivered early; earlier failures preserved |
| mod-field-camp | Practical | project/field-camp / .worktrees/field-camp | 2026-09-05 BUILD, decision in decisions/field-camp-selection.md | Complete safe solo supply-trip loop and full acceptance | READY_FOR_HARVEST — exact796e27e; official33955341216 and independent review PASS; delivered early; subordinate |
| mod-field-repairs | Practical | project/field-repairs / .worktrees/field-repairs | 2026-09-05T13:27:10Z owner authorization | Complete frozen candidate by22:34:32Z today; full independent acceptance | BUILDING — decisions/field-repairs-selection.md and independent proposal review recorded; Director/Reviewer PASS before code |
| mod-triage-night | Wildcard | project/triage-night / .worktrees/triage-night | 2026-09-05T13:27:10Z owner authorization | Complete frozen candidate by22:34:32Z today; full independent acceptance | BUILDING — decisions/triage-night-selection.md preserves full five/three tournament, Director/Reviewer PASS and Wildcard choice before code |

These consume the entire additional-project authorization. No further project/substitute;
accepted Hunt Rhythm, Stormwright and Field Camp remain frozen except owner-reported fixes,
which immediately preempt the additions. Complete proposal dispositions are recorded in the two decision files and
reviews/additional-project-proposal-review.md; authorization does not certify code or waive any gate.

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
One-human qualifying path (solo or human-plus-bots):
Human custom actions and bot/helper responsibilities:
Why ordinary pinned bot behavior suffices:
Difficulty/enemy scaling and no-bots behavior:
Complete primary loop including outcome/retry/abort:
Bot assumptions pending live/in-game validation:
Director and independent Reviewer one-human design dispositions:
Decision: BUILD / SCOUT / DEFER
```

## Queue discipline

- All lanes must pass locked `ONE_HUMAN_PLAYABILITY.md` before implementation approval.
  Stormwright, Holdfast, Warband Arena and Hunt Rhythm require explicit reassessment.

- Do not duplicate an actively claimed concept without a Director decision.
- Prefer one owner per project.
- Builders should hand completed candidates to Reviewer rather than endlessly polishing their own work.
- If blocked, either cut to a coherent smaller V1 or move to `BLOCKED.md`/`IDEA_VAULT.md` and release the worker.
- During CONVERGENCE, the queue should shrink.
- During HARVEST, this file must receive no newly started implementation project.
