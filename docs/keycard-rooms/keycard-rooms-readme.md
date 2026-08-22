# KeyCard Rooms setup and loot configuration notes

## References

- Steam Workshop: <https://steamcommunity.com/workshop/filedetails/?id=2620165863>
- Public source: <https://github.com/ManuShamil/DayZ-KeyCardSystem-Public/tree/main>

The Workshop page currently reports that the item has been removed and is incompatible with DayZ. The public repository describes itself as the source for the live version, but its latest `main` commit observed during this review was dated May 20, 2024. Confirm that any installed Workshop files still match the public source before relying on implementation details below.

## Conclusion

A repack should not be needed for ordinary room-loot customization. The mod already reads its door locations and rewards from a server-local JSON file.

The server component generates:

```text
$profile:KeyCardSystem/config.json
```

This server is launched with:

```text
-profiles=config
```

Therefore, the generated file should be located at:

```text
config/KeyCardSystem/config.json
```

Allow the mod to generate this file on its first successful startup, stop the server, and then edit the generated file.

## How the reward system works

Each entry in the JSON `locations` array contains:

- Security-door classname, position, and orientation
- Automatic close time
- Close delay
- Reward-crate position and orientation
- `fixedRewards`
- `randomRewards`

Rewards can include nested attachments. For example, a weapon can be created with an optic, and the optic can contain a battery.

When an authorized player opens a door, the server:

1. Opens the security door and starts its automatic-close timer.
2. Creates a `RedemptionMilitaryCrate` at the location's configured crate position.
3. Directly creates the fixed and selected random rewards inside the crate with `CreateInInventory()`.
4. Deletes a matching reward crate near the configured position when the door closes.

This is consequently a door reward-crate system, rather than ordinary loose loot distributed across room spawn points.

## Interaction with the Central Economy

Reward-crate contents bypass normal Central Economy selection. The reward code does not consult:

- Tier 1 through Tier 4 values
- Military, Police, Town, Hunting, or other usage categories
- Nominal, minimum, lifetime, or restock values
- The surrounding building's normal loot spawn points

If the JSON specifies an `SVD`, the script creates an SVD regardless of the room's map tier or location usage.

There can still be an indirect interaction with CE counting through an item's `count_in_cargo`, `count_in_hoarder`, `count_in_map`, and `count_in_player` flags in `types.xml`. Check those flags when balancing configured rewards. For example, this mission currently gives the SVD `count_in_cargo="0"`, so an SVD held in the reward crate should not reduce the CE's counted map supply.

The keycards are separate from the room rewards. To distribute keycards through normal map loot, add the appropriate classnames to the mission's `types.xml` and assign the desired usage and tier values:

```text
RedemptionKeyCard_01
RedemptionKeyCard_02
RedemptionKeyCard_03
RedemptionKeyCard_04
```

Those XML settings can govern where keycards appear. They do not govern the contents of the reward crates.

Do not assume that the dynamically created room buildings will reliably acquire vanilla CE loot points. The source does not explicitly populate their normal building loot proxies; its intended special-loot path is the temporary crate.

## Fixed and random reward behavior

The public source generates the same example reward arrays for all nine default doors. Door levels T1, T2, and T3 do not inherently select different-quality reward pools.

The generated example effectively provides:

- One fixed SVD with a PSO optic and battery
- One randomly selected SVD with a PSO optic and battery

The `chance` values in `randomRewards` behave as relative selection weights, not independent chances for every entry to spawn. The code sums all weights and selects one entry from the cumulative range. Therefore, if the array contains only one SVD with a weight of `0.5`, that SVD is still selected every time.

The same weighted-one-of behavior applies to nested random attachments. The current code has no explicit built-in `none` outcome. Multiple entries are needed to produce an actual choice among items.

## Persistence/cache caveat after editing loot

The mod copies configuration data into binary persistence files:

```text
config/KeyCardSystem/data/cache.dat
config/KeyCardSystem/data/persistance.dat
```

The source deliberately excludes `fixedRewards` and `randomRewards` when checking whether the JSON configuration changed. Editing only the loot arrays may therefore leave existing doors using old rewards loaded from `persistance.dat`.

After changing room loot:

1. Stop the server.
2. Back up the `config/KeyCardSystem` directory.
3. Remove `cache.dat` and `persistance.dat` from `config/KeyCardSystem/data`.
4. Start the server and let the mod rebuild them from `config.json`.
5. Test at least one complete open/loot/automatic-close cycle.

Removing those files resets the KeyCardSystem's cached door state and timers. It does not reset the DayZ player database or the main world persistence.

