# Stormwright applicable runtime evidence path

This post-launch work supplies the normal-startup evidence already required for a
candidate using `WorldScript::OnStartup`. It does not restart prelaunch, replace any
existing check, or certify encounter gameplay, public walking access or bot competence.

The [official AzerothCore setup guide](https://www.azerothcore.org/wiki/linux-server-setup)
links pre-extracted data. The [public v20 release](https://github.com/wowgaming/client-data/releases/tag/v20.0)
contains `Data.zip`, asset `482333572`, size `1196168257`, published 2026-07-19.
Its API SHA-256 is `a3d4df635ae6c2c8f08052c32a79e0f806955150ad36b014a823dd08a32a4610`.
The supplemental check verifies the complete download against that digest before extracting
only maps/vmaps/mmaps. The original recorded ac-data DBC checkout is preserved.

The exact pinned core (2026-08-28 commit `47960183bb03b83e8943eb2f0f39c16df9710c9d`)
expects MAPS version9 (`GridTerrainData.h`, blob `18324d574e00781121aecd039a272983b757b2d4`),
MMAP version20 (`MapDefines.h`, blob `f23e35e79df30b7090c90e08aeca94ff94e5e641`), and
VMAP_4.8 (`VMapDefinitions.h`, blob `971913a0e7cb6f16343eae04616115ea35974b09`).
Read-only byte-range inspection of the public ZIP found matching headers and client12340.
This preliminary probe downloaded approximately6.3MB, not the whole release; it is not
a substitute for the full hash verification or real core loading in the necessary CI run.

| Public archive entry | SHA-256 of extracted entry bytes |
|---|---|
| maps/0014338.map | 31b4ac2c572399bc6728abacd590b16a69eb6baf38422606189b48d51ff3b31a |
| maps/0014339.map | 53f91498f975e0214d85cd94d80e8d408cd464052bc62f8dca2d348525651677 |
| mmaps/0014338.mmtile | b0b5cb0e9ef7bc9fd3e4fafb06813488b8352860ff7a59a7fe640452a448f1f2 |
| mmaps/0014339.mmtile | 03428a2c39b346690f00d1a7f975a2dc04a899632919eb31680041147713b99e |
| vmaps/001.vmtree | e7c792d29fc91da53595128ae98cf3bf0d4763fbd2adf6294037fdf0e7ac9c62 |

A bounded offline projection of the pin's uint16 terrain interpolation puts the center,
registrar, three rods and add position near Z=-58.75008. The113 sampled footprint points
span approximately[-59.20214,-58.74958], maximum center difference0.4521. Those two terrain
tiles have no liquid/hole blocks. This is terrain-data research only: the actual module
still derives Z at runtime and applies its own phase-aware height/ground checks. VMAP
collision, MMAP routes, class balance, visuals and actual human/bot traversal are not
proved by this projection. No guessed coordinate replaces runtime checks.

The protected supplemental script uses the same installed binary, module SQL and disposable
localhost databases after all existing dry-runs and unfiltered upstream unit tests.
It records exact owned SQL identities, enables module INFO evidence without hiding errors,
binds only loopback, keeps RA/SOAP/cluster disabled, observes actual registrar spawning,
allows normal updates and requests console shutdown. The five-minute runtime bound and
30-second termination grace are retained. All logs, fixture settings, release identity and
success receipt enter the normal artifact. Existing final source/log/integrity checks follow.
The existing project rules executable also compiles with strict warnings-as-errors and runs
in this same required candidate job; no additional control cycle is dispatched.

Independent Reviewer inspected the draft configuration, pinned SQL/CLI/logging APIs and
unchanged-stage placement, finding no blocking fixture contradiction. Final exact-revision
review and actual CI execution remain separate evidence. Both gameplay lanes continue.
