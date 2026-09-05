# WoW Server Forge — Mission

## Current owner sequencing and deadline

The controlling 2026-09-05 amendment in `AGENTS.md` / `DEADLINE.md` supersedes older
launch restrictions here. Finish current clean33947235843; after ANY terminal result start
approved Hunt Rhythm and Stormwright implementation, with Reviewer validation/repair in
parallel. Never idle both builders for another full control. Acceptance, one-human quality,
pins, source/isolation and exact WorldMock restrictions remain intact. Fixed provisional
deadline: 2026-09-06T18:34:32Z, from receipt2026-09-05T06:34:32Z, not implementation start.
Use recorded convergence/harvest timestamps; never extend the ceiling. Preserve truthful
results and existing start. No fresh tournament for the two approved assignments.


## Objective

Run an approximately 36-hour autonomous development sprint that produces the maximum useful set of COMPLETE, runnable, review-passed AzerothCore 3.3.5a projects for Tyler's private server.

The sprint is an R&D harvest, not deployment.

The output should be a shelf of high-quality candidates that Tyler can later install and test on the real server one at a time.

Every candidate must satisfy locked `ONE_HUMAN_PLAYABILITY.md`: a complete worthwhile
primary loop usable by Tyler alone or with normally controllable pinned Playerbots. No
other real person, second client or second operated account may be necessary. Keep the
actual mechanic and challenge; optional multiplayer enhances an already complete path.

## Success is measured by finished usable projects

Optimize for:

1. complete gameplay value;
2. successful pinned-build validation;
3. independent review quality;
4. low live-deployment risk;
5. novelty and fun;
6. maintainability;
7. number of finished candidates only after the above.

Do NOT optimize for:

- lines of code;
- project count alone;
- token conservation;
- giant speculative architectures;
- impressive unfinished prototypes;
- exhaustive test suites that delay playable output.

Five complete strong modules are better than fifteen half-built ones.

## Portfolio philosophy

Maintain a mixed portfolio.

### Practical lane

Favor systems with obvious usefulness and a high completion probability, such as server-side events, challenges, contracts, collections, world activities, progression, conveniences, replayability systems, GM/event tooling, or other ideas supported cleanly by the pinned APIs.

These examples are prompts, not a locked backlog.

### Wildcard lane

Reserve meaningful capacity for independent creative exploration.

Wildcard should ask:

> If I were designing a memorable private WotLK server with these exact technical capabilities, what would I build that the owner might not think to request?

It may pursue unconventional concepts after passing the mandatory Wildcard creative-quality
gate in `AGENTS.md` and `WILDCARD_AUTEUR.md`: at least five independent mechanically distinct
options, a shortlist of three evaluated by Director and Reviewer, and Wildcard's durable choice
among passing concepts before implementation. Selection requires strong gameplay,
replayability or sustained utility, meaningful server impact, differentiation, installation value,
and credible completion. Flavor-first systems, shallow novelty and one-use gimmicks do not pass.
If no option passes, generate another set rather than lowering the bar.

This is the AI Auteur / Flagship Gameplay lane: prioritize one standout complete module,
with repeated player value and a memorable visible demonstration. Keep selection bounded.
Another Wildcard project waits for the flagship's review and official-gate pass while BUILD
permits. Preserve the designer's voice; Director provides quality control, not taste imitation.

The experiment succeeds when at least some Wildcard output feels genuinely independent rather than another variation of the practical backlog.

## Project selection scoring

Before starting a substantial implementation, record a concise internal/project note with:

- player value / fun;
- novelty;
- feasibility on the pinned APIs;
- technical risk;
- expected implementation size;
- estimated probability of reaching the finish gate before the current phase deadline.
- exact one-human path, human/bot/helper roles, ordinary pinned behavior evidence,
  difficulty/enemy scaling, no-bots behavior, full-loop access/outcome/retry/exit, and
  remaining bot assumptions under `ONE_HUMAN_PLAYABILITY.md`.

As the sprint progresses, required completion confidence rises.

Early build phase may accept calculated risk.

Convergence should strongly prefer projects likely to finish.

Harvest may start no new implementation project.

## Scope rule

Every project should define the smallest version that is already worth installing and playing.

Complete that first.

Optional expansions may be added only when the base candidate already passes or is very close to the finish gate and the Director judges the deadline risk acceptable.

Do not build generalized frameworks before proving the actual gameplay loop.

## Validation target

The ideal pre-live validation chain is:

```text
spec/design
  -> implementation
  -> source review
  -> exact pinned compile
  -> fix loop
  -> config/SQL/data validation
  -> disposable install
  -> disposable worldserver startup/module load where feasible
  -> independent review
  -> documentation
  -> clean candidate commit
  -> READY FOR LIVE TEST
```

Tyler's later in-game test is intentionally outside the autonomous sprint.

## Compatible target

```text
AzerothCore 47960183bb03b83e8943eb2f0f39c16df9710c9d
mod-playerbots 2f7d9f774987d0157c6a0d0cc08c40bec3db3945
WoW 3.3.5a build 12340
Ubuntu 24.04 family
```

## Existing project separation

Adventure Nexus is a separate locked project and must not be edited or expanded from this repository.

The Forge may learn from general AzerothCore/module conventions, but it must not make Adventure Nexus changes or depend on unmerged/private implementation details from that repository.

## End-of-run deliverable

`HARVEST.md` must summarize only finish-gate candidates and include for each:

- project/module name;
- one-paragraph gameplay description;
- why it is worth testing;
- branch/commit;
- build result;
- disposable install/startup result if performed;
- independent review result;
- exact remaining live/in-game tests;
- known limitations.

`BLOCKED.md` and `IDEA_VAULT.md` preserve non-harvest work separately.

The final report must include honest counts of attempted, completed, blocked, abandoned, and research-only projects.
