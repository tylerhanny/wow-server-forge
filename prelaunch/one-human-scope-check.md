# One-human authority path enforcement check

Independent Reviewer performed a disposable local reproduction of the existing official path allowlist. No judge change was needed or made.

- Judge commit: `a1754a6bb8c8310fac7e78f1452a5f3fec766e8b`.
- Workflow SHA-256: `c7ce13faa48f8336b3b3c161e5ab202c717e7eaf4b1308ece56b147542ee6e81`.
- Code tested: the exact `bad=...` allowlist block extracted from the `scope` step in that committed workflow, without rewriting its expression or conditions.
- Fixture: a new Git repository inside ignored reviewer `.forge-local/one-human-scope-fixture`, with a committed baseline authority file and actual positive/negative commit diffs.

| Local fixture diff | Result |
|---|---|
| `projects/mod-scope-control/README.md` plus `handoffs/mod-scope-control.md` | Allowlist exits 0. |
| The same project/handoff plus modified root `ONE_HUMAN_PLAYABILITY.md` | Allowlist exits 1, reporting the root authority path as outside allowed project/handoff paths. |

The exact rejection was:

```text
Candidate changed paths outside projects/<slug>/ and handoffs/<slug>.md:
ONE_HUMAN_PLAYABILITY.md
```

This reproduces the root-file protection even though the earlier explicit locked-name regex predates the new authority. That regex is not the only scope control: the following positive path allowlist rejects every root file. Adding a cosmetic name to the earlier regex would not strengthen this result and would unnecessarily change the running judge's identity.

This is **local scope-block evidence only**. It is not a claim that the fixture passed the entire official workflow, compiled, started, or exercised actual one-human gameplay. The clean control remains subject to its separate complete official run and the new authority's substantive design/source review remains mandatory for every gameplay candidate.

The small reproduction script and full JSON output are retained in reviewer `.forge-local/verify-one-human-scope.py` and `.forge-local/one-human-scope-result.json`; no dependency sources or generated build trees are committed.
