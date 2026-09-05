PROJECT=mod-hunt-rhythm
OWNER=practical
BRANCH=project/hunt-rhythm
CANDIDATE_SHA=UNSET
STATE=VALIDATING
CLAIMED_SCOPE=Opt-in session-only outdoor leveling streak; capped base kill-XP bonus; self-service start/status/stop; lifecycle resets
BUILD_RESULT=NOT_RUN
OFFICIAL_GATE=NOT_RUN
ONE_HUMAN_REVIEW=PASS_SOURCE_AT_fa31ee9713d634ed1cddde75ed62c9aa71607125; disposable/gameplay validation pending
REVIEWER=SOURCE_REVIEW_PASS_AT_fa31ee9713d634ed1cddde75ed62c9aa71607125; official evidence review pending
NEXT_ACTION=Run the official gate for the frozen candidate and independently review its actual evidence

Implementation started after the final serial clean control passed, under the owner's
fixed deadline. This source-reviewed candidate contains real C++ hooks, commands, bounded config,
arithmetic/expiry helpers, compile-time rule checks and complete player/operator instructions.
It is not a compile/install/startup or harvest success claim. No live-server work occurred.
Independent source and one-human review passed at `fa31ee9713d634ed1cddde75ed62c9aa71607125`
after the pet-XP guard correction. This final freeze only updates evidence documents.
The exact frozen candidate SHA is recorded externally by Director; a commit cannot contain
its own SHA. `CANDIDATE_SHA=UNSET` does not claim that the source revision is the tested SHA.

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
Independent implementation `ONE_HUMAN_REVIEW=PASS` at the reviewed source revision;
disposable validation remains pending. Gameplay and ordinary bot feel
remain PENDING LIVE/IN-GAME VALIDATION. The approved proposal does not self-certify code.

## Review focus and limitations

- XP headroom: preserve baseline awards when the added amount cannot safely pass the
  pinned float +5%, RAF/rested and current-XP accumulation, or hunter-pet float
  `Rate.XP.Pet` scaling/current-pet-XP accumulation. Do not saturate core awards.
- Eligibility precedes any advance/refresh, including loot recipient and no-play-time
  flags; player death/map change preserves opt-in, login/logout/reload clears it.
- Session state is mutex protected, stores GUIDs rather than Player pointers, and calls
  core/game/chat APIs outside the lock. Successful config reload swaps rules and clears
  sessions together.
- Independent source review passed; native discovery, compilation, installation, runtime
  and the full official suite still need actual candidate evidence. Additional XP-modifying modules
  need separate compatibility review. No gameplay/bot-competence claim is made.
