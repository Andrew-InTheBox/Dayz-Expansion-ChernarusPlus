[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki)

---

# 1) Finding HardlineSettings.json

Inside your `mpmissions/dayzoffline.mapname/expansion/settings/` you will find the **HardlineSettings.json**

## Setting Parameters:

### `"m_Version"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Current setting file version. Never change this unless you know what you are doing!

### `"PoorItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "poor".

### `"CommonItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "common".

### `"UncommonItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "uncommon".

### `"RareItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "rare".

### `"EpicItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "epic".

### `"LegendaryItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "legendary".

### `"MythicItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "mythic".

### `"ExoticItemRequirement"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Required player reputation points to buy/sell an item from the market that has the rarity "exotic".

### `"ShowHardlineHUD"`

Boolean.

Show/hide the hardline reputation points indicator in the main HUD.

### `"UseReputation"`

Boolean.

Use the hardline reputation system and let players gain reputation points for certain actions like eliminating an entity.

### `"UseFactionReputation"`

Boolean.

Use the faction reputation system and let players gain reputation points for all valid [eAIFactions](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/AI/Scripts/3_Game/DayZExpansion_AI/Factions/eAIFaction.c) individually that they can join.

### `"EnableFactionPersistence"`

Boolean.

Enable/disable faction persistence so players can join a faction and stay in that faction over server restarts.

### `"EnableItemRarity"`

Boolean.

Enable/disable the item rarity system. Will display the configured rarity given in the "ItemRarity" array on items in tooltips, icons or some menus.

### `"UseItemRarityOnInventoryIcons"`

Boolean.

Enable/disable if items icons and slots get colorized with the configured rarity color given in the "ItemRarity" array. The feature can also be disabled in the in-game client settings if this setting is enabled so players can always disable the colors.

### `"UseItemRarityForMarketPurchase"`

Boolean.

Enable/disable if players can only buy items from the market if they have the required reputation points for the certain item defined in the item required parameters for each individual item rarity. So if an item has a rarity has an Epic rarity defined in the "ItemRarity" array the player will need the required reputation points defined in the "EpicItemRequirement" parameter to buy the certain item.

### `"UseItemRarityForMarketSell"`

Boolean.

Enable/disable if players can only sell items at the market if they have the required reputation points for the certain item defined in the item required parameters for each individual item rarity. So if an item has a rarity has an Epic rarity defined in the "ItemRarity" array the player will need the required reputation points defined in the "EpicItemRequirement" parameter to sell the certain item.

### `"MaxReputation"`

Integer.

Max reputation points a player can reach overall.

### `"ReputationLossOnDeath"`

Integer.

Reputation points a player will lose whenever he dies to an enemy player or another entity.

### `"DefaultItemRarity"`

Integer<[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Default item rarity for all items that have no entry defined in the "ItemRarity" array.

### `"EntityReputation"`

Map<String, Integer>.

Need to be a valid entity class name and a reputation value that should get added or deducted from the player when eliminating the certain entity.
Can be a base class name or a specific one.

### `"ItemRarity"`

Map<String, [ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)>.

Defines item rarity of an item when the "EnableItemRarity" parameter is enabled. Needs to be a valid item base class name and an item rarity value ([ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)).

---

Item rarities [[ExpansionHardlineItemRarity](https://github.com/salutesh/DayZ-Expansion-Scripts/blob/release/DayZExpansion/Hardline/Scripts/3_Game/DayZExpansion_Hardline/DayZExpansion_Hardline_Enums.c)]:

```
Poor = 1
Common = 2
Uncommon = 3
Rare = 4
Epic = 5
Legendary = 6
Mythic = 7
Exotic = 8
Quest = 9
Collectable = 10
Ingredient = 11
```

Example setting JSON file:

```
{
    "m_Version": 10,
    "PoorItemRequirement": 0,
    "CommonItemRequirement": 0,
    "UncommonItemRequirement": 0,
    "RareItemRequirement": 0,
    "EpicItemRequirement": 0,
    "LegendaryItemRequirement": 0,
    "MythicItemRequirement": 0,
    "ExoticItemRequirement": 0,
    "ShowHardlineHUD": 1,
    "UseReputation": 1,
    "UseFactionReputation": 1,
    "EnableFactionPersistence": 1,
    "EnableItemRarity": 1,
    "UseItemRarityOnInventoryIcons": 1,
    "UseItemRarityForMarketPurchase": 0,
    "UseItemRarityForMarketSell": 0,
    "MaxReputation": 10000,
    "ReputationLossOnDeath": 100,
    "DefaultItemRarity": 2,
    "EntityReputation": {
        "Animal_GallusGallusDomesticus": 1,
        "eAIBase": 100,
        "AnimalBase": 10,
        "ZmbM_SoldierNormal_Base": 20,
        "Animal_UrsusArctos": 50,
        "ZmbM_NBC_Grey": 20,
        "ZombieBase": 10,
        "PlayerBase": 100,
        "Animal_UrsusMaritimus": 50,
        "ZmbM_NBC_Yellow": 20
    },
    "ItemRarity": {
        "aviatorglasses": 3,
        "booniehat_blue": 4,
        "canvas_backpack_red": 4,
        "civsedandoors_driver_black": 4,
        "tomato": 3,
        "joggingshoes_black": 2,
        "sparkplug": 4,
        "mag_cz550_10rnd": 5,
        "flag_chel": 1
    }
}
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
