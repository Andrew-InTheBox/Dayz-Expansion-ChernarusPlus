[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"AccuracyMin"`

Float. Minimum accuracy of the AI (0.0-1.0)

This setting can be overridden in each patrols themselves.

### `"AccuracyMax"`

Float. Maxium accuracy of the AI (0.0-1.0)

This setting can be overridden in each patrols themselves.

### `"ThreatDistanceLimit"`

Float. Maximum distance the AI is allowed to calculate a potential target as a threat.

This setting can be overridden in each patrols themselves.

### `"NoiseInvestigationDistanceLimit"`

Float. How far away a noise can be for AI to consider checking it out.

This setting can be overridden in each patrols themselves.

### `"DamageMultiplier"`

Float. How much damage AI is doing. 1.0 = 100%

This setting can be overridden in each patrols themselves.

### `"DamageReceivedMultiplier"`

Float. How much damage AI is receiving when attacked. 1.0 = 100%

This setting can be overridden in each patrols themselves.

### `"Admins"`

TStringArray. A list of steam id in quotes to allow access to a debug menu for AI

For more information [Click here](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-How-to-access-the-AI-Menu)

### `"Vaulting"`

Boolean.

* 0 = AI wont vault
* 1 = AI can vault over objects

### `"SniperProneDistanceThreshold"`

Float. How close a target can be for AI to go prone when using a bolt action rifle. If the target is closer than this value, AI won't go prone.

### `"Manners"`

Boolean.

* 0 = AI wont taunt or emote
* 1 = AI will taunt after killing a target, or emote, randomly

### `"MemeLevel"`

Integrer. Make the AI behave in goofy ways

* 0 = Turned off
* ??? = Do something

### `"CanRecruitFriendly"`

Boolean.

* 0 = Friendly AI cannot be recruited
* 1 = Players can recruit Friendly AIs (Based on Faction relations)

### `"CanRecruitGuards"`

Boolean.

* 0 = Guards cannot be recruited
* 1 = Players can recruit Guards

### `"PreventClimb"`

TStringArray. A list of objects classnames the AI shouldn't be able to climb. For example "Land\_Mil\_Airfield\_HQ" (this one is hardcoded)

### `"PlayerFactions"`

TStringArray. A list of Factions in quotes. One of this listed factions will be randomly assigned to new players

For more information [Click here](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-How-to-assign-a-player-to-a-faction)

### `"LogAIHitBy"`

Bool. Log AI getting hit to admin log.

### `"LogAIKilled"`

Bool. Log AI getting killed to admin log.

### `"EnableZombieVehicleAttackHandler"`

Bool. Zombies will attack vehicles if a player sits in them.

### `"EnableZombieVehicleAttackPhysics"`

Bool. Zombies will shake up the vehicle while attacking it.

### `"LightingConfigMinNightVisibilityMeters"`

Sets how far AI can see at night without flashlight/NVG depending on lightingConfig value in CfgGameplay.json

Default for Chernarus:

```
    "LightingConfigMinNightVisibilityMeters": {
        "0": 100.0,
        "1": 10.0
    }
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
