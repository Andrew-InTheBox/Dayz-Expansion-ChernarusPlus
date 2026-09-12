# KeyCard Rooms server companion

This is a server-only companion for the signed Workshop `@KeyCard-Rooms` mod.
It leaves all vendor PBOs unchanged and replaces the hardcoded T1, T2, and T3
`AddLoot` methods at runtime.

This code is bundled into the full ChernaTrader Secure Rooms Workshop build; it
is not deployed as a separate server mod. Rewards are configured in
`config/KeyCardSystem/rewards.json`. Each named reward pool gets all
`fixedRewards` plus `randomRewardCount` weighted selections from
`randomRewards`, without selecting the same entry twice. The default count is one.
Attachments are guaranteed and recursively attached to their parent item. An
optional `randomAttachments` group makes at most one weighted attachment choice
after passing its parent item's `randomAttachmentChance` roll.
Cargo is placed directly in the crate only when its parent reward is selected.

Door locations may set an optional `rewardTier` value in
`config/KeyCardSystem/config.json`. `T1`, `T2`, and `T3` retain their legacy
behavior, while names such as `T3_HEAVY` select a location-specific pool. The
setting selects the logical reward pool independently of `className` (the
physical door model) and `cardTier` (the required keycard). Locations without
`rewardTier` fall back to the tier implied by their door class.

Reward definitions use `poolName` as their identifier. The legacy
`doorClassName` property remains supported as a fallback for existing files.

Fixed rewards may use a `chance` between zero and one as an independent optional
roll. Omitted, zero, and `1.0` values remain guaranteed for compatibility.

`rewards.json` is maintained by hand (the old generator script
`custom_scripts/loot_types/configure_keycard_rewards.py` would overwrite it).
Authoring rules for `attachments`:

- List a magazine first; it is attached via `ExpansionCreateAttachment`, which
  fixes the weapon FSM state. Attached magazines spawn EMPTY.
- Attachments that provide a slot must precede the attachments that need it
  (e.g. `MP5_RailHndgrd` before `M68Optic`).
- Optics are intentionally placed in `cargo` (loose in the crate), not
  attached; keep the `chance` field at 1.0 as it is ignored for attachments.
- `randomAttachmentChance` is a probability from 0.0 through 1.0. When its roll
  succeeds, exactly one valid entry from `randomAttachments` is selected using
  the entries' relative `chance` weights. Ordinary `attachments` are unaffected.

Run `build.bat`, then deploy the resulting PBO to
`_@KeyCardRoomsServer/Addons/` and load that folder through `-serverMod` after
`_@Heatmap`.
