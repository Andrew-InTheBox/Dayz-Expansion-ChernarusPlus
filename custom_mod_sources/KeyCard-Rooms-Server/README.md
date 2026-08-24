# KeyCard Rooms server companion

This is a server-only companion for the signed Workshop `@KeyCard-Rooms` mod.
It leaves all vendor PBOs unchanged and replaces the hardcoded T1, T2, and T3
`AddLoot` methods at runtime.

Rewards are configured in `config/KeyCardRoomsCompanion/rewards.json`. Each door
tier gets all `fixedRewards` plus `randomRewardCount` weighted selections from
`randomRewards`, without selecting the same entry twice. The default count is one.
Attachments are guaranteed and recursively attached to their parent item.
Cargo is placed directly in the crate only when its parent reward is selected.

`rewards.json` is maintained by hand (the old generator script
`custom_scripts/loot_types/configure_keycard_rewards.py` would overwrite it).
Authoring rules for `attachments`:

- List a magazine first; it is attached via `ExpansionCreateAttachment`, which
  fixes the weapon FSM state. Attached magazines spawn EMPTY.
- Attachments that provide a slot must precede the attachments that need it
  (e.g. `MP5_RailHndgrd` before `M68Optic`).
- Optics are intentionally placed in `cargo` (loose in the crate), not
  attached; keep the `chance` field at 1.0 as it is ignored for attachments.

Run `build.bat`, then deploy the resulting PBO to
`_@KeyCardRoomsServer/Addons/` and load that folder through `-serverMod` after
`_@Heatmap`.
