# WoW Server Forge — Final Harvest

Only projects that pass the mandatory finish gate in `AGENTS.md` may appear in the READY section.

`Almost done`, prototypes, ideas, and unverified implementations belong elsewhere.

## READY FOR LIVE TEST

### Hunt Rhythm — Practical

**Delivered early on 2026-09-05.** Opt-in outdoor leveling streaks reward choosing routes
and sustaining ordinary eligible kills, with a modest base kill-XP bonus capped at 10%
by default. It provides a repeatable solo leveling loop without custom SQL, NPCs or economy.

- Exact candidate: `4aaa3ae188e7bcdba2569676911e14142ac378e2`, branch `project/hunt-rhythm`;
  its unchanged project tree is integrated on main.
- Exact target: AC `47960183bb03b83e8943eb2f0f39c16df9710c9d`, Playerbots
  `2f7d9f774987d0157c6a0d0cc08c40bec3db3945`, Ubuntu 24.04 x86-64, client 3.3.5a build 12340.
- [Official run 33951428776](https://github.com/tylerhanny/wow-server-forge/actions/runs/33951428776)
  PASS under judge `e35e85a787d7576d58cb691f6335b638ee8bc342`: full compilation,
  installation, config/data/SQL checks, auth/world dry-runs, native unit tests and final
  dependency integrity. Actual native module loader/config marker observed; Errors.log empty.
- Independent source, actual artifact and **ONE_HUMAN_REVIEW=PASS**.
- [Final attestation](handoffs/mod-hunt-rhythm.md), [independent review](reviews/mod-hunt-rhythm-final-review.md),
  [machine-readable evidence](deliveries/evidence/mod-hunt-rhythm-33951428776.json),
  [exact install/config/rollback and one-human smoke guide](deliveries/mod-hunt-rhythm-install.md).
- Source package: `mod-hunt-rhythm-4aaa3ae.zip`; SHA256
  `72f4b97e6ad9c2b59c7cbc8c666e07ba43de5090c27ae76d4e269db5b53af6fb`.

One human can start with `.rhythm start`, reach the six-kill default cap, fail by timeout
or death, retry and exit with `.rhythm stop`, using one ordinary character and stock client.
Bots are optional ordinary combat companions; they operate no custom mechanics.
The linked guide covers exact ordered steps and lifecycle/exclusion checks.

Remaining **PENDING LIVE/IN-GAME VALIDATION**: real XP/class/pet/rested/RAF interactions,
route pacing and bot behavior/feel. Other XP-modifying modules were not part of this
validated combination. State is session-only; disabling/removing never subtracts earned XP.
The gate retained four visible verified upstream warnings and no project warnings. Native
tests selected 11,395: 5,909 passed, 5,486 native conditional skips, one pre-existing disabled
test; no Forge test was removed or weakened. See final evidence for exact identities.

Stormwright and Field Camp remain pending actual validation and independent evidence review.
Neither is included in READY. Deliver each ready candidate independently; handoff is due
by 2026-09-06T12:34:32Z, followed by the protected six-hour owner feedback window.

## Current run totals (not final)

```text
Attempted: 3
Ready for live test: 1
Blocked: 0
Abandoned: 0
Research only: 0
Wildcard-ready projects: 0
Live server changes: 0 (must remain 0)
```

## Integrity rule

No project enters READY without satisfying locked `ONE_HUMAN_PLAYABILITY.md`, including
an explicit independent PASS and required README/final-handoff section. Optional human
multiplayer cannot conceal an incomplete one-human primary loop.

The final report must not inflate completed-project counts by splitting one coherent module into trivial subprojects.
