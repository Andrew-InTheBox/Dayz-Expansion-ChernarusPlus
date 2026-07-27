[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

Unlike most other settings that may not be map-specific, you can find the SpawnSettings.json in your mpmission\dayzOffline.`<mapname>`\expansion\settings folder.

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

# Starting Clothing:

### `"EnableCustomClothing"`

Bool.

* 0 = The player will spawn with the vanilla default clothing items attached to his character
* 1 = The player will spawn with the configured clothing items in this file

### `"SetRandomHealth"`

Bool.

* 0 = All the clothing items with that the player spawns are in a pristine condition
* 1 = All the clothing items with that the player spawns are in a random condition

### `"Headgear"`

Array.

* List of class names used for the custom clothing.

Need to be headgear attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Glasses"`

Array.

* List of class names used for the custom clothing.

Need to be eyewear attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Masks"`

Array.

* List of class names used for the custom clothing.

Need to masks attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Tops"`

Array.

* List of class names used for custom clothing.

Need to be top/shirts/jackets attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Vests"`

Array.

* List of class names used for the custom clothing.

Need to be vests attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Gloves"`

Array.

* List of class names used for the custom clothing.

Need to be gloves attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Pants"`

Array.

* List of class names used for the custom clothing.

Need to be pants/shorts attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Belts"`

Array.

* List of class names used for the custom clothing.

Need to be belt attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Shoes"`

Array.

* List of class names used for the custom clothing.

Need to be shoes attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Armbands"`

Array.

* List of class names used for the custom clothing.

Need to be armbands attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

### `"Backpacks"`

Array.

* List of class names used for the custom clothing.

Need to be backpacks attachments/items!
If the array only contains one item class name it the characters will always spawn with this item when "UseCustomClothing" is enabled
otherwise, the item will be selected randomly.

# Spawn Selection:

### `"EnableSpawnSelection"`

Bool.

* 0 = Players will spawn randomly on the map like in vanilla.
* 1 = Players will be able to choose where to spawn on the map according the config done bellow.

### `"SpawnOnTerritory"`

Bool.

* 0 = Players can't respawn at their territories.
* 1 = You can respawn at your territory.

### `"SpawnLocations"`

Array. List of spawn locations that will get displayed in the spawn selection menu of the player.

### `"Name"`

String. The name of the location

### `"Positions"`

Array. List of positions

```
{
    "Name": "My Location Name",
    "Positions": [
        [
            100,         | Potential spawn position 1
            2,           | If only one position is set, the player will always spawn at this position
            50           | Also, the first spawn position will be used to create the 2d marker on the map
        ],
        [
            250,         | Potential spawn position  2
            2.75,
            100
        ]
    ],
    "UseCooldown": 0     | Bool. Gives this position a cooldown if enabled and when the "EnableRespawnCooldowns" setting is enabled too.
},
```

# Starting Gear:

### `"EnableStartingGear"`

Bool.

* 0 = The player will spawn with the vanilla default gear.
* 1 = The player will spawn with the configured gear in this file.

### `"UseUpperGear"`

Bool.

* 0 = The "UpperGear" will not be used. Nothing from this list will spawn on the player character.
* 1 = The items from "UpperGear" will be added into the inventory of the player in his Upper inventory (shirt inventory).

### `"UsePantsGear"`

Bool.

* 0 = The "PantsGear" will not be used. Nothing from this list will spawn on the player character.
* 1 = The items from "PantsGear" will be added into the inventory of the player in his Pant inventory.

### `"UseBackpackGear"`

Bool.

* 0 = The "BackpackGear" will not be used. Nothing from this list will spawn on the player character.
* 1 = The items from "BackpackGear" will be added into the inventory of the player in his backpack inventory.

### `"UseVestGear"`

Bool.

* 0 = The "VestGear" will not be used. Nothing from this list will spawn on the player character.
* 1 = The items from "VestGear" will be added into the inventory of the player in his vest inventory.

### `"UsePrimaryWeapon"`

Bool.

* 0 = The "PrimaryWeapon" will not be used. Player will not spawn with a primary weapon.
* 1 = The item defined at "PrimaryWeapon" will be added into the inventory of the player in his primary weapon slot.

### `"UseSecondaryWeapon"`

Bool.

* 0 = The "SecondaryWeapon" will not be used. Player will not spawn with a secondary weapon.
* 1 = The item defined at "SecondaryWeapon" will be added into the inventory of the player in his secondary weapon slot.

### `"UpperGear"`

Array.

* List of Items used for the upper gear.

Example :

```
{
    "ClassName": "Rag",
    "Quantity": 4,
    "Attachments": []
},
{
    "ClassName": "FNX45",
    "Quantity": 1,
    "Attachments": [
        "Mag_FNX45_15Rnd",
        "PistolSuppressor"
    ]
}
```

### `"PantsGear"`

Array.

* List of Items used for the pants gear.

### `"BackpackGear"`

Array.

* List of Items used for the backpack gear.

### `"VestGear"`

Array.

* List of Items used for the vest gear.

### `"PrimaryWeapon"`

Array.

* Item that gets attached to the player's primary weapon slot. Need to be a Fire- or Meele Weapon like an Axe.

### `"SecondaryWeapon"`

Array.

* Item that gets attached to the player's secondary weapon slot. Need to be a Fire- or Meele Weapon like an Axe.

### `"ApplyEnergySources"`

Bool.

* 0 = Nothing happens here.
* 1 = All gear items with that the player character spawned get a V9 batterie when they can fit and need one.

### `"SetRandomHealth"`

Bool.

* 0 = All the gear items with that the player spawns are in a pristine condition.
* 1 = All the gear items with that the player character spawned are in a random condition.

### `"UseLoadouts"`

Bool.

* 0 = When respawning, the system wont use loadouts.
* 1 = When respawning, the loadouts will be used. You can combine the starting gear and starting clothing with loadouts if you want. You could use loadouts to pick a random outfit set and use the above settings to give the generic items you want players to always have for example.

### `"MaleLoadouts"`

Array. List of loadouts and chance to be picked

* Loadout Name
* Chance from 0.0 to 1.0

### `"FemaleLoadouts"`

Array. List of loadouts and chance to be picked

* Loadout Name
* Chance from 0.0 to 1.0

### `"SpawnHealthValue"`

Float. How much Health (not the blood icon) the player will spawn with

### `"SpawnEnergyValue"`

Float. How much Energy (food) the player will spawn with

### `"SpawnWaterValue"`

Float. How much Water (thirst) the player will spawn with

### `"EnableRespawnCooldowns"`

Bool.

* 0 = The Cooldown system will be disabled.
* 1 = Enable the cooldown system and adds a cooldown for the player for all spawn points within the `"SpawnLocations"` array which have the `"UseCooldown"` bolean enabled.

### `"RespawnCooldown"`

Integer. Cooldown **seconds**. Once the player spawned on that spawn location, a cooldown of `"RespawnCooldown"` seconds will start and when the `"UseCooldown"` boolean is enabled for that spawn location in the `"Positions"` list.

### `"RespawnUTCTime"`

Bool.

* 0 = The Spawn Selection cooldowns will be calculated based on the server Local time.
* 1 = The Spawn Selection cooldowns will be calculated based on the [UTC](https://time.is/en/UTC) time.

### `"PunishMultispawn"`

Bool.

* 0 = This feature will be disabled.
* 1 = Punish the player with an additional cooldown time defined in the `"PunishCooldown"` setting when they use the same spawn location point multiple times.

### `"PunishCooldown"`

Integer. Additional Cooldown in **seconds** if the spawn location has been used too many times by the player. This mean the player will have the time of `"PunishCooldown"` AND `"RespawnCooldown"` combined.

### `"PunishTimeframe"`

Integer. Time in **seconds**. If the player try to respawn to the same spawn location too quickly the player will trigger the `"PunishCooldown"` if `"PunishMultispawn"` is enabled. This `"PunishTimeframe"` is the amount of time required between two respawns at the same location to not trigger this punishment.

### `"CreateDeathMarker"`

Bool.

* 0 = This feature will be disabled.
* 1 = Create a marker on the players latest death location on the spawn selection menu map.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
