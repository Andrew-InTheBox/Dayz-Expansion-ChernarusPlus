# Adding Expansion Vehicles to a DayZ Server

This guide explains how to configure Expansion vehicles (using Landrover as an example) across the required configuration files. Four files must work together to fully define a vehicle spawn system.

## Overview: The Four Required Files

| File | Location | Purpose |
|------|----------|---------|
| `expansion_events.xml` | `mpmissions/<mission>/expansion_ce/` | Defines spawn event with nominal counts |
| `expansion_types.xml` | `mpmissions/<mission>/expansion_ce/` | Defines vehicle type properties and lifecycle |
| `expansion_spawnabletypes.xml` | `mpmissions/<mission>/expansion_ce/` | Defines attachments that spawn on vehicle |
| `cfgeventspawns.xml` | `mpmissions/<mission>/` | Defines actual X,Y,Z spawn coordinates |

## File 1: expansion_events.xml (Spawn Event Definition)

This file defines the vehicle spawn event and controls how many vehicles exist on the map.

### Example: VehicleLandRover Event

```xml
<event name="VehicleLandRover">
    <nominal>4</nominal>
    <min>2</min>
    <max>5</max>
    <lifetime>300</lifetime>
    <restock>0</restock>
    <saferadius>500</saferadius>
    <distanceradius>500</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>mixed</limit>
    <active>1</active>
    <children>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover"/>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover_Yellow"/>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover_Red"/>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover_Green"/>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover_Grey"/>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover_Orange"/>
        <child lootmax="0" lootmin="0" max="5" min="1" type="Expansion_Landrover_Blue"/>
    </children>
</event>
```

### Key Parameters Explained

| Parameter | Description |
|-----------|-------------|
| `nominal` | Target number of vehicles to maintain on map |
| `min` | Minimum vehicles before respawn triggers |
| `max` | Maximum allowed vehicles |
| `lifetime` | Seconds before cleanup check (300 = 5 minutes) |
| `restock` | Restock interval (0 = no auto restock) |
| `saferadius` | Distance from players before spawn allowed |
| `distanceradius` | Spawn distance consideration |
| `cleanupradius` | Cleanup radius when no players nearby |
| `position` | `fixed` = use coordinates from cfgeventspawns.xml |
| `active` | 1 = enabled, 0 = disabled |

### Children (Vehicle Variants)

Each `<child>` element specifies a vehicle class that can spawn:
- `type` - The exact class name from expansion_types.xml
- `min/max` - Weight for random selection among variants

---

## File 2: expansion_types.xml (Vehicle Type Properties)

This file defines the vehicle type properties including lifetime and restock behavior.

### Example: Landrover Type Definition

```xml
<type name="Expansion_Landrover">
    <nominal>0</nominal>
    <lifetime>3888000</lifetime>
    <restock>1800</restock>
    <min>0</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>100</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="vehicles"/>
</type>
```

### Key Parameters

| Parameter | Description |
|-----------|-------------|
| `nominal` | Usually 0 for event-spawned vehicles |
| `lifetime` | How long vehicle persists (3888000 = ~45 days) |
| `restock` | Respawn interval in seconds (1800 = 30 minutes) |
| `count_in_map` | 1 = count this vehicle toward limits |

### Required Entries

You need entries for:
1. **Base vehicle** - `Expansion_Landrover`
2. **Color variants** - `Expansion_Landrover_Yellow`, `_Red`, `_Blue`, etc.
3. **Vehicle parts** (for repair system):
   - `Expansion_Landrover_Wheel`
   - `Expansion_Landrover_Wheel_Ruined`
   - `Expansion_Landrover_Hood`
   - `Expansion_Landrover_Driverdoor`
   - `Expansion_Landrover_Codriverdoor`
   - `Expansion_Landrover_Left`
   - `Expansion_Landrover_Right`
   - `Expansion_Landrover_Trunk`

---

## File 3: expansion_spawnabletypes.xml (Attachments)

This file defines what parts/items spawn ON the vehicle when it appears.

### Example: Landrover Spawnable Type

```xml
<type name="Expansion_Landrover">
    <!-- Wheels (5 slots) -->
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Wheel" chance="0.80" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Wheel" chance="0.80" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Wheel" chance="0.80" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Wheel" chance="0.80" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Wheel" chance="0.80" />
    </attachments>

    <!-- Engine components -->
    <attachments chance="1.00">
        <item name="CarRadiator" chance="0.30" />
    </attachments>
    <attachments chance="1.00">
        <item name="CarBattery" chance="0.30" />
    </attachments>
    <attachments chance="1.00">
        <item name="SparkPlug" chance="0.40" />
    </attachments>

    <!-- Headlights (2 slots) -->
    <attachments chance="1.00">
        <item name="HeadlightH7" chance="0.20" />
    </attachments>
    <attachments chance="1.00">
        <item name="HeadlightH7" chance="0.20" />
    </attachments>

    <!-- Body panels/doors -->
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Hood" chance="0.40" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Driverdoor" chance="0.40" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Codriverdoor" chance="0.40" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Left" chance="0.40" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Right" chance="0.40" />
    </attachments>
    <attachments chance="1.00">
        <item name="Expansion_Landrover_Trunk" chance="0.40" />
    </attachments>
</type>
```

### Attachment Chance Values

