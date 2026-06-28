# DayZ Chernarusplus with Expansion

This repository contains configuration files located in `./config` and `./mpmissions/Expansion.Chernarusplus` directories for setting up a DayZ server (version 1.25) that includes the Expansion bundle and MMG gear. The setup features market trader files and several quests.

## Note on Server-Side Mods

The startup batch file `start_automods.bat` automatically loads any directory starting with "@" as a mod. Therefore, server-side mods must be named differently to avoid being loaded in this manner. In this setup, server-side mods are prefixed with "_XYZ". Add your server-side mods manually to the startup batch file following this convention. The only server-side mod I'm running is `Dynamic_AI_Addon` by TrueDolphin.

## Required Mods

The following mods are required for this project. These are located in directories at the top level of the project and start with the "@" symbol:

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
- **MoreWolves**
- **SNAFUWeapons**
- **RedFalcon Helis**
- **MetroWatchPack OG**
- **_DayZ-Dynamic-AI-Addon** (server-side)

Make sure you have these mods installed to ensure full functionality of the quests and other custom features provided in this project.

## Project Structure

### Custom Scripts

#### `custom_scripts/analyze_quests.py`

This script is used to generate reports for quests defined in the configuration. It processes the quests and outputs details about each quest, including quest ID, title, objectives, quest giver, and rewards.

Several other useful scripts are in that directory, use at your own risk and make sure you understand what they do.  Some will absolutely trash your files if you aren't careful.

### Docs files

Copied and pasted into txt files from the Expansion Wiki, I use these to query with [Continue.Dev](https://www.continue.dev) in VS Code when I can't remember how to do something with market or quests.  Continue.dev is great and you can bring your own API keys, highly recommended.

#### `docs/expansion_market.txt`


#### `docs/expansion_quests.txt`



