# Triage Night — Wildcard handoff

Status: **SOURCE_REVIEW=PASS; implementation ONE_HUMAN_REVIEW=PASS; official acceptance PENDING**.
Project: projects/mod-triage-night. Branch: project/triage-night. Exclusive builder:
Wildcard. First local source checkpoint: fb5abd8f3a369ea92adef4842064405d48ee366f.
Complete independently reviewed source: e8907bd72940628148150621d7c8143624c47045.
The final freeze changes review-status documentation only; its exact SHA will be used for
the required official dispatch. Owner-reported fixes preempt this project.

Triage Night gives one priest a repeatable support-role encounter: three persistent patients,
five45-second rounds, four10-second breaks and two6-second stabilization charges. Normal
healing spells and mana create priorities; no player resources or economy rewards are granted.
Training/Veteran changes pressure. Success/failure, status/results, normal rest/retry and
abort are complete in source; actual compilation and client behavior remain unproven.

## One-Human Playability

The qualifying path is one level-80 priest with ordinary learned direct single-target heals
and healing gear, on one normal client/account with zero bots. Every custom action belongs
to the human: start/preset, heal target/spell, stabilization target/timing, result/retry/stop.
There is no second human, operated account or client. Bots provide no required helper role;
other healer classes and party/AoE compatibility are not claimed.

Use .triage help, then .triage start on suitable dry open outdoor ground. The start checks
nearby height/LOS and can decline unsuitable ground without a GM teleport. After the briefing,
keep all three numbered patients alive through all five rounds. Patient health and normal
player mana carry forward. .triage stabilize 1|2|3 pauses that patient's future deterioration
for six seconds without healing them. Only two charges exist. Scripted loss bypasses shields.
Use .triage status for health/charges and the last five results this login. Complete the shift
or experience a normal patient/pilot/departure/time failure; rest normally and retry or stop.

Owned AI blocks outside damage and non-pilot healing, disables native regeneration, and
aborts on reset/evade. Active casts/channels are allowed. Death/logout/map departure,
configuration reload/disable, partial creation and timeout clean up owned actors. Global
actor leases and per-login queues/results are bounded.

Independent **ONE_HUMAN_REVIEW=PASS for implementation source** at
e8907bd72940628148150621d7c8143624c47045. SOURCE_REVIEW and owned SQL/reference source review
also passed at that source. Compilation/install/runtime and official acceptance remain pending.
Actual targetability, stock health bars/poses, pressure/balance and optional bot coexistence remain
**PENDING LIVE/IN-GAME VALIDATION**.

## Installation and acceptance pointers

- Exact AC47960183bb03b83e8943eb2f0f39c16df9710c9d; PB2f7d9f774987d0157c6a0d0cc08c40bec3db3945;
  stock client12340 and Ubuntu24.04x86-64. No upstream edits.
- Native module folder/discovery: modules/mod-triage-night; configTriageNight.Enable.
- Collision preflight is mandatory for creature template/model IDs911100–911103. SQL uses
  plain INSERT only: data/sql/db-world/2026_09_05_00_triage_night.sql. No permanent spawns,
  npc_text, quest/item/economy or character SQL. Native updater versus manual-once import
  distinction and guarded rollback are documented in README.
- No OnStartup registrar or new observer; commands start actors on the player's map update.
  Official module-load/dry-run evidence does not execute the logged-in encounter.
- Read docs/REFERENCES.md for exact native APIs/models/pressure values, docs/VALIDATION.md
  for the honest stage matrix, docs/DEMO.md for the future90-second capture, and README's
  ordered one-human smoke checklist. No such client test is claimed completed.
- Reversible disable: TriageNight.Enable=0 and normal config reload/restart. Full removal:
  stop, remove module/rebuild/install and its config, then guarded sql/uninstall_world.sql
  after checking owned identities. No live server action has been performed by Forge.

The final exact candidate must receive independent source/one-human review and the unchanged
default-branch official gate before it can be marked READY FOR LIVE TEST. Candidate and judge
SHAs, all actual stage results and any failures must be retained in the final evidence record.
