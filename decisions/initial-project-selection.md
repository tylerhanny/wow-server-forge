# Initial project selection — Director assessment

State: **PRELAUNCH; no gameplay implementation authorized yet**.
All judgments below are proposal assessments, not proof of working code, balance, bot
competence, client visuals, or official acceptance. The sprint clock remains unset.

## Inputs

- Five mechanically distinct Auteur concepts: tournament source commit
  `ad264556c8fd688ea462ead3ab7ece753f142819`.
- Corrected complete one-human paths: source commit
  `84df9c388f4a7b0b5b0968bae966b11c885f29d3`.
- Practical complete solo proposal: source commit
  `87d44127c8049526a6213beebf084e97cd1c6ddc`.
- Locked `ONE_HUMAN_PLAYABILITY.md`, `WILDCARD_AUTEUR.md` and unchanged technical gates.
- Independent visual audit: `prelaunch/stormwright-visual-audit.md`. Spell 62186 is not
  approved as a harmless visual; a verified stock visual-kit packet path is available.

## Director comparison of the strongest three

| Dimension | Stormwright | Holdfast | Warband Arena |
|---|---|---|---|
| Actual play/decisions | Routing marks, choosing available rods, offense versus recovery, exploiting a limited vulnerability window. | Interception, keeping beacon integrity, sacrificing score for repair, choosing extraction risk. | Drafting counters, formation, active combat and casualty-budget choices. |
| Replay/value after surprise | Execution, route planning, cooldown/resource recovery and bounded presets remain meaningful after learning the mechanic. | Different assaults and group composition change tactical pressure and extraction outcomes. | Opponent order, class/roster synergy and casualties change the next decision. |
| Visible impact/demo | Enemy lightning becomes a usable environmental resource and then a visible attack on its source. Strongest immediate demonstration. | A physical objective near collapse and a saved assault make the stakes visible; solo sapper timing remains serialized. | The purchased squad visibly fights and survives or dies; results alter subsequent drafts. |
| Differentiation/install value | A complete self-service environmental encounter with a distinct human role, beyond a convenience command or stat modifier. | A complete defense/extraction activity; objective attrition makes survival different from success. | A real squad game coupled to ordinary character combat; not a renamed bot-command wrapper. |
| One-human primary path | Full Solo Pilot profile, all custom actions human-operated, optional bots only ordinary combat. The rod problem is retained. | One central beacon, sequential captain choices, solo wave cap and checkpoint recovery; no second defender/operator required. | One captain with owned temporary allies; zero participating Playerbots is the default complete path. |
| Closure risk | Bounded actors and one venue; highest risks are visual readability, solo health/recovery budget, combat interaction and cleanup. | More wave/site data; prevent evade-healing and validate all solo wave/arming bounds. | Largest AI/target/faction/economy/balance surface; disproportionate risk for the first flagship. |

Director dispositions:

- **Stormwright: PASS quality and one-human design floors**, with the complete Solo Pilot
  loop, self-service start/outcome/retry/exit, validated stock references, bounded roster/actors
  and all disclosed one-human scope requirements retained. This is a credible 36-hour V1,
  not an assertion that tuning or visual clarity is already proven.
- **Holdfast: PASS quality and one-human design floors**, with one beacon, serialized
  sapper arming, complete solo wave table, paid beacon repair and scoped Rally. Strong fallback.
- **Warband Arena: PASS one-human design floor; DEFER for first-flagship selection** on
  comparative completion risk. Meaningful gameplay is present, but four AI roles, healer
  targeting, formation recovery and casualty-economy correctness consume more review buffer.
  This is not a claim that the idea requires another human or is technically impossible.

The first two convincingly satisfy the mandatory installation, repeat-use, real-gameplay,
visible-demonstration, enduring-value and credible-closure tests at proposal level. Wildcard
has independently expressed a preference for Stormwright after the comparison; Director
does not replace that creative choice. Independent Reviewer dispositions are now recorded in
`prelaunch/reviewer-one-human-dispositions.md` at source commit
`0aa6e58c02b862b7a7c179529886668d097739be`: all four one-human design paths PASS,
Stormwright/Holdfast pass quality and feasibility, and Warband is a feasible but riskier
alternative. Wildcard has now chosen **Stormwright (`mod-stormwright`)** in
`prelaunch/wildcard-final-choice.md`, source commit
`fded6b842de4c5584270752acfb9ed78aa61dee6`. This completes the bounded tournament;
Holdfast remains deferred fallback and Warband remains deferred. No parallel flagship build.

## Practical

**Hunt Rhythm: PASS Practical quality and one-human design floors.** Its qualifying loop is
actually solo: a normal leveling character opts in, chooses a route, chains ordinary eligible
kills, receives capped base-XP bonuses, loses the chain through timeout/death, retries and
opts out alone. No enemies or group requirements are created. Bots are optional ordinary
combat help. Limited novelty is appropriate to this bounded Practical project, not a substitute
for the Auteur flagship. Preserve precise eligibility, integer-safe capped arithmetic and
honest pet/rested/RAF interactions. Independent Reviewer has recorded proposal PASS in
`prelaunch/reviewer-one-human-dispositions.md`.

## Selection checkpoint

INDEPENDENT_REVIEW_RECORD=prelaunch/reviewer-one-human-dispositions.md; source 0aa6e58c02b862b7a7c179529886668d097739be
WILDCARD_FINAL_CHOICE=mod-stormwright; author record fded6b842de4c5584270752acfb9ed78aa61dee6
PRACTICAL_PROSPECTIVE_PROJECT=mod-hunt-rhythm
IMPLEMENTATION_AUTHORIZED=NO; requires completed prelaunch and recorded launch

All actual gameplay and bot-feel checks remain **PENDING LIVE/IN-GAME VALIDATION**.
Neither concept selection nor the disposable smoke control counts as a completed Forge project.
