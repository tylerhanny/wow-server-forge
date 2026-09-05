# Field Camp — Practical implementation decision

Decision recorded 2026-09-05 during BUILD, before substantive implementation.
**DIRECTOR=BUILD. ONE_HUMAN_DESIGN_REVIEW=PASS (Director and independent Reviewer).**
This is proposal approval, not implementation, runtime or harvest certification.

Practical compared Field Camp, Field Repairs and Quartermaster Work Orders. Field Camp
offers a repeatable useful supply-trip loop with no new economy or SQL; Field Repairs
is a smaller but narrower fallback, and Work Orders requires more data/economy review.
The Director selects Field Camp for high install value and a credible complete V1 within
the fixed remaining window. It neither duplicates Hunt Rhythm's XP chain nor Stormwright's
independently owned flagship encounter. Hunt Rhythm remains frozen at `4aaa3ae` for its
already-running official validation and retains priority for actual correctness findings.

Owner: Practical. Slug: `mod-field-camp`. Branch: `project/field-camp`.
Separate worktree: `.worktrees/field-camp`. No other builder owns this project.

## One-Human Playability

An ordinary solo human, safely outdoors, sets one personal session-only location using
`.camp set`, travels normally to a same-continent town to sell/repair, and requests return
with `.camp return`. Status explains the anchor/cooldown; accepted return starts a bounded
cooldown while preserving the anchor. Unsafe state or failed request leaves it available
for retry. `.camp clear`, logout or restart removes the anchor. This is the full useful
loop with one human/client/account. No helper, extra enemy or difficulty scaling exists.
Bots have no custom action or transported role; their optional regroup behavior is not
assumed. The complete supported path is solo, with bot follow/arrival explicitly pending
later in-game checks. Human client arrival and travel feel likewise remain untested.

## Coherent V1 and review conditions

- One session-only same-map, exact-same-phase anchor. No SQL, shared camps, cross-map
  portals, other-player summoning, persistent network, reward or privileged teleport flags.
- The original destination comes from the human's valid location, then is revalidated
  with finite bounded phase-aware ground/liquid checks at return. Missing or materially
  changed ground rejects the request; never invent a fallback landing.
- Bind and return reject dead/combat/PvP/flight/fall/water/taxi/vehicle/transport/already-
  teleporting and control-impairing states. Core TeleportTo clears some control effects
  before its veto hook, so the project must reject those states before calling it.
- Save the exact phase mask and require equality; phase overlap is insufficient.
- Cooldown survives anchor replacement and clear within the current session. Status
  distinguishes accepted teleport request from confirmed client arrival.
- Configuration, command feedback, cleanup and exact one-human success/failure/retry/exit
  smoke instructions must be complete. All ordinary finish gates remain mandatory.

Independent Reviewer checked the exact pinned APIs and found no fundamental feasibility
blocker under these conditions. Main risks are landing/phase/teleport lifecycle and
cooldown edges. Initial completion estimate is 3–5 hours plus real validation latency;
the fixed 2026-09-06T18:34:32Z deadline remains unchanged. Reduce or defer if meaningful
closure becomes unlikely; no source/pin or acceptance exception is granted.
