"""Build keycard-room reward pools and disable their rated items in CE types."""

import csv
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
RATINGS = ROOT / "custom_scripts/loot_types/weapon_ratings/weapon_ratings.csv"
TYPE_FILES = (
    ROOT / "mpmissions/Expansion.chernarusplus/db/types.xml",
    ROOT / "mpmissions/Expansion.chernarusplus/snafu/SNAFU_types.xml",
)
SPAWNABLE_FILES = (
    ROOT / "mpmissions/Expansion.chernarusplus/cfgspawnabletypes.xml",
    ROOT / "mpmissions/Expansion.chernarusplus/snafu/snafuspawnabletypes.xml",
)
REWARDS = ROOT / "config/KeyCardRoomsCompanion/rewards.json"
EXCLUDED_STANDALONE_REWARDS = {
    "M4_CQBBttstck",
    "M4_MPBttstck",
    "M4_MPHndgrd",
    "M4_OEBttstck",
    "M4_PlasticHndgrd",
    "M4_RISHndgrd",
}
LOOSE_OPTICS = {
    "ACOGOptic",
    "ACOGOptic_6x",
    "FNP45_MRDSOptic",
    "KashtanOptic",
    "KobraOptic",
    "M68Optic",
    "PSO1Optic",
    "PSO11Optic",
    "PUScopeOptic",
    "SNAFU_Tango6T_Black",
}
MAGAZINES = {
    "Mag_1911_7Rnd",
    "Mag_AK101_30Rnd",
    "Mag_AK74_30Rnd",
    "Mag_AK74_45Rnd",
    "Mag_AKM_30Rnd",
    "Mag_Aug_30Rnd",
    "Mag_CMAG_30Rnd",
    "Mag_CZ75_15Rnd",
    "Mag_FAMAS_25Rnd",
    "Mag_FNX45_15Rnd",
    "Mag_M14_20Rnd",
    "Mag_MP5_30Rnd",
    "Mag_PP19_64Rnd",
    "Mag_Saiga_8Rnd",
    "Mag_SCARH_20Rnd",
    "Mag_SVD_10Rnd",
    "Mag_SV98_10Rnd",
    "Mag_UMP_25Rnd",
    "Mag_VAL_20Rnd",
    "Mag_Vikhr_30Rnd",
    "SNAFU_PMAG556_Black",
    "SNAFUGevar_10rdMag",
    "SNAFUP90_50rdMag",
    "SNAFURPD_100rdMag",
}


def cargo(class_name, count=1):
    return {"className": class_name, "count": count}


def reward(class_name, attachments=(), cargo_items=(), container_items=(), chance=1.0):
    # Optics are always spawned loose. Direct optic attachment has proven
    # unreliable, while ordinary crate cargo is dependable.
    direct_attachments = [name for name in attachments if name not in LOOSE_OPTICS]
    # Expansion's weapon FSM synchronization is most reliable when a magazine
    # is created before stocks, handguards, suppressors, and other attachments.
    direct_attachments.sort(key=lambda name: name not in MAGAZINES)
    loose_optics = [cargo(name) for name in attachments if name in LOOSE_OPTICS]
    return {
        "className": class_name,
        "chance": chance,
        "attachments": [reward(name) for name in direct_attachments],
        "containerCargo": list(container_items),
        "cargo": loose_optics + list(cargo_items),
    }


