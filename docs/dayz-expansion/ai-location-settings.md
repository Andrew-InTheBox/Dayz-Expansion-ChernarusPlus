This file controls how AI navigate the world.

You can find this file at `mpmissions\<mapname>\expansion\settings\AILocationSettings.json`

### `RoamingLocations`

List of available locations for roaming AI (`"WaypointBehavior": "ROAMING"` in AIPatrolSettings.json). This will be filled automatically from the locations found in `CfgWorlds <mapname> Names`.
For maps that have no named locations, a list of random locations will be auto-generated 10 seconds after the server has finished loading.

Each location needs to have the following format:

```
        {
            "Name": "Settlement_Capital (Petropavlovsk-Sakhalinsky)",
            "Position": [
                4749.0,
                0.0,
                10695.0
            ],
            "Radius": 1000.0,
            "Type": "Capital",
            "Enabled": 1
        }
```

`Name` is just tell the locations apart more easily and you can choose anything you like. `Type` is pre-filled from the entries in `CfgWorlds`, you can leave it empty when adding custom locations.
If `Enabled` is 1 or `true`, AI can pick it as roaming destination, if it is 0 or `false`, the location will be ignored.

### `ExcludedRoamingBuildings`

List of building classnames or partial classnames (compared from the beginning of each string) that roaming AI (`"WaypointBehavior": "ROAMING"` in AIPatrolSettings.json) should not pick as destination (they may still go there to loot, which is fine).
It is **strongly** recommended to leave the defaults intact and only add to this list.

### `NoGoAreas`

List of areas that AI should avoid. Use sparsely since it affects pathfinding efficiency.
Each no go area needs to be in the following format:

```
	{
            "Name": "Hashima Exclusion Zone",
            "Position": [
                558.0,
                0.0,
                4558.0
            ],
            "Radius": 300.0,
            "Height": 130.0
        }
```

# Example file

Just an example, do NOT use this on your server.

```
{
    "m_Version": 1,
    "RoamingLocations": [
        {
            "Name": "Local_Random_1",
            "Position": [
                3335.79296875,
                10.640130996704102,
                4087.0830078125
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_2",
            "Position": [
                2573.40185546875,
                9.963448524475098,
                2610.62255859375
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_3",
            "Position": [
                1017.3966674804688,
                70.19000244140625,
                1893.38916015625
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_4",
            "Position": [
                1014.41552734375,
                49.70000076293945,
                1743.70556640625
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_5",
            "Position": [
                884.370849609375,
                20.486984252929689,
                1746.639404296875
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_6",
            "Position": [
                4177.36376953125,
                27.42099952697754,
                818.2633056640625
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_7",
            "Position": [
                1014.4307250976563,
                57.58000183105469,
                1743.693115234375
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_8",
            "Position": [
                906.4388427734375,
                57.470001220703128,
                1788.4852294921876
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_9",
            "Position": [
                3390.047119140625,
                14.184137344360352,
                4003.8798828125
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_10",
            "Position": [
                4114.3642578125,
                1.1689999103546143,
                1012.1612548828125
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        },
        {
            "Name": "Local_Random_11",
            "Position": [
                3708.531005859375,
                -3.8339545726776125,
                2351.710693359375
            ],
            "Radius": 100.0,
            "Type": "Local",
            "Enabled": 1
        }
    ],
    "ExcludedRoamingBuildings": [
        "Land_CementWorks_Hall2_Grey",
        "Land_Factory_Small",
        "Land_House_1W09",
        "Land_House_2W03",
        "Land_HouseBlock_1F4",
        "Land_Boathouse",
        "Land_Mine_Building",
        "Land_Shed_W2",
        "Land_Tenement_Big"
    ],
    "NoGoAreas": [
        {
            "Name": "Hashima Exclusion Zone",
            "Position": [
                558.0,
                0.0,
                4558.0
            ],
            "Radius": 300.0,
            "Height": 130.0
        }
    ]
}
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
