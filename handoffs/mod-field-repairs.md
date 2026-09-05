# Field Repairs — final independent acceptance and early handoff

```text
PROJECT=mod-field-repairs
OWNER=Practical
BRANCH=project/field-repairs
CANDIDATE_SHA=1450d92f8bcf3a8282526120753ed5f750939722
STATE=READY_FOR_HARVEST
OWNER_DELIVERY=READY FOR LIVE TEST; early delivery 2026-09-05
BUILD_RESULT=PASS_REAL_FULL_PINNED_BUILD
OFFICIAL_GATE=PASS
ONE_HUMAN_REVIEW=PASS
REVIEWER=Independent Reviewer/Closer; source and actual artifact review PASS
NEXT_ACTION=Owner installation/playtesting; actual feedback preempts additional work
```

This external main-branch attestation supersedes the frozen candidate's pending pre-run
status. Its exact tested project tree is integrated unchanged. Proposal approval was
recorded before implementation; acceptance now rests on this candidate's own actual gate
and independent source, one-human and artifact review.

## Feature, package and installation

Field Repairs buys native personal-gold repairs for equipped and carried gear while safely
outdoors. The ordinary human inspects status, requests the service, confirms within30seconds,
observes the actual gear/wallet outcome, earns gold and retries, or cancels/expires without
payment. Current native prices apply with no reputation discount, extra fee, free repair,
guild spending or automatic payment. Native affordability is per item: partial repair is
possible and is disclosed before consent. Bank, buyback and key slots are excluded.

Commands: `.fieldrepair` / `.fieldrepair status`, `.fieldrepair request`,
`.fieldrepair confirm`, `.fieldrepair cancel`. Only setting: `FieldRepairs.Enable=1`.
Consent lifetime is fixed30seconds. No SQL, NPC, permanent module record or bot repair exists.

[Exact installation/configuration/rollback and ordered one-human tests](../deliveries/mod-field-repairs-install.md).
Source package `mod-field-repairs-1450d92.zip` has six module files matching the exact
candidate's Git blobs. SHA256:
`6e266bc2dd1becb1ae0b036e521f4f3d31d5e8a13a8c8fb862bb4732215372d3`.
The source README retains its historically correct pending status; this external final
attestation records the later acceptance without substituting a different tested SHA.

Install as `modules/mod-field-repairs` using native discovery, reconfigure/build/install to
a separate disposable prefix, and copy installed `etc/modules/mod_field_repairs.conf.dist`
to `.conf` if an override is needed. No upstream loader/CMake or SQL edit is required.
Retain native `Logger.module=4,Console Server`; INFO is4 and WARN is3.

## Exact independent evidence

- Candidate `1450d92f8bcf3a8282526120753ed5f750939722`; reviewed implementation
  `e560e72a09ed99c4d3391c90a242f9b8f5a9b277`. Final freeze changed only review-status docs.
