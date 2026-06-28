#!/usr/bin/env python3
"""
Fix M79 ammo placement in DayZ loadout files.

This script moves Ammo_40mm_Explosive from M79 weapon's InventoryCargo 
to the Set's InventoryCargo, since weapons don't have internal storage.
"""

import json
import os
import sys
from pathlib import Path


def fix_m79_ammo_in_loadout(data):
    """
    Fix M79 ammo placement in a single loadout data structure.
    
    Args:
        data: The loaded JSON data from a loadout file
        
    Returns:
        tuple: (modified_data, changes_made, change_log)
    """
    changes_made = False
    change_log = []
    
    # Process each Set
    sets = data.get('Sets', [])
    for set_idx, set_data in enumerate(sets):
        set_name = set_data.get('ClassName', f'Set_{set_idx}')
        
        # Look for M79 weapons in this set's InventoryAttachments
        for attachment in set_data.get('InventoryAttachments', []):
            if attachment.get('SlotName') == 'Shoulder':
                for item in attachment.get('Items', []):
                    if item.get('ClassName') == 'M79':
                        # Found M79! Check if it has ammo in its InventoryCargo
                        m79_cargo = item.get('InventoryCargo', [])
                        ammo_to_move = []
                        
                        # Find all Ammo_40mm_Explosive in M79's cargo
                        for cargo_idx in range(len(m79_cargo) - 1, -1, -1):  # Reverse order for safe removal
                            cargo_item = m79_cargo[cargo_idx]
                            if cargo_item.get('ClassName') == 'Ammo_40mm_Explosive':
                                ammo_to_move.append(cargo_item)
                                m79_cargo.pop(cargo_idx)  # Remove from weapon cargo
                                changes_made = True
                                change_log.append(f"Set {set_idx} ({set_name}): Moved Ammo_40mm_Explosive from M79 InventoryCargo to Set InventoryCargo")
                        
                        # Add the moved ammo to the Set's InventoryCargo
                        if ammo_to_move:
                            set_inventory_cargo = set_data.setdefault('InventoryCargo', [])
                            set_inventory_cargo.extend(ammo_to_move)
    
    return data, changes_made, change_log


def process_loadout_file(file_path, dry_run=False):
    """
    Process a single loadout file.
    
    Args:
        file_path: Path to the loadout JSON file
        dry_run: If True, don't write changes, just report what would be done
        
    Returns:
        tuple: (success, changes_made, change_log)
    """
    try:
        print(f"Processing: {file_path}")
        
        # Read the file
        with open(file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        # Fix M79 ammo placement
        modified_data, changes_made, change_log = fix_m79_ammo_in_loadout(data)
        
        if changes_made:
            print(f"  Changes needed in {file_path}:")
            for log_entry in change_log:
                print(f"    - {log_entry}")
                
            if not dry_run:
                # Write the modified data back
                with open(file_path, 'w', encoding='utf-8') as f:
                    json.dump(modified_data, f, indent=4, ensure_ascii=False)
                print(f"  ✓ Changes written to {file_path}")
            else:
                print(f"  ✓ Dry run - no changes written")
        else:
            print(f"  No M79 ammo issues found in {file_path}")
            
        return True, changes_made, change_log
        
    except Exception as e:
        print(f"  ❌ Error processing {file_path}: {e}")
        return False, False, []


def main():
    """Main function."""
    import argparse
    
    parser = argparse.ArgumentParser(description='Fix M79 ammo placement in DayZ loadout files')
    parser.add_argument('files', nargs='*', help='Specific loadout files to process')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be changed without making changes')
    parser.add_argument('--all', action='store_true', help='Process all loadout files in config/ExpansionMod/Loadouts/')
    
    args = parser.parse_args()
    
    if not args.files and not args.all:
        print("Usage: python fix_m79_ammo.py [--dry-run] [--all | file1.json file2.json ...]")
        print("Examples:")
        print("  python fix_m79_ammo.py --dry-run config/ExpansionMod/Loadouts/BanditLoadout.json")
        print("  python fix_m79_ammo.py --all")
        sys.exit(1)
    
    files_to_process = []
    
    if args.all:
        # Find all loadout files
        loadout_dir = Path("config/ExpansionMod/Loadouts")
        if loadout_dir.exists():
            files_to_process = list(loadout_dir.glob("*.json"))
        else:
            print(f"❌ Directory not found: {loadout_dir}")
            sys.exit(1)
    else:
        files_to_process = [Path(f) for f in args.files]
    
    # Process files
    total_files = len(files_to_process)
    successful_files = 0
    files_with_changes = 0
    
    print(f"Processing {total_files} files...")
    print("=" * 50)
    
    for file_path in files_to_process:
        if not file_path.exists():
            print(f"❌ File not found: {file_path}")
            continue
            
        success, changes_made, change_log = process_loadout_file(file_path, args.dry_run)
        
        if success:
            successful_files += 1
            if changes_made:
                files_with_changes += 1
        
        print()  # Empty line between files
    
    # Summary
    print("=" * 50)
    print(f"Summary:")
    print(f"  Total files processed: {successful_files}/{total_files}")
    print(f"  Files with M79 ammo changes: {files_with_changes}")
    
    if args.dry_run:
        print(f"  (Dry run - no actual changes made)")


if __name__ == '__main__':
    main()