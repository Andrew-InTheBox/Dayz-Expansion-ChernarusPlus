#!/usr/bin/env python3
"""
Add FNX45 pistols with 2 magazines to Sets that contain M79 grenade launchers.

This script adds a backup pistol (FNX45) with 2 magazines to any Set that contains
M79 grenade launchers and their ammo. This gives bots with M79s a secondary weapon
for close-range combat.

Usage:
    python add_fnx45_to_m79_sets.py [file.json] [--dry-run] [--all]

Examples:
    # Test on single file (dry run)
    python add_fnx45_to_m79_sets.py --dry-run config/ExpansionMod/Loadouts/BanditLoadout.json
    
    # Fix single file
    python add_fnx45_to_m79_sets.py config/ExpansionMod/Loadouts/BanditLoadout.json
    
    # Fix all loadout files with M79s
    python add_fnx45_to_m79_sets.py --all
"""

import json
import argparse
import sys
import os
from pathlib import Path

# FNX45 weapon configuration based on existing loadout patterns
FNX45_WEAPON_CONFIG = {
    "ClassName": "FNX45",
    "Chance": 1.0,
    "Quantity": {
        "Min": 0.0,
        "Max": 0.0
    },
    "Health": [],
    "InventoryAttachments": [
        {
            "SlotName": "",
            "Items": [
                {
                    "ClassName": "Mag_FNX45_15Rnd",
                    "Chance": 1.0,
                    "Quantity": {
                        "Min": 0.0,
                        "Max": 0.0
                    },
                    "Health": [],
                    "InventoryAttachments": [],
                    "InventoryCargo": [],
                    "ConstructionPartsBuilt": [],
                    "Sets": []
                }
            ]
        }
    ],
    "InventoryCargo": [],
    "ConstructionPartsBuilt": [],
    "Sets": []
}

# Magazine configuration for Set's InventoryCargo
FNX45_MAGAZINE_CONFIG = {
    "ClassName": "Mag_FNX45_15Rnd",
    "Chance": 1.0,
    "Quantity": {
        "Min": 0.0,
        "Max": 0.0
    },
    "Health": [],
    "InventoryAttachments": [],
    "InventoryCargo": [],
    "ConstructionPartsBuilt": [],
    "Sets": []
}

def has_m79_and_ammo(set_item):
    """Check if a Set contains M79 and its ammo"""
    has_m79 = False
    has_ammo = False
    
    # Check InventoryAttachments for M79
    for attachment in set_item.get("InventoryAttachments", []):
        for item in attachment.get("Items", []):
            if item.get("ClassName") == "M79":
                has_m79 = True
                break
    
    # Check InventoryCargo for Ammo_40mm_Explosive
    for cargo_item in set_item.get("InventoryCargo", []):
        if cargo_item.get("ClassName") == "Ammo_40mm_Explosive":
            has_ammo = True
            break
    
    return has_m79 and has_ammo

def has_fnx45(set_item):
    """Check if a Set already contains FNX45"""
    # Check InventoryAttachments for FNX45
    for attachment in set_item.get("InventoryAttachments", []):
        for item in attachment.get("Items", []):
            if item.get("ClassName") == "FNX45":
                return True
    
    # Check InventoryCargo for FNX45
    for cargo_item in set_item.get("InventoryCargo", []):
        if cargo_item.get("ClassName") == "FNX45":
            return True
    
    return False

def add_fnx45_to_set(set_item):
    """Add FNX45 pistol and 2 magazines to a Set"""
    modifications_made = []
    
    # Add FNX45 weapon to InventoryAttachments
    hands_attachment = None
    for attachment in set_item.get("InventoryAttachments", []):
        if attachment.get("SlotName") == "Hands":
            hands_attachment = attachment
            break
    
    if not hands_attachment:
        # Create new Hands attachment
        hands_attachment = {
            "SlotName": "Hands",
            "Items": []
        }
        if "InventoryAttachments" not in set_item:
            set_item["InventoryAttachments"] = []
        set_item["InventoryAttachments"].append(hands_attachment)
        modifications_made.append("Created new Hands attachment slot")
    
    # Add FNX45 to Hands slot
    hands_attachment["Items"].append(FNX45_WEAPON_CONFIG.copy())
    modifications_made.append("Added FNX45 pistol to Hands slot")
    
    # Add 2 extra magazines to InventoryCargo
    if "InventoryCargo" not in set_item:
        set_item["InventoryCargo"] = []
    
    # Add 2 magazines
    set_item["InventoryCargo"].append(FNX45_MAGAZINE_CONFIG.copy())
    set_item["InventoryCargo"].append(FNX45_MAGAZINE_CONFIG.copy())
    modifications_made.append("Added 2x Mag_FNX45_15Rnd to InventoryCargo")
    
    return modifications_made

def process_loadout_file(file_path, dry_run=False):
    """Process a single loadout file"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except (json.JSONDecodeError, FileNotFoundError) as e:
        print(f"Error reading {file_path}: {e}")
        return False
    
    sets_modified = 0
    total_modifications = []
    
    # Process all Sets in the loadout
    for set_item in data.get("Sets", []):
        if has_m79_and_ammo(set_item):
            if has_fnx45(set_item):
                print(f"  Set already has FNX45, skipping")
                continue
            
            if not dry_run:
                modifications = add_fnx45_to_set(set_item)
                total_modifications.extend(modifications)
                sets_modified += 1
                print(f"  Modified Set: {', '.join(modifications)}")
            else:
                print(f"  [DRY RUN] Would add FNX45 + 2 magazines to M79 Set")
                sets_modified += 1
    
    if sets_modified > 0:
        if not dry_run:
            # Write back to file
            with open(file_path, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=4, ensure_ascii=False)
            print(f"[MODIFIED] Modified {sets_modified} Sets in {file_path}")
        else:
            print(f"[DRY RUN] Would modify {sets_modified} Sets in {file_path}")
        return True
    else:
        print(f"[INFO] No M79 Sets found in {file_path}")
        return False

def main():
    parser = argparse.ArgumentParser(description='Add FNX45 pistols to M79-containing Sets')
    parser.add_argument('file', nargs='?', help='Loadout file to process')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be changed without modifying files')
    parser.add_argument('--all', action='store_true', help='Process all loadout files with M79s')
    
    args = parser.parse_args()
    
    if args.all:
        # Process all known loadout files with M79s
        loadout_files = [
            "config/ExpansionMod/Loadouts/BanditLoadout.json",
            "config/ExpansionMod/Loadouts/EastLoadout.json", 
            "config/ExpansionMod/Loadouts/GorkaLoadout.json",
            "config/ExpansionMod/Loadouts/PoliceLoadout.json",
            "config/ExpansionMod/Loadouts/WestLoadout.json"
        ]
        
        files_modified = 0
        for file_path in loadout_files:
            if os.path.exists(file_path):
                print(f"\nProcessing {file_path}...")
                if process_loadout_file(file_path, args.dry_run):
                    files_modified += 1
            else:
                print(f"[WARNING] File not found: {file_path}")
        
        if args.dry_run:
            print(f"\n[DRY RUN] Would modify {files_modified} files total")
        else:
            print(f"\n[MODIFIED] Modified {files_modified} files total")
    
    elif args.file:
        if not os.path.exists(args.file):
            print(f"Error: File not found: {args.file}")
            sys.exit(1)
        
        print(f"Processing {args.file}...")
        process_loadout_file(args.file, args.dry_run)
    
    else:
        parser.print_help()
        sys.exit(1)

if __name__ == "__main__":
    main()