#!/usr/bin/env python3
"""
Move FNX45 pistols from "Hands" slot to InventoryCargo in M79-containing Sets.

This script fixes the issue where FNX45 pistols in "Hands" slots get dropped when 
bots equip their M79 primary weapon. It moves existing FNX45s to InventoryCargo 
where they will persist regardless of equipped weapons.

Usage:
    python move_fnx45_from_hands_to_cargo.py [file.json] [--dry-run] [--all]

Examples:
    # Test on single file (dry run)
    python move_fnx45_from_hands_to_cargo.py --dry-run config/ExpansionMod/Loadouts/BanditLoadout.json
    
    # Fix single file
    python move_fnx45_from_hands_to_cargo.py config/ExpansionMod/Loadouts/BanditLoadout.json
    
    # Fix all loadout files with M79s
    python move_fnx45_from_hands_to_cargo.py --all
"""

import json
import argparse
import sys
import os
from pathlib import Path

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

def find_and_remove_fnx45_from_hands(set_item):
    """Find and remove FNX45 from Hands slot, return it if found"""
    fnx45_item = None
    
    # Look through InventoryAttachments for Hands slot
    for attachment in set_item.get("InventoryAttachments", []):
        if attachment.get("SlotName") == "Hands":
            # Check each item in Hands slot
            items_to_keep = []
            for item in attachment.get("Items", []):
                if item.get("ClassName") == "FNX45":
                    fnx45_item = item.copy()  # Store the FNX45 item
                    print(f"    Found FNX45 in Hands slot, removing...")
                else:
                    items_to_keep.append(item)
            
            # Update the Items list without the FNX45
            attachment["Items"] = items_to_keep
            
            # If Hands slot is now empty, we could remove it entirely
            if not items_to_keep:
                print(f"    Hands slot is now empty")
            
            break
    
    return fnx45_item

def add_fnx45_to_cargo(set_item, fnx45_item):
    """Add FNX45 item to InventoryCargo"""
    if "InventoryCargo" not in set_item:
        set_item["InventoryCargo"] = []
    
    # Add the FNX45 to InventoryCargo
    set_item["InventoryCargo"].append(fnx45_item)
    print(f"    Added FNX45 to InventoryCargo")

def clean_empty_hands_slots(set_item):
    """Remove empty Hands attachment slots"""
    if "InventoryAttachments" not in set_item:
        return
    
    attachments_to_keep = []
    for attachment in set_item["InventoryAttachments"]:
        if attachment.get("SlotName") == "Hands":
            # Keep only if it has items
            if attachment.get("Items"):
                attachments_to_keep.append(attachment)
            else:
                print(f"    Removed empty Hands slot")
        else:
            attachments_to_keep.append(attachment)
    
    set_item["InventoryAttachments"] = attachments_to_keep

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
            # Try to find and remove FNX45 from Hands slot
            fnx45_item = find_and_remove_fnx45_from_hands(set_item)
            
            if fnx45_item:
                if not dry_run:
                    # Move it to InventoryCargo
                    add_fnx45_to_cargo(set_item, fnx45_item)
                    
                    # Clean up empty Hands slots
                    clean_empty_hands_slots(set_item)
                    
                    sets_modified += 1
                    total_modifications.append("Moved FNX45 from Hands to InventoryCargo")
                else:
                    print(f"  [DRY RUN] Would move FNX45 from Hands to InventoryCargo")
                    sets_modified += 1
            else:
                print(f"  No FNX45 found in Hands slot (may already be moved)")
    
    if sets_modified > 0:
        if not dry_run:
            # Write back to file
            with open(file_path, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=4, ensure_ascii=False)
            print(f"[MODIFIED] Moved FNX45 in {sets_modified} Sets in {file_path}")
        else:
            print(f"[DRY RUN] Would modify {sets_modified} Sets in {file_path}")
        return True
    else:
        print(f"[INFO] No FNX45 movements needed in {file_path}")
        return False

def main():
    parser = argparse.ArgumentParser(description='Move FNX45 pistols from Hands to InventoryCargo in M79 Sets')
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