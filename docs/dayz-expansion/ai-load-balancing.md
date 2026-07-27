`mpmissions/dayzoffline.mapname/expansion/settings/AIPatrolSettings.json` contains the load balancing settings.

### `LoadBalancingCategories`

Allows to specify how many patrols of each type are allowed to spawn/stay depending on the amount of online players. If a patrol is already spawned, and more players connect than the load balancing allows for that range of players, then the patrol will automatically despawn (AI will sit down just like players would when logging out, and cannot be killed while in this despawn phase).

Each individual patrol can have a `LoadBalancingCategory` assigned, and each category can define at least one or more entries that define ranges of online players and maximum amount of patrols for each range.

If no category is assigned (`""`), then the following defaults will be used:

* `ObjectPatrols` will use the `ObjectPatrol` category (if it exists)
* `Patrols` will use the `Patrol` category (if it exists)
* Quest AI (e.g. AICamp or AIPatrol when DayZ-Expansion-Quests is loaded) will use the `Quest` category (if it exists)

If a `Global` category exists, it will always be used in addition to the individual categories, so if an individual category doesn't limit a patrol, then any global limit(s) will still be in effect (if any).

Note that a value of `-1` for `MaxPatrols` means no limit will be applied by that specific entry.

You can edit, add and remove categories to your liking, there's no requirement to stick to any default category (but note that if you want global patrol limiting, then the category needs to be called `Global`). Removing all categories means no limits will be in effect.

Example of a default configuration:

```
    "LoadBalancingCategories": {
        "Example": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 255,
                "MaxPatrols": -1
            }
        ],
        "Quest": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 255,
                "MaxPatrols": -1
            }
        ],
        "ObjectPatrol": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 255,
                "MaxPatrols": 5
            }
        ],
        "HelicopterWreck": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 255,
                "MaxPatrols": 3
            }
        ],
        "Global": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 10,
                "MaxPatrols": 10
            },
            {
                "MinPlayers": 11,
                "MaxPlayers": 20,
                "MaxPatrols": 8
            },
            {
                "MinPlayers": 21,
                "MaxPlayers": 30,
                "MaxPatrols": 6
            },
            {
                "MinPlayers": 31,
                "MaxPlayers": 40,
                "MaxPatrols": 4
            },
            {
                "MinPlayers": 41,
                "MaxPlayers": 50,
                "MaxPatrols": 2
            },
            {
                "MinPlayers": 51,
                "MaxPlayers": 255,
                "MaxPatrols": 0
            }
        ],
        "ContaminatedArea": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 255,
                "MaxPatrols": 2
            }
        ],
        "Patrol": [
            {
                "MinPlayers": 0,
                "MaxPlayers": 255,
                "MaxPatrols": 5
            }
        ]
    }
```

The default settings are fairly conservative, and allow up to 10 patrols (with anywhere from 1-3 AI each) when up to 10 players are online, but only 2 patrols when 50 players are online. This assumes a server that can handle 60 players.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
