[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"EnableStatusTab"`

Bool.

* 0 = This page won't be displayed in the book.
* 1 = The status tab will be available. The status tab contains character info like health, hunger/thirst values, etc.

### `"EnablePartyTab"`

Bool.

* 0 = This page won't be displayed in the book.
* 1 = The party tab will be available allowing players to manage and creating parties and invite players. You can tweak parties in the PartySettings.json

### `"EnableServerInfoTab"`

Bool.

* 0 = This page won't be displayed in the book.
* 1 = A server info page will be available allowing you to provide a description of your server, buttons to redirect the player to your discord, forum or other places.

### `"EnableServerRulesTab"`

Bool.

* 0 = This page won't be displayed in the book.
* 1 = The server rules tab will be available. This page allow servers to display their rules

### `"EnableTerritoryTab"`

Bool.

* 0 = This page won't be displayed in the book.
* 1 = The territory tab will be available allowing players to manage their territories and invite players. You can tweak territories in the TerritorySettings.json

### `"EnableBookMenu"`

Bool.

* 0 = The Book will be disabled
* 1 = Players can press B to open the Book.

### `"CreateBookmarks"`

Bool.

* 0 = Bookmarks won't be displayed for each book categories (pages)
* 1 = Bookmarks will be displayed on the top of the book for quick navigation between the categories.

### `"ShowHaBStats"`

Bool. If the mod Heroes and Bandits is loaded, this setting will be added

* 0 = Do not show any stats related to Heroes and Bandits
* 1 = Display stats related to Heroes and Bandits

### `"RuleCategories"`

Array. Contain all the rules categories.

### `"RuleCategories"` -> `"CategoryName"`

String. Title of the category.

### `"RuleCategories"` -> `"Rules"`

Array. A list of rules.

### `"RuleCategories"` -> `"Rules"` -> `"RuleParagraph"`

String. Usualy server like to enumarate their rules. This setting allows you to do this and the way you want it.

### `"RuleCategories"` -> `"Rules"` -> `"RuleText"`

String. The text of your rule.

```
"RuleCategories": 
[
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
],
```

### `"DisplayServerSettingsInServerInfoTab"`

Bool.

* 0 = The server settings won't be displayed in the server info page.
* 1 = Will display the server settings in the server info tab on the right page

### `"SettingCategories"`

Array. Contain all the settings categories.

### `"SettingCategories"` -> `"CategoryName"`

String. The title of this setting category name.

### `"SettingCategories"` -> `"Settings"`

Array. Contain all the settings of this category.

### `"SettingCategories"` -> `"Settings"` -> `"SettingTitle"`

String. The path of the setting.

* Format: "Expansion.Settings.Category.SettingName"
* Example: "Expansion.Settings.BaseBuilding.CanCraftVanillaBasebuilding"

### `"SettingCategories"` -> `"Settings"` -> `"SettingText"`

String. You can write a custom description or leave it empty.

### `"SettingCategories"` -> `"Settings"` -> `"SettingValue"`

String. You can also use this setting to display a custom secondary information about this setting. If it's enabled or disabled for example.

```
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
```

### `"Links"`

Array. Contain a list of social links.

### `"Links"` -> `"Name"`

String. The name to display

### `"Links"` -> `"URL"`

String. The URL used for this link

### `"Links"` -> `"IconName"`

String. The icon to display. A list will be provided later

### `"Links"` -> `"IconColor"`

Integer. The color of the icon

Use [this website to generate the color](https://argb-int-calculator.netlify.app/) you want to apply on your Icon!

Enter the RGBA values and then click on the button "ARGB → int" to generate the color code you will need.

* R: Red
* G: Green
* B: Blue
* A: Opacity from 0 (can't be seen) to 255 (very visible, opaque)

You can use [this website to generate the RGBA color](https://htmlcolors.com/rgba-color), however watch out this website generate the A value from 0 to 1 instead of 255 !

```
{
    "Name": "Feedback",
    "URL": "https://exp.thurston.pw/",
    "IconName": "Forums",
    "IconColor": -14473430
}
```

### `"Descriptions"`

Array. A list of description categories.

### `"Descriptions"` -> `"CategoryName"`

String. The title of this category.

### `"Descriptions"` -> `"Descriptions"`

Array. A list of description for this category

### `"Descriptions"` -> `"Descriptions"` -> `"DescriptionText"`

String. A paragraph.

```
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
```

### `"CraftingCategories"`

Array. A list of crafting categories.

### `"CraftingCategories"` -> `"CategoryName"`

String. The title of this category.

### `"DescrCraftingCategoriesptions"` -> `"Results"`

Array. A list of craftable items for this category

```
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
```

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
