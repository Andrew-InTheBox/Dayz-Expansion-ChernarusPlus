# ChernaTrader Secure Rooms source

This directory is a vendored snapshot of the public KeyCard Rooms source. The
exact upstream revision is recorded in `UPSTREAM_COMMIT.txt`.

Steam Workshop item:

https://steamcommunity.com/sharedfiles/filedetails/?id=3790655182

## Why this source is here

The installed `@KeyCard-Rooms` package contains an older server implementation
whose reward contents are hardcoded in `KeyCardSystemServerConfig.pbo`. This
custom build reads door locations from `config/KeyCardSystem/config.json` and
reward pools from `config/KeyCardSystem/rewards.json`.

The project now builds a complete signed client/server replacement. The door
and keycard asset PBOs remain byte-identical to upstream, while the shared and
server script PBOs are rebuilt from this source.

## Custom reward cargo

Both fixed and random reward objects accept an optional `cargo` array. Cargo is
created directly in the reward crate only when its parent reward is spawned, so
it can bundle non-attachment supplies with a selected weapon.

```json
"cargo": [
  { "className": "AmmoBox_762x54_20Rnd", "count": 2 }
]
```

An omitted `cargo` array adds nothing. A `count` below 1 is treated as 1.

The build uses:

```text
C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe
```

## Independent card tiers and named reward pools

Each entry in `$profile:KeyCardSystem/config.json` supports three independent
settings:

```json
{
  "className": "Land_KlimaX_T1Door",
  "cardTier": "T3",
  "rewardTier": "T3_HEAVY"
}
```

- `className` selects the physical T1, T2, or T3 door model.
- `cardTier` selects the required `T1`, `T2`, or `T3` keycard.
- `rewardTier` selects a named pool in `rewards.json`. `T1`, `T2`, and `T3`
  remain supported defaults; descriptive names such as `T3_HEAVY` and
  `T3_PRECISION` allow location-specific loot.

If `cardTier` or `rewardTier` is omitted, it falls back to the tier implied by
`className`. A named pool that has no matching entry produces an empty crate and
a server-log warning. The required card tier is network synchronized to the
client and is revalidated by the server before a card is consumed.

In `rewards.json`, `poolName` is the reward-pool identifier. It is independent
of both the physical door class and required card tier. For example, a pool
selected by `"rewardTier": "T3_HEAVY"` uses:

```json
{
  "poolName": "T3_HEAVY",
  "randomRewardCount": 1,
  "randomRewards": [],
  "fixedRewards": []
}
```

The legacy `doorClassName` reward property remains accepted so existing server
configurations continue to load, but new configurations should use `poolName`.

Fixed rewards are guaranteed when `chance` is omitted, zero, or `1.0`. A value
between zero and one makes that fixed reward an independent optional roll. This
is useful for utility items such as NVGs without allowing them to replace the
room's weapon draw.

## Full branded build

Run `build_full_mod.bat` to build and sign the combined client/server Workshop
package under:

```text
build/ChernaTraderSecureRooms/@ChernaTrader-SecureRooms
```

The build creates `ChernaTraderSecureRooms_v1.biprivatekey` under the ignored
`private_keys` directory. Never upload or distribute that private key. Only the
public `.bikey` belongs in the Workshop package and the server `keys` folder.

The combined package includes the customized server companion so the original
`@KeyCard-Rooms` and `_@KeyCardRoomsServer` packages are not loaded alongside
it.
