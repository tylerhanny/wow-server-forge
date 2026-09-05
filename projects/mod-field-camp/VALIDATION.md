# Field Camp validation

Candidate state: independently reviewed minimal compilation repair awaiting revalidation.
No local C++ compiler is available. No build/install/runtime/test success is claimed.

| Check | Actual result |
|---|---|
| Director and independent one-human proposal review | PASS, before implementation; `decisions/field-camp-selection.md` |
| Independent implementation/source review | PASS for exact repair `6ce52323b96be5dba4f4dfea5668032d17acdc3a`; final changes record review/source evidence only |
| ONE_HUMAN_REVIEW for implementation | PASS at the same repair checkpoint for the complete solo source path; actual execution/client evidence pending |
| Exact pinned API inspection | Source-only: signatures and caveats below verified |
| Whitespace hygiene | PASS: `git diff --cached --check` on the complete initial candidate; rechecked at commit |
| Module discovery/configure | PASS in failed candidate run `33952603462`; repaired candidate requires its own run |
| Compilation | FAIL for `ec9eea979c9344853aaf02d46ba9f6632636254b`, run `33952603462`; repair NOT_RUN |
| Disposable install/config loading | NOT_RUN |
| SQL/data | Not applicable: no module SQL or authored world data |
| Official candidate gate | FAIL for `ec9eea979c9344853aaf02d46ba9f6632636254b`, run `33952603462`; repair NOT_RUN |
| Disposable startup/module load | NOT_RUN; expected INFO marker `FIELD_CAMP_CONFIG` |
| In-game manual checklist | PENDING LIVE/IN-GAME VALIDATION |

The external Director attestation must name the frozen candidate SHA, exact judge SHA/hash,
AC/PB pins, run/build/install/SQL/config/startup results and independent Reviewer disposition.
A configuration marker alone is not arrival or gameplay evidence.

## Actual compilation failure and minimal repair

Official run `33952603462` against `ec9eea979c9344853aaf02d46ba9f6632636254b`
failed at `FieldCamp.cpp:79:48`: `HasDelayedTeleport` is private in pinned `Player.h:3019`.
The actual complete build log records that diagnostic at lines 245–249. Configure and
source/compile-command provenance passed; full compile failed, and install/runtime/unit
execution did not run. The prior source review missed member accessibility and is not
retroactively treated as a compile pass. Failed SHA and run remain preserved.

The code repair only removes that private call and retains public `IsBeingTeleported()`.
Pinned `Player.h:2125` checks both near/far semaphores. The delayed same-map branch at
`Player.cpp:1509–1516` sets its near semaphore before returning; the delayed far branch
at `1574–1581` likewise sets the far semaphore. `PlayerUpdates.cpp:419–423` later consumes
the private queued state and calls `TeleportTo`. Thus the public predicate already rejects
those pending requests; no safety policy, dependency source, pin or judge change is needed.
All three cached raw source hashes were rechecked against exact-pin inventory and matched.
Independent Reviewer approved the exact repair `6ce52323b96be5dba4f4dfea5668032d17acdc3a`
for source correctness and the unchanged complete one-human loop. A full official run is
still required for the frozen final candidate.

The bounded dispatch check also verified `Opcodes.cpp:280`: `CMSG_MESSAGECHAT` is
`PROCESS_THREADUNSAFE`; `WorldSession.cpp:65–106` excludes it from the map packet filter
and routes it through the world session filter. `ChatHandler.cpp:307` invokes the command
parser. There is no callback or command dispatch between the inline private-flag and
near/far semaphore assignments in either delayed branch. The two newly read public source
files match pinned inventory: Opcodes Git blob `c2d99161e6220ac6012e4a63cf293278a22660a5`,
ChatHandler Git blob `e5381d13b68a4ddc157f1d70a5eefbf310b04fdb`.

## Pinned API evidence and implementation choices

All source references use AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
Small public source caches were compared against the independently verified pinned source
inventory from disposable control evidence; no downloaded dependency file is committed here.

- `Player.h:1107–1110` has `TeleportTo(WorldLocation const&, options=0, target=nullptr)`.
  `Player.cpp:1401–1646` validates maps, applies default movement/control/transport cleanup,
  invokes `OnPlayerBeforeTeleport`, and can return true for a delayed same-map request.
  Client acknowledgement/arrival remains separate. No privileged options are used.
- `Player.h:2125` exposes the public near/far teleport-state check, including the delayed
  branches described above. `HasDelayedTeleport` at 3019 is private and must not be used
  by modules. `Player::CanTeleport` is acknowledgement bookkeeping, not eligibility.
- `Player.cpp:2191–2195` implements `IsFalling()` with previous Z; explicit movement
  FALLING/FALLING_FAR checks also reject jumping/falling. `Unit.h` exposes flying including
  disabled gravity, hover, water, combat, vehicle and control state getters.
- `Object.h:517,519,694` exposes phase and transport. `InSamePhase` may permit overlapping
  masks, so saved/current phase equality is required. `Object.h:524` exposes `IsOutdoors`.
- `Map.h:397` exposes phase-aware `GetHeight` with a bounded search distance; `Map.h:251`
  exposes `GetLiquidData` and the pinned liquid-contact mask is used. Ground floor is
  recorded/rechecked without substituting the saved Z. `MapMgr.h:110` validates WorldLocation.
- `Position.h:261` supplies `WorldLocation(mapId, Position const&)`.
- Native `src/`/`conf/` discovery and `Addmod_field_campScripts` avoid build hooks.
  Existing PlayerScript login/logout and WorldScript after-config hooks clean session state.

Independently matched new header identities during implementation:

| Source | Git blob | Raw SHA256 |
|---|---|---|
| `Entities/Unit/UnitDefines.h` | `3b81afcadc2cee120f0c179727231be2a9675196` | `6bdd9185c52f27f26be9f4a906be214f58cb66f01a12c3cad550f5fa0e1c31ec` |
| `Entities/Object/Position.h` | `f1e0cfab6458a1d24084ef2869bf6a9a3f600f9c` | `de8e1af86c0cba2a2e2a06400997d5d2810d56c78a6ef5594cf7c481fa9629bb` |
| `Entities/Object/Object.h` | `ce311a2ef17dc776ccdf240dd8305196210c2072` | `56fbe0a67239f279c167e7f1127710f17881954ab48b60aa4045580036160c2e` |
| `Maps/MapMgr.h` | `8524382c11a36c4819ca422c811e78fbc4ccc6f0` | `7f010affbd5fc74c0ecc990cd8172f119b76369468ce5d5c09c7d7500652f8ca` |

Session mutation and settings are protected by one mutex. Core calls and chat occur outside
the lock. A generation/revision check rejects a camp changed while landing is inspected;
the cooldown reservation is rolled back on native rejection without recreating a session
cleared by reload/logout. Clear/replacement do not reset cooldown. No delayed module task
holds Player pointers; native TeleportTo owns its own transfer lifecycle.

## Remaining manual uncertainty

Actual arrival, safe terrain interpretation, PvP/phase edge conditions, other module vetoes,
temporary pet unsummoning and optional Playerbot regroup behavior require later disposable
client testing. The full one-human checklist and conservative limitations are in README.
