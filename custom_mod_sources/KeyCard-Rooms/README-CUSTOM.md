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

The build uses:

```text
C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe
```

## Deployment plan

Do not overwrite the live mod until the customized PBOs have been packed,
re-extracted to verify their prefixes, and tested against a generated JSON
configuration. Deployment should preserve backups of the installed PBOs.
