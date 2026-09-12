"""Apply the first-pass keycard progression balance to rewards.json.

The script is intentionally idempotent so the server manager can rerun it after
manually adjusting unrelated rewards. It keeps T1 unchanged, trims T2 package
completeness, and replaces the shared T3 pool with heavy and precision pools.
"""

from __future__ import annotations

import copy
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
REWARDS = ROOT / "config/KeyCardSystem/rewards.json"

T2_SUPPRESSORS_TO_REMOVE = {
    "AugShort",
    "AK74",
    "M16A2",
}
HEAVY_WEAPONS = ("SCARH", "SNAFURPD", "M79", "M14")
PRECISION_WEAPONS = ("SVD", "SNAFUGevar_Black", "M14")


def pool_id(pool: dict) -> str:
    return pool["doorClassName"]


def trim_package(reward: dict) -> dict:
    reward = copy.deepcopy(reward)
    for cargo in reward.get("cargo", []):
        if cargo["className"].startswith("AmmoBox_"):
            cargo["count"] = 1
    return reward


def main() -> None:
    data = json.loads(REWARDS.read_text(encoding="utf-8"))
    pools = {pool_id(pool): pool for pool in data["tiers"]}

    t2 = pools["Land_KlimaX_T2Door"]
    for reward in t2["randomRewards"]:
        reward["cargo"] = [
            {**cargo, "count": 1}
            if cargo["className"].startswith("AmmoBox_")
            else cargo
            for cargo in reward.get("cargo", [])
        ]
        if reward["className"] in T2_SUPPRESSORS_TO_REMOVE:
            reward["attachments"] = [
                attachment
                for attachment in reward.get("attachments", [])
                if attachment["className"] not in {"M4_Suppressor", "AK_Suppressor"}
            ]

    source_t3 = pools.get("Land_KlimaX_T3Door")
    if source_t3 is None:
        # Permit safe reruns after the shared T3 pool has already been replaced.
        candidates = pools.get("T3_HEAVY", {}).get("randomRewards", []) + pools.get(
            "T3_PRECISION", {}
        ).get("randomRewards", [])
        by_name = {reward["className"]: reward for reward in candidates}
    else:
        by_name = {reward["className"]: reward for reward in source_t3["randomRewards"]}

    def select(names: tuple[str, ...]) -> list[dict]:
        selected = []
        for name in names:
            if name not in by_name:
                raise RuntimeError(f"T3 source reward is missing {name}")
            reward = trim_package(by_name[name])
            if name == "M79":
                for cargo in reward.get("cargo", []):
                    if cargo["className"] == "Ammo_40mm_Explosive":
                        cargo["count"] = 2
                    elif cargo["className"] == "Ammo_40mm_Smoke_White":
                        cargo["count"] = 1
            elif name == "SNAFUGevar_Black":
                # Its attached magazine is enough for the initial package.
                reward["cargo"] = [
                    cargo
                    for cargo in reward.get("cargo", [])
                    if cargo["className"] != "SNAFUGevar_10rdMag"
                ]
            selected.append(reward)
        return selected

    optional_nvg = {
        "className": "NVGoggles",
        "chance": 0.3,
        "attachments": [],
        "containerCargo": [],
        "cargo": [],
    }
    heavy = {
        "doorClassName": "T3_HEAVY",
        "randomRewardCount": 1,
        "randomRewards": select(HEAVY_WEAPONS),
        "fixedRewards": [copy.deepcopy(optional_nvg)],
    }
    precision = {
        "doorClassName": "T3_PRECISION",
        "randomRewardCount": 1,
        "randomRewards": select(PRECISION_WEAPONS),
        "fixedRewards": [copy.deepcopy(optional_nvg)],
    }

    data["tiers"] = [
        pool
        for pool in data["tiers"]
        if pool_id(pool) not in {"Land_KlimaX_T3Door", "T3_HEAVY", "T3_PRECISION"}
    ] + [heavy, precision]
    with REWARDS.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write(json.dumps(data, indent=4) + "\n")


if __name__ == "__main__":
    main()
