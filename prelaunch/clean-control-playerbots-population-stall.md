# Clean control: disposable Playerbots population stall

Reviewer disposition: **CANCELLED; not a complete gate pass.** Run
`33941967266` tested candidate `87b822fd41bb6013358aa6f5e16ca252ad79761c`
with judge `04f15bd01c7d49813053a5737f9141885c000ce6`. The Director normally
cancelled the stalled dry-run; the always-running artifact step completed.
No unit-test execution or final post-runtime integrity check occurred.

## Actual evidence

- Full compilation completed at `2026-09-05T05:06:54Z`; fixture restoration,
  dependency integrity, install, SQL validation, runtime-data preparation and
  disposable MySQL preparation passed. Runtime began at `05:07:01Z` and was
  cancelled at `05:20:44Z` after exceeding both nominal five-minute limits.
- Authserver completed its dry-run and closed its database connections.
- Worldserver populated and migrated the disposable databases, loaded core
  scripts and emitted `FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159`.
  It did not emit the required world initialization/dry-run completion markers.
- Buffered console capture ends partway through initialization. `Server.log`
  reaches Playerbots initialization. `Playerbots.log` shows 100 accounts and
  1,000 generated characters, ending with:
  `Waiting for 1000 characters loading into database (1217 queries)...`.
  `Errors.log` is empty. The precise reason the queue did not drain is not
  established by these logs; absence of errors does not imply runtime success.
- Artifact `9963623959`, 680,619 bytes, API-reported archive SHA256
  `094f89d4fa4708472cc9bb23a5a8ceef3022d1f4af90cf42d62885e4c13ad6d0`.
  Reviewer downloaded its contents and matched candidate, judge, both pins and
  all nine protected hashes against the exact judge Git blobs.

Reviewer rechecked the complete 203,042-byte build capture against its stream
and persisted receipt SHA256:
`256040d4314bacaa6e760237bcedbf33d8b144cd9900043aeead38392bd8e2bf`.
Exit status is zero, the four visible known upstream warnings match their
verified source inventory, all 1,829 compiler commands retain `-Werror`, and
only the 1,822 verified upstream commands have the authorized demotion.
The exact authorized WorldMock original/applied/post-build/restored identities
and all-other-source checks pass. The 3,634-file original inventories match
before and after build. No corrected full header is exported or installed.
The installed binaries include authserver and worldserver; unit_tests was
built but **not executed** in this run.

Useful raw evidence SHA256 values:

| File | SHA256 |
| --- | --- |
| authserver-dry-run.log | `dd2b8ed83ab4f1634bfeb802e059f6c04a25decced1ac717ae1aa343701a9993` |
| worldserver-dry-run.log | `b7866a421a42539a623a73ae27fe4cc6c8459604475727655d96402b7d06ed5c` |
| Server.log | `71bb8109b84de8b7a718c5b3fdb93c89aacb1b8d9b5b2a3374ac3192a2540295` |
| Playerbots.log | `51000181b068087d8de9f0d00f336ab0f1f235165912f25b3626376d5790e1bf` |

## Source-grounded fixture correction

At Playerbots pin `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`,
`src/PlayerbotAIConfig.cpp:752` invokes `CreateRandomBots()` unconditionally.
`RandomBotAutologin=0` alone therefore does not stop creation.
`src/Bot/Factory/RandomPlayerbotFactory.cpp:318–427` calculates needed random
accounts from `MaxRandomBots` and adds `AddClassAccountPoolSize`;
`RandomBotAccountCount=0` means automatic calculation, not zero accounts.
The fresh default profile produces 50 random accounts plus 50 addclass
accounts. Its character queue wait at lines 740–745 has no stop/deadline check.
Worldserver's signal handler sets a stop flag, explaining why a TERM-only
timeout does not necessarily terminate that startup wait.

Reviewer independently matched the researched config source SHA256
`f59d62e6d50baa7c4a04096eb4ceebad6dd10941fb5d5d4bd11c26b87e10bdab`
and factory source SHA256
`cfc424ce406a7cdf28f80e52e5b5f0f15775361411932801bfe0a737a36f17b3`
to the exact-pin inventory in this artifact.

Authorized workflow-only correction `ed2357393262a97b9bf30ce3b6e6eb3378326e02`
sets the installed disposable configuration to:

```ini
AiPlayerbot.Enabled = 1
AiPlayerbot.RandomBotAutologin = 0
AiPlayerbot.MinRandomBots = 0
AiPlayerbot.MaxRandomBots = 0
AiPlayerbot.RandomBotAccountCount = 0
AiPlayerbot.AddClassAccountPoolSize = 0
```

Playerbots initialization and ordinary player-owned bot capability remain
enabled. This startup fixture omits automatic random-world population and
the generated addclass reserve pool; it does not validate bot gameplay.
The six effective values are preserved in the existing evidence artifact.
Both existing five-minute process deadlines gain a 30-second forced-kill
grace to terminate a future TERM-resistant startup. No deadline increases,
source edits, dependency changes, sentinel skips or test changes are included.

Existing YAML validation and all 17 shell syntax checks passed. Executing the
exact embedded transformation against the pinned distributed config changed
only the four intended nonzero settings, preserving Enabled=1 and AccountCount=0.
No new test suite or prelaunch gate was added. A fresh complete clean control
and existing tamper control must validate the revised judge; this historical
run remains cancelled and the sprint clock remains unstarted.
