# Hunt Rhythm validation evidence

Status: source-reviewed candidate awaiting official validation, **NOT CERTIFIED**.

| Check | Actual result |
| --- | --- |
| Pinned API/source research | Completed; independent source review PASS at `fa31ee9713d634ed1cddde75ed62c9aa71607125` |
| Module discovery/config installation | NOT_RUN for this candidate |
| Compilation/linking | NOT_RUN; no local C++ compiler found on PATH |
| Embedded rule assertions | Written; NOT_RUN until actual compilation |
| Full upstream unit tests | NOT_RUN for this candidate |
| Disposable install/startup/module load | NOT_RUN for this candidate |
| Official exact-candidate gate | NOT_RUN |
| Independent implementation review | SOURCE_REVIEW=PASS at the source revision above; official evidence review PENDING |
| One-human implementation disposition | ONE_HUMAN_REVIEW=PASS for the complete solo/source path; disposable/gameplay evidence still pending |
| In-game/Playerbots behavior | PENDING LIVE/IN-GAME VALIDATION |

The earlier clean control validates the forge harness, not this candidate. No existing
green control verdict, source inspection, or arithmetic argument is substituted for a
Hunt Rhythm compile, official gate, independent review, or actual gameplay evidence.

Core source references: `PlayerScript.h` hooks; `KillRewarder.cpp:149–188` group/aura/hook
ordering; `Player.cpp:2404–2475` favored/trial/partial/RAF/rested/player accumulation;
`Player.cpp:9095–9105` rested pool; `AllMapScript.cpp:184–194` map-entry lifecycle.
All were read at AC `47960183bb03b83e8943eb2f0f39c16df9710c9d` with PB
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`. Independent preflight confirmed the
conservative headroom check must use the core's float expression for its +5% bound.
Reviewer identified the additional hunter-pet path in `Pet.cpp:886`:
`RATE_XP_PET` float scaling and current pet XP also need a bound. The correction adds a
separate conservative guard and compile-time boundary cases; actual compilation remains
NOT_RUN. Pet/current-XP and nonfinite rate checks do not alter baseline core awards.
The independent Reviewer inspected the exact correction and approved the full source,
lifecycle, arithmetic and one-human flow at `fa31ee9713d634ed1cddde75ed62c9aa71607125`.
The final pre-run documentation freeze changes no implementation or configuration.

No project SQL, custom build hook, dependency edit, new infrastructure, runtime network
service or live-server operation is involved.