T3 = [
    reward("SKS", ["PUScopeOptic"], [cargo("AmmoBox_762x39_20Rnd", 2)]),
    reward("FNX45", ["Mag_FNX45_15Rnd", "PistolSuppressor", "FNP45_MRDSOptic"], [cargo("AmmoBox_45ACP_25rnd", 2)]),
    reward("PP19", ["PP19_Bttstck", "Mag_PP19_64Rnd", "PistolSuppressor", "KobraOptic"], [cargo("AmmoBox_9x19_25rnd", 2)]),
    reward("UMP45", ["Mag_UMP_25Rnd", "PistolSuppressor", "UniversalLight", "ACOGOptic"], [cargo("AmmoBox_45ACP_25rnd", 2)]),
    reward("AugShort", ["Mag_Aug_30Rnd"], [cargo("AmmoBox_556x45_20Rnd", 2)]),
    reward("AK101", ["AK_PlasticBttstck", "AK_PlasticHndgrd", "Mag_AK101_30Rnd", "KashtanOptic"], [cargo("AmmoBox_556x45_20Rnd", 2)]),
    reward("M79", cargo_items=[cargo("Ammo_40mm_Explosive", 4), cargo("Ammo_40mm_Smoke_White", 2), cargo("NVGoggles")]),
    reward("AK74", ["AK74_WoodBttstck", "AK74_Hndgrd", "Mag_AK74_45Rnd", "KashtanOptic"], [cargo("AmmoBox_545x39_20Rnd", 2)]),
    reward("FAMAS", ["Mag_FAMAS_25Rnd"], [cargo("AmmoBox_556x45_20Rnd", 2)]),
    reward("M16A2", ["Mag_CMAG_30Rnd"], [cargo("AmmoBox_556x45_20Rnd", 2)]),
    reward("SVD", ["Mag_SVD_10Rnd", "PSO11Optic"], [cargo("AmmoBox_762x54_20Rnd", 2)]),
    reward("Vikhr", ["Mag_Vikhr_30Rnd", "PSO1Optic"], [cargo("AmmoBox_9x39_20Rnd", 2)]),
    reward("VSS", ["Mag_VAL_20Rnd", "PSO11Optic"], [cargo("AmmoBox_9x39_20Rnd", 2)]),
    reward("SV98", ["Mag_SV98_10Rnd", "ACOGOptic_6x"], [cargo("AmmoBox_762x54_20Rnd", 2)]),
    reward("AKM", ["AK_PlasticBttstck", "AK_PlasticHndgrd", "AK_Suppressor", "Mag_AKM_30Rnd", "PSO11Optic"], [cargo("AmmoBox_762x39_20Rnd", 2)]),
    reward("ASVAL", ["Mag_Vikhr_30Rnd", "UniversalLight", "ACOGOptic"], [cargo("AmmoBox_9x39_20Rnd", 2)]),
    reward("SCARH", ["SCAR_PrecisionBttstck", "Mag_SCARH_20Rnd", "ACOGOptic_6x"], [cargo("AmmoBox_308Win_20Rnd", 2)]),
    reward("SNAFU_ADAR_Modular16_GUN", ["SNAFU_MK15", "SNAFU_PRSGen3_Stock", "SNAFU_PistolGripColtA2", "SNAFU_FGCR_Grip", "SNAFU_PMAG556_Black", "SNAFU_Tango6T_Black"], [cargo("AmmoBox_556x45_20Rnd", 2)]),
    reward("SNAFUP90", ["SNAFUP90_50rdMag", "SNAFU_Tango6T_Black"], [cargo("SNAFUP90_50rdMag", 2)]),
    reward("SNAFURPD", ["SNAFURPD_100rdMag"], [cargo("AmmoBox_762x39_20Rnd", 2)]),
    reward("GCGN_BenelliM4", cargo_items=[cargo("AmmoBox_00buck_10rnd", 2)]),
    reward("SNAFUTAR21_Green", ["Mag_CMAG_30Rnd", "SNAFU_Tango6T_Black"], [cargo("AmmoBox_556x45_20Rnd", 2)]),
    reward("SNAFUGevar_Black", ["SNAFUGevar_10rdMag", "SNAFU_Tango6T_Black"], [cargo("AmmoBox_308Win_20Rnd", 2)]),
]

