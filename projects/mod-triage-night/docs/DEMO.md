# Triage Night — future ninety-second demonstration

This is a capture plan for later owner testing, not evidence that gameplay was executed.
Use one level-80 priest in ordinary healing gear, one client and zero bots. Keep direct
single-target heals and normal mana available. Begin on suitable open outdoor ground.

| Capture time | Human action and visible point |
|---|---|
| 0–10s | Enter .triage start. Show the three numbered patients, normal mana and ten-second briefing. Frame all three with friendly nameplates/health bars where the stock client permits. |
| 10–30s | Read the first round's fast-bleeder notice. Select that patient and demonstrate a normal efficient heal while the other patients keep their existing wounds. |
| 30–55s | Switch targets as health priorities change. Let the viewer see normal healing animations and mana use; keep every patient alive. No GM health or mana command is used. |
| 55–65s | Show the finite recovery break: patients retain wounds. Choose between another heal and ordinary mana recovery before the next round begins. |
| 65–77s | Read round2's new burst target. The warning appears eight seconds into the round and impact four seconds later. Frame the warned target's health loss. |
| 77–87s | Stabilize one other bleeding patient with .triage stabilize 1,2 or3 as appropriate, then directly heal the burst casualty. Show that stabilization paused loss but did not refill health and only one emergency charge remains. |
| 87–90s | Show .triage status: the current round, actual patient health and finite charges. Continue the real shift after the clip, or use .triage stop for a clean abort. |

Timing assumes ordinary uninterrupted server updates. A delayed update does not compress
several warnings into one frame; the run still has a real six-minute cap. If actual target
visibility or tuning prevents this ordinary sequence, record that finding rather than use
GM setup or present a staged workaround as the qualifying loop.

## Tyler's capture and verification checklist

- Patient semicircle with numbered names and a normal priest UI; no second client/bot helper.
- One burst warning and the same patient's health at its later impact.
- A normal healing cast, genuine mana change and a stabilization confirmation showing the
  remaining charge. Demonstrate that the stabilized patient still needs healing.
- After the full shift, capture success or ordinary failure plus the per-login result.
- Capture normal rest/retry and a clean .triage stop; verify owned actors disappear.
- Record priest gear/spells, Training/Veteran choice, health-bar/pose clarity, unexpected
  healing restrictions and whether the changing priorities remain fun after several runs.

The intended difference from stock First Aid Triage is repeated choice among actual healing
spells, persistent patient wounds, mana management and scarce stabilization across a whole
shift. The intended replay value is better crisis management, not collecting flavor text.
