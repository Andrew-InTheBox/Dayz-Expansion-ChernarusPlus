[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"Enabled"`

Bool.

* 0 = All the missions will be disabled.
* 1 = It will enable missions, currently only airdrop missions are available but more are planned in the futur.

### `"InitialMissionStartDelay"`

Integer. After a server restart, how long the mission need to wait to start. This number is in milliseconds.

### `"TimeBetweenMissions"`

Integer. Time in milliseconds before a new mission start

### `"MinMissions"`

Integer. Minimum mission allowed at once. The number should not be greater than "MaxMissions".

### `"MaxMissions"`

Integer. Maximum mission allowed at once.

### `"MinPlayersToStartMissions"`

Integer. Minimum required of players to start a mission.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
