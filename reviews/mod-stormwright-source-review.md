# Stormwright independent implementation review

Reviewed checkpoint: `c1f3926dcc8988d6f1461affeee0c817c97f911d`.
Initial source checkpoint: `d41563ef97f2c09d851785542cddec186758194a`.

Final frozen candidate: `a1558178ceee2b92e020928ecb8fd3f59c3c34a2`.
Independent comparison found only README, validation and handoff review-status
changes; source, SQL, configuration and tests are byte-identical. The dispositions
below also apply to that final candidate, whose actual execution remains pending.

**SOURCE_REVIEW=PASS. ONE_HUMAN_REVIEW=PASS — implementation source only.**
Compilation, installed data, normal server startup and final exact-candidate
acceptance are pending. No gameplay, navigation, client or bot behavior was run.

The implementation, rules/checks, SQL/config, reference record, README and handoff
were inspected. The diff from launch base `72ce4e0` contains only the single module
and matching handoff; `git diff --check` passed. There is no candidate CMake hook,
production dependency edit, client change, permanent stock spawn edit or external API requirement.
The target remains exact AC `47960183bb03b83e8943eb2f0f39c16df9710c9d` and PB
`2f7d9f774987d0157c6a0d0cc08c40bec3db3945`.

## Corrected finding

The initial controller handled a pending boss victory before checking pilot death,
disconnect, departure, disablement or abort. A boss death followed by pilot failure
before the next controller update could incorrectly win. The reviewed checkpoint
checks those failure conditions first, then accepts the confirmed owned boss death.
README explicitly documents the resulting simultaneous-failure precedence.

## Reviewed behavior and exact API use

- Native registration, CreatureScript gossip sender/action methods, AI damage,
  attack, GUID and evade overrides match the pin. WorldObject summon duration is
  uint32 milliseconds; Creature despawn uses the chrono duration passed by the code.
- One registrar owns GUID-based roster, boss, rods, marker and bounded pursuers.
  Serial/actor/pilot/range/LOS checks protect each rod action. Charge is consumed
  before effects; stale/duplicate activation cannot award another heal or discharge.
- Tracking, lock and impact remain separate visible phases even after a delayed
  update. Ground retains a complete living solo-pilot recovery path at full ward;
  Discharge trades that recovery for damage, exposure and a nearby owned-add blast.
- Failure, timeout, abort, missing actors and evade end the attempt. Terminal state
  precedes despawn callbacks; run resources reset on retry. Owned health regeneration
  is disabled. No extra operator, custom bot menus or exact bot positioning is needed.
- Terrain comes from installed map data with bounded phase-aware height/liquid
  checks. No guessed Z fallback is accepted. This is not proof of public approach,
  navigation, terrain collision or client clickability.
- Recorded stock models and direct visual-kit packets provide visible feedback
  without casting the source encounter spells. Assets and packet existence do not
  establish actual visual readability; the manual checklist preserves that limit.

Practical's independent bounded SQL review also passed at this exact checkpoint:
all named columns match the pinned schema; the reserved IDs are absent in the base
tables; registered script names match the source; insert collisions fail rather than
replace unrelated rows. Uninstall is limited to matching owned IDs/scripts/text and
preserves updater history with explicit reinstall instructions. Actual installation
and resulting rows still require CI evidence.

## One-human disposition and remaining evidence

The complete qualifying path is an ordinary level-80 solo human: travel to the
registrar, choose a preset, bait and dodge lightning, operate all three rods, choose
offense/recovery, win or fail, read an outcome, retry and leave. Solo has at most one
living pursuing add. Optional ordinary bots only fight/tank/heal/follow; the frozen
starting roster changes combat health/pressure and party add cap, not custom duties.
The no-bots path preserves the same primary mechanic and recovery decisions.

The existing compile-time checks and executable developer rules tests were read,
not executed locally. The official gate must build this exact source and record
all warnings, install/config/SQL evidence, unfiltered upstream tests and integrity.
Because dry-run exits before OnStartup, the applicable normal-world registrar
startup/clean shutdown evidence is also pending. That evidence still cannot certify
encounter playthrough, class tuning, stock-client feedback, public travel or bot feel.
Those are explicitly PENDING IN-GAME VALIDATION in the complete manual checklist.
