-- Stormwright owned templates only. Applied once by AzerothCore's module updater.
-- Exact target: AC 47960183bb03b83e8943eb2f0f39c16df9710c9d.
-- An occupied ID is an installation error: do not use mysql --force or REPLACE.
-- No permanent creature spawns: the module derives placement from installed maps.
START TRANSACTION;

INSERT INTO `creature_template`
(`entry`, `name`, `subname`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`,
 `speed_walk`, `speed_run`, `BaseAttackTime`, `RangeAttackTime`, `unit_class`,
 `unit_flags`, `type`, `ExperienceModifier`, `RegenHealth`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(910900, 'Nix Stormwright', 'Stormwright - Solo Pilot Trials', 80, 80, 2, 35, 1,
 1, 1, 2000, 2000, 1, 2, 7, 0, 0, 0x01002042, 'npc_stormwright_registrar', 12340),
(910901, 'Stormwright Capacitor', 'Catch - Ground or Discharge', 80, 80, 2, 35, 1,
 1, 1, 2000, 2000, 1, 2, 10, 0, 0, 0x01002042, 'npc_stormwright_rod', 12340),
(910902, 'The Unbound Storm', 'Stormwright', 80, 80, 2, 14, 0,
 1, 0.9, 2000, 2000, 1, 0, 4, 0, 0, 0x0706007C, 'npc_stormwright_enemy', 12340),
(910903, 'Stormwright Pursuer', 'Lure into a capacitor blast', 80, 80, 2, 14, 0,
 1, 1, 2000, 2000, 1, 0, 4, 0, 0, 0x0706007C, 'npc_stormwright_enemy', 12340),
(910904, 'Stormwright Mark', 'Move away after lock', 80, 80, 2, 35, 0,
 1, 1, 2000, 2000, 1, 33554434, 10, 0, 0, 0x01002042, 'npc_stormwright_marker', 12340);

-- Model references only; never copy stock NPC AI, auras, factions or loot.
INSERT INTO `creature_template_model`
(`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`)
VALUES
(910900, 0, 5443, 1, 1, 12340),
(910901, 0, 17856, 1, 1, 12340),
(910902, 0, 26382, 1, 1, 12340),
(910903, 0, 23349, 1, 1, 12340),
(910904, 0, 26753, 1, 1, 12340);

INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `Probability0`)
VALUES (910900,
 'Stormwright: turn the storm into your weapon. Lead a tracking mark to a ready capacitor, then move when it locks. A large capacitor holds charge: Discharge opens the boss armor; Ground restores your health and ward. Small capacitors are cooling. One human operates every special action. Ordinary companions only fight. Three misses break the ward; twelve minutes ends the attempt.',
 'Stormwright: turn the storm into your weapon. Lead a tracking mark to a ready capacitor, then move when it locks. A large capacitor holds charge: Discharge opens the boss armor; Ground restores your health and ward. Small capacitors are cooling. One human operates every special action. Ordinary companions only fight. Three misses break the ward; twelve minutes ends the attempt.',
 1);

COMMIT;
