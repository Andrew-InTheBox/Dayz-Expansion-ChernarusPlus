[Return to the overview "The Market System"](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-The-Market-System)

NOTE that traders will only act as traders if they are within the radius of a traderzone. See [Market Zones Settings](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Market-TraderZones-Settings)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"DisplayName"`

String.

Display name of the trader that will be displayed on the top of the market menu when using this trader.

You can use **Localized** strings `#STR_BLABLA` or raw text `Hello World !`. Here are two examples:

```
"DisplayName": "#STR_EXPANSION_MARKET_TRADER_VEHICLE_PARTS",
```

```
"DisplayName": "Vehicle Parts",
```

### `"MinRequiredReputation"` - Only if you have Expansion Hardline !

Integer.

The Minimum Reputation Required from the **player** to be able to interact with this trader.

```
"MinRequiredReputation": 0,
```

### `"MaxRequiredReputation"` - Only if you have Expansion Hardline !

Integer.

The Maximum Reputation Required from the **player** to be able to interact with this trader.

```
"MaxRequiredReputation": 2147483647,
```

### `"TraderIcon"`

String.

Icon of the trader that will be displayed on the top of the market menu when using this trader, see [List of default icon names](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-List-of-default-icon-names).

```
"TraderIcon": "Gas",
```

### `"Currencies"`

Array [String].

Classnames of the currencies this trader will accept. This currencies will need to be first configured in your **Market** folder. For more informations please read this guide: <https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Setting-up-Custom-Market-Currencies>

```
"Currencies": [
    "expansionbanknotehryvnia",
    "expansionbanknoteeuro"
],
```

### `"Categories"`

Array [String].

Filenames (without JSON extension) of market categories in ExpansionMod\Market that this trader should show. Can be used instead of or in addition to `Items`. Also supports the same buy/sell integers (see below) as `Items`, but has to be entered in a slightly different way (instead of `"CategoryFilename"`, use `"CategoryFilename:<value>"`).

* 0 = Can only be bought from this trader, but not sold
* 1 = Buy and Sell
* 2 = Can only be sold to this trader, but not bought
* 3 = Not visible but still available for item customisation (weapons, vests, backpacks) and attachments (vehicles)

Example:

```
    "Categories": {
        "Cars:1",
        "Vehicle_Parts:3"
    }
```

### `"Items"`

Map [String, Integer].

A list of items the trader can sell/buy.
The integer value controls whether an item can be only be bought (`0`), bought and sold (`1`), or only sold (`2`) at this specific trader. A special value of `3` is also possible, which means the item should not be shown in the trader menu normally and is only sellable/purchasable as attachment.

* 0 = Can only be bought from this trader, but not sold
* 1 = Buy and Sell
* 2 = Can only be sold to this trader, but not bought
* 3 = Not visible but still available for item customisation (weapons, vests, backpacks) and attachments

Example:

```
    "Items": {
        "expansioncarkey": 0,
        "engineoil": 2
    }
```

---

For further information please take a look at the setup guide for the trader entities/NPCs:

<https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Setting-up-Trader-Entities-and-NPCs>

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
