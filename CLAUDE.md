Overall project description

This project is a DayZ server setup.  Configuration files tend to be in /config or /mpmissions/Expansion.chernarusplus.   We are using the core componts of a mod called DayZ Expansion which has a set of docs pages at and under this url:  https://github.com/salutesh/DayZ-Expansion-Scripts/wiki

AI aka bot patrols are configured in the file AIPatrolSettings.json located at mpmissions\Expansion.chernarusplus\expansion\settings\AIPatrolSettings.json

The loadouts the patrols wear are located in a folder here and are all json files:  config\ExpansionMod\Loadouts

Both of these files are 3000 lines or more, so we shouldn't try to read the whole things into context, but instead try to find releavent sections, or write python scripts to help us work and analyze their contents.

M79 Grenade Launcher Loadout Issue - SOLVED

## Problem Discovery
Initially had issues with M79 grenade launcher bots only spawning with 1 ammo instead of the expected 3 rounds. Through analysis, we discovered a critical issue with loadout.json structure.

## Key Findings About loadout.json Structure

### InventoryCargo Usage Patterns
- **Clothing items** (jackets, pants, vests): `InventoryCargo` works correctly - items spawn in clothing pockets/storage
- **Weapons**: Most weapons don't have internal inventory storage, only attachment slots
- **Sets**: Each Set has its own `InventoryCargo` for loose items that go into clothing inventory

### The M79 Ammo Problem
The original setup had:
1. 1x `Ammo_40mm_Explosive` in M79's `InventoryCargo` (❌ doesn't work - weapons have no internal storage)
2. 2x `Ammo_40mm_Explosive` in Set's `InventoryCargo` (✅ works - goes into clothing)

**Result**: Bots only got 2 rounds total instead of 3, because the weapon's InventoryCargo was ignored by the game engine.

## Solution Implemented
Created `custom_scripts/fix_m79_ammo.py` that:
- Moves all `Ammo_40mm_Explosive` from M79 weapon's `InventoryCargo` to the Set's `InventoryCargo` 
- Ensures bots get the full intended ammo supply in their clothing inventory
- M79 comes loaded by default + extra rounds in inventory

## Script Usage
```bash
# Test on single file (dry run)
python custom_scripts/fix_m79_ammo.py --dry-run config/ExpansionMod/Loadouts/BanditLoadout.json

# Fix single file
python custom_scripts/fix_m79_ammo.py config/ExpansionMod/Loadouts/BanditLoadout.json  

# Fix all loadout files with M79s
python custom_scripts/fix_m79_ammo.py --all
```

## Files Fixed
Applied to all loadout files with M79s:
- BanditLoadout.json
- EastLoadout.json  
- GorkaLoadout.json
- PoliceLoadout.json
- WestLoadout.json

## General Rule for Future Loadout Edits
- **Weapons**: Only use `InventoryCargo` for loaded ammo if the weapon type supports it (most don't)
- **Extra Items**: Always put loose items (ammo, supplies) in Set's `InventoryCargo` or clothing item's `InventoryCargo`
- **Clothing**: Items with pockets/storage can hold items in their `InventoryCargo`  

Important: when running python scripts, use the venv here:  /home/acb/venv-dirs/venv-utils.  If needed we can pip install additional libraries into it.