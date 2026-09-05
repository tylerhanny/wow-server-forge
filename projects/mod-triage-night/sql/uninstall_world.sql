-- Stop the disposable/server process and remove the module before full removal.
-- This removes only the reserved rows still bearing Triage Night script identity.
START TRANSACTION;
DELETE m FROM `creature_template_model` m
INNER JOIN `creature_template` c ON c.`entry` = m.`CreatureID`
WHERE c.`entry` BETWEEN 911100 AND 911103
  AND c.`ScriptName` IN ('npc_triage_night_controller', 'npc_triage_night_patient');
DELETE FROM `creature_template`
WHERE `entry` BETWEEN 911100 AND 911103
  AND `ScriptName` IN ('npc_triage_night_controller', 'npc_triage_night_patient');
COMMIT;
