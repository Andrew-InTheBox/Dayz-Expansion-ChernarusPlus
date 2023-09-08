# DayZ Chernarusplus with Expansion

This repository contains configuration files located in `./config` and `./mpmissions/Expansion.Chernarusplus` directories for setting up a DayZ server (version 1.22) that includes the Expansion bundle and MMG gear. The setup features market trader files and several quests.

## Note on Server-Side Mods

The startup batch file automatically loads any directory starting with "@" as a mod. Therefore, server-side mods must be named differently to avoid being loaded in this manner. In this setup, server-side mods are prefixed with "_XYZ". Add your server-side mods manually to the startup batch file following this convention.

## Mods Used

The following mods are used in this setup:

- **BulletStacksPlusEnhanced**
- **CF**
- **COT**
- **DabsFramework**
- **DayZ-Editor-Loader**
- **Dayz-Expansion-Animations**
- **DayZ-Expansion-Bundle**
- **DayZ-Expansion-Licensed**
- **MMG-MightysMilitaryGear**
- **PvZmoD_CustomizableZombies**
- **_DayZ-Dynamic-AI-Addon** (server-side)
