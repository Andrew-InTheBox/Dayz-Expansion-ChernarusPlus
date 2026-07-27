[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"Enabled"`

Boolean.

* 0 = Disable
* 1 = Enable

Enable/Disable the garage system and its modules.

### `"AllowStoringDEVehicles"`

Bool. Allow storing vehicles spawned by dynamic CE events (e.g. events.xml). Note that you should set nominal and min to zero in your `events.xml` files before enabling this, or each stored vehicle can respawn!

### `"GarageMode"`

Enum.

* 0 = Territory Mode: Player needs to be a member/owner of a territory to store/retrieve vehicles on garage points.
* 1 = Personal Mode: Player can store/retrieve vehicles without any requirement on garage access points.

### `"GarageStoreMode"`

Enum.

* 0 = Personal Mode: Only players can store there vehicles.
* 1 = Shared Mode: All territory members can store a vehicles if the vehicle owner was a member.
* 2 = Tyrannical Mode: Only the territory owner and moderators can store vehicles of territory members.

### `"GarageRetrieveMode"`

Enum.

* 0 = Personal Mode: Only players can retrieve there vehicles.
* 1 = Shared Mode: All territory members can retrieve vehicles if the vehicle was stored by a territory member.
* 2 = Tyrannical Mode: Only the territory owner and moderators can retrieve vehicles if the vehicle was stored by a territory member.

### `"MaxStorableVehicles"`

Integer.

Max. amount of vehicles a player or territory can store in the vitual garage, depending on the selected garage mode.

### `"VehicleSearchRadius"`

Float.

Max. distance in meters within the the garage access points detects world vehicles.
Vehicles standing outside of this range dont get displayed in the menu.

### `"CanStoreWithCargo"`

Boolean.

* 0 = Disable
* 1 = Enable

Allow vehicles to be stored with there cargo items. This does not include the vehicles attachments as these get always stored by default.

### `"UseVirtualStorageForCargo"`

Boolean.

* 0 = Disable
* 1 = Enable

Normally, for if CanStoreWithCargo is enabled the cargo items of the vehicle are transferred to a hidden placeholder in the world, so that `count_in_cargo="1"` still works. When this setting is enabled, the cargo items are stored in the entity storage with the vehicle instead.

### `"NeedKeyToStore"`

Boolean.

* 0 = Disable
* 1 = Enable

A car key needs to be bound to the vehicle to store it the garage.

### `"EntityWhitelist"`

Array.
List of the entity class names that can be used as garage access point. The action will be displayed on all entities defined in this array.

### `"EnableGroupFeatures"`

Boolean.

* 0 = Disable
* 1 = Enable

If the expansion group mod is loaded the virtual garage includes some additional features that can be enabled/disabled here.

### `"GroupStoreMode"`

Enum.

* 0 = Group members can only store vehicles of other group members.
* 1 = Group members can only retrieve vehicles of other group members.
* 2 = Group members can store and retrieve vehicles of other group members.

### `"EnableMarketFeatures"`

Boolean.

* 0 = Disable
* 1 = Enable

If the expansion market mod is loaded the virtual garage includes some additional features that can be enabled/disabled here.

### `"StorePricePercent"`

Float.

Controls the price percantage value for storing a vehicle. The base price is always the max. buy price of the vehicle in the expansion market settings. StaticStorePrice setting value need to be 0.

### `"StaticStorePrice"`

Integer.

Controls the static price for storing a vehicle. StorePricePercent setting value need to be 0.

If territories are used the following settings can be used to control the upgrade values for the virtual garage when the `Expansion Parking Meter`
is deployed within a territory. The parking meter can be upgraded and depending on the upgrade the storage and/or detection range of the parking meter access point can be increased.

### `"MaxStorableTier1 - MaxStorableTier3"`

Integer.

Controls how many vehicles can be stored in the territory garage by the territory members when the certain upgrade is installed.

### `"ParkingMeterEnableFlavor"`

Boolean.

* 0 = Disable
* 1 = Enable some cosmetic changes to the parking meter which doesnt affect gameplay in anyway. This is just a small easter egg.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
