# Hunt Rhythm

An opt-in outdoor leveling streak for AzerothCore 3.3.5a. Keep a safe hunting route
moving to earn a small capped bonus to eligible kill XP. No database tables, spawned
enemies, items, client addon, external service, or dependency source changes.

**Status: implemented first checkpoint; compile, install, runtime and independent
implementation review are PENDING. Not READY FOR LIVE TEST.**

Exact target: WoW 3.3.5a build 12340, Ubuntu Server 24.04 x86-64,
AzerothCore `47960183bb03b83e8943eb2f0f39c16df9710c9d` and Playerbots
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.

## Play

All commands work for ordinary player accounts and affect only the current character.
Console commands are disabled.

| Command | Effect |
| --- | --- |
| `.rhythm start` | Opt in for this login. Repeating it reports status without extending the timer. |
| `.rhythm status` or `.rhythm` | Show opt-in, eligibility, streak, remaining window and the next kill's percentage. |
| `.rhythm stop` | Clear the session and return to ordinary XP rules. |

With default settings, consecutive qualifying kills receive **0%, 2%, 4%, 6%, 8%,
then 10%** added base XP. Later kills stay at 10%. Every qualifying kill refreshes a
60-second window. An interval of **60 seconds or more** expires the chain before the
next qualifying kill. Ineligible events never advance or refresh it. Chat reports a
new chain and percentage changes; staying at the cap does not spam a notice every kill.

Death and entering a map reset the chain while preserving opt-in. Same-map zone travel
does not reset it. Logout/login, restart, `.rhythm stop`, and a successful configuration
reload clear opt-in as well. A failed configuration reload does not apply new settings.
Earned XP is never removed. Recovery followed by another eligible kill is a clean retry.

## Eligibility and XP behavior

The character must be alive, below the effective normal/trial level cap, allowed to gain
XP, and in an outdoor world map. The award must be positive normal kill XP and the victim
must be a hostile, XP-bearing creature in that same map with normal loot credit. Excluded:
players, pets, summons, totems, critters, owned/charmed units, elites, world bosses,
dungeons/raids, battlegrounds and arenas. Non-elite rare creatures remain eligible.
Quest/exploration XP does not qualify. The module neither grants credit nor bypasses
normal group range, level disparity, gray-target or tagging rules.

The bonus is `floor(base kill XP * percentage / 100)`. Very small awards can round the
bonus to zero. Here "base" means the amount at the pinned `OnPlayerGiveXP` hook, **after**
normal group share/gray penalties and XP aura adjustments. The core subsequently derives
pet XP from that amount (solo 100%, grouped 50%); player XP separately receives favored-area
+5%, partial-playtime reduction and either rested or RAF processing. Rested XP consumes
the normal rested pool. The displayed percentage is not a promise of identical percentage
changes to every final reward component.

The helper checks the added amount with wide arithmetic and bounds the pinned core's
float-rounded +5%, worst-case RAF total of 3x, and current XP. When those bounds cannot
be established, only the added bonus is withheld and ordinary XP is passed through. The
eligible kill still advances the chain. This does not repair pre-existing extreme-rate
core XP arithmetic. Additional modules that change this hook or the effective XP level
need separate compatibility review; this V1 targets the exact core plus pinned Playerbots.

## Install and configure

Use an isolated development server for installation and validation. This repository's
automation never connects to or deploys to the live server.

1. Check out both exact dependency commits above and place Playerbots in
   `azerothcore/modules/mod-playerbots`.
2. Copy this directory's contents to `azerothcore/modules/mod-hunt-rhythm`, so the module
   contains `src/` and `conf/`. There is no SQL migration or custom CMake hook.
3. Reconfigure and build using the server's ordinary native module build, then install
   into the disposable prefix. Native discovery calls `Addmod_hunt_rhythmScripts()`.
4. Copy installed `etc/modules/mod_hunt_rhythm.conf.dist` to
   `etc/modules/mod_hunt_rhythm.conf` if it does not already exist. Restart the test server,
   or use the normal operator config reload for later changes.
5. Check server logs for `HUNT_RHYTHM_CONFIG reload=0 enabled=1 window=60 step=2 cap=10`.
   A module-load message alone does not prove gameplay or a complete startup pass.

| Setting | Default | Accepted values |
| --- | --- | --- |
| `HuntRhythm.Enable` | `1` | `0` or `1` |
| `HuntRhythm.WindowSeconds` | `60` | 15–300 seconds |
| `HuntRhythm.StepPercent` | `2` | 1–5 percentage points |
| `HuntRhythm.MaxBonusPercent` | `10` | 1–20 percent |

