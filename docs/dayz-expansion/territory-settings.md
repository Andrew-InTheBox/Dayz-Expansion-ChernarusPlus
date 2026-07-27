[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"EnableTerritories"`

Bool.

* 0 = The Territory flag will only have the vanilla functionnality.
* 1 = Will enable Expansion Territory system.

### `"UseWholeMapForInviteList"`

Bool.

* 0 = The player can only invite players in his territory if they are near him.
* 1 = The player can invite anyone in his territory, even if they are on the other side of the map.

### `"TerritorySize"`

Float. the radius of territory in meters.

### `"TerritoryPerimterSize"`

Float. A perimeter surrounding a territory to prevent other territories to be built in. It will prevent territories to overlap if the value set is the same as TerritorySize or higher.
![perimeter sheet](https://camo.githubusercontent.com/b24a0800979e9d540e40cdfdc7a9335735ede86f8f14de596b395d7a6b2f7d73/68747470733a2f2f692e696d6775722e636f6d2f674a5835556c612e706e67)

### `"MaxMembersInTerritory"`

Integer. The max amount of members allowed per territories. If <= 0, unlimited territory size.

### `"MaxTerritoryPerPlayer"`

Integer. The max amount of territories allowed per player. If <= 0, unlimited territory allowed.

### `"TerritoryAuthenticationRadius"`

Float. The radius from where a player can accept a territory invite.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
