import json
import os

IGNORE_FILES = [
    "FireFighterLoadout.json",
    "PlayerFemaleSuitLoadout.json",
    "PlayerMaleSuitLoadout.json",
    "PlayerSurvivorLoadout.json"
]

def update_ammo_properties(json_file, chance, min_quantity, max_quantity):
    """Update ammo properties for all items with ClassName starting with 'Ammo_'"""
    # Read the JSON file
    with open(json_file, 'r') as file:
        data = json.load(file)

    # Track if any changes were made
    changes_made = False

    # Function to recursively search and update ammo properties
    def update_ammo_recursive(item):
        nonlocal changes_made
        if isinstance(item, dict):
            # Check if the item is an Ammo_ type
            if item.get("ClassName", "").startswith("Ammo_"):
                # Update Chance, Min, and Max values
                item["Chance"] = chance
                item["Quantity"]["Min"] = min_quantity
                item["Quantity"]["Max"] = max_quantity
                changes_made = True

            # Continue searching through all keys
            for key, value in item.items():
                if isinstance(value, (dict, list)):
                    update_ammo_recursive(value)
                        
        elif isinstance(item, list):
            for sub_item in item:
                update_ammo_recursive(sub_item)

    # Start the recursive search from the root of the JSON
    update_ammo_recursive(data)

    # Only write back if changes were made
    if changes_made:
        with open(json_file, 'w') as file:
            json.dump(data, file, indent=4)
        print(f"Updated ammo properties in {json_file}")
        return True
    else:
        print(f"No ammo entries found in {json_file}")
        return False

def process_directory_for_ammo_updates(directory_path, chance, min_quantity, max_quantity):
    """Process all JSON files in directory to update ammo properties"""
    files_updated = 0
    
    for root, dirs, files in os.walk(directory_path):
        for file in files:
            # Skip files in the ignore list
            if file in IGNORE_FILES:
                print(f"Skipping ignored file: {file}")
                continue
                
            if file.endswith('.json'):
                json_file = os.path.join(root, file)
                try:
                    if update_ammo_properties(json_file, chance, min_quantity, max_quantity):
                        files_updated += 1
                except Exception as e:
                    print(f"Error processing {json_file}: {str(e)}")
    
    print(f"Total files updated: {files_updated}")

# Configuration
directory_path = r'C:\Program Files (x86)\Steam\steamapps\common\DayZServerChernaTrader\config\ExpansionMod\Loadouts'

# Usage - Update ammo properties for all Ammo_ items
process_directory_for_ammo_updates(directory_path, chance=0.2, min_quantity=0.2, max_quantity=0.4)