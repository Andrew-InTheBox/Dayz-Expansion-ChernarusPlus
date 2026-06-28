#!/usr/bin/env python3
"""
Analyze DayZ ExpansionMod loadout files to find weapon Sets that lack corresponding ammo or magazines.
This helps identify potentially under-equipped bot configurations.
"""

import json
import os
import argparse
from collections import defaultdict

def is_weapon_class(class_name):
    """Check if a class name appears to be a weapon (basic heuristics)"""
    weapon_indicators = [
        'AK', 'M4', 'Mosin', 'SKS', 'Winchester', 'Blaze', 'CR', 'VSD', 'SVD', 'VSS',
        'UMP', 'MP5', 'Bizon', 'Scorpion', 'FNX', 'Glock', 'Makarov', 'Magnum',
        'Shotgun', 'Izh', 'B95', 'Scout', 'Hunting', 'Repeater', 'Carbine',
        'M79', 'LAR', 'Tundra', 'Pioneer', 'Longhorn', 'Deagle', 'P1', 'Mkii',
        'SSG82', 'FAMAS', 'AUG'
    ]
    
    # Exclude obvious non-weapons
    non_weapons = ['Ammo_', 'Mag_', 'Optic', 'Suppressor', 'Compensator', 'Bayonet']
    
    for exclude in non_weapons:
        if exclude in class_name:
            return False
            
    for indicator in weapon_indicators:
        if indicator in class_name:
            return True
            
    return False

def find_items_in_inventory_cargo(cargo_list):
    """Find all items in InventoryCargo, returns dict of {class_name: count}"""
    items = defaultdict(int)
    
    for item in cargo_list:
        class_name = item.get('ClassName', '')
        items[class_name] += 1
    
    return dict(items)

def analyze_set_for_weapons_and_ammo(set_item, set_index, loadout_name):
    """Analyze a single Set for weapons and corresponding ammo/magazines"""
    results = []
    
    # Find all items in this Set's InventoryCargo
    inventory_items = find_items_in_inventory_cargo(set_item.get('InventoryCargo', []))
    
    # Find weapons in this Set (could be in InventoryAttachments or InventoryCargo)
    weapons_found = []
    
    # Check InventoryAttachments for weapons
    for attachment in set_item.get('InventoryAttachments', []):
        slot_name = attachment.get('SlotName', '')
        for item in attachment.get('Items', []):
            class_name = item.get('ClassName', '')
            if is_weapon_class(class_name):
                weapons_found.append({
                    'weapon': class_name,
                    'location': f'InventoryAttachments[{slot_name}]'
                })
    
    # Check InventoryCargo for weapons
    for item in set_item.get('InventoryCargo', []):
        class_name = item.get('ClassName', '')
        if is_weapon_class(class_name):
            weapons_found.append({
                'weapon': class_name,
                'location': 'InventoryCargo'
            })
    
    # For each weapon found, check if there's corresponding ammo/magazines
    for weapon_info in weapons_found:
        weapon_name = weapon_info['weapon']
        weapon_location = weapon_info['location']
        
        # Look for ammo (Ammo_) or magazines (Mag_) in the Set's InventoryCargo
        ammo_items = [name for name in inventory_items.keys() if name.startswith('Ammo_')]
        mag_items = [name for name in inventory_items.keys() if name.startswith('Mag_')]
        
        total_ammo_items = len(ammo_items) + len(mag_items)
        
        results.append({
            'loadout': loadout_name,
            'set_index': set_index,
            'weapon': weapon_name,
            'weapon_location': weapon_location,
            'ammo_items': ammo_items,
            'mag_items': mag_items,
            'total_ammo_count': sum(inventory_items[item] for item in ammo_items),
            'total_mag_count': sum(inventory_items[item] for item in mag_items),
            'has_ammo_or_mags': total_ammo_items > 0,
            'all_inventory_items': inventory_items
        })
    
    return results

def analyze_loadout_file(filepath):
    """Analyze a single loadout file for weapon/ammo patterns"""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        return []
    
    loadout_name = os.path.basename(filepath)
    results = []
    
    # Find all Sets in the loadout
    sets_list = data.get('Sets', [])
    
    for set_index, set_item in enumerate(sets_list):
        set_results = analyze_set_for_weapons_and_ammo(set_item, set_index, loadout_name)
        results.extend(set_results)
    
    return results

def print_analysis_report(all_results):
    """Print a detailed report of the analysis"""
    print("\n" + "="*80)
    print("WEAPON AMMO ANALYSIS REPORT")
    print("="*80)
    
    # Separate results into those with and without ammo/mags
    with_ammo = [r for r in all_results if r['has_ammo_or_mags']]
    without_ammo = [r for r in all_results if not r['has_ammo_or_mags']]
    
    print(f"\nSUMMARY:")
    print(f"  Total weapon Sets analyzed: {len(all_results)}")
    print(f"  Sets WITH ammo/magazines: {len(with_ammo)}")
    print(f"  Sets WITHOUT ammo/magazines: {len(without_ammo)}")
    
    if without_ammo:
        print(f"\n{'='*50}")
        print("WEAPONS WITHOUT AMMO/MAGAZINES (POTENTIAL ISSUES):")
        print("="*50)
        
        for result in without_ammo:
            print(f"\nFile: {result['loadout']}")
            print(f"  Set #{result['set_index']}: {result['weapon']} (in {result['weapon_location']})")
            print(f"  InventoryCargo items: {list(result['all_inventory_items'].keys())}")
    
    if with_ammo:
        print(f"\n{'='*50}")
        print("WEAPONS WITH AMMO/MAGAZINES:")
        print("="*50)
        
        for result in with_ammo:
            print(f"\nFile: {result['loadout']}")
            print(f"  Set #{result['set_index']}: {result['weapon']} (in {result['weapon_location']})")
            if result['ammo_items']:
                print(f"    Ammo: {result['ammo_items']} (total: {result['total_ammo_count']})")
            if result['mag_items']:
                print(f"    Magazines: {result['mag_items']} (total: {result['total_mag_count']})")

def main():
    parser = argparse.ArgumentParser(description='Analyze weapon Sets for missing ammo/magazines')
    parser.add_argument('--loadouts-dir', default='config/ExpansionMod/Loadouts',
                       help='Directory containing loadout JSON files')
    parser.add_argument('--file', help='Analyze specific loadout file instead of all files')
    parser.add_argument('--show-all', action='store_true', 
                       help='Show all weapon Sets, not just those without ammo')
    
    args = parser.parse_args()
    
    all_results = []
    
    if args.file:
        # Analyze single file
        results = analyze_loadout_file(args.file)
        all_results.extend(results)
    else:
        # Analyze all files in directory
        loadouts_dir = args.loadouts_dir
        if not os.path.exists(loadouts_dir):
            print(f"Error: Directory {loadouts_dir} not found")
            return
        
        for filename in os.listdir(loadouts_dir):
            if filename.endswith('.json'):
                filepath = os.path.join(loadouts_dir, filename)
                print(f"Analyzing {filename}...")
                results = analyze_loadout_file(filepath)
                all_results.extend(results)
    
    print_analysis_report(all_results)
    
    # Summary of potentially problematic Sets
    without_ammo = [r for r in all_results if not r['has_ammo_or_mags']]
    if without_ammo:
        print(f"\n{'='*50}")
        print("SUMMARY OF POTENTIAL ISSUES:")
        print("="*50)
        print("The following weapon Sets may need ammo/magazines added:")
        for result in without_ammo:
            print(f"  - {result['loadout']} Set #{result['set_index']}: {result['weapon']}")

if __name__ == "__main__":
    main()