## Custom assets versus room compositions

The mod includes these purpose-built assets:

- `Land_KlimaX_T1Door`
- `Land_KlimaX_T2Door`
- `Land_KlimaX_T3Door`
- Four keycard models
- `RedemptionMilitaryCrate`

The nine rooms are not nine complete custom room models. The bundled Chernarus preset constructs them from a mixture of custom doors, ordinary DayZ buildings, and `vbldr_*` objects used to close openings or form barriers.

The supporting preset includes:

- `Land_Mil_Barracks2` near a T1 door
- `Land_Workshop2` near a T1 door
- Builder logs/barriers around a T1 door
- `Land_Shed_M1` around a T1 door
- `Land_Shed_M3` around a T1 door
- `Land_Mil_Barracks1` around a T2 door
- `Land_Barn_Brick1` around a T2 door
- Prison bars and logs around a T2 door
- `Land_Mil_AircraftShelter`, aircraft-shelter doors, and metal plates around the T3 door

The source preset places approximately 60 supporting objects in total.

### Map-edit preset switch

The JSON contains:

```json
"disableMapEditsPreset": true
```

In the reviewed source, `true` disables the supplied supporting Chernarus building edits. Set it to `false` to enable those edits.

The distinction is important:

- The `locations` array controls security-door and reward-crate positions.
- `disableMapEditsPreset` controls the surrounding buildings, barriers, logs, and plates supplied by the preset.

If the doors are configured but the map-edit preset is disabled, some doors may be exposed, floating, or attached to nothing unless equivalent structures are supplied by another map edit.

## Default coordinates

DayZ vectors use `X Y Z`. For a two-dimensional map, use the `X / Z` values.

| Level | Door X/Y/Z | Reward crate X/Y/Z |
| --- | --- | --- |
| T1 | `2493.35 193.60 5081.33` | `2489.09 194.82 5074.34` |
| T1 | `9847.759766 283.299988 8708.379883` | `9844.941406 283.347778 8708.894531` |
| T1 | `6198.29 301.01 7726.80` | `6200.301270 301.137756 7725.487793` |
| T1 | `7816.770020 140.143997 12409.500000` | `7816.721191 140.013031 12410.583008` |
| T1 | `7622.580078 214.850006 5201.629883` | `7622.511719 214.923615 5202.895996` |
| T2 | `2840.07 270.742 9742.71` | `2835.42 270.0 9749.29` |
| T2 | `6035.05 267.285 10400.70` | `6041.54 267.351 10396.60` |
| T2 | `3966.530029 311.619995 8777.599609` | `3966.502197 311.533478 8772.284180` |
| T3 | `1747.739990 450.299988 14021.799805` | `1758.643799 450.303833 14022.893555` |

Door and crate coordinates are hardcoded only as the initial defaults used when generating `config.json`. Once the JSON exists, those positions and orientations can be edited there without repacking the mod. Supporting preset structures remain hardcoded in the server-config source, so moving a complete room composition is different from moving only its door and crate.

## Suggested future setup procedure

1. Confirm that the Workshop mod can still be downloaded and is compatible with the current DayZ server version.
2. Install its required client and server components and any declared dependencies.
3. Preserve the original signing and client/server mod separation from the supplied package.
4. Start the server once to generate `config/KeyCardSystem/config.json`.
5. Stop the server and back up the generated KeyCardSystem directory.
6. Decide whether to enable the bundled Chernarus map-edit preset.
7. Replace the example SVD rewards with balanced per-location loot arrays.
8. Add the keycard classnames to `types.xml` if they should enter the normal map economy.
9. Clear only the KeyCardSystem `.dat` cache files after reward changes.
10. Validate all nine locations for terrain alignment, conflicting map edits, inaccessible doors, and crate placement.
11. Test opening, reward creation, automatic closing, crate deletion, and server restart persistence.

## When source changes or repacking might be justified

Normal reward customization does not require repacking. A small server-side override or a source fork would only be useful for features such as:

- Named, reusable loot pools
- Separate T1, T2, and T3 pools without repeating arrays
- Independent per-item probabilities
- An explicit chance to spawn nothing
- Minimum and maximum reward counts
- Selection based on map tier or location usage
- Automatic detection of loot-only JSON changes
- Validation and logging for invalid classnames
- Moving or replacing complete supporting room compositions through an external config

If a fork is eventually made, preserve the original PBO prefixes and `CfgMods` paths. A repacked PBO will not retain the original signature. The public repository did not contain a visible license granting redistribution rights during this review, so obtain permission before publishing or redistributing a repack.
