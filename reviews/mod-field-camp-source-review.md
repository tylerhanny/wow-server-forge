# Field Camp independent implementation review

Reviewed checkpoint: `b1b84172b96b41e230bae5f8c6564b3195eb61a7`.

Final frozen candidate: `ec9eea979c9344853aaf02d46ba9f6632636254b`.
Independent comparison found only README, validation and handoff review-status
changes; source and configuration are byte-identical. The dispositions below
also apply to the final candidate; official run `33952603462` remains pending.

**SOURCE_REVIEW=PASS. ONE_HUMAN_REVIEW=PASS — implementation source only.**
All five project/handoff files were read. No actionable remaining source finding
was identified. `git diff --check` passed. Compilation, installation, startup,
actual player transfer and final exact-candidate acceptance remain pending.

The implementation follows the approved single-session anchor contract using
ordinary SEC_PLAYER commands and the exact pinned AzerothCore APIs. It adds no
SQL, build hook, dependency modification, persistent player record or bot transport.
The target is AC `47960183bb03b83e8943eb2f0f39c16df9710c9d` with Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945` unchanged.

- Eligibility checks reject death, combat, PvP/duels, logout, pending transfers,
  flight/fall/hover/water, vehicle/transport/taxi, casts and control impairments.
  The actual pinned IsFalling helper is supplemented by movement flags and a
  finite floor check; CanTeleport ACK bookkeeping is not used as eligibility.
- The saved world map and exact phase mask must match. Current and original
  destination coordinates receive bounded phase-aware ground/liquid checks;
  changed saved floor rejects the request without inventing a replacement Z.
- GUID-keyed state and configuration use a mutex. Core/map/chat/teleport calls
  occur outside it; generation/revision checks reserve a return only for the
  inspected camp. A native rejection refunds its reservation without recreating
  a session cleared by reload/logout.
- Clear and replacement preserve a running cooldown. Login/logout/restart and
  successful configuration reload intentionally remove session state. These
  temporary limits and the lack of persistent anticheat are documented.
- Default TeleportTo options retain core restrictions, veto and pet handling.
  The message says request accepted, not arrival confirmed. The README correctly
  notes that core cleanup can precede a veto and client acknowledgment is separate.

The complete qualifying solo loop is set, travel normally for town supplies,
request return, observe the result/cooldown, retry after safe-state failures or
cooldown, and clear to exit. One ordinary human performs every custom action.
No helper, other client/operator, enemy scaling or bot cognition is required.
The same utility works with no bots; optional party/pet regrouping is explicitly
outside the transport promise.

README and handoff include the exact One-Human Playability section and full manual
steps. Actual terrain interpretation, arrival, PvP/phase edges, other teleport
hooks and optional bot/pet behavior remain PENDING LIVE/IN-GAME VALIDATION. No
local compiler run or gameplay was performed or inferred from this review.
