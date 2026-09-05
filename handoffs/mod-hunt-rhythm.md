PROJECT=mod-hunt-rhythm
OWNER=practical
BRANCH=project/hunt-rhythm
CANDIDATE_SHA=UNSET
STATE=BUILDING
CLAIMED_SCOPE=Opt-in session-only outdoor leveling streak; capped base kill-XP bonus; self-service start/status/stop; lifecycle resets
BUILD_RESULT=NOT_RUN
OFFICIAL_GATE=NOT_RUN
ONE_HUMAN_REVIEW=PENDING_IMPLEMENTATION; approved proposal disposition is not implementation acceptance
REVIEWER=PENDING_IMPLEMENTATION_REVIEW
NEXT_ACTION=Independently review the first complete source and obtain actual candidate compilation

Implementation started after the final serial clean control passed, under the owner's
fixed deadline. This first checkpoint contains real C++ hooks, commands, bounded config,
arithmetic/expiry helpers, compile-time rule checks and complete player/operator instructions.
It is not a compile/install/startup or harvest success claim. No live-server work occurred.

Exact compatibility: AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, WoW client 3.3.5a build12340, Ubuntu24.04x64.
Changes are limited to `projects/mod-hunt-rhythm/` and this handoff. No SQL or custom
CMake hook is needed. The module's static assertions are pending actual compilation.

## One-Human Playability

The complete primary path is solo: a normal leveling character opts in with `.rhythm
start`, chooses a safe route, kills ordinary hostile non-elite XP-bearing outdoor
creatures within the configured window, receives a capped bonus, recovers/retries after
timeout or death, and exits with `.rhythm stop`. No second human, second client or
second operated account is required. No enemies, health, damage or group requirements
are added. The default sixth timely kill reaches the10% outcome; the loop then repeats.

Optional normal pinned bots only fight, tank, heal and follow. The human operates all
Rhythm commands and chooses targets/routes. Bots need no custom cognition, commands,
menus, exact timing or positional mechanics. Removing bots preserves the entire loop.
Normal shared XP credit remains authoritative; bots never enroll automatically.

Exact one-human manual steps, eligibility/exclusions, configuration, pet/rested/RAF
semantics, no-bots behavior, success/failure/retry/abort and removal instructions are in
the project's README under `One-Human Playability`. Every manual step is PENDING.
Independent implementation `ONE_HUMAN_REVIEW=PENDING`; gameplay and ordinary bot feel
remain PENDING LIVE/IN-GAME VALIDATION. The approved proposal does not self-certify code.

## Review focus and limitations

- XP headroom: preserve baseline awards when the added amount cannot safely pass the
  pinned float +5%, RAF/rested and current-XP accumulation. Do not saturate core awards.
- Eligibility precedes any advance/refresh, including loot recipient and no-play-time
  flags; player death/map change preserves opt-in, login/logout/reload clears it.
- Session state is mutex protected, stores GUIDs rather than Player pointers, and calls
  core/game/chat APIs outside the lock. Successful config reload swaps rules and clears
  sessions together.
- Source correctness, native discovery, compilation, installation, runtime and the full
  official suite still need actual candidate evidence. Additional XP-modifying modules
  need separate compatibility review. No gameplay/bot-competence claim is made.
