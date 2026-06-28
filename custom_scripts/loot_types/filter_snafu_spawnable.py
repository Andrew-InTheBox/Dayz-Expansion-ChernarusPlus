#!/usr/bin/env python3
"""
Script to filter snafuspawnabletypes25percent.xml to keep only the type entries listed in types-keep.txt
"""

import re
import os

def main():
    # File paths
    xml_file = r"mpmissions\Expansion.chernarusplus\snafu\snafuspawnabletypes25percent.xml"
    keep_file = r"mpmissions\Expansion.chernarusplus\snafu\types-keep.txt"
    backup_file = xml_file + ".backup"
    
    # Read the list of type names to keep
    with open(keep_file, 'r', encoding='utf-8') as f:
        keep_types = set()
        for line in f:
            line = line.strip()
            if line:
                keep_types.add(line)
    
    print(f"Found {len(keep_types)} type names to keep:")
    for name in sorted(keep_types):
        print(f"  - {name}")
    
    # Read the original XML file
    with open(xml_file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Create backup
    with open(backup_file, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"Created backup: {backup_file}")
    
    # Pattern to match type entries in spawnable types XML
    # This captures from <type name="..."> to its corresponding </type>
    type_pattern = r'\t<type name="([^"]+)">(.*?)\t</type>'
    
    # Find all type entries
    matches = re.findall(type_pattern, content, re.DOTALL)
    print(f"Found {len(matches)} total type entries in XML")
    
    # Get the header (everything before first type entry)
    first_type_match = re.search(r'\t<type name="[^"]+">', content)
    if first_type_match:
        header = content[:first_type_match.start()]
    else:
        header = ""
    
    # Filter and rebuild content
    filtered_entries = []
    kept_count = 0
    removed_count = 0
    
    for type_name, type_content in matches:
        if type_name in keep_types:
            full_entry = f'\t<type name="{type_name}">{type_content}\t</type>'
            filtered_entries.append(full_entry)
            kept_count += 1
            print(f"KEEPING: {type_name}")
        else:
            removed_count += 1
            print(f"REMOVING: {type_name}")
    
    # Rebuild the file
    new_content = header
    for entry in filtered_entries:
        new_content += entry + '\n'
    
    # Remove any trailing newlines and ensure proper ending
    new_content = new_content.rstrip('\n')
    
    # Write the filtered content
    with open(xml_file, 'w', encoding='utf-8') as f:
        f.write(new_content)
    
    print(f"\nOperation completed:")
    print(f"  - Kept: {kept_count} type entries")
    print(f"  - Removed: {removed_count} type entries")
    print(f"  - Original file backed up as: {backup_file}")
    print(f"  - Filtered file saved as: {xml_file}")

if __name__ == "__main__":
    main()