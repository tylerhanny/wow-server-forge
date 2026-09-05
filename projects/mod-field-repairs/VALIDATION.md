# Field Repairs validation

Status: complete implementation checkpoint awaiting independent source review and the
required official candidate gate. **Compilation, installation, module startup and native
unit execution: NOT_RUN.** No local C++ compiler is available. No live server or client
has been accessed. This document contains source reasoning, not execution evidence.

## Exact target and isolation

- AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`.
- Playerbots `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.
- Ubuntu Server 24.04 x86-64, WoW 3.3.5a build 12340.
- Native `src/` discovery and `Addmod_field_repairsScripts`; native `conf/*.conf.dist`.
- No CMake/build hooks, warning suppression, dependency edits, SQL, world spawns,
  item grants, custom debit, persistence or external runtime calls.
- Independent judge remains unchanged. The precise owner-authorized WorldMock correction
  is confined to disposable CI, never an installation/module dependency.

## Pinned source inspection

The implementation was checked against exact-pin public source cached inside the Forge.
Relevant identities were compared with the existing official source inventory:

| Source | Git blob | Raw SHA256 |
|---|---|---|
| `Player.cpp` | `2494c50366d891a930c6816b338e63449ae165f3` | `a0a957cdf288178d8fb5f259873ab8be85d27a12a90c703abeb5229e24ea4f4d` |
| `Player.h` | `b4ef4551b704f66662ed406580436dc554c69f64` | `74bbdb808f307ca346bde6933519364b6e198015e84e730ebc03db7e043266dd` |
| `Item.h` | `7ee99e77bd1e79a037c39f2e51384f6f32f016c4` | `51591ba537339aca1820597aefe3c51ef07ee8d3de2e4e24a2ca30b1a51a3864` |
| `ItemTemplate.h` | `2ce1f3195401788d1586e96cf30e4be3d007da41` | `ba59e1dc1d72e2a0ea855533b9def8295a16493b203686a46cdd8fffcad16402` |
| `Bag.h` | `dff1d41437f235f7a03b1be4de8312b4fa267e87` | `a7ac7c11e56e413abc6c4a80bdf322abeddf41c985eb65c6aa2bac9017f8f798` |
| `DBCStores.h` | `f1c5f98fb934f7815c9bca553988074bff66b861` | `75aefe478f31fdebdcce59bccb83f42314408706a9584bbfc61bf64dbf2d48f8` |
| `DBCStructure.h` | `3db5fe364fab348ee3b514c1c85488ee0c3a5c9d` | `c8f2d645c0ce4b51d5586aec6ba43143c8ea6fd2ed273efdc5a1528ae6bc3279` |

`Player.h:2084–2085` exposes paid repair publicly. `Player.cpp:4900–4990` gives the exact
slot iteration, unsigned/double/float price order, personal signed debit, per-item
affordability continuation and native durability/stat changes. Personal payment does not
assign returned TotalCost, so the module reports observed wallet change instead.
`ItemTemplate.h:557–567` narrows its index to uint8; the module checks raw class/subclass
first. `DBCStructure.h:904–913` provides the 29 multipliers and float quality factor.

Command and lifecycle hooks use the pinned public interfaces already inspected for the
Practical modules. Teleport exclusion uses public `IsBeingTeleported()`; no private delayed
teleport method is called. Near/far semaphores also cover the pinned queued teleport branches
at returned command boundaries. All eligibility and current pricing are rechecked on confirm.

## Source checks and remaining execution

`FieldRepairsRuleChecks.cpp` contains compile-time assertions of the actual consent and
cost helpers. Cases cover exact expiry, normal/fractional/zero factors, inconsistent
durability, uint32 product overflow before the double factor, unsigned conversion bounds,
signed debit bounds including float rounding at INT32_MAX, negative/NaN/infinite inputs
and extreme repair rates. These assertions **have not compiled locally**; their result
will be established by the real module build. No new test framework or official test
filter was added.

Before acceptance the exact frozen SHA requires the existing full official configure,
build/install, config discovery, SQL applicability, startup, unfiltered native tests,
source/fixture integrity and independent artifact review. Expected default INFO marker:
`FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`, with `Logger.module` severity `4`.
No SQL exists. A dry-run/config marker cannot execute player repair commands or establish
client inventory/stat behavior.

Independent implementation SOURCE_REVIEW and ONE_HUMAN_REVIEW: **PENDING**.
Proposal quality, pinned feasibility and complete solo design were independently approved
before code; that earlier disposition does not pre-approve this implementation.
The README's exact solo manual checklist remains **PENDING LIVE/IN-GAME VALIDATION**.

No failed candidate run is omitted: this project has not yet been dispatched.
