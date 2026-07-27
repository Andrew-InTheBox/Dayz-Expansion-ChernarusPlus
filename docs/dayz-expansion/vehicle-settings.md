[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"VehicleSync"` - not used, ignore.

Integer.

### `"VehicleRequireKeyToStart"`

Bool.

* 0 = Even if your car is paired to a key, you don't need to have the key in the vehicle inventory or on yourself.
* 1 = You will need a car key paired to the vehicle in your inventory or in the inventory of the vehicle to start the engine.
* 2 = You need to have the key in your hands to start the engine.

### `"VehicleRequireAllDoors"`

Bool.

* 0 = Even if you are missing some doors, you can still lock the vehicle.
* 1 = You will need all the doors of the car to lock your vehicle.

### `"VehicleLockedAllowInventoryAccess"`

Bool.

* 0 = Players will need to unlock the vehicle to access the inventory.
* 1 = Allow players to access the inventory of the vehicle even if this vehicle is locked.

### `"MasterKeyPairingMode"`

Integer.

* -1 = infinite master pairing uses
* 0 = disabled. You can pair any keys to your already paired car.
* 1 = limited uses before becoming a normal car key (MasterKeyUses)
* 2 = renewable with a electronicalrepairkit or a keygrinder (will also use MasterKeyUses)
* 3 = renewable with a keygrinder (will also use MasterKeyUses).

P.S. Expansion provide his own "KeyGrinder" but we have added compability to the KeyGrinder from the mod MuchCarKeys in case if you want to

### `"MasterKeyUses"`

Integer. Amount of times the masterkey can pair unpaired keys.

### `"CanPickLock"`

Bool.

* 0 = You can't lock pick vehicles.
* 1 = Allow players to lock pick vehicles.

### `"PickLockTools"`

Array. A list of classnames (items) allowed to lockpick cars.

### `"PickLockChancePercent"`

Integer. The Percentage of chance to successfully lock pick a vehicle (**from 0 to 100**)

### `"PickLockTimeSeconds"`

Integer. How many seconds it will take to do the lock pick action

### `"PickLockToolDamagePercent"`

Integer. How much damage the tool will take when completing the action. In percentage (**from 0 to 100**).

### `"VehicleLockedAllowInventoryAccess"`

Bool.

* 0 = Players will need to unlock the vehicle to access the inventory.
* 1 = Allow players to access the inventory of the vehicle even if this vehicle is locked.

### `"EnableWindAerodynamics"`

Bool.

* 0 = The helicopters won't have wind simulation.
* 1 = Enable wind simulation for helicopters.

### `"EnableTailRotorDamage"`

Bool.

* 0 = rotors of helicopters can't be damaged.
* 1 = rotors of helicopters can be damaged and will spin if destroy making the helicopters almost unusable.

### `"Towing"`

Bool.

* 0 = Towing is disabled.
* 1 = Allow cars to tow other cars. Helicopters can tow any types vehicles.

### `"EnableHelicopterExplosions"`

Bool.

* 0 = Helicopters won't explode.
* 1 = Helicopters can explode.

### `"DisableVehicleDamage"`

Bool.

* 0 = The Vehicles can take damage from anything (collision damage multipliers apply).
* 1 = The vehicles can't take damage (collision and bullet proof)

### `"VehicleCrewDamageMultiplier"`

Float. Collision damage multiplier for the crew. How fast they will blackout or die. 0 is no damage, 1 is vanilla damage, above 1 is stronger than vanilla.

### `"VehicleSpeedDamageMultiplier"`

Float. Collision damage multiplier for the speed of the car. 0 is no damage, 1 is vanilla damage, above 1 is stronger than vanilla.

### `"VehicleRoadKillDamageMultiplier"`

Float. Collision damage multiplier for the pedestrians. How fast they will blackout or die. 0 is no damage, 1 is vanilla damage, above 1 is stronger than vanilla.

### `"CanChangeLock"`

Bool.

* 0 = Disabled, you cannot change the lock of a vehicle (key).
* 1 = You can change the lock of a vehicle (key).

### `"ChangeLockTools"`

Array. A list of classnames (items) allowed to change the lock of a vehicle.

### `"ChangeLockTimeSeconds"`

Integer. Time it will take to change the lock in seconds (s)

### `"PickLockToolDamagePercent"`

Float. How much damage the tool will take when executing the action (in percentage, from 0 to 100)

### `"PlacePlayerOnGroundOnReconnectInVehicle"`

Integer. If the player crash (or server crash). Should the player be placed on the ground ?

* 0 = disabled
* 1 = Always
* 2 = Only on server restarts

### `"RevvingOverMaxRPMRuinsEngineInstantly"`

Bool.

* 0 = Disabled, the engine won't be damaged.
* 1 = Going beyond the red bar from your RPM gauge will ruin the vehicle engine. (vanilla)

### `"VehicleDropsRuinedDoors"`

Bool.

* 0 = Disabled (vanilla)
* 1 = If a car door is ruined, this door will detach from the vehicle and fall down.

### `"ExplodingVehicleDropsAttachments"`

Bool.

* 0 = Disabled (vanilla)
* 1 = All the attachments of this vehicle will be detached and will fall.

### `"DesyncInvulnerabilityTimeoutSeconds"`

Float. How long of an invulnerability window is granted during desync.

### `"DamagedEngineStartupChancePercent"`

Float. Likelyhood of being able to start a damaged (50% health) engine. Gradually approaches this value when the engine is no longer 100% health, and then gradually approaches zero as engine health gets lower than 50%. The transition is linear if startup chance is equal to 50%, and follows a power curve otherwise.

### `"EnableVehicleCovers"`

Bool. Enable covering vehicles with a camonet. Not only conceals the vehicle, but also good for server performance since the covered vehicle has no physics.

### `"AllowCoveringDEVehicles"`

Bool. Allow covering vehicles spawned by dynamic CE events (e.g. events.xml). Note that you should set nominal and min to zero in your events.xml files before enabling this, or each covered vehicle can respawn!

### `"UseVirtualStorageForCoverCargo"`

Bool. Instead of keeping items in cargo on the covered vehicle, they are saved to virtual storage and completely removed from the game world (will be restored when the vehicle is uncovered). May be good for server performance, but loot that is marked `count_in_cargo="1"` will be able to respawn.

### `"VehicleAutoCoverTimeSeconds"`

Float. Time in seconds until a vehicle which engine is not running and without driver or passengers will be automatically covered. Note that vehicles spawned by events.xml will not be automatically covered (see above), you can manually cover it once though which will remove it from the event spawner, after which it will be included in automatic covering.

### `"VehicleAutoCoverRequireCamonet"`

Bool. Require an attached camonet on the vehicle for autocover.

### `"VehiclesConfig"`

Array. A list of classnames (vehicles) and their config for player attachment

### `"VehiclesConfig"` -> `"ClassName"`

String. The classname of the vehicle

### `"VehiclesConfig"` -> `"CanPlayerAttach"`

Bool.

* 0 = Players won't be able to attach on the vehicle
* 1 = Players can attach on this vehicle while it's moving

### `"VehiclesConfig"` -> `"LockComplexity"`

Float.

Affects the lockpick chance (higher value = lower chance).

```
{
    "ClassName": "OffroadHatchback",
    "CanPlayerAttach": 0,
    "LockComplexity": 1.0
}
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