- `1.00` = 100% chance the slot is considered
- `0.80` = 80% chance the item spawns in that slot
- Lower values = more damaged/incomplete spawns

**Note:** You need separate `<type>` blocks for each color variant if they use color-matched parts.

---

## File 4: cfgeventspawns.xml (Spawn Coordinates)

This file defines the actual map locations where vehicles can spawn.

### Example: VehicleLandRover Spawn Points

```xml
<event name="VehicleLandRover">
    <pos x="4233.940430" y="240.956482" z="10391.328125" a="62.495396" />
    <pos x="4233.940430" y="240.956482" z="10391.328125" a="62.495396" />
    <pos x="4233.940430" y="240.956482" z="10391.328125" a="62.495396" />
    <pos x="2579.301270" y="398.926697" z="5527.257324" a="-124.636536" />
    <pos x="4926.367188" y="525.644897" z="2076.613037" a="-111.321892" />
    <pos x="7262.602539" y="295.396698" z="2966.472412" a="-109.614449" />
</event>
```

### Coordinate Format

| Attribute | Description |
|-----------|-------------|
| `x` | East-West map coordinate |
| `z` | North-South map coordinate |
| `y` | Elevation (height above sea level) |
| `a` | Rotation angle in degrees |

### Important Notes

- The `event name` must **exactly match** the event name in `expansion_events.xml`
- Number of `<pos>` entries should be >= `nominal` from the event definition
- Duplicate coordinates are allowed (vehicle randomly picks from list)
- Use negative `a` values for counter-clockwise rotation

### Finding Coordinates

You can find coordinates by:
1. In-game admin tools showing player position
2. iZurvive map (approximate)
3. DayZ Editor tools
4. Copying from other working spawn configs

---

## Configuration Flow Diagram

```
cfgeventspawns.xml          expansion_events.xml
        │                           │
        │ WHERE (coordinates)       │ WHAT (vehicle classes)
        │                           │ HOW MANY (nominal/min/max)
        └───────────┬───────────────┘
                    │
                    ▼
            VEHICLE SPAWNS
                    │
                    │
        ┌───────────┴───────────┐
        │                       │
        ▼                       ▼
expansion_types.xml    expansion_spawnabletypes.xml
        │                       │
        │ LIFECYCLE             │ ATTACHMENTS
        │ (lifetime/restock)    │ (wheels, doors, parts)
```

---

## Checklist: Adding a New Vehicle Type

When adding Expansion vehicles to a new server:

### 1. expansion_events.xml
- [ ] Add `<event>` block with unique event name
- [ ] Set appropriate `nominal`, `min`, `max` values
- [ ] Set `position` to `fixed` for coordinate-based spawning
- [ ] Add all vehicle class variants as `<child>` elements
- [ ] Set `active` to `1`

### 2. expansion_types.xml
- [ ] Add `<type>` entry for base vehicle class
- [ ] Add `<type>` entries for all color variants
- [ ] Add `<type>` entries for vehicle parts (wheels, doors, etc.)
- [ ] Set appropriate `lifetime` (recommend 3888000 for ~45 days)

### 3. expansion_spawnabletypes.xml
- [ ] Add `<type>` block for base vehicle
- [ ] Define all attachment slots (wheels, engine parts, doors)
- [ ] Set spawn chances for each attachment
- [ ] Repeat for each color variant if using color-matched parts

### 4. cfgeventspawns.xml
- [ ] Add `<event>` block matching the event name exactly
- [ ] Add `<pos>` entries for each spawn location
- [ ] Ensure number of positions >= nominal value
- [ ] Verify coordinates are valid map locations

---

## Common Vehicle Class Names (Expansion)

| Vehicle | Base Class | Event Name Example |
|---------|------------|-------------------|
| Land Rover | `Expansion_Landrover` | VehicleLandRover |
| UAZ | `ExpansionUAZ` | VehicleUAZ |
| Bus | `Expansion_Bus` | VehicleBus |
| Motorcycle | `ExpansionMotorcycle` | VehicleMotorcycle |
| Helicopter | `ExpansionUH1H` | VehicleUH1H |
| Boat | `ExpansionZodiacBoat` | VehicleZodiac |

---

## Troubleshooting

### Vehicle not spawning
1. Check event name matches exactly between `expansion_events.xml` and `cfgeventspawns.xml`
2. Verify `active` is set to `1` in the event
3. Check coordinates are valid (not underwater, inside buildings)
4. Verify vehicle class names are spelled correctly

### Vehicle spawns without parts
1. Check `expansion_spawnabletypes.xml` has matching `<type>` entry
2. Verify part class names are correct
3. Increase `chance` values for attachments

### Vehicle despawns too quickly
1. Increase `lifetime` in `expansion_types.xml`
2. Check `cleanupradius` in event definition
3. Verify `deletable` flag is set to `0`

---

## Reference: Landrover Color Variants

All available Landrover class names:
- `Expansion_Landrover` (default)
- `Expansion_Landrover_Yellow`
- `Expansion_Landrover_Red`
- `Expansion_Landrover_Green`
- `Expansion_Landrover_Grey`
- `Expansion_Landrover_Orange`
- `Expansion_Landrover_Blue`

Each color variant has matching parts (e.g., `Expansion_Landrover_Yellow_Hood`).