T2 = [
    reward("CZ75", ["Mag_CZ75_15Rnd", "PistolSuppressor", "TLRLight"], [cargo("AmmoBox_9x19_25rnd", 2)]),
    reward("AKS74U", ["AKS74U_Bttstck", "Mag_AK74_30Rnd"], [cargo("AmmoBox_545x39_20Rnd", 2)]),
    reward("MP5K", ["MP5_RailHndgrd", "MP5k_StockBttstck", "Mag_MP5_30Rnd", "PistolSuppressor", "M68Optic"], [cargo("AmmoBox_9x19_25rnd", 2)]),
    reward("Saiga", ["Saiga_Bttstck", "Mag_Saiga_8Rnd"], [cargo("AmmoBox_00buck_10rnd", 2)]),
    reward("Engraved1911", ["PistolSuppressor", "Mag_1911_7Rnd"], [cargo("AmmoBox_45ACP_25rnd", 2)]),
    reward("M14", ["Mag_M14_20Rnd", "ACOGOptic_6x"], [cargo("AmmoBox_308Win_20Rnd", 2)]),
]

T1 = [
    reward("WeaponCleaningKit"),
    reward("FirstAidKit", container_items=[cargo("BandageDressing"), cargo("TetracyclineAntibiotics"), cargo("VitaminBottle")]),
    reward("Canteen"),
    reward("CombatKnife"), reward("AmmoBox_762x39_20Rnd"),
    reward("AmmoBox_545x39_20Rnd"), reward("AmmoBox_556x45_20Rnd"),
    reward("AmmoBox_308Win_20Rnd"), reward("AmmoBox_9x19_25rnd"),
    reward("AmmoBox_00buck_10rnd"),
]


def rated_items():
    with RATINGS.open(encoding="utf-8-sig", newline="") as handle:
        rows = csv.DictReader(handle)
        return {
            row["type_id"]
            for row in rows
            if row["Rating (4 is best)"] in {"3", "4"}
            and row["Military"].lower() == "true"
            and row["in_current_setup"].lower() == "true"
        }


def disable_ce_items(selected):
    found = set()
    for path in TYPE_FILES:
        text = path.read_text(encoding="utf-8-sig")
        for class_name in sorted(selected):
            pattern = re.compile(r'(<type\s+name="' + re.escape(class_name) + r'"\s*>.*?</type>)', re.S)
            match = pattern.search(text)
            if not match:
                continue
            original_block = match.group(1)
            nominal = 1 if 'deloot="1"' in original_block else 0
            block = re.sub(
                r"<nominal>\d+</nominal>",
                f"<nominal>{nominal}</nominal>",
                original_block,
                count=1,
            )
            block = re.sub(r"<min>\d+</min>", "<min>0</min>", block, count=1)
            text = text[:match.start()] + block + text[match.end():]
            found.add(class_name)
        path.write_text(text, encoding="utf-8", newline="")
    missing = selected - found
    if missing:
        raise RuntimeError(f"Rated items missing from active type files: {sorted(missing)}")

    for path in SPAWNABLE_FILES:
        text = path.read_text(encoding="utf-8-sig")
        for class_name in sorted(selected):
            text = re.sub(
                r'^\s*<item\s+name="' + re.escape(class_name) + r'"[^>]*/>\s*\r?\n',
                "",
                text,
                flags=re.M,
            )
        path.write_text(text, encoding="utf-8", newline="")


def main():
    selected = rated_items()
    config = {
        "version": 1,
        "tiers": [
            {"doorClassName": "Land_KlimaX_T1Door", "randomRewardCount": 5, "randomRewards": T1, "fixedRewards": []},
            {"doorClassName": "Land_KlimaX_T2Door", "randomRewardCount": 3, "randomRewards": T2, "fixedRewards": []},
            {"doorClassName": "Land_KlimaX_T3Door", "randomRewardCount": 2, "randomRewards": T3, "fixedRewards": []},
        ],
    }
    encoded = json.dumps(config, indent=4) + "\n"
    absent = sorted(name for name in selected - EXCLUDED_STANDALONE_REWARDS if name not in encoded)
    if absent:
        raise RuntimeError(f"Rated items absent from reward config: {absent}")
    disable_ce_items(selected)
    REWARDS.write_text(encoded, encoding="utf-8", newline="\n")
    print(f"Disabled {len(selected)} CE items and wrote {len(T3)} T3, {len(T2)} T2, {len(T1)} T1 rewards")


if __name__ == "__main__":
    main()
