# ExpansionMod BookSettings.json Reference

## File Location

```text
Profiles/ExpansionMod/Settings/BookSettings.json
```

## Settings Reference

Supported value types include:

- `array`
- `bool`
- `color`
- `icon`
- `int`
- `string`

## Parameters

| Type | Parameter | Description | Default | Example |
|---|---|---|---:|---:|
| `int` | `m_Version` | Contains the current setting version number. Never change this value unless you really know what you are doing, as it is used internally for automatic conversion of old settings whenever something changes. | `5` | `5` |
| `bool` | `EnableStatusTab` | `0` = This page will not be displayed in the book.<br>`1` = The status tab will be available. The status tab contains character info such as health, hunger, thirst values, and more. | `1` | `1` |
| `bool` | `EnablePartyTab` | `0` = This page will not be displayed in the book.<br>`1` = The party tab will be available, allowing players to manage and create parties and invite players. Parties can be tweaked in `PartySettings.json`. | `1` | `1` |
| `bool` | `EnableServerInfoTab` | `0` = This page will not be displayed in the book.<br>`1` = A server info page will be available, allowing you to provide a description of your server and buttons to redirect players to your Discord, forum, or other places. | `1` | `1` |
| `bool` | `EnableServerRulesTab` | `0` = This page will not be displayed in the book.<br>`1` = The server rules tab will be available. This page allows servers to display their rules. | `1` | `1` |
| `bool` | `EnableTerritoryTab` | `0` = This page will not be displayed in the book.<br>`1` = The territory tab will be available, allowing players to manage their territories and invite players. Territories can be tweaked in `TerritorySettings.json`. | `1` | `1` |
| `bool` | `EnableBookMenu` | `0` = The book will be disabled.<br>`1` = Players can press `B` to open the book. | `1` | `1` |
| `int` | `CreateBookmarks` | `0` = Bookmarks will not be displayed for each book category/page.<br>`1` = Bookmarks will be displayed at the top of the book for quick navigation between categories. | `0` | `0` |
| `bool` | `ShowHaBStats` | If the mod **Heroes and Bandits** is loaded, this setting will be added.<br><br>`0` = Do not show any stats related to Heroes and Bandits.<br>`1` = Display stats related to Heroes and Bandits. | `1` | `1` |
| `bool` | `ShowPlayerFaction` | Enables or disables player faction display. | `0` | `0` |
| `array` | `RuleCategories` | Contains all rule categories. See [RuleCategories](#rulecategories) below. | See example | See example |
| `int` | `DisplayServerSettingsInServerInfoTab` | `0` = Server settings will not be displayed in the server info page.<br>`1` = Server settings will be displayed in the server info tab on the right page. | `1` | `1` |
| `array` | `SettingCategories` | Contains all setting categories. See [SettingCategories](#settingcategories) below. | See example | See example |
| `array` | `Links` | Contains a list of social links. See [Links](#links) below. | See example | See example |
| `array` | `Descriptions` | Contains a list of description categories. See [Descriptions](#descriptions) below. | See example | See example |
| `array` | `CraftingCategories` | Contains a list of crafting categories. See [CraftingCategories](#craftingcategories) below. | See example | See example |
| `bool` | `EnableCraftingRecipesTab` | Enables or disables the crafting recipes tab. | `1` | `1` |

---

## `RuleCategories`

Contains all rule categories.

### Fields

| Field | Type | Description |
|---|---|---|
| `CategoryName` | `string` | Title of the category. |
| `Rules` | `array` | A list of rules. |
| `Rules[].RuleParagraph` | `string` | Usually, servers enumerate their rules. This setting allows you to format numbering or lettering however you want. |
| `Rules[].RuleText` | `string` | The text of the rule. |

### Item Fields

Objects with:

- `CategoryName`
- `Rules`

### Example

```json
{
  "RuleCategories": [
    {
      "CategoryName": "General",
      "Rules": [
        {
          "RuleParagraph": "1.1.",
          "RuleText": "Insults, discrimination, extremist and racist statements or texts are taboo."
        },
        {
          "RuleParagraph": "1.2.",
          "RuleText": "We reserve the right to exclude people from the server who share extremist or racist ideas or who clearly disturb the server harmony."
        }
      ]
    },
    {
      "CategoryName": "Memes",
      "Rules": [
        {
          "RuleParagraph": "A)",
          "RuleText": "No step on snek"
        },
        {
          "RuleParagraph": "B)",
          "RuleText": "Kiwis are forbidden"
        }
      ]
    }
  ]
}
```

---

## `SettingCategories`

Contains all setting categories.

### Fields

| Field | Type | Description |
|---|---|---|
| `CategoryName` | `string` | The title of this setting category. |
| `Settings` | `array` | Contains all settings in this category. |
| `Settings[].SettingTitle` | `string` | The path of the setting.<br><br>Format: `Expansion.Settings.Category.SettingName`<br>Example: `Expansion.Settings.BaseBuilding.CanCraftVanillaBasebuilding` |
| `Settings[].SettingText` | `string` | Custom description text. This can be left empty. |
| `Settings[].SettingValue` | `string` | Custom secondary information about this setting, such as whether it is enabled or disabled. |

### Item Fields

Objects with:

- `CategoryName`
- `Settings`

### Example

```json
{
  "SettingCategories": [
    {
      "CategoryName": "Base-Building Settings",
      "Settings": [
        {
          "SettingTitle": "Expansion.Settings.BaseBuilding.CanCraftVanillaBasebuilding",
          "SettingText": "",
          "SettingValue": ""
        },
        {
          "SettingTitle": "Expansion.Settings.BaseBuilding.CanCraftExpansionBasebuilding",
          "SettingText": "",
          "SettingValue": ""
        }
      ]
    },
    {
      "CategoryName": "Raid Settings",
      "Settings": [
        {
          "SettingTitle": "Expansion.Settings.Raid.CanRaidSafes",
          "SettingText": "",
          "SettingValue": ""
        }
      ]
    }
  ]
}
```

---

## `Links`

Contains a list of social links.

### Fields

| Field | Type | Description |
|---|---|---|
| `Name` | `string` | The name to display. |
| `URL` | `string` | The URL used for this link. |
| `IconName` | `string` | The icon to display. A list may be provided later. |
| `IconColor` | `int` | The color of the icon. |

### Item Fields

Objects with:

- `Name`
- `URL`
- `IconName`
- `IconColor`

### Icon Color Notes

Use an RGBA-to-ARGB integer converter to generate the color code required for `IconColor`.

RGBA values:

- `R`: Red
- `G`: Green
- `B`: Blue
- `A`: Opacity from `0` to `255`
  - `0` = invisible
  - `255` = fully visible/opaque

Some RGBA generators use an alpha value from `0` to `1` instead of `0` to `255`, so watch out for that difference.

### Example

```json
{
  "Name": "Feedback",
  "URL": "https://exp.thurston.pw/",
  "IconName": "Forums",
  "IconColor": -14473430
}
```

---

## `Descriptions`

Contains a list of description categories.

### Fields

| Field | Type | Description |
|---|---|---|
| `CategoryName` | `string` | The title of this category. |
| `Descriptions` | `array` | A list of descriptions for this category. |
| `Descriptions[].DescriptionText` | `string` | A paragraph. |

### Item Fields

Objects with:

- `CategoryName`
- `Descriptions`

### Example

```json
{
  "Descriptions": [
    {
      "CategoryName": "My First Category",
      "Descriptions": [
        {
          "DescriptionText": "My first paragraph !"
        },
        {
          "DescriptionText": "And my second paragraph :)"
        }
      ]
    },
    {
      "CategoryName": "My Second Category",
      "Descriptions": [
        {
          "DescriptionText": "And this paragraph is in a new category"
        }
      ]
    }
  ]
}
```

---

## `CraftingCategories`

Contains a list of crafting categories.

### Fields

| Field | Type | Description |
|---|---|---|
| `CategoryName` | `string` | The title of this category. |
| `Results` | `array` | A list of craftable items for this category. |

> Note: The original reference appears to contain a typo: `DescrCraftingCategoriesptions -> Results`. This is documented here as `CraftingCategories -> Results`.

### Item Fields

Objects with:

- `CategoryName`
- `Results`

### Example

```json
{
  "CraftingCategories": [
    {
      "CategoryName": "The three must know crafts",
      "Results": [
        "fireplace",
        "splint",
        "improvisedsuppressor"
      ]
    },
    {
      "CategoryName": "Fishing",
      "Results": [
        "bait",
        "bonebait",
        "bonehook",
        "improvisedfishingrod"
      ]
    }
  ]
}
```
