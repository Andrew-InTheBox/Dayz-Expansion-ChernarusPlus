# Project Overview

This project is a DayZ server setup. Configuration files tend to live in `/config` or `/mpmissions/Expansion.chernarusplus`.

We use the core components of the **DayZ Expansion** mod:
- Docs: https://github.com/salutesh/DayZ-Expansion-Scripts/wiki
- Local copy: `docs\dayz-expansion`

General DayZ modding info: https://github.com/StarDZ-Team/DayZ-Modding-Wiki/tree/main

## Key File Locations

| Purpose | Path |
|---|---|
| AI/bot patrol settings | `mpmissions\Expansion.chernarusplus\expansion\settings\AIPatrolSettings.json` |
| Patrol loadouts | `config\ExpansionMod\Loadouts\*.json` |

## Working with Large Config Files

Many XML/JSON config files are 3000+ lines. Don't read them in full — instead:
- Search for relevant sections, or
- Write a Python script to analyze/edit their contents

**Python venv:** always use `C:\Users\andre\venv-dirs\venv-utils` for scripts. Install additional packages into it as needed.

## economy.xml Reference

Each category controls a different part of the loot/spawn economy:

| Category | Meaning |
|---|---|
| `dynamic` | Loot from `types.xml` (tents, containers, etc.) |
| `animals` | Bears, wolves, etc. |
| `zombies` | Infected |
| `vehicles` | Cars (wrecks, bonfires, containers, DE) |
| `randoms` | Dynamic events (e.g. helicopter crashes) |
| `custom` | Map group positions, init, territories |
| `building` | Building doors on the map |
| `player` | Player persistence |

Each category has four flags (`1` = on, `0` = off):
- `init` — initial load-up
- `load` — object spawns
- `respawn` — respawning
- `save` — save to persistence files

**Default/original values:**
```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<economy>
    <dynamic init="1" load="1" respawn="1" save="1"/>
    <animals init="1" load="0" respawn="1" save="0"/>
    <zombies init="1" load="0" respawn="1" save="0"/>
    <vehicles init="1" load="1" respawn="1" save="1"/>
    <randoms init="0" load="0" respawn="1" save="0"/>
    <custom init="0" load="0" respawn="0" save="0"/>
    <building init="1" load="1" respawn="0" save="1"/>
    <player init="1" load="1" respawn="1" save="1"/>
</economy>
```

### Fixing Loot / Player Persistence (Soft Wipe)

Use this to reset loot state without a full wipe (source: [Discord](https://discord.com/channels/523890175563137034/1062856027810304130)):

1. Stop the server.
2. Set `dynamic`'s `init` and `load` to `0`.
3. Start the server, then stop it again.
4. Set `dynamic`'s `init` and `load` back to `1`.
5. Start the server and give it time — loot should regenerate correctly.

Note: this won't fix custom buildings where the map itself has been updated.
