# Field Camp independent proposal review

2026-09-05. Reviewed the first option in Practical's
`.forge-local/practical-next-options.md`, before substantive implementation.

**ONE_HUMAN_REVIEW=PASS — design and pinned-source feasibility only.** The solo
set-camp, travel to town for supplies, return, observe cooldown, repeat, retry
after a rejected request, and clear loop is complete and useful. All custom
actions belong to one ordinary human. No enemy scaling, other operator or bot
transport behavior is required. Optional bots remain outside the transport
contract; the full utility works without them.

No fundamental API blocker was found at AzerothCore
`47960183bb03b83e8943eb2f0f39c16df9710c9d`. The proposed one-anchor, session-only,
same-world-map limits keep this separate from cross-map portals and persistent
travel networks. The following concrete implementation conditions preserve the
proposal's behavior:

- Store the exact phase mask and require equality before return. `Object.h:519`
  shows that `InSamePhase` may accept merely overlapping masks.
- Recheck the original saved landing with a phase-aware, finite, bounded floor
  and liquid query. Missing or changed ground rejects the return; it does not
  justify inventing an alternative destination or using privileged flags.
- Check alive/grounded/combat/PvP/flight/fall/water/taxi/transport/vehicle and
  existing teleport state. Reject control-impairing states before invoking the
  core teleport: `Player.cpp:1401` onward can remove stun/fear/confuse/root before
  the `OnPlayerBeforeTeleport` veto. `CanTeleport` is ACK bookkeeping, not a
  general eligibility predicate.
- Preserve the cooldown separately from anchor replacement or clearing within
  the session. Rejected requests preserve the anchor and do not consume a return.
- Core `TeleportTo` returning true can mean a deferred request or a transfer
  awaiting client acknowledgment. Report request acceptance honestly; source or
  CI checks do not prove the player arrived. Do not invent custom bot transport.

This disposition does not certify implementation, compilation, landing safety
at every world location, or in-game arrival/feel. Those remain subject to actual
candidate source review, its official gate and the documented manual checklist.
No extra prelaunch gate or new validation framework is proposed.
