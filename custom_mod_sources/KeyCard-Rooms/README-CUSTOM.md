# Local KeyCard Rooms source

This directory is a vendored snapshot of the public KeyCard Rooms source. The
exact upstream revision is recorded in `UPSTREAM_COMMIT.txt`.

## Why this source is here

The installed `@KeyCard-Rooms` package contains an older server implementation
whose reward contents are hardcoded in `KeyCardSystemServerConfig.pbo`. The
vendored upstream revision moves reward definitions into
`config/KeyCardSystem/config.json`, including nested attachments and weighted
random rewards.

Only these server-side script modules need to be customized and rebuilt:

- `KeyCardSystemServer`
- `KeyCardSystemServerConfig`

The unchanged doors, keycards, models, textures, sounds, and common client
scripts continue to come from the installed vendor PBOs.

## Build

Run `build_server_pbos.bat` from Windows. It temporarily maps this directory to
`P:`, which Mikero's config validator needs in order to resolve prefixed script
paths, and writes:

- `build/KeyCardSystemServer.pbo`
- `build/KeyCardSystemServerConfig.pbo`

The script does not deploy or overwrite live PBOs. Build and verification
outputs are intentionally ignored by Git.

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

## Deployment status

The rebuilt vendor PBO approach was tested and then retired because Workshop
clients load `KeyCardSystemServer.pbo` and require the signed Workshop version.
The live `@KeyCard-Rooms` folder must remain byte-for-byte vendor supplied.

The active customization is now the uniquely named server-only companion in
`../KeyCard-Rooms-Server`. It overrides the three door loot methods while being
loaded through `-serverMod`, so clients continue using the normal Workshop mod.
