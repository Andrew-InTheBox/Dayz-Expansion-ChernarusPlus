import os
import json

def update_stock_thresholds(directory, file_prefix, max_threshold, min_threshold):
    for file_name in os.listdir(directory):
        if file_name.startswith(file_prefix) and file_name.endswith('.json'):
            file_path = os.path.join(directory, file_name)
            try:
                with open(file_path, 'r') as file:
                    data = json.load(file)
                
                # Update thresholds
                for item in data.get("Items", []):
                    item["MaxStockThreshold"] = max_threshold
                    item["MinStockThreshold"] = min_threshold
                
                # Write updated data back to file
                with open(file_path, 'w') as file:
                    json.dump(data, file, indent=4)
                
                print(f"Updated {file_name}")

            except json.JSONDecodeError as e:
                print(f"Failed to decode JSON from {file_path}: {e}")
            except Exception as e:
                print(f"Error processing {file_path}: {e}")

if __name__ == "__main__":
    directory = './config/ExpansionMod/Market/'
    file_prefix = 'MMG_'
    max_threshold = 50
    min_threshold = 5

    update_stock_thresholds(directory, file_prefix, max_threshold, min_threshold)
