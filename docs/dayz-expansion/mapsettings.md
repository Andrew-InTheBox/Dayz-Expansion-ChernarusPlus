[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

Unlike most other settings that may not be map-specific, you can find the MapSettings.json in your mpmission\dayzOffline.`<mapname>`\expansion\settings folder.

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"EnableMap"`

Bool.

* 0 = Will use the vanilla map UI (white map)
* 1 = Will use the Expansion map UI (colored map)

### `"UseMapOnMapItem"`

Bool.

* 0 = The default vanilla map UI will be used when using the map item "open map" action.
* 1 = The Expansion map UI will be used when using the map item "open map" action.

### `"ShowPlayerPosition"`

Integer.

* 0 = The player will not have a marker on his location.
* 1 = The player will have a marker on the map on his exact location. In short, a "you are here" marker.
* 2 = The player will have a marker on the map on his exact location if the player have a compass in his inventory or his hands.

### `"ShowMapStats"`

Bool.

* 0 = The player won't be able to know the XYZ position of a marker.
* 1 = The player will be able to know the XYZ position of a marker with the marker list of by holding SHIFT when his mouse will be hover a marker on the map.

### `"NeedPenItemForCreateMarker"`

Bool.

* 0 = The player don't need a Pen to create markers on the map.
* 1 = The player need a Pen in his inventory to create markers on the map.

### `"NeedGPSItemForCreateMarker"`

Bool.

* 0 = The player don't need a GPS to create markers on the map.
* 1 = The player need a GPS in his inventory to create markers on the map.

### `"CanCreateMarker"`

Bool.

* 0 = The player won't be able to create any markers.
* 1 = Allow the player to create markers on the map.

### `"CanCreate3DMarker"`

Bool. Require "CanCreateMarker" to be enabled (set to 1)

* 0 = The player will not be able to create 3D markers.
* 1 = Allow the player to create 3D markers on the map.

### `"CanOpenMapWithKeyBinding"`

Bool.

* 0 = The player will have to open a physical item map to see the map.
* 1 = The player can open the map with a keybind instead of interacting with the physical map ("Open map" action).

### `"ShowDistanceOnPersonalMarkers"`

Bool.

* 0 = The personal markers won't show their distance from the player.
* 1 = The distance will be displayed under every personal 3d markers.

### `"EnableHUDGPS"`

Bool.

* 0 = The player will be only able to open the map with M
* 1 = The player will be able to enabled the GPS HUD by Holding N and to switch modes by tapping N. He will also be able to open the map with M

### `"NeedGPSItemForKeyBinding"`

Bool.

* 0 = You don't need the GPS item to open the map (M) or the GPS UI (hold N and tap N to switch modes)
* 1 = You need the physical GPS item to open the map (M) or the GPS UI (hold N and tap N to switch modes)

### `"NeedMapItemForKeyBinding"`

Bool.

* 0 = You don't need the map item to open the map (M)
* 1 = You need the physical map item to open the map (M)

### `"EnableServerMarkers"`

Bool.

* 0 = All the server markers will be disabled and invisible on the map.
* 1 = The server markers will be enabled and visible.

### `"ShowNameOnServerMarkers"`

Bool.

* 0 = All the server markers won't have a name.
* 1 = All the server markers will display the name they have configured.

### `"ShowDistanceOnServerMarkers"`

Bool.

* 0 = The distance under the server markers won't be displayed.
* 1 = The distance under the server markers will be displayed.

### `"ServerMarkers"`

Array. Allow server owners to display server markers on the map. See [this tutorial](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/How-to-configure-the-Expansion-Map-Markers) for more explaination.

### `"EnableHUDCompass"`

Bool.

* 0 = The HUD compass will be disabled
* 1 = Players will have a HUD compass on the top of their screen.

### `"NeedCompassItemForHUDCompass"`

Bool.

* 0 = The Item compass is not needed
* 1 = To see the HUD compass, the player need a compass in his inventory

### `"NeedGPSItemForHUDCompass"`

Bool.

* 0 = The Item GPS is not needed
* 1 = To see the HUD compass, the player need a GPS in his inventory

### `"CompassColor"`

Integer. The color of the Compass HUD

Use [this website to generate the color](https://argb-int-calculator.netlify.app/) you want!

Enter the RGBA values and then click on the button "ARGB → int" to generate the color code you will need.

* R: Red
* G: Green
* B: Blue
* A: Opacity from 0 (can't be seen) to 255 (very visible, opaque)

You can use [this website to generate the RGBA color](https://htmlcolors.com/rgba-color), however watch out this website generate the A value from 0 to 1 instead of 255 !

### `"CreateDeathMarker"`

Bool.

Whether or not to create a map marker at the position of your death when you die.

### `"PlayerLocationNotifier"`

Bool.

* 0 = The player will not get any notifications telling him where he is and what time is it.
* 1 = The player will get a dayz mod styled notification with the town name and time and date.

![Player Location Notifier](https://camo.githubusercontent.com/093bc2d5a25807ac198bbbd39fdf2e87a00eae76578bcf29140a2a4f0483d060/68747470733a2f2f692e696d6775722e636f6d2f6f5272764252452e706e67)

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
