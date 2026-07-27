[Return to the overview "The Market System"](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-The-Market-System)

Unlike most other settings that may not be map-specific, you can find the traderzones folder in your mpmission\dayzOffline.`<mapname>`\expansion folder.

Traders will only act as traders if they are within the radius of a traderzone. NOTE that zones are spheres, so altitude for `Position` needs to be set correctly!

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"m_DisplayName"`

String.

Market zone display name, can be what ever you want. Used for logging.

### `"Position"`

Vector.

Center position of the market zone in the game world.

### `"Radius"`

Float.

Used to define the size of the trader zone in the game world.

### `"BuyPricePercent"`

Float.

This controls the buy price for all market items in this specific zone.
By default this value is 100% of the buy price as calculated from an item's stock, min price, max price, and min/max stock thresholds (see market categories settings).

### `"SellPricePercent"`

Float.

This controls the sell price for all market items in this specific zone.
By default this value is -1.0, meaning the global value from market settings will be used, but can be overridden by setting this to the desired percentage.

### `"Stock"`

Map<String, Integer>.

Contains all the items that can be purchased in this market zone and the current stock of each item.
You can set the stock for each individual item or set it to 0 (meaning traders in this zone will only start selling the item after players have sold at least one of the respective item to the trader).

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