- [Official run33970121674](https://github.com/tylerhanny/wow-server-forge/actions/runs/33970121674)
  passed every applicable stage; validation job completed2026-09-05T14:02:41Z.
- Judge `8d21e8b1b4920b4966760ba621751725bd411444`; workflow SHA256
  `550fc47bc810b165707bb70f2c1f7ebfeab478466055deda3ab96f9e99aaf635`.
- Exact AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d`; Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`; Ubuntu24.04x86-64; stock3.3.5a build12340.
- Artifact9970803705,877388bytes; GitHub API archive digest
  `81710133c5ab281f38e8f15d3440a8ee6beefe801b5bf45de9936c19bdb8e4cd`.
  Extracted file hashes were checked; the archive digest is API metadata.
- [Compact evidence](../deliveries/evidence/mod-field-repairs-33970121674.json),
  [independent source review](../reviews/mod-field-repairs-source-review.md),
  [final independent review](../reviews/mod-field-repairs-final-review.md).

The unchanged judge configured Clang18, Release, all applications, static scripts/modules,
WITH_WARNINGS=ON, BUILD_TESTING=ON, NOPCH=true, ccache launchers and language flags
`-Werror -ferror-limit=0`, using protected file-provenance warning enforcement. Its exact
configure command is preserved in the immutable workflow and run. The complete protected
build command was `cmake --build ac/build --config Release -j 5`, then
`cmake --install ac/build --config Release` into a disposable prefix.

The203155-byte complete build log matches stream/receipt SHA256
`cdb19217d6b0b89bdcd848ada158a01a8b78d38abb1697fa2a5c07378af2e055`, return0.
All1830 compile commands retain Werror;1822 verified upstream-only demotions and both
project translation units stayed strict. Four unchanged Playerbots diagnostics remain
visible; no project/unknown warning or error was accepted. All ten protected judge hashes
match exact Git blobs. The3634-source before/after inventory matches and both dependency
trees are Git-clean. The exact authorized disposable WorldMock correction was identity-
checked and restored before install; no corrected fixture or dependency source is shipped.

Native module registration/install/config passed. The world dry-run loads
`mod_field_repairs.conf` and emits `FIELD_REPAIRS_CONFIG reload=0 enabled=1 consent=30`.
Both authserver/worldserver dry-runs completed; Errors.log is empty. SQL applicability
passed because this module owns no SQL. The Stormwright-only normal-startup supplement
was correctly inapplicable. Sixteen protected tests plus the real compiler scope probe
passed. Native tests selected11395:5909 passed,5486 native conditional skips and one
pre-existing disabled test. No Forge filter, removed assertion or newly skipped test was used.

The actual cache restored the accepted Stormwright run33960843535 key under the identical
protected-policy prefix. It recorded1826 preprocessed hits and4 misses, saved current
outputs, and reduced this full compile to422seconds (7m02s). All four upstream warnings
remain in the captured log. No per-warning cache-hit attribution is claimed and no verdict
was reused; the current candidate was fully linked, installed, started and tested.

## One-Human Playability

Independent ONE_HUMAN_REVIEW=PASS for the complete solo source and applicable disposable
evidence. One ordinary level1–80 character with durable gear, one human/client/account
can perform the whole service. No class spell, GM action, second participant or helper is
required. Zero bots is complete. Optional ordinary bots can fight/follow while the human
earns money; they receive no repair and operate no custom command. No enemy/roster scaling.

Exact manual order, all **PENDING LIVE/IN-GAME VALIDATION**:

1. Safely outdoors on a normal world map, compare `.fieldrepair status` to damaged gear/gold.
2. Request, read current personal-gold prices/partial-repair disclosure, then cancel.
   Verify no gear or money change and that direct confirmation refuses.
3. Request and confirm within30seconds. Compare real durability, wallet delta, repaired/
   remaining counts and restored broken-item stats. Healthy gear must incur no charge.
4. With insufficient funds, observe native no/partial repair; earn gold normally and retry.
5. Test expiry; confirm while combat or casting is active and require refusal without
   payment. Every confirm consumes consent. Merely entering and leaving combat does not
   cancel unexpired consent. Death/map/logout/reload clears it; recover and request anew.
6. Cancel or stop interacting to exit. In disposable operator testing, disable/reload blocks
   service and clears pending consent; re-enable needs a fresh request. Optionally test bot
   coexistence after the complete solo loop and verify only human gear/wallet are serviced.

Prices, native partial ordering, client inventory/stat updates, coexisting module callbacks
and bot-party feel remain manual. Wallet delta is observed, not an isolated transaction
ledger or refund promise. Unsafe item/pricing input refuses the whole attempt before the
single native repair call; this entry point does not patch the baseline core's arithmetic.

## Disable and rollback

Set `FieldRepairs.Enable=0` and successfully reload config or cleanly restart. Confirm
`enabled=0` in the log. For removal, stop normally, archive the module/config, move only
this module out, rebuild/install without it to a new prefix and retire its old config.
Keep Playerbots/unrelated modules and prior working binaries intact. No SQL/player record
cleanup is needed. Completed repairs and spent gold are ordinary core state and are not
undone by disable/removal. The Forge has not accessed or deployed to the live server.
