-- Manual only: stop the disposable worldserver and remove the module first.
-- Delete only identities still owned by Stormwright. No stock spawns are touched.
START TRANSACTION;
DELETE m FROM `creature_template_model` m
INNER JOIN `creature_template` c ON c.`entry` = m.`CreatureID`
WHERE c.`entry` BETWEEN 910900 AND 910904
  AND c.`ScriptName` IN ('npc_stormwright_registrar', 'npc_stormwright_rod', 'npc_stormwright_enemy', 'npc_stormwright_marker');
DELETE FROM `creature_template`
WHERE `entry` BETWEEN 910900 AND 910904
  AND `ScriptName` IN ('npc_stormwright_registrar', 'npc_stormwright_rod', 'npc_stormwright_enemy', 'npc_stormwright_marker');
DELETE FROM `npc_text` WHERE `ID` = 910900 AND `text0_0` LIKE 'Stormwright: turn the storm into your weapon.%';
COMMIT;
