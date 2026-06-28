#!/usr/bin/env python3
"""
Add roaming patrol entries to AIPatrolSettings.json

Reads patrol names and coordinates from add_roamers.txt and creates
new patrol entries matching existing ROAMING patrols in AIPatrolSettings.json
"""

import json
import re
import argparse
from pathlib import Path


def parse_roamers_file(filepath):
    """Parse add_roamers.txt to extract patrol names and coordinates"""
    patrols = []

    with open(filepath, 'r') as f:
        lines = f.readlines()

    i = 0
    while i < len(lines):
        line = lines[i].strip()

        # Skip empty lines
        if not line:
            i += 1
            continue

        # Check if this is a location name
        if i + 1 < len(lines):
            next_line = lines[i + 1].strip()
            # Look for coordinate pattern <x, y, z>
            coord_match = re.match(r'<([\d.]+),\s*([\d.]+),\s*([\d.]+)>', next_line)

            if coord_match:
                name = line
                x = float(coord_match.group(1))
                y = float(coord_match.group(2))
                z = float(coord_match.group(3))

                patrols.append({
                    'name': name,
                    'coords': [x, y, z]
                })
                i += 2  # Skip both name and coordinate lines
                continue

        i += 1

    return patrols


def create_roaming_patrol_template(name, coords, existing_template):
    """Create a new patrol entry based on existing ROAMING patrol template"""
    # Deep copy the template
    new_patrol = json.loads(json.dumps(existing_template))

    # Update name and waypoint
    new_patrol['Name'] = f'Roaming-{name}'
    new_patrol['Waypoints'] = [coords]

    return new_patrol


def add_roaming_patrols(settings_file, roamers_file, dry_run=False):
    """Add roaming patrols from roamers_file to settings_file"""

    # Load AIPatrolSettings.json
    with open(settings_file, 'r') as f:
        data = json.load(f)

    # Find existing ROAMING patrols to use as template
    patrols = data.get('Patrols', [])
    roaming_patrols = [p for p in patrols if p.get('Behaviour') == 'ROAMING']

    if not roaming_patrols:
        print("ERROR: No existing ROAMING patrols found in AIPatrolSettings.json")
        return False

    # Use first roaming patrol as template
    template = roaming_patrols[0]
    print(f"Using template from: {template['Name']}")

    # Parse roamers file
    new_patrols = parse_roamers_file(roamers_file)
    print(f"\nFound {len(new_patrols)} new patrols to add:")
    for patrol in new_patrols:
        print(f"  - {patrol['name']}: {patrol['coords']}")

    # Check for existing patrol names to avoid duplicates
    existing_names = {p['Name'] for p in patrols}

    # Create new patrol entries
    added_count = 0
    skipped_count = 0

    for patrol_data in new_patrols:
        patrol_name = f"Roaming-{patrol_data['name']}"

        if patrol_name in existing_names:
            print(f"\nSkipping {patrol_name} - already exists")
            skipped_count += 1
            continue

        new_patrol = create_roaming_patrol_template(
            patrol_data['name'],
            patrol_data['coords'],
            template
        )

        if dry_run:
            print(f"\n[DRY RUN] Would add patrol: {patrol_name}")
        else:
            data['Patrols'].append(new_patrol)
            print(f"\nAdded patrol: {patrol_name}")

        added_count += 1

    # Save updated file
    if not dry_run and added_count > 0:
        with open(settings_file, 'w') as f:
            json.dump(data, f, indent=2)
        print(f"\n✓ Successfully added {added_count} new patrols to {settings_file}")

    if skipped_count > 0:
        print(f"\n⚠ Skipped {skipped_count} duplicate patrol(s)")

    if dry_run:
        print(f"\n[DRY RUN] Would have added {added_count} patrol(s)")

    return True


def main():
    parser = argparse.ArgumentParser(
        description='Add roaming patrol entries to AIPatrolSettings.json'
    )
    parser.add_argument(
        '--settings',
        default=r'mpmissions\dayzOffline.enoch\expansion\settings\AIPatrolSettings.json',
        help='Path to AIPatrolSettings.json'
    )
    parser.add_argument(
        '--roamers',
        default=r'custom_scripts\add_roamers.txt',
        help='Path to add_roamers.txt'
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Show what would be added without making changes'
    )

    args = parser.parse_args()

    # Validate files exist
    settings_path = Path(args.settings)
    roamers_path = Path(args.roamers)

    if not settings_path.exists():
        print(f"ERROR: Settings file not found: {settings_path}")
        return 1

    if not roamers_path.exists():
        print(f"ERROR: Roamers file not found: {roamers_path}")
        return 1

    # Run the script
    success = add_roaming_patrols(
        settings_path,
        roamers_path,
        dry_run=args.dry_run
    )

    return 0 if success else 1


if __name__ == '__main__':
    exit(main())