[Return to the summary](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BServer-Hosting%5D-Server-settings/)

---

### `"m_Version"`

Integer.

Contains the current setting version number, **never** change this value unless you *really* know what you are doing as it's used internally for automatic conversion of old settings whenever we change something.

### `"EnableNotification"`

Bool.

* 0 = All the notifications will be disabled.
* 1 = Notifications will be enabled.

### `"ShowPlayerJoinServer"`

Bool.

* 0 = The "Player Joined the server" notification will not be displayed
* 1 = The "Player Joined the server" notification will be enabled

### `"JoinMessageType"`

Integer.

* 0 = The notification will be displayed in the chat
* 1 = The notification will be displayed as a notification on the top left corner of your screen

### `"ShowPlayerLeftServer"`

Bool.

* 0 = The "Player left the server" notification will not be displayed
* 1 = The "Player left the server" notification will be enabled

### `"LeftMessageType"`

Integer.

* 0 = The notification will be displayed in the chat
* 1 = The notification will be displayed as a notification on the top left corner of your screen

### `"ShowAirdropStarted"`

Bool.

* 0 = The notification when ever an airdrop event started will not be displayed
* 1 = Displays the notification when ever a airdrop event started.

### `"ShowAirdropClosingOn"`

Bool.

* 0 = The notification when ever an airdrop plane gets close to the drop location will not be displayed
* 1 = Displays the notification when ever a airdrop plane gets close to the drop location

### `"ShowAirdropDropped"`

Bool.

* 0 = The notification when ever an airdrop has been droped on the drop location will not be displayed
* 1 = Displays the notification when ever a airdrop has been droped on the drop location

### `"ShowAirdropEnded"`

Bool. ("The Airdrop at ... was destroyed by infected.")

* 0 = The notification when ever an airdrop has ended on the drop location will not be displayed
* 1 = Displays the notification when ever a airdrop has ended on the drop location

### `"ShowPlayerAirdropStarted"`

Bool.

* 0 = The notification when ever a player calls an airdrop with an airdrop flare will not get displayed
* 1 = Displays the notification when a player calls an airdrop with an airdrop flare.

### `"ShowPlayerAirdropClosingOn"`

Bool.

* 0 = The notification when ever a player calls an airdorop with an airdrop flare and it gets close to the drop location will not be displayed
* 1 = Displays the notification when ever a player calls an airdorop with an airdrop flare and it gets close to the drop location

### `"ShowPlayerAirdropDropped"`

Bool.

* 0 = The notification when ever a player calls an airdorop with an airdrop flare and it has been droped on the drop location will not be displayed
* 1 = Displays the notification when ever a player calls an airdorop with an airdrop flare and it has been droped on the drop location

### `"ShowTerritoryNotifications"`

Bool.

* 0 = The notification when ever a player enters an territory will not be displayed
* 1 = Displays the notification when ever a player enters an territory

### `"EnableKillFeed"`

Bool.

* 0 = All the kill-feed notifications will be disabled
* 1 = Kill-feed will be enabled

### `"KillFeedMessageType"`

Bool.

* 0 = Kill-feed notification will be displayed in the chat
* 1 = Kill-feed notification will be displayed as a notification on the top left corner of your screen

### `"KillFeedFall"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by fall damage
* 1 = Displays kill-feed notifications related to player deaths by fall damage

### `"KillFeedCarHitDriver"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an car hit with a driver in the car
* 1 = Displays kill-feed notifications related to player deaths by a car hit with a driver in the car

### `"KillFeedCarHitNoDriver"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an car hit with no driver in the car
* 1 = Displays kill-feed notifications related to player deaths by an car hit with no driver in the car

### `"KillFeedCarCrash"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an car crash as a driver
* 1 = Displays kill-feed notifications related to player deaths by an car crash as a driver

### `"KillFeedCarCrashCrew"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an car crash as a passanger
* 1 = Displays kill-feed notifications related to player deaths by an car crash as a passanger

### `"KillFeedHeliHitDriver"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an heli hit with a pilot
* 1 = Displays kill-feed notifications related to player deaths by an heli hit with a pilot

### `"KillFeedHeliHitNoDriver"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an heli hit with no pilot
* 1 = Displays kill-feed notifications related to player deaths by an heli hit with no pilot

### `"KillFeedHeliCrash"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an heli crash as a pilot
* 1 = Displays kill-feed notifications related to player deaths by an heli crash as a pilot

### `"KillFeedHeliCrashCrew"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an heli crash as a passanger
* 1 = Displays kill-feed notifications related to player deaths by an heli crash as a passanger

### `"KillFeedBarbedWire"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by hit damage from barbed wires
* 1 = Displays kill-feed notifications related to player deaths by hit damage from barbed wires

### `"KillFeedFire"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by hit damage from fireplaces
* 1 = Displays kill-feed notifications related to player deaths by hit damage from fireplaces

### `"KillFeedWeaponExplosion"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by hit damage from a weapon explosion (granades, satchels..)
* 1 = Displays kill-feed notifications related to player deaths by hit damage from a weapon explosion

### `"KillFeedDehydration"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by dehydration
* 1 = Displays kill-feed notifications related to player deaths by dehydration

### `"KillFeedStarvation"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by starvation
* 1 = Displays kill-feed notifications related to player deaths by starvation

### `"KillFeedBleeding"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by blood loss
* 1 = Displays kill-feed notifications related to player deaths by blood loss

### `"KillFeedSuicide"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by a suicide
* 1 = Displays kill-feed notifications related to player deaths by a suicide

### `"KillFeedWeapon"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by a fire weapon
* 1 = Displays kill-feed notifications related to player deaths by a fire weapon

### `"KillFeedMeleeWeapon"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by a melee weapon
* 1 = Displays kill-feed notifications related to player deaths by a meele weapon

### `"KillFeedBarehands"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an other player in a fist fight
* 1 = Displays kill-feed notifications related to player deaths by an other player in a fist fight

### `"KillFeedInfected"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an infected/zombie
* 1 = Displays kill-feed notifications related to player deaths by an infected/zombie

### `"KillFeedAnimal"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by an wild animal
* 1 = Displays kill-feed notifications related to player deaths by an wild animal

### `"KillFeedKilledUnknown"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by and unknown source with an entity
* 1 = Displays kill-feed notifications related to player deaths by and unknown sourcew ith an entity

### `"KillFeedDiedUnknown"`

Bool.

* 0 = Disables the display of kill-feed notifications related to player deaths by and unknown source
* 1 = Displays kill-feed notifications related to player deaths by and unknown source

### `"EnableKillFeedDiscordMsg"`

Bool.

**THIS SYSTEM DOES NOT WORK CORRECTLY AS INTENDED SO FAR AND IS DISABLED BY DEFAULT!**

* 0 = Disables the display of kill-feed discord messages when the CF webhook has been configured correctly
* 1 = Displays kill-feed discord messages when the CF webhook has been configured correctly

Copyright© 2020-2026 DayZ Expansion Mod Team. We do not authorize any entity to publish this DayZ Standalone modification without licensing from the DayZ Expansion Mod Team.
