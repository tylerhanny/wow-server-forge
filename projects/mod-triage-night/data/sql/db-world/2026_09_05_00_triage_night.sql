-- Triage Night owned templates only. Exact AC 47960183bb03b83e8943eb2f0f39c16df9710c9d.
-- Native module updater: apply once. Any occupied ID is an installation error.
-- Do not use REPLACE, INSERT IGNORE or mysql --force. No permanent world spawns.
START TRANSACTION;

INSERT INTO `creature_template`
(`entry`, `name`, `subname`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`,
 `speed_walk`, `speed_run`, `BaseAttackTime`, `RangeAttackTime`, `unit_class`,
 `unit_flags`, `type`, `type_flags`, `ExperienceModifier`, `RegenHealth`, `ScriptName`, `VerifiedBuild`)
VALUES
(911100, 'Triage Night Controller', '', 80, 80, 2, 35, 0,
 1, 1, 2000, 2000, 1, 33554434, 10, 0, 0, 0, 'npc_triage_night_controller', 12340),
(911101, 'Patient One', 'Triage Night - stabilize 1', 80, 80, 2, 35, 0,
 1, 1, 2000, 2000, 1, 0, 7, 4096, 0, 0, 'npc_triage_night_patient', 12340),
(911102, 'Patient Two', 'Triage Night - stabilize 2', 80, 80, 2, 35, 0,
 1, 1, 2000, 2000, 1, 0, 7, 4096, 0, 0, 'npc_triage_night_patient', 12340),
(911103, 'Patient Three', 'Triage Night - stabilize 3', 80, 80, 2, 35, 0,
 1, 1, 2000, 2000, 1, 0, 7, 4096, 0, 0, 'npc_triage_night_patient', 12340);

-- CAN_ASSIST=0x1000 is required for ordinary player healing of non-PvP NPCs.
-- Only the invisible controller is non-attackable/not-selectable. Patient AI
-- filters damage and non-pilot healing without blocking legitimate heal targets.
INSERT INTO `creature_template_model`
(`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES
(911100, 0, 13069, 1, 1, 12340),
(911101, 0, 6570, 1, 1, 12340),
(911102, 0, 2588, 1, 1, 12340),
(911103, 0, 1027, 1, 1, 12340);

COMMIT;
