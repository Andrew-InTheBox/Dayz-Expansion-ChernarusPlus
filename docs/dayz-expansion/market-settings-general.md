[Return to the overview "The Market System"](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-The-Market-System)

Unlike most other settings that may not be map-specific, you can find the MarketSettings.json in your mpmission\dayzOffline.`<mapname>`\expansion\settings folder.

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"MarketSystemEnabled"`

Boolean.

* 0 = Disables the Market system.
* 1 = Enables the Market system.

### `"MaxVehicleDistanceToTrader"`

Maximum distance of a normal size vehicle (car/heli/boat) you own or have driven for it to show in a vehicle trader as sellable, and max distance of vehicle spawn zone.

### `"MaxLargeVehicleDistanceToTrader"`

Maximum distance of a large size vehicle (e.g. aircraft carrier) you own or have driven for it to show in a vehicle trader as sellable, and max distance of vehicle spawn zone.

### `"LargeVehicles"`

Array of vehicle class names that should use `MaxLargeVehicleDistanceToTrader` instead of `MaxVehicleDistanceToTrader`.

### `"LandSpawnPositions"`

Array of spawn positions and orientations for land vehicle spawn zones (e.g. cars).
Needs to have at least one entry in a radius of no more than `<MaxVehicleDistanceToTrader>` or `<MaxLargeVehicleDistanceToTrader>` from a vehicle trader.

Example

```
            "Position": [
                11903.400390625,
                140.0,
                12455.099609375
            ],
            "Orientation": [
                24.0,
                0.0,
                0.0
            ]
```

### `"AirSpawnPositions"`

Array of spawn positions and orientations for air vehicle spawn zones (e.g. helis).
Needs to have at least one entry in a radius of no more than `<MaxVehicleDistanceToTrader>` or `<MaxLargeVehicleDistanceToTrader>` from a vehicle trader.

Example

```
            "Position": [
                11903.400390625,
                140.0,
                12455.099609375
            ],
            "Orientation": [
                24.0,
                0.0,
                0.0
            ]
```

### `"WaterSpawnPositions"`

Array of spawn positions and orientations for water vehicle spawn zones (e.g. boats).
Needs to have at least one entry in a radius of no more than `<MaxVehicleDistanceToTrader>` or `<MaxLargeVehicleDistanceToTrader>` from a vehicle trader.

Example

```
            "Position": [
                11903.400390625,
                140.0,
                12455.099609375
            ],
            "Orientation": [
                24.0,
                0.0,
                0.0
            ]
```

### `"NetworkCategories"`

Used only internally.

Don't touch this setting as it's automatically generated and will be overwritten if changed.

### `"MarketMenuColors"`

Colors to be used for the market menu.

If you would like to customize the style of the menu you can do that by changing the color values in this section.
The format is hexadecimal RRGGBBAA, hexadecimal RGBA, or decimal R G B A with range 0-255 (alpha is optional in all cases).

* `"BaseColorVignette"`: **Vignette background color of the menu**
* `"BaseColorHeaders"`: **Color for all the header elements**
* `"BaseColorLabels"`: **Color for all the label backgrounds**
* `"BaseColorText"`: **Color for all text elements within the menu**
* `"BaseColorInfoSectionBackground"`: **Background color for the item info section**
* `"BaseColorTooltipsCorners"`: **Color of the tooltip elements corners**
* `"BaseColorTooltipsSeperatorLine"`: **Color of the tooltip element separator line**
* `"BaseColorTooltipsBackground"`: **Color of the tooltip element background**
* `"ColorDecreaseQuantityButton"`: **Decrease quantity button color**
* `"ColorSetQuantityButton"`: **Set quantity button color**
* `"ColorIncreaseQuantityButton"`: **Increase quantity button color**
* `"ColorSellPanel"`: **Sell panel background color**
* `"ColorSellButton"`: **Sell button color**
* `"ColorBuyPanel"`: **Buy panel background color**
* `"ColorBuyButton"`: **Buy button color**
* `"ColorMarketIcon"`: **Controls main market trader icon color. The icon gets displayed next to the trader type name on the upper left corner.**
* `"ColorFilterOptionsButton"`: **Hover color when hovering over the weapon filter button (if visible)**
* `"ColorFilterOptionsIcon"`: **Icon color of the weapon filter button.**
* `"ColorSearchFilterButton"`: **Search filter button color when hovering over it.**
* `"ColorCategoryButton"`: **Button color for the market category buttons when hovering over it.**
* `"ColorCategoryCollapseIcon"`: **Icon color of the market category arrow icon when the category is collapsed.**
* `"ColorItemButton"`: **Market item entry button color when hovering over the element**
* `"ColorItemInfoIcon"`: **Icon color of the info icon that get displayed on a item entry when it has a special condition**
* `"ColorItemInfoHasContainerItems"`: **Info text color for the text that get displayed in the item info tooltip when the item has other items in its container.**
* `"ColorItemInfoHasAttachments"`: \*\*Info text color for the text that get displayed in the item info tooltip when the item has attachments.
* `"ColorItemInfoHasBullets"`: **Info text color for the text that get displayed in the item info tooltip when the item is a magazine and has bullets in it.**
* `"ColorItemInfoIsAttachment"`: **Info text color for the text that get displayed in the item info tooltip when the item attached to an other item.**
* `"ColorItemInfoIsEquipped"`: **Info text color for the text that get displayed in the item info tooltip when the item is on inventory slot.**
* `"ColorItemInfoAttachments"`: **Info text color for the text that get displayed in the detailed item view tooltip when the item has default attachment items that can be bought.**
* `"ColorToggleCategoriesText"`: **Toggle categories button text color**
* `"ColorCategoryCorners"`: **Category element corners color**
* `"ColorCategoryBackground"`: **Category element background color**

You can use this site to generate the hex color values for these settings: <https://color.adobe.com/de/create/color-wheel>
(if you want alpha transparency, you have to add it manually after the first six digits)

### `"CurrencyIcon"`:

String.

Path to the icon that will be used as the currency icon within the market menu.

(Default: "DayZExpansion/Market/GUI/icons/coinstack2\_64x64.edds")

### `"ATMSystemEnabled"`

Boolean.

* 0 = Disables ATM lockers.
* 1 = Enables ATM lockers.

### `"MaxDepositMoney"`

Integer.

Max amount of money the players can deposit in the ATM Locker.

### `"DefaultDepositMoney"`

Integer.

Default money the player will get added to his ATM account when he joins the server for the first time.

### `"ATMPlayerTransferEnabled"`

Boolean.

* 0 = Disables ATM player to player money transfer.
* 1 = Enables ATM player to player money transfer.

### `"ATMPartyLockerEnabled"`

Boolean.

* 0 = Disables ATM party money account/deposit.
* 1 = Enables ATM party money account/deposit.

### `"MaxPartyDepositMoney"`

Integer.

Max amount of money the players can deposit in the ATM party account/deposit.

### `"SellPricePercent"`

Float.

Controls the global sell price difference of all market items.
By default this value is 75% of the buy price. Note that you can also configure sell price percentage individually for each market zone (see [zone settings](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Market-TraderZones-Settings)) or even individual items (see [market categories and items settings](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Market-Categories-Settings)) to override the global value individually.

### `"Currencies"`

Array. A list of currencies which can be stored in the player bank account from a ATM

```
"Currencies": [
    "expansiongoldbar",
    "expansiongoldnugget",
    "expansionsilverbar",
    "expansionsilvernugget"
]
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
