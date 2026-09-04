# Stormwright stock visual audit

Reviewer source/data audit only. No implementation, compilation, client rendering, or gameplay validation is claimed. This does not start the sprint or approve an implementation.

## Finding: spell 62186 is not visual-only

Pinned [Thorim source](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/scripts/Northrend/Ulduar/Ulduar/boss_thorim.cpp#L46) names 62186 `SPELL_LIGHTNING_ORB_VISUAL`. That name does not describe all its behavior.

The public `ac-data/ac-data` artifact was read at exact data commit `74643b700b1cd806845a1dfd926a2c46e7890dbe`. This is a recorded runtime-data revision, not a change to either required source dependency. `Spell.dbc` Git blob `804810aca3e4fa3bf17247ea6b6e8781eccaf595` was verified by computing the Git blob hash over the downloaded bytes. The WDBC header, file length, 234 fields, and 936-byte record size were checked against the pinned `DBCStructure.h` layout.

| Spell | Actual relevant fields |
|---|---|
| 62186, Lightning Orb Charged | Effect 6 (`APPLY_AURA`), aura 23 (`PERIODIC_TRIGGER_SPELL`), period 8,000 ms, trigger spell 62278, self target, visual 13114. |
| 62278, Lightning Orb Charger | Effect 3 (`DUMMY`), target 38 (`UNIT_NEARBY_ENTRY`). |
| 62466, Lightning Charge | Includes school-damage effect 2 with base points 17,343; it is not a harmless fallback visual. |

Pinned base [conditions.sql](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/data/sql/base/db_world/conditions.sql#L4456) constrains 62278 to creature 32865 (Thorim). Pinned Thorim `SpellHit` lines 603–610 reacts to 62278 by casting 62466 damage and 62279 buff. This audit does not claim that a cast elsewhere would successfully hit Thorim; it establishes that the aura performs encounter-specific work and cannot be represented as pure visual feedback. No existing spell, condition, or core script may be changed to neutralize it for this candidate.

## Available module-only visual path

Pinned [Unit.h](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.h#L2032) exposes `SendPlaySpellVisual` and `SendPlaySpellImpact`. The [implementation](https://github.com/mod-playerbots/azerothcore-wotlk/blob/47960183bb03b83e8943eb2f0f39c16df9710c9d/src/server/game/Entities/Unit/Unit.cpp#L15194) constructs a visual/impact packet with a GUID and **SpellVisualKit.dbc index**. It does not cast a spell, apply an aura, run a periodic trigger, or deal damage.

At the recorded data commit:

- `SpellVisual.dbc` Git blob `bf7cd0124dda3b83c39009e9f6d0afd832ae84ef` was verified.
- `SpellVisualKit.dbc` Git blob `07d8b6c08d12b68f644b035a728688cc1019f9b3` was verified.
- SpellVisual row 13114 has StateKit **12201**; that kit exists in SpellVisualKit.dbc. The other precast/casting/impact/state-done/channel kit fields in that row are zero.

Consequently 13114 must not be passed as though it were automatically the kit ID. A direct packet with a properly reviewed kit provides a feasible stock-client visual route. Existence of kit 12201 does not establish that a state kit is legible as a one-shot effect, whether it persists, how it ends, or whether it is the best final asset. Client readability/lifetime checks remain necessary, and actor/encounter cleanup must bound any chosen effect. A different audited kit is an ordinary asset choice, not a reason to weaken the desired gameplay loop.

## Concept disposition

This finding rejects the assumption that casting 62186 is harmless. It does **not** reject Stormwright: the pinned API exposes a source-supported visual-only route without changing the core, Playerbots, client, or existing encounter spell data. Final shortlist review still requires an actual player-controlled bait/capture/spend loop, useful repeatability, a bounded arena, and clear participation/cleanup behavior.

The original downloaded binary files and the small independent parsing script remain in ignored reviewer `.forge-local/`; they are not candidate assets or committed dependency data.
