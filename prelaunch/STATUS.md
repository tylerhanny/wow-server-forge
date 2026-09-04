# Prelaunch validation record

The sprint remains **ARMED_NOT_STARTED**. No timestamps have been started.

**Owner explicitly resumed; reconciled at 2026-09-04T20:10:30Z.** Internal workers and
monitoring have resumed. The existing clean-control run was still compiling. One-human
playability authority and independent proposal reassessments are required before launch.

## Infrastructure

- Repository cloned into the selected project directory itself.
- `.worktrees/` and `.forge-local/` are ignored on main (`5160975`).
- Isolated lane worktrees created for Practical, Wildcard, and Reviewer.
- GitHub CLI access confirmed; `Official Candidate Gate` is active (workflow ID `350442956`).
- No live server or Adventure Nexus access performed.

## Assigned prelaunch work

| Owner | Assignment | State |
|---|---|---|
| Director | One-human locked authority and external proof; launch coordination | Active |
| Practical | Hunt Rhythm one-human reassessment | Proposal approved; awaits launch |
| Reviewer | Clean CI monitoring; one-human/Auteur independent review | Proposals reviewed; clean CI pending |
| Wildcard | Three-shortlist one-human paths and final creative choice | Stormwright selected; awaits launch |

## Required launch evidence

- New one-human authority control: **REJECTED as required** by the unchanged official judge.
  - Candidate `813e433cfb69b37a7f56e6db55a58a2d410c6add` modified only locked
    `ONE_HUMAN_PLAYABILITY.md`; scope rejected it at `2026-09-04T20:16:57Z` before build.
  - Run: https://github.com/tylerhanny/wow-server-forge/actions/runs/33915425037
  - Judge `7317977b3619e6984f76fb8bcd7c25b0af0610d1`, workflow hash
    `c7ce13faa48f8336b3b3c161e5ab202c717e7eaf4b1308ece56b147542ee6e81`.
  - Evidence: `prelaunch/evidence/one-human-tamper-control.json` and matching run log excerpt.
  - No workflow change or interruption of the clean control was needed.

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

At pause the corrected clean run had passed scope/discovery/configure and was still compiling.
Compile/install/runtime/unit-test success remains unproven until its actual result is inspected.

Reviewer repair rationale and exact source evidence: `prelaunch/reviewer-audit.md`.
The repair preserves both dependency pins and warnings-as-errors, adds the missing
Playerbots disposable DB connection, and strengthens recorded judge, loader, test,
dependency and runtime evidence. No acceptance requirement was weakened.

## Prepared launch choices (research only)

- Practical: `mod-hunt-rhythm`, opt-in outdoor kill-XP rhythm, bounded to a small
  bonus with no SQL or persistent economy. Proposal: `notes/practical-first-project.md`.
- Wildcard: **Stormwright selected for launch after the completed tournament**. The owner rejected The Small Council;
  it is preserved only in `IDEA_VAULT.md`. The AI Auteur tournament requires at least five
  mechanically distinct concepts, a shortlist of three evaluated by Director and Reviewer,
  then Wildcard's choice among passing options. See `WILDCARD_AUTEUR.md`.
  - Completed comparison: `prelaunch/wildcard-quality-pass-1.md` (source lane commit
    `ad264556c8fd688ea462ead3ab7ece753f142819`).
  - Shortlist: Stormwright, Holdfast, Warband Arena. Wildcard preference: Stormwright.
  - Director comparison: `decisions/initial-project-selection.md`.
  - Independent dispositions: `prelaunch/reviewer-one-human-dispositions.md`, source `0aa6e58`.
  - Wildcard final choice: `prelaunch/wildcard-final-choice.md`, source `fded6b8`.
  - All four assessed concepts passed the one-human proposal floor; Stormwright is the
    selected flagship, Holdfast deferred fallback, Warband deferred for comparative closure risk.
  - Independent asset findings: `prelaunch/stormwright-visual-audit.md` (source lane
    commit `e9a5fba`). These are source/data findings, not client gameplay validation.
- These are distinct prospective assignments, not started projects or harvest entries.

Every current/future project must also pass locked `ONE_HUMAN_PLAYABILITY.md`. No current
concept is automatically accepted or rejected. Full human/bot roles, scaling, no-bots behavior
and complete loop have independent proposal dispositions; real bot feel remains pending live tests.

Practical independently audited one-human propagation at main
`2cc3ae60e4607dc0879194a598884128c3e25021`: **PASS, no omissions** across the dedicated
authority, AGENTS, mission, team protocol, Auteur standard, all four role charters, proposal
requirements, finish gate and handoff template. This read-only audit did not change the judge.

Disposable controls are infrastructure tests and do not count as Forge projects.
Launch remains forbidden until the rejected tamper and passing clean control are recorded here with exact SHAs and run URLs.

## Continuity

Task heartbeat: `wow-forge-director-continuity`, **ACTIVE after explicit owner resume**;
15-minute interval, with the mandatory one-human policy included. No duplicate was created.
Recovery procedure: `prelaunch/RECOVERY.md`.

The Director manages internal subagents; separate user-created worker chats are not required.
Every resume must fetch safely and reconcile branch/CI evidence before acting. Any automated
wake-up must preserve the unset clock until both controls are proven, and never extend a
recorded deadline after launch.
