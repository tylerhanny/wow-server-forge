# Exact-pin reference evidence

All AzerothCore references below are from mod-playerbots/azerothcore-wotlk commit
47960183bb03b83e8943eb2f0f39c16df9710c9d. Playerbots remains unchanged at
2f7d9f774987d0157c6a0d0cc08c40bec3db3945. No custom Playerbots API is required.

| Reference | Pinned evidence and use |
|---|---|
| Unit.cpp, blob 9caf5369970fee5bcc0578642bdda2fcc893dce1 | Lines8109–8123 call victim AI HealReceived before ModifyHealth. Lines10889–10977 validate assists; living/selectable, friendly CAN_ASSIST patients must not be NON_ATTACKABLE/immune-PC. |
| Unit.h, blob edaf3e9e3a18f72eb46646758d712a55fff1d7a3 | Line844 exposes getClass(),868 IsValidAssistTarget,1784 SetStandState. |
| UnitAI.h, blob a4c01dd47ddee532fe9b86158495e178c46f1933 | DamageTaken and HealReceived signatures permit owned damage/healing filtering. |
| Creature.h, blob a26e257a895c87636da5ad2885bb58af6f37c745 | SetRegeneratingHealth(false); DespawnOrUnsummon accepts Milliseconds. Native regeneration and evade/reset must be considered separately. |
| SharedDefines.h, blob 8b6dacc8b6f8d213aca65f9f4a69cfc6347ad1e4 | CREATURE_TYPE_FLAG_CAN_ASSIST=0x00001000 at2701; this is the creature_template.type_flags value4096. |
| Object.h, blob ce311a2ef17dc776ccdf240dd8305196210c2072 | Distance/LOS queries and temporary SummonCreature; its lifetime argument is uint32 milliseconds, not a chrono duration. |
| Position.h, blob f1e0cfab6458a1d24084ef2869bf6a9a3f600f9c | WorldLocation map/XYZ/orientation constructor and normalized orientation. |
| ScriptedCreature.h, blob a39f1a417449bc3af95cde9f16074a70b0d8bde9 | ScriptedAI has a virtual destructor; native GenericCreatureScript binds the owned AIs. |
| PlayerScript.h | PLAYERHOOK_ON_UPDATE maps to OnPlayerUpdate; login/logout/death/map-change hooks permit session invalidation. Commands queue actions, avoiding actor operations in command handlers. |
| Map height/liquid APIs | Nearby phase-aware GetHeight with a bounded search, INVALID_HEIGHT rejection and GetLiquidData contact check follow the same pinned API path already compiled for Field Camp. This is source compatibility evidence, not proof of this encounter's client visibility. |
| npcs_special.cpp, blob 14069c94b93db7003c4d7844813855da64f9a475 | Stock First Aid Triage uses injured poses/timed health reduction and recognizes bandage spell20804. Its existing quest/data/scripts are not changed or attached to these templates. |

## Owned SQL and stock models

Only creature_template and creature_template_model IDs911100–911103 are inserted. Read-only
inspection of the pinned base tables found no rows at these IDs. Another installation's
custom modules can still collide; the documented preflight is mandatory before import.
The update uses plain INSERT, a transaction, and no stock updates/deletes. No permanent
creature or gameobject spawn, npc_text, quest, item, loot or character table is needed.

Exact ac-data commit: 74643b700b1cd806845a1dfd926a2c46e7890dbe.
CreatureDisplayInfo.dbc blob: ac0fd4d64da74f8d9b750b18cd15ee2ff21941ae.
CreatureModelData.dbc blob: 05faab49646ac73885bcc7c3a2c1d3899a76ded8.

| Owned entry | Display | Model | Stock model path |
|---|---|---|---|
| 911100 controller | 13069 | 1731 | Creature/InvisibleStalker/InvisibleStalker.mdx |
| 911101 Patient One | 6570 | 51 | Character/Orc/Male/OrcMale.mdx |
| 911102 Patient Two | 2588 | 185 | Character/Troll/Male/TrollMale.mdx |
| 911103 Patient Three | 1027 | 57 | Character/Scourge/Male/ScourgeMale.mdx |

These are display references only. The module does not copy the source NPC factions, AI,
auras, scripts or quest behavior. Patients use friendly faction35 and CAN_ASSIST, no unit
flags that block ordinary healing, and RegenHealth0 plus the owned no-regen AI setting.
Only the invisible controller is non-attackable/not-selectable. No visual spell is cast;
feedback uses native health, stand states, ordinary player spells and concise messages.

## Pressure starting values — not measured balance

Each new patient has12000 health. The five rounds apply role-based loss once per visible
injury second, with no native regeneration. Training uses the values below; Veteran
multiplies each loss by135%, with integer truncation. Patient roles rotate across rounds
and attempts. Bursts land at seconds12,24,36, warned at8,20,32. There is no warning for a
burst beyond the45-second round. Six-second stabilization suppresses future scripted loss,
including a burst within its active window, but never heals existing wounds.

| Round | Role A / B / C loss per second | Burst |
|---|---|---|
| 1 | 350 /120 /120 | None |
| 2 | 80 /250 /150 | 7200 on A |
| 3 | 450 /450 /80 | None |
| 4 | 250 /250 /250 | 4800, rotating B→C→A |
| 5 | 450 /350 /200 | 6200 on C |

The smaller health capacity makes burst preparation matter instead of allowing several
unanswered bursts. These are source-based starting values. Actual priest gear/spell choice,
mana pressure, health-bar readability and fun require the documented manual playtest.
No source analysis is presented as measured client balance.
