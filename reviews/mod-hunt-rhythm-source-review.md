# Hunt Rhythm independent source review

Reviewed checkpoint: `fa31ee9713d634ed1cddde75ed62c9aa71607125`.
Initial checkpoint: `432531a0c824d1db5f845fadfbe0628d0459ad4d`.

Final frozen candidate: `4aaa3ae188e7bcdba2569676911e14142ac378e2`.
Independent comparison with the reviewed checkpoint found changes only in
README, VALIDATION and handoff review-status text; source and configuration
are byte-identical. Those documents accurately retain pending execution and
in-game evidence. The source and one-human dispositions therefore also apply
to this final candidate. Official run `33951428776` is the execution attempt;
its outcome is not inferred from this source review.

**SOURCE_REVIEW=PASS. ONE_HUMAN_REVIEW=PASS.** These are implementation-source
dispositions, not compile, install, runtime, gameplay or harvest certification.
The exact candidate still requires its actual official gate and final evidence
review. No cache change or further prelaunch control is a prerequisite.

Reviewer inspected all seven project/handoff files and matched the relevant
APIs to AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`, with pinned
Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945` unchanged.

## Actual finding and correction

The initial implementation correctly bounded player XP through the core's
float-rounded favored bonus, mutually exclusive RAF/rested processing and
current player XP, but omitted the downstream hunter-pet rate and accumulation.
At exact pinned `Pet.cpp:886`, `GivePetXP` multiplies by `RATE_XP_PET` before
adding `UNIT_FIELD_PETEXPERIENCE`. For example, base 1,000,000,000 plus 10% with
pet rate 4 would change a representable baseline 4,000,000,000 award into an
out-of-range 4,400,000,000 float-to-uint32 conversion.

The corrected checkpoint snapshots hunter-pet XP/rate outside the store lock
and checks the same float multiplication, rejecting negative/nonfinite or
overflowing results before integer conversion. Comparing through double keeps
the exact UINT32_MAX ceiling, avoiding its rounding to 2^32 as float. Wide pet
accumulation is checked too. Only the added bonus is declined; original core XP
is preserved. The full-amount guard is intentionally conservative for grouped
or non-gaining pets, and this is documented. Corresponding compile-time cases
are present but were not represented as executed locally.

## Reviewed implementation behavior

- Native module discovery/registration, exact enabled PlayerScript/WorldScript
  hooks and ordinary-account command table signatures match the pin.
- Eligible positive kill XP, player state, world-map/target exclusions and
  normal loot credit are checked before any chain advance or refresh.
- Default current-kill bonuses are 0/2/4/6/8/10%; expiry occurs at elapsed time
  greater than or equal to 60 seconds. Repeating start does not extend a chain.
- GUID-only session state is mutex protected. No Player pointer is retained;
  core/chat access occurs outside the store lock. Death/map entry resets the
  chain; login/logout/stop/successful reload clears opt-in as documented.
- Added XP uses wide intermediates and both downstream guards; unsafe additions
  preserve baseline awards. No core, Playerbots, SQL or build-hook changes exist.
- The complete solo path provides access, opt-in, route/target choices, visible
  progress, capped outcome, timeout/death failure, retry and exit. Optional bots
  only perform ordinary combat/follow roles; no second operator or custom bot
  cognition is required. Bot removal preserves the same primary loop.

No remaining actionable source finding was identified after the pet correction.
`git diff --check 72ce4e0 fa31ee9713d634ed1cddde75ed62c9aa71607125 --
projects/mod-hunt-rhythm handoffs/mod-hunt-rhythm.md` passed. No local C++
compiler run occurred. Candidate compile/link, install, configuration sentinel,
official upstream tests, final integrity and runtime evidence remain pending.
Class pacing, actual XP/chat behavior and ordinary bot competence remain
PENDING LIVE/IN-GAME VALIDATION, with explicit manual steps in the README.
