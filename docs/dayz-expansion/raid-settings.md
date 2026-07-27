[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"ExplosionTime"`

Integer. Time in seconds it takes for the ExpansionSatchel to explode.

### `"ExplosiveDamageWhitelist"`

Array of string. Put every classname of the explosive items you want to be able to be used for raiding.

The classnames are not the **weapons items** nor the **explosives items** but the explosion itself. For example you can disable rpg explosions with "Expansion\_RPG\_Explosion"

```
"ExplosiveDamageWhitelist": [
    "classname01_withaCommaAtTheEnd",
    "classname02_withoutCommaAtTheEndBecauseItsTheLastOne"
],
```

### `"EnableExplosiveWhitelist"`

Bool.

* 0 = Every items from the game will be able to raid basebuilding elements regardless of ExplosiveDamageWhitelist.
* 1 = Only the items listed above will be able to raid basebuilding elements.

### `"ExplosionDamageMultiplier"`

Float. It is a damage multiplier for all explosion type damages to Expansion base parts. For example with the default value of 50, a grenade that does 50 damage will do 50 \* 50 damage to the wall, so 2500. For reference, vanilla grenades do 50 damage, Expansion rockets do 300, and C4 does 600. Less than 1 values work here as well, so 0x will disable damage to base parts, and .5x will halve them. Note, walls currently have an HP of 30,000.

### `"ProjectileDamageMultiplier"`

Float. It is a damage multiplier for all bullet type damages to Expansion base parts. For example with the default value of 2, a bullet that does 65 damage will do 65 \* 2 damage to the wall, so 130. **Less than 1 values work here as well, so 0x will disable damage** to base parts, and .5x will halve them. Note, walls currently have an HP of 30,000.

### `"CanRaidSafes"`

Bool.

* 0 = Players won't be able to destroy Expansion safes.
* 1 = Allow to players to raid expansion safes.

### `"SafeExplosionDamageMultiplier"`

Float. It is a damage multiplier for all explosion type damages to Expansion base parts. For example with the default value of 50, a grenade that does 50 damage will do 50 \* 50 damage to the safe, so 2500. For reference, vanilla grenades do 50 damage, Expansion rockets do 300, and C4 does 600. Less than 1 values work here as well, so 0x will disable damage to base parts, and .5x will halve them. Note, safes currently have 20,000 15,000 and 10,000 HP.

### `"SafeProjectileDamageMultiplier"`

Float. It is a damage multiplier for all bullet type damages to Expansion base parts. For example with the default value of 2, a bullet that does 65 damage will do 65 \* 2 damage to the safe, so 130. **Less than 1 values work here as well, so 0x will disable damage** to base parts, and .5x will halve them. Note, safes currently have 20,000 15,000 and 10,000 HP.

### `"SafeRaidTools"`

Array. List of tools allowed for raiding safes

```
"SafeRaidTools": [
    "classname01_withaCommaAtTheEnd",
    "classname02_withoutCommaAtTheEndBecauseItsTheLastOne"
],
```

### `"SafeRaidToolTimeSeconds"`

Integer. Time needed to raid safe with tool

### `"SafeRaidToolCycles"`

Integer. Number of cycles needed to raid safe

### `"SafeRaidToolDamagePercent"`

Integer. Total damage dealt to tool over time (100 = tool will be in ruined state after all cycles finished)

### `"BarbedWireRaidTools"`

Array. List of tools allowed for raiding barbed wire

```
"BarbedWireRaidTools": [
    "classname01_withaCommaAtTheEnd",
    "classname02_withoutCommaAtTheEndBecauseItsTheLastOne"
],
```

### `"BarbedWireRaidToolTimeSeconds"`

Integer. Time needed to raid barbed wire with tool

### `"BarbedWireRaidToolCycles"`

Integer. Number of cycles needed to raid barbed wire

### `"BarbedWireRaidToolDamagePercent"`

Integer. Total damage dealt to tool over time (100 = tool will be in ruined state after all cycles finished)

### `"CanRaidLocksOnWalls"`

Integer.

* 0 = You can't raid codelocks on tents
* 1 = Make locks (both vanilla and Expansion) raidable on walls doors and gates
* 2 = Make locks (both vanilla and Expansion) raidable on wall doors
* 3 = Make locks (both vanilla and Expansion) raidable on wall gates

### `"CanRaidLocksOnFences"`

Bool.

* 0 = You can't raid codelocks on fences
* 1 = Make locks (both vanilla and Expansion) raidable on fences

### `"CanRaidLocksOnTents"`

Bool.

* 0 = You can't raid codelocks on tents
* 1 = Make locks (both vanilla and Expansion) raidable on tents

### `"LockRaidTools"`

Array. List of tools allowed for raiding locks

```
"LockRaidTools": [
    "classname01_withaCommaAtTheEnd",
    "classname02_withoutCommaAtTheEndBecauseItsTheLastOne"
],
```

### `"LockOnWallRaidToolTimeSeconds"`

Integer. Time needed to raid lock on wall with tool

### `"LockOnFenceRaidToolTimeSeconds"`

Integer. Time needed to raid lock on fence with tool

### `"LockOnTentRaidToolTimeSeconds"`

Integer. Time needed to raid lock on tent with tool

### `"LockRaidToolCycles"`

Integer. Number of cycles needed to raid lock

### `"LockRaidToolDamagePercent"`

Integer. Total damage dealt to tool over time (100 = tool will be in ruined state after all cycles finished)

### `"BaseBuildingRaidMode"`

Integer.

* -1 = Expansion BaseBuilding elements can't be raided.
* 0 = every basebuilding elements can be raided.
* 1 = only doors/gates.
* 2 = only doors/gates/windows.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
