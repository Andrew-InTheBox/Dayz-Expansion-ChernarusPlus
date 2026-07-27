[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"EnablePlayerTags"`

Bool.

* 0 = Disabled.
* 1 = Players nametags will be enabled. Looking at a player will display his name.

If you want this feature to be enabled anywhere. Make sure `"ShowPlayerTagsInSafeZones"` and `"ShowPlayerTagsInTerritories"` are disabled (0)

### `"PlayerTagViewRange"`

Integer.

The maximum distance (in meters) to see the nametags when looking at a player.

### `"PlayerTagsIcon"`

Integer.

The path of a edds icon so you can use your own icon or another expansion icon.

### `"PlayerTagsColor"`

Integer.

The color of the icon, use [this website to generate the color](https://argb-int-calculator.netlify.app/) you want.
Enter the RGBA values and then click on the button "ARGB → int" to generate the color code you will need.

```
R: Red
G: Green
B: Blue
A: Opacity from 0 (can't be seen) to 255 (very visible, opaque)
```

You can use [this website to generate the RGBA color](https://htmlcolors.com/rgba-color), however watch out this website generate the A value from 0 to 1 instead of 255 !

### `"PlayerNameColor"`

Integer.

Color for the name displayed in the tag, use [this website to generate the color](https://argb-int-calculator.netlify.app/) you want.
Enter the RGBA values and then click on the button "ARGB → int" to generate the color code you will need.

```
R: Red
G: Green
B: Blue
A: Opacity from 0 (can't be seen) to 255 (very visible, opaque)
```

You can use [this website to generate the RGBA color](https://htmlcolors.com/rgba-color), however watch out this website generate the A value from 0 to 1 instead of 255 !

### `"ShowPlayerTagsInSafeZones"`

Bool.

* 0 = Disabled.
* 1 = Should you only allow players to see the nametags of others while inside a safezone.

### `"ShowPlayerTagsInTerritories"`

Integer.

* 0 = Disabled.
* 1 = Should you only allow players to see the nametags of others while inside a territory.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
