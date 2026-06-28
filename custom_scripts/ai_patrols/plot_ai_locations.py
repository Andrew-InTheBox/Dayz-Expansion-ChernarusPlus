#!/usr/bin/env python3
"""
Plot AI location and no-go area circles from AILocationSettings.json on the Chernarus map.
"""

import json
import matplotlib.pyplot as plt
from matplotlib.patches import Circle
from datetime import datetime
from pathlib import Path
from argparse import ArgumentParser

SCRIPT_DIR = Path(__file__).resolve().parent
CUSTOM_SCRIPTS_DIR = SCRIPT_DIR.parent
REPO_ROOT = CUSTOM_SCRIPTS_DIR.parent

BACKGROUND_IMAGE_PATH = CUSTOM_SCRIPTS_DIR / 'assets' / 'chernarus-map-background.png'
BACKGROUND_EXTENT = (0, 15380, 0, 15380)

# Fixed alignment offset used by the other AI patrol plotter for this map image.
COORDINATE_OFFSET = 32.0


def plot_ai_locations(json_file_path, output_dir=None, label_points=True):
    """
    Read AILocationSettings.json and create a map plot of AI location circles.

    Args:
        json_file_path: Path to the AILocationSettings.json file
        output_dir: Directory to save the output image (defaults to current directory)
        label_points: Whether to label RoamingLocations and NoGoAreas by name
    """
    # Read the JSON file
    with open(json_file_path, 'r') as f:
        data = json.load(f)

    dx = COORDINATE_OFFSET
    dz = COORDINATE_OFFSET

    # Extract location data
    locations = data.get('RoamingLocations', [])
    no_go_areas = data.get('NoGoAreas', [])

    if not locations and not no_go_areas:
        print("No RoamingLocations or NoGoAreas found in the JSON file!")
        return

    def extract_circles(items, default_radius=100.0):
        circles = []
        for location in items:
            position = location.get('Position', [])
            name = location.get('Name', 'Unknown')
            radius = location.get('Radius', default_radius)

            if len(position) >= 3 and radius > 0:
                circles.append(
                    {
                        'x': position[0] + dx,
                        'z': position[2] + dz,
                        'name': name,
                        'radius': radius,
                    }
                )
        return circles

    roaming_circles = extract_circles(locations)
    no_go_circles = extract_circles(no_go_areas, default_radius=0.0)

    # Create the plot
    fig, ax = plt.subplots(figsize=(12, 10), dpi=150)

    # Draw background image if present
    if BACKGROUND_IMAGE_PATH.exists():
        background = plt.imread(BACKGROUND_IMAGE_PATH)
        ax.imshow(background, extent=BACKGROUND_EXTENT, origin='upper')
    else:
        print(f"Background image not found: {BACKGROUND_IMAGE_PATH}")

    # Draw roaming location circles with actual radius values.
    for circle_data in roaming_circles:
        circle = Circle(
            (circle_data['x'], circle_data['z']),
            circle_data['radius'],
            fill=True,
            facecolor='red',
            alpha=0.25,
            edgecolor='darkred',
            linewidth=1.0,
            zorder=4,
        )
        ax.add_patch(circle)

    if roaming_circles:
        ax.scatter(
            [circle_data['x'] for circle_data in roaming_circles],
            [circle_data['z'] for circle_data in roaming_circles],
            c='red',
            s=18,
            alpha=0.85,
            edgecolors='black',
            linewidth=0.45,
            label='RoamingLocations',
            zorder=5,
        )

    # Draw no-go areas distinctly so small exclusion zones are easy to inspect.
    for circle_data in no_go_circles:
        circle = Circle(
            (circle_data['x'], circle_data['z']),
            circle_data['radius'],
            fill=True,
            facecolor='dodgerblue',
            alpha=0.35,
            edgecolor='navy',
            linewidth=1.4,
            zorder=7,
        )
        ax.add_patch(circle)

    if no_go_circles:
        ax.scatter(
            [circle_data['x'] for circle_data in no_go_circles],
            [circle_data['z'] for circle_data in no_go_circles],
            c='navy',
            s=22,
            alpha=0.9,
            edgecolors='white',
            linewidth=0.45,
            label='NoGoAreas',
            zorder=8,
        )

    if label_points:
        for circle_data in roaming_circles:
            ax.annotate(
                circle_data['name'],
                (circle_data['x'], circle_data['z']),
                fontsize=5.5,
                alpha=0.85,
                xytext=(3, 3),
                textcoords='offset points',
                bbox=dict(facecolor='white', alpha=0.65, edgecolor='none', pad=1.0),
                zorder=6,
            )

        for circle_data in no_go_circles:
            ax.annotate(
                circle_data['name'],
                (circle_data['x'], circle_data['z']),
                fontsize=6,
                alpha=0.95,
                xytext=(4, 4),
                textcoords='offset points',
                bbox=dict(facecolor='white', alpha=0.8, edgecolor='none', pad=1.2),
                zorder=9,
            )

    # Set labels and title
    ax.set_xlabel('X Coordinate (meters)', fontsize=12)
    ax.set_ylabel('Z Coordinate (meters)', fontsize=12)
    ax.set_title('AI Location and No-Go Area Circles', fontsize=14, fontweight='bold')

    # Add grid for better readability
    ax.grid(True, alpha=0.3, linestyle='--')

    # Set axis limits to the Chernarus map background extent.
    ax.set_xlim(BACKGROUND_EXTENT[0], BACKGROUND_EXTENT[1])
    ax.set_ylim(BACKGROUND_EXTENT[2], BACKGROUND_EXTENT[3])

    # Make sure the plot is square with equal aspect ratio
    ax.set_aspect('equal', adjustable='box')

    if roaming_circles or no_go_circles:
        ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

    # Generate timestamp for filename
    timestamp = datetime.now().strftime('%Y%m%d%H%M')
    output_filename = f'AILocationsPlots-{timestamp}.png'

    # Determine output path
    if output_dir:
        output_path = Path(output_dir) / output_filename
    else:
        output_path = Path(output_filename)

    output_path.parent.mkdir(parents=True, exist_ok=True)

    # Save the figure
    plt.tight_layout()
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Plot saved to: {output_path}")
    print(f"RoamingLocations plotted: {len(roaming_circles)}")
    print(f"NoGoAreas plotted: {len(no_go_circles)}")

    # Close the plot to free memory
    plt.close()


if __name__ == '__main__':
    parser = ArgumentParser(description=__doc__)
    parser.add_argument(
        "--no-labels",
        action="store_true",
        help="Do not label RoamingLocations or NoGoAreas.",
    )
    args = parser.parse_args()

    json_path = REPO_ROOT / 'mpmissions' / 'Expansion.chernarusplus' / 'expansion' / 'settings' / 'AILocationSettings.json'

    # Output to this script category's output directory
    output_directory = SCRIPT_DIR / 'output'

    print(f"Reading AI locations from: {json_path}")
    plot_ai_locations(json_path, output_directory, label_points=not args.no_labels)
