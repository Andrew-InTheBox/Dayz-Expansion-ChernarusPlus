#!/usr/bin/env python3
"""
Script to analyze Quantity usage in DayZ loadout files.
Finds items with non-zero Quantity values to understand how multiples work.
"""

import json
import os
import sys
from pathlib import Path

def find_items_with_quantity(loadout_dir):
    """Find all items in InventoryCargo with non-zero Quantity values."""
    results = []

    for filepath in Path(loadout_dir).glob('*.json'):
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                data = json.load(f)

            # Recursively search for InventoryCargo sections
            def search_inventory(obj, path=''):
                if isinstance(obj, dict):
                    if 'InventoryCargo' in obj and isinstance(obj['InventoryCargo'], list):
                        for idx, item in enumerate(obj['InventoryCargo']):
                            if isinstance(item, dict):
                                classname = item.get('ClassName', '')
                                quantity = item.get('Quantity', {})
                                min_q = quantity.get('Min', 0.0)
                                max_q = quantity.get('Max', 0.0)

                                # Check if has non-zero quantity
                                if min_q != 0.0 or max_q != 0.0:
                                    is_ammo = 'ammo' in classname.lower()
                                    results.append({
                                        'file': filepath.name,
                                        'path': path,
                                        'class': classname,
                                        'min': min_q,
                                        'max': max_q,
                                        'is_ammo': is_ammo
                                    })

                    for key, value in obj.items():
                        search_inventory(value, f'{path}.{key}' if path else key)
                elif isinstance(obj, list):
                    for idx, item in enumerate(obj):
                        search_inventory(item, f'{path}[{idx}]')

            search_inventory(data)
        except Exception as e:
            print(f'Error reading {filepath.name}: {e}', file=sys.stderr)

    return results

def main():
    script_dir = Path(__file__).parent
    loadout_dir = script_dir.parent / 'config' / 'ExpansionMod' / 'Loadouts'

    if not loadout_dir.exists():
        print(f"Error: Loadout directory not found: {loadout_dir}", file=sys.stderr)
        return 1

    results = find_items_with_quantity(loadout_dir)

    # Separate ammo and non-ammo
    ammo_items = [r for r in results if r['is_ammo']]
    non_ammo_items = [r for r in results if not r['is_ammo']]

    print("=" * 80)
    print(f"QUANTITY USAGE ANALYSIS")
    print("=" * 80)
    print()

    print(f"Total items with non-zero Quantity: {len(results)}")
    print(f"  - Ammo items: {len(ammo_items)}")
    print(f"  - Non-ammo items: {len(non_ammo_items)}")
    print()

    if non_ammo_items:
        print("=" * 80)
        print("NON-AMMO ITEMS WITH QUANTITY (these are interesting!):")
        print("=" * 80)
        for r in non_ammo_items:
            print(f"\nFile: {r['file']}")
            print(f"  Path: {r['path']}")
            print(f"  ClassName: {r['class']}")
            print(f"  Quantity: Min={r['min']}, Max={r['max']}")
    else:
        print("No non-ammo items found with non-zero Quantity values.")
        print("This suggests Quantity might only work for stackable items like ammo.")

    print()
    print("=" * 80)
    print("SAMPLE AMMO ITEMS (for comparison):")
    print("=" * 80)
    for r in ammo_items[:5]:
        print(f"\nFile: {r['file']}")
        print(f"  ClassName: {r['class']}")
        print(f"  Quantity: Min={r['min']}, Max={r['max']}")

    return 0

if __name__ == '__main__':
    sys.exit(main())