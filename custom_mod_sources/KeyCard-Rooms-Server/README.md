# KeyCard Rooms server companion

This is a server-only companion for the signed Workshop `@KeyCard-Rooms` mod.
It leaves all vendor PBOs unchanged and replaces the hardcoded T1, T2, and T3
`AddLoot` methods at runtime.

Rewards are configured in `config/KeyCardRoomsCompanion/rewards.json`. Each door
tier gets all `fixedRewards` plus `randomRewardCount` weighted selections from
`randomRewards`, without selecting the same entry twice. The default count is one.
Attachments are guaranteed and recursively attached to their parent item. An
optional `randomAttachments` group makes at most one weighted attachment choice
after passing its parent item's `randomAttachmentChance` roll.
Cargo is placed directly in the crate only when its parent reward is selected.

Door locations may set an optional `rewardTier` value of `T1`, `T2`, or `T3`
in `config/KeyCardSystem/config.json`. This selects the logical reward pool
independently of `className`, which continues to select the physical door model
and its keycard authorization. Locations without `rewardTier` fall back to the
tier implied by their door class.

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