Out-of-range numeric settings are clamped with a server warning. A cap need not be a
multiple of the step: the final increase stops exactly at the cap. Invalid nonnumeric
values follow the pinned core config reader's behavior. A successful reload clears every
session; players must use `.rhythm start` again. Disabling restores ordinary awards.

To remove the feature, stop the test server, remove `modules/mod-hunt-rhythm`, reconfigure
and rebuild/reinstall the server, and remove its installed config. There is no persistent
player data or SQL cleanup. Never replace running binaries as part of uninstall.

## One-Human Playability

**Primary qualifying path: one human, solo.** No second human, second client or second
operated account is required. Every ordinary leveling class can participate from level 1
until its effective cap; the demonstration below uses level 10–30 for visible XP amounts.
The human opts in, chooses a route and ordinary combat targets, manages health/mana and
pull risk, checks progress, and decides when to stop. No particular class ability, pet,
profession, multi-target attack, interrupt or simultaneous interaction is required.

The module spawns and scales no enemies. A solo player can pull one normal creature at
a time. The same timer and percentage cap apply regardless of party size. Route density
and class downtime affect whether a chain can be sustained; the bounded operator timer
can be adjusted after actual playtesting without removing the route/survival decision.
Timeout or death loses the streak, not earned XP, and never locks retry or exit.

**Optional path: one human with ordinary pinned Playerbots.** Any already supported
party composition may fight, heal, tank or follow through normal bot controls. No bot
must issue Rhythm commands, read chat, solve a custom mechanic, select menus, coordinate
positions or stop damage at a special threshold. Only the human's opted-in, ordinarily
credited shared XP awards advance their chain. Bots are never automatically enrolled.
No bots are required: removing all bots leaves the complete solo loop intact. Random
population and generated addclass accounts are not requirements of this module.

Proposal quality and one-human design were independently approved before implementation.
**ONE_HUMAN_REVIEW=PENDING for this implementation.** Actual class pacing, pet/rested XP
feel, bot pathfinding, bot competence and shared-credit behavior remain **PENDING
LIVE/IN-GAME VALIDATION**. CI dry-run exits before normal world updates and cannot prove
these properties.

### Exact manual checklist — one human only

All steps are **PENDING**, on a disposable test server with one stock 3.3.5a client.

1. Log in as an ordinary level 10–30 character in a normal outdoor area with several
   hostile, non-elite XP-bearing creatures. Stay solo without bots. `.rhythm status`
   must show opted out; `.rhythm start` must explain the rules without GM access.
2. Kill one suitable creature and check status: streak 1, a live timer, next award +2%.
   Kill five more, each less than 60 seconds after the preceding kill. Expect applied
   2/4/6/8/10% bonuses and a cap notice on kill six. One more timely kill stays at 10%
   with no repeated cap notice. This completes the full success/outcome loop.
3. During a chain, repeat `.rhythm start`: its timer must not extend. Wait until at
   least 60 seconds after the previous eligible kill and check status. Expect expiry;
   the next kill must restart at streak 1 and 0% without a second participant or menu.
4. Build another chain, die through normal combat, recover and retry. The chain resets
   while opt-in remains; earned XP remains. Changing maps must likewise reset the chain,
   while merely crossing a zone boundary within one map must not.
5. `.rhythm stop` must immediately exit; subsequent kills receive no Rhythm bonus.
   Start again, log out and back in on the same account/client: expect opted out.
6. Check ordinary quest/exploration rewards, gray targets, pets/summons, non-hostile
   critters, elites and dungeon enemies: none may advance/refresh a chain. Normal core
   rewards remain normal. XP-locked, dead and capped characters must get clear command
   feedback and no added XP. A valid credited outdoor kill can retry afterward.
7. If the character has a pet or rested pool, inspect the documented core-derived
   rewards. RAF behavior is source-reviewed; testing it is optional and must not require
   a second operated account for the primary demonstration. Record it untested if absent.
8. Optionally repeat the whole loop with an already available ordinary bot party, using
   only supported grouping/combat controls. Only the human enters Rhythm commands.
   Remove the bots and repeat a solo chain to verify the full no-bots path remains usable.
9. Operator check in the disposable server: reload a changed bounded timer/cap and verify
   sessions become opted out. Disable the feature and verify ordinary XP; re-enable and
   opt in again. Check clamping separately and retain resulting config warnings honestly.

## Validation

See [VALIDATION.md](VALIDATION.md) for actual evidence and remaining gaps.
`src/HuntRhythmRuleChecks.cpp` contains focused compile-time assertions against the real
rule helper, including exact expiry, refresh, cap, rounding, saturation and overflow
decline. They use no new framework or mocked server and count as passed only after an
actual compilation. They do not replace upstream tests or gameplay checks.
