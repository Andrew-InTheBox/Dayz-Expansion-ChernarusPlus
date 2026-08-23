# KeyCard Rooms server companion

This is a server-only companion for the signed Workshop `@KeyCard-Rooms` mod.
It leaves all vendor PBOs unchanged and replaces the hardcoded T1, T2, and T3
`AddLoot` methods at runtime.

Rewards are configured in `config/KeyCardRoomsCompanion/rewards.json`. Each door
tier gets all `fixedRewards` plus `randomRewardCount` weighted selections from
`randomRewards`, without selecting the same entry twice. The default count is one.
Attachments are guaranteed and recursively attached to their parent item.
Cargo is placed directly in the crate only when its parent reward is selected.

Run `build.bat`, then deploy the resulting PBO to
`_@KeyCardRoomsServer/Addons/` and load that folder through `-serverMod` after
`_@Heatmap`.
