# Triage Night validation record

Current status: **DEVELOPMENT — NOT READY FOR LIVE TEST**.

Exact pins: AzerothCore47960183bb03b83e8943eb2f0f39c16df9710c9d and
Playerbots2f7d9f774987d0157c6a0d0cc08c40bec3db3945, stock client12340,
Ubuntu24.04 x86-64. Only projects/mod-triage-night and its matching handoff may differ
from the candidate base. No official judge, protected input or dependency file is changed.

| Check | Actual evidence/status |
|---|---|
| Proposal quality and one-human design | Independent Director/Reviewer PASS recorded before implementation on main8d21e8b; this is not implementation acceptance. |
| First local source checkpoint | fb5abd8f3a369ea92adef4842064405d48ee366f; sent to independent Reviewer without pushing an unfinished remote branch. |
| Pinned API/data inspection | Relevant native assist/heal, lifetime, position and model references inspected; exact identities in REFERENCES.md. Own follow-through corrected getClass spelling before gate dispatch. |
| Whitespace/scope hygiene | First source checkpoint git diff --cached --check passed; final candidate must repeat its normal scope/hygiene check. |
| Independent source review | PENDING for the complete final implementation. |
| ONE_HUMAN_REVIEW | PENDING for implementation; proposal PASS does not carry automatically. |
| Module discovery/configure/full compilation | PENDING; no local C++ execution is claimed. |
| Install/config/SQL/reference checks | PENDING actual official evidence. Owned SQL/model references are complete but static inspection is not SQL application. |
| Disposable startup/module load/native units | PENDING actual official evidence. No OnStartup actor is required or registered. |
| Official exact-candidate gate | NOT DISPATCHED. Reviewer owns the one necessary full run after source-ready freeze. |
| Logged-in encounter, stock health bars/poses, healing and balance | PENDING LIVE/IN-GAME VALIDATION; dry-run/module-load cannot prove them. |

## Project-local deterministic coverage

src/TriageNightRulesChecks.cpp is compiled with the module. Its static assertions exercise
all presets/role rotations, all five rounds/four breaks, all225 injury steps, nine burst
warnings whose target matches the later impact, finite non-stacking stabilization, expiry,
retry reset, delayed-update behavior and the six-minute hard cap. No assertion has executed
until actual C++ compilation succeeds. These checks supplement the unchanged official
native units; they do not replace the external judge or simulate a WoW client.

The controller keeps native player health/mana untouched. Injury actions preserve patient
health across rounds; the AI rejects outside damage and non-pilot healing, disables native
regen and aborts on reset/evade. Public commands enqueue bounded requests for map updates;
stale controller identities cannot apply stabilization/stop to a new shift. Session records
are bounded and cleared at logout. Controller leases remain counted through actual cleanup.
These implementation statements require independent inspection and official compilation.

## Required final evidence

Before READY FOR LIVE TEST, bind independent source and ONE_HUMAN review to the final source,
freeze the complete candidate, and run the current default-branch official gate at its exact
SHA. Record candidate/judge identities and actual configure/build/install/config/SQL/startup/
unit/integrity outcomes, retain any failed attempts, and fix material findings. No fixture
change or new observer is requested. Player-triggered actor behavior remains an explicit
later manual test; it must not be inferred from module discovery or a dry-run exit.
