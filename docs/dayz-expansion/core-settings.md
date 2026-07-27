---

### `"m_Version"`

Integer. Used for internal file version tracking, do not edit.

### `"ServerUpdateRateLimit"`

Integer.

This setting is limiting server script update rate (vanilla) per second. If you are using the `-limitFPS` parameter on the command line, then `ServerUpdateRateLimit` should be lower.

* 0 = let the game handle normally
* 40 = minimum allowed

### `"FixCELifetime"`

Bool.

When set to 1 or `true`, corrects the lifetime of items spawned by the central economy (see vanilla bug [T194225](https://feedback.bistudio.com/T194225))

### `"EnableInventoryCargoTidy"`

Bool.

When set to 1 or `true`, shows a "tidy cargo" icon for each clothing/container in inventory on client which players can use to auto-arrange and combine items in a way that maximizes free space.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
