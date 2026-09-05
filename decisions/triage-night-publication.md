# Exact Triage Night public-source authorization and execution

The owner directly authorized public-source publication in the conversation; recorded
2026-09-05T14:28:20Z. This resolves the earlier automatic publication rejection only for:

- Repository: `https://github.com/tylerhanny/wow-server-forge.git` (PUBLIC).
- Branch: `project/triage-night`.
- Exact unchanged candidate: `b404a1bd4614a8b956187f17baf585eee6d16cf6`.
- Purpose: the existing official Forge validation workflow and its required review.

The owner expressly acknowledged that this publishes the candidate source publicly.
Local worktree/HEAD/branch/origin were checked clean and exact. The authorized
`git push -u origin project/triage-night` succeeded without altering the candidate.
Subsequent `git ls-remote --exit-code origin refs/heads/project/triage-night` returned
exactly `b404a1bd4614a8b956187f17baf585eee6d16cf6` for that ref.

Independent Reviewer then dispatched exactly one required official run:
[33971943070](https://github.com/tylerhanny/wow-server-forge/actions/runs/33971943070),
created2026-09-05T14:29:03Z, default-branch judge
`8070cf87ba160d08c507e98dc809a949c573f986`. Protected workflow/validation bytes are
unchanged from the accepted judge. Actual run/artifact review remains required before READY.

No additional project/repository/branch, changed candidate publication, dependency change,
live-server access or validation relaxation is authorized by this narrow instruction.
Do not ask again for this exact push. If the candidate SHA changes, its publication needs
new direct approval. Source/one-human/SQL review PASS is preserved; all official evidence
and the fixed schedule remain mandatory. The previous rejections stay historical, resolved.
