[Return to the overview "The Market System"](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-The-Market-System)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"DisplayName"`

String.

Display name of the market category that will be used within the market menu.

You can use **Localized** strings `#STR_BLABLA` or raw text `Hello World !`. Here are two examples:

```
"DisplayName": "#STR_EXPANSION_MARKET_CATEGORY_AMMOBOXES",
```

```
"DisplayName": "Ammo Boxes",
```

### `"Icon"`

String.

Icon of the category that will be displayed. You can find a list of valid icon names at <https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-List-of-default-icon-names>

```
"Icon": "Deliver",
```

### `"Color"`

String.

The **Hex color code** for this category.

You can find many online tools and softwares to find the desired color like this website for example <https://www.color-hex.com/> (without the # )

```
"Color": "FBFCFEFF",
```

### `"IsExchange"`

Bool.

Is this category (this file) used for any type of currencies players will use to buy and sell items.

Keep in mind enabling this setting (to 1) will make ALL the items in this file flagged as currency items. Make sure this file contain **only** currency items.

```
"IsExchange": 0,
```

### `"InitStockPercent"`

Float.

`Percentage of max stock` that each item will be initialized to in each zone on first server start (will only take effect for new zone files or zone files that did not have the item yet, or if you remove the item's existing entry from the existing zone file).

```
"InitStockPercent": 75.0,
```

### `"Items"`

Array of items.

Contains all the items and associated information for price and stock control.

* **`"ClassName"`:** String. Class name of the item/object you want to add to this category.
* **`"MaxPriceThreshold"`:** Integer. Maximum price the item can have (when stock is at minimum).
* **`"MinPriceThreshold"`:** Integer. Minimal price the item can have (when stock is at maximum).
* **`"SellPricePercent"`:** Float. Percentage of the price to use as sell price. Special value `-1` means use zone setting. Note that unlike for zones, the encoding used here is bfloat16 to optimize network performance, so precision is limited to around two to three decimal digits.
* **`"MaxStockThreshold"`:** Integer. Maximum stock the item can have overall in the market.
* **`"MinStockThreshold"`:** Integer. Minimal stock the item can have in the market.
* **`"QuantityPercent"`:** Integer. From 0 to 100 will be the percentage of the quantity of the item (mag, liquid, ammo, etc). -1 will default to 100%
* **`"SpawnAttachments"`:** Array [String]. Contains all the class names of items that will be attached by default when the player decides to buy the item with its default attachments. This also works with weapons if you want to create default weapon loadouts.
* **`"Variants"`:** Array [String]. Contains all the class names of the items that will be displayed as a variant for this base item.
  If you have for example different color variations for an item, then you can add these items into this array and they will be displayed in a dropdown menu in the detailed market item section whenever the base item has been selected. By default a variant will take over the configuration of the base item. If you want to have a different min/max price or min/max stock threshold configuration for a variant, then it also needs its own entry in the "Items" array with the desired configuration.

If you want an item to have static (infinite) stock, set both `MinStockThreshold` and `MaxStockThreshold` to 1.

If you want an item to have static price, set both `MinPriceThreshold` and `MaxPriceThreshold` to the same value.

a few examples:

```
{
    "ClassName": "ammobox_00buck_10rnd",
    "MaxPriceThreshold": 80,
    "MinPriceThreshold": 40,
    "SellPricePercent": -1.0,
    "MaxStockThreshold": 250,
    "MinStockThreshold": 1,
    "QuantityPercent": -1,
    "SpawnAttachments": [],
    "Variants": []
},
```

```
{
    "ClassName": "childbag_red",
    "MaxPriceThreshold": 40,
    "MinPriceThreshold": 20,
    "SellPricePercent": -1.0,
    "MaxStockThreshold": 100,
    "MinStockThreshold": 1,
    "QuantityPercent": -1,
    "SpawnAttachments": [],
    "Variants": [
        "childbag_blue",
        "childbag_green"
    ]
},
{
    "ClassName": "childbag_green",
    "MaxPriceThreshold": 50,
    "MinPriceThreshold": 25,
    "SellPricePercent": -1.0,
    "MaxStockThreshold": 100,
    "MinStockThreshold": 1,
    "QuantityPercent": -1,
    "SpawnAttachments": [],
    "Variants": []
},
```

```
{
    "ClassName": "fal",
    "MaxPriceThreshold": 2000,
    "MinPriceThreshold": 1700,
    "SellPricePercent": -1.0,
    "MaxStockThreshold": 100,
    "MinStockThreshold": 1,
    "QuantityPercent": -1,
    "SpawnAttachments": [
        "fal_oebttstck",
        "mag_fal_20rnd"
    ],
    "Variants": []
},
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
