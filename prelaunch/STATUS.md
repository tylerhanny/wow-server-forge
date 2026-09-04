# Prelaunch validation record

The sprint remains **ARMED_NOT_STARTED**. No timestamps have been started.

## Infrastructure

- Repository cloned into the selected project directory itself.
- `.worktrees/` and `.forge-local/` are ignored on main (`5160975`).
- Isolated lane worktrees created for Practical, Wildcard, and Reviewer.
- GitHub CLI access confirmed; `Official Candidate Gate` is active (workflow ID `350442956`).
- No live server or Adventure Nexus access performed.

## Assigned prelaunch work

| Owner | Assignment | State |
|---|---|---|
| Director | External tampering control; workflow dispatch/evidence; durable coordination | In progress |
| Practical | Minimal exact-pin clean module control on `project/forge-smoke-clean` | In progress |
| Reviewer | Independent judge/source audit and evidence-backed prelaunch repairs | In progress |
| Wildcard | Independent pinned-API scouting and first-project proposal; no implementation before launch | In progress |

## Required launch evidence

- Tampering control: **REJECTED as required** by the default-branch judge.
  - Candidate: `2d74a0b1599313a9b09c7baf5b961d3744f48ed6` (`project/forge-smoke-tamper`).
  - Judge commit: `516097591614c2df9c401b3283f60a24e6cb2e05`.
  - Run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33910753708
  - At `2026-09-04T19:21:49Z`, the integrity step rejected the deliberate `VALIDATION_INTEGRITY.md` change with exit code 1, before dependency checkout/build.
  - Log excerpt: `prelaunch/evidence/tamper-33910753708.txt`.
- Tampering control after Reviewer repair: **REJECTED as required**.
  - Same tamper candidate `2d74a0b1599313a9b09c7baf5b961d3744f48ed6`.
  - Judge `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b`.
  - Run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33911649850
  - Actual authority rejection retained in `prelaunch/evidence/tamper-33911649850.txt`.
- Clean control configure/compile/install/immutability/config/runtime: **IN PROGRESS**.
  - Candidate: `87b822fd41bb6013358aa6f5e16ca252ad79761c` (`project/forge-smoke-clean`).
  - Initial judge: `283b0d4d063458cb4db6f1fa81d314ad8a82f080`.
  - Initial run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33911309528
  - Initial run passed configure, then was **CANCELLED** during compile because the
    independent source audit proved the fourth database fixture was missing. It is
    not accepted as compile/runtime success.
  - Corrected judge: `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b`.
  - Active corrected run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33911646203
  - Expected dry-run proof: `FORGE_SMOKE_CONFIG reload=0 enabled=1 control=314159`.
- Reviewer judge disposition: **PENDING**.

Reviewer repair rationale and exact source evidence: `prelaunch/reviewer-audit.md`.
The repair preserves both dependency pins and warnings-as-errors, adds the missing
Playerbots disposable DB connection, and strengthens recorded judge, loader, test,
dependency and runtime evidence. No acceptance requirement was weakened.

## Prepared launch choices (research only)

- Practical: `mod-hunt-rhythm`, opt-in outdoor kill-XP rhythm, bounded to a small
  bonus with no SQL or persistent economy. Proposal: `notes/practical-first-project.md`.
- Wildcard: `mod-small-council`, independent emote-riddle critter courts with a
  persistent narrative ending. Proposal: `prelaunch/wildcard-scout.md`.
- These are distinct prospective assignments, not started projects or harvest entries.

Disposable controls are infrastructure tests and do not count as Forge projects.
Launch remains forbidden until the rejected tamper and passing clean control are recorded here with exact SHAs and run URLs.

## Continuity

Task heartbeat: `wow-forge-director-continuity`, active every 15 minutes.
Recovery procedure: `prelaunch/RECOVERY.md`.

The Director manages internal subagents; separate user-created worker chats are not required.
Every resume must fetch safely and reconcile branch/CI evidence before acting. Any automated
wake-up must preserve the unset clock until both controls are proven, and never extend a
recorded deadline after launch.
