[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `m_Version`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `Enabled`

Boolean.

* 0 = OFF | Disabled
* 1 = ON | Enabled

### `FormationScale`

Float. How far apart the individual formation positions are.

For formations that are on a grid (like Vee, InvVee, Wall, Column and InvColumn), the value determines the side length of the grid in meters.

For formations that are not on a grid (like Star, StarDot, Circle and CircleDot), the value roughly determines the distance between the positions (in case of star-based formations, the inner positions, with distances between outer positions scaled accordingly).

Default: -1.0 (uses AISettings.json value, which defaults to 1.0)

### `DespawnTime`

Float. How long in seconds will it take for the patrol to despawn if no players are in DespawnRadius.

* -1 = Use the value from AISettings.json

### `RespawnTime`

Float. How long in seconds until this patrol can respawn if no players are in MinDistRadius ?

* If set to -1 will use the value from AISettings.json

### `MinDistRadius`

Float. The required minimum distance from a player to spawn. If a player is closer than MinDistRadius meters, then the patrol won't spawn

* If set to -1 will use the value from AISettings.json

### `MaxDistRadius`

Float. The required maxium distance from a player to spawn. If a player is further away than MaxDistRadius meters, then the patrol won't spawn

* If set to -1 will use the value from AISettings.json

### `DespawnRadius`

Float. The required distance from a player to despawn. If a player is closer than DespawnRadius meters, then the patrol won't despawn

### `AccuracyMin`

Float. Minimum accuracy of the AI (0.0-1.0)

* If set to -1 will use the value from AISettings.json

### `AccuracyMax`

Float. Maximum accuracy of the AI (0.0-1.0)

* If set to -1 will use the value from AISettings.json

### `ThreatDistanceLimit`

Float. Distance in meters when the target will start be considered a potential threat. AI will not see enemies past this distance, so use with care.

* If set to -1 will use the value from AISettings.json

### `NoiseInvestigationDistanceLimit`

Float. Max distance in meters that AI will search for noise sources. -1 = use value from AISettings.json

### `MaxFlankingDistance`

Float. Max distance to enemy in meters that AI will try to flank the enemy (default 200). -1 = use value from AISettings.json

### `EnableFlankingOutsideCombat`

Int. Enable flanking outside combat. Note that this will give AI a sort of "sixth sense" about enemies, but not necessarily their exact position when there is no line of sight. 0 = disabled, 1 = enabled, -1 = use value from AISettings.json

### `DamageMultiplier`

Float. Damage multiplier from the AI (default 1.0 = no change). Base damage they will deal multiplied by this value.

* If set to -1 will use the value from AISettings.json

### `DamageReceivedMultiplier`

Damage multiplier for damage the AI receive (default 1.0 = no change). Base damage they receive will be multiplied by this value.

* If set to -1 will use the value from AISettings.json

### `LoadBalancingCategories`

[AI Load Balancing](/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-AI-Load-Balancing)

### `Patrols`

[How to create AI Patrols](/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-How-to-create-AI-Patrols)

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
