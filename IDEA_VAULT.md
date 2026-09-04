# WoW Server Forge — Idea Vault

Preserve worthwhile concepts that should not consume implementation time during the current sprint.

Ideas here are NOT harvest-ready projects.

## Research / deferred concepts

### The Small Council — not approved for implementation

- Origin: Wildcard prelaunch scouting; no implementation was started.
- Concept: ordinary critters host targeted-emote riddle audiences; three persistent
  story seals unlock a narrative ending.
- Source feasibility: the pinned `OnPlayerTextEmote` hook, map-local creature lookup,
  private chat and character persistence could support it. Bot emotes reach the same hook;
  a product would need bot exclusion, target/lifecycle checks and data validation.
- Owner disposition (2026-09-04): **NOT APPROVED**. Its principal payoff was one-off
  riddles, flavor and a journal, without enough repeated gameplay, decisions or meaningful
  server impact to justify implementation time. Novelty and feasibility did not meet the
  installation/testing-value bar.
- This is deferred research only, not an active assignment, attempted implementation,
  finished project or harvest candidate. Do not resume it under a routine idle-lane claim.
- Historical source-only scouting: commit `173d1d631f088dfeaf9d8f7911b69c57e6d36d09`.

Use:

```text
Concept:
Origin: Practical / Wildcard / Scout
Why it could be interesting:
Technical observations:
Why it was not built now:
Likely smallest viable implementation:
Key risks/open questions:
```

## Wildcard fresh-slate rule

After several completed/attempted concepts, the Director may ask Wildcard for a fresh ideation pass using only:

- the exact pinned technical environment;
- stock-client/no-core-mod safety boundaries;
- the hard deadline;
- the goal of making the server more fun, surprising, replayable, atmospheric, or memorable.

Do not always show Wildcard the entire existing idea history before that fresh pass. Independent samples from the design space are desirable.
