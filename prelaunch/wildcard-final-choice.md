# Wildcard final flagship choice — Stormwright

```text
AUTHOR_CHOICE=STORMWRIGHT
PROJECT_SLUG=mod-stormwright
DISPOSITION=SELECTED_FOR_LAUNCH; NOT_IMPLEMENTING
TOURNAMENT=ad264556c8fd688ea462ead3ab7ece753f142819
ONE_HUMAN_ADDENDUM=84df9c388f4a7b0b5b0968bae966b11c885f29d3
INDEPENDENT_REVIEW=0aa6e58c02b862b7a7c179529886668d097739be
DIRECTOR_FLOORS=Stormwright PASS; Holdfast PASS; Warband deferred for first-flagship closure risk
ONE_HUMAN_REVIEW=PASS_FOR_EVALUATED_PROPOSAL_ONLY
IMPLEMENTATION_REVIEW=NOT_RUN
OFFICIAL_CANDIDATE_GATE=NOT_RUN
IMPLEMENTATION_START=WAIT_FOR_PROVEN_PRELAUNCH_JUDGE_AND_DIRECTOR_RECORDED_START
```

**Stormwright — turn the boss's storm into your weapon before it tears the arena apart.**

I choose Stormwright from the concepts that passed both independent floors. I read the Reviewer's committed final disposition at the exact SHA above; it passes Stormwright's gameplay, bounded technical/finish, and complete one-human proposal paths. Director communicated matching passes after reviewing the one-human addendum. Director will integrate this choice and the dispositions into the shared selection/ownership record. These are proposal decisions, not claims that any implementation or gameplay test exists.

## Final creator rationale and tradeoffs

Stormwright makes the human player control the encounter's environment: bait a strike, capture it, and decide whether its charge buys recovery or a damage opportunity. Cooling rods and pursuing adds keep that decision tied to movement and combat after the initial surprise. The discharge is a clear, visible moment worth showing someone, and the full loop can run with one person at one client.

I prefer one polished environmental encounter over a larger wave, roster, or boss framework. The deliberate tradeoffs are a single authored arena, level-80 scope, no persistent power/economy system, and ordinary bot combat only. Holdfast remains a viable deferred fallback; it will not be built in parallel. Warband Arena is deferred because four AI roles and its casualty economy have the larger closure surface. No further ideation pass is needed for this selection.

## Selected complete V1 and binding conditions

- One public, self-service registrar and safely authored arena; one boss, three capacitor rods, one pursuing-add role, and a bounded 8–12 minute encounter with explicit win/fail/abort/reset.
- One human pilot performs every start/preset choice, bait/lock/dodge, rod selection, Ground/Discharge and retry/exit action. No second human/client/account or custom bot choreography is required.
- A **complete Solo Pilot profile** for one level-80 character with no participating bots: at most one live pursuing add, budgeted ordinary incoming damage, material discharge damage, and pilot-operated Ground restoring bounded personal health plus one missing ward point. Ground remains usable at full ward when the pilot is hurt; consuming it still forfeits a discharge opportunity.
- Optional normal controllable bots supply ordinary tank/heal/attack/follow support only. Freeze starting roster/scaling. Party size may increase ordinary combat pressure, never the required number of custom operators or a requirement for exact bot positions.
- Preserve the actual storm cycle, distinguish tracking from locked impact, visibly show charged/cooling rods and boss vulnerability, and keep offensive/recovery decisions meaningful. Do not substitute automated discharge, a permanently safe idle loop, or chat-only descriptions for the gameplay/visible feedback.
- Prefer **direct validated SpellVisualKit packets and owned stock-model actors** for feedback. Spell 62186 is unapproved and must not be cast as a harmless placeholder. Kit 12201 is a verified reference candidate, not a claim of tested client appearance/lifetime. Early asset/site validation must establish a bounded, legible route; visuals never decide gameplay authority.
- Validate living pilot, run ownership, interaction range, charge and phase on every activation. Ground cannot resurrect, heal bystanders, work after abort, or execute twice from repeated input. Every owned actor/marker has a finite lifetime and cleanup for death/logout/map/leave/timeout/failed summon. Record outcomes exactly once as assisted encounter results, with no outsider-proof ranking claim.
- Ship complete module-owned SQL/config/reference validation, ordinary-player access, outcomes, retry, and exit. No existing core, Playerbots, creature-template, quest or unrelated project changes; exact pins remain mandatory.

The first approved implementation work after launch should resolve the highest-risk site/feedback/solo-health-budget path, then complete this one V1. A legitimate failed gate is repaired in the candidate or referred independently to Reviewer; the judge is not changed by the builder. If the defining readable mechanic cannot be completed within scope, stop and report the failure rather than relabeling an incomplete or text-only encounter as the flagship.

## Required final package

The candidate README and handoff must include the exact **One-Human Playability** section, supported solo/ordinary-bot settings, all human-only actions, scaling/limitations and a complete one-client smoke checklist. They must also include the hook/loop/replay explanation, stock-client feedback, a concise final creator note, an exact implemented **60–90 second demonstration flow**, Tyler's screenshot/video capture checklist, and meaningful differences from ordinary WotLK combat.

The proposal's 75-second showcase is a planning reference; final timing must match the actual completed implementation. Actual client visuals, class/gear balance and ordinary bot behavior remain **PENDING LIVE/IN-GAME VALIDATION** even after the required source/disposable/official checks pass. No live server will be accessed by the forge.

This is the sole Wildcard flagship. Another project may start only after this one passes independent implementation review and its exact-SHA official gate, while BUILD and remaining time permit. **Formal launch has not occurred; this choice does not start implementation or the 36-hour clock.**
