[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"EnableGlobalChat"`

Bool.

* 0 = The global chat (blue chat) will be disabled.
* 1 = It will enable the global chat. The global chat allow players to talk to anyone from anywhere on the map.

### `"EnablePartyChat"` (requires DayZ-Expansion-Groups or Bundle)

Bool.

* 0 = The party chat (green chat) will be disabled.
* 1 = It will enable the party chat. The party chat allow players to talk to anyone in their group from anyone on the map.

### `"EnableTransportChat"`

Bool.

* 0 = The transport chat (yellow chat) will be disabled.
* 1 = It will enable the transport chat. The transport chat allow players to talk to anyone inside the same vehicle than you.

### `"ChatColors"`

Array<String, String>.

A list of **Hex colors** for each chat channels. The first part of the setting is the name of the chat channel we want to target and the second part it's new color.

```
"MyChannel_ChatColor": "EB45EBFF",
```

You can find many online tools and softwares to find the desired color like this website for example <https://www.color-hex.com/> (without the # )

```
"SystemChatColor": "EB45EBFF",
"AdminChatColor": "FF392BFF",
"GlobalChatColor": "58C3FFFF",
"DirectChatColor": "FFFFFFFF",
"TransportChatColor": "FFCE09FF",
"PartyChatColor": "0AFA7AFF",
"TransmitterChatColor": "F9FF49FF"
```

* SystemChatColor: When the **SERVER** is writting a message - Everyone can see this channel
* AdminChatColor: When a **ADMIN** is writting a message - Everyone can see this channel
* GlobalChatColor: When someone is writting a server wide (global) message.
* DirectChatColor: The "local" chat, this chat is the default channel dayz provide.
* TransportChatColor: When a player in the same vehicle than you is writting.
* PartyChatColor: When a player from your group is writting. - Only if you have Expansion Party !
* TransmitterChatColor: When a player is using PE in a town and you are in the area.

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
