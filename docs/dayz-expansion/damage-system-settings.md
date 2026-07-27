[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

For more consistent and reliable explosion damage to items, the Expansion damage system can be enabled and will be used in addition to the vanilla damage system.

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### **`Enabled`**

Bool.

Turn the whole system on/off (default enabled if using Expansion Basebuilding).

### **`CheckForBlockingObjects`**

Bool.

Whether to check if an object (building or large item) is blocking the path from the explosion source to the target (default enabled). When turning this off, the only determining factor for explosion damage is distance between explosion source and target, regardless if there are any objects in between.

### **`ExplosionTargets`**

Array (string).

List of config or script classnames that should use the Expansion explosion damage system (default `["ExpansionBaseBuilding", "ExpansionSafeBase"]` if using Expansion Basebuilding). **Note** that these are not explosives, but items that should receive the damage!

### **`ExplosiveProjectiles`**

Map (string).

Classnames of explosive projectiles mapped to their respective explosive ammo (e.g. `{"Bullet_40mm_Explosive": "Explosion_40mm_Ammo"}`).
This is needed for some vanilla projectiles like the M79 explosive grenade.

---

Example configuration:

```
{
    "m_Version": 1,
    "Enabled": 1,
    "CheckForBlockingObjects": 1,
    "ExplosionTargets": [
        "ExpansionBaseBuilding",
        "ExpansionSafeBase"
    ],
    "ExplosiveProjectiles": {
        "Bullet_40mm_Explosive": "Explosion_40mm_Ammo"
    }
}
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
