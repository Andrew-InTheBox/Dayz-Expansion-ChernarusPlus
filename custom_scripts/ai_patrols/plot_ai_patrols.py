import json
import matplotlib.pyplot as plt
from matplotlib.patches import Circle
from datetime import datetime
from pathlib import Path
import numpy as np
from argparse import ArgumentParser

# Get script and repo directories
script_dir = Path(__file__).resolve().parent
custom_scripts_dir = script_dir.parent
repo_root = custom_scripts_dir.parent

# Input file paths (relative to repo root; mpmissions subfolder varies by project)
mpmissions_dir = repo_root / 'mpmissions'


def resolve_first(glob_pattern):
    candidates = sorted(mpmissions_dir.glob(glob_pattern))
    return candidates[0] if candidates else None

# Generate output filename with timestamp
output_filename = f"{datetime.now().strftime('%Y%m%d%H%M')}_patrols.png"
output_path = script_dir / 'output' / output_filename

# Background image (relative to custom_scripts)
background_image_path = custom_scripts_dir / 'assets' / 'chernarus-map-background.png'
# Map extent for background image (min_x, max_x, min_z, max_z) in meters
# Patrol coordinates are on a 15380 x 15380 scale.
background_extent = (0, 15380, 0, 15380)
# Fixed alignment offset for this server/map background.
coordinate_offset = 32.0

def main():
    parser = ArgumentParser(description="Plot AI patrol waypoints and AI location radii.")
    parser.add_argument(
        "--locations-only",
        action="store_true",
        help="Plot only AILocationSettings.json circles and label them by Name.",
    )
    parser.add_argument(
        "--label-locations",
        action="store_true",
        help="Label AILocationSettings.json circles by Name while still plotting patrol data.",
    )
    parser.add_argument(
        "--no-patrol-labels",
        action="store_true",
        help="Do not draw patrol name labels.",
    )
    parser.add_argument(
        "--focus-region",
        nargs=4,
        type=float,
        metavar=("MIN_X", "MAX_X", "MIN_Z", "MAX_Z"),
        help="Zoom to a specific map region.",
    )
    parser.add_argument(
        "--focus-center",
        nargs=2,
        type=float,
        metavar=("X", "Z"),
        help="Center point for zoom region.",
    )
    parser.add_argument(
        "--focus-size",
        nargs=2,
        type=float,
        metavar=("WIDTH", "HEIGHT"),
        help="Width/height for --focus-center region in meters (default: 800 800).",
    )
    args = parser.parse_args()

    if args.focus_region and args.focus_center:
        parser.error("Use either --focus-region or --focus-center, not both.")

    if args.focus_size and not args.focus_center:
        parser.error("--focus-size requires --focus-center.")

    dx = coordinate_offset
    dz = coordinate_offset

    patrol_file_path = None
    if not args.locations_only:
        patrol_file_path = resolve_first('*/expansion/settings/AIPatrolSettings.json')
        if patrol_file_path is None:
            raise FileNotFoundError(
                f"No AIPatrolSettings.json found under: {mpmissions_dir}"
            )

    ai_locations_path = resolve_first('*/expansion/settings/AILocationSettings.json')
    if ai_locations_path is None and args.locations_only:
        raise FileNotFoundError(
            f"No AILocationSettings.json found under: {mpmissions_dir}"
        )

    plot_data = []
    if patrol_file_path is not None:
        with open(patrol_file_path, 'r') as file:
            data = json.load(file)

        patrols = data.get("Patrols", [])
        for patrol in patrols:
            name = patrol.get("Name", "Unknown")
            waypoints = patrol.get("Waypoints", [])
            coords = [(wp[0] + dx, wp[2] + dz) for wp in waypoints]
            if coords:
                plot_data.append((name, coords))

    ai_locations = []
    if ai_locations_path is not None:
        with open(ai_locations_path, 'r') as file:
            locations_data = json.load(file)
        ai_locations = locations_data.get('RoamingLocations', [])

    # Plot the data
    fig, ax = plt.subplots(figsize=(12, 10))

    # Draw background image if present
    if background_image_path.exists():
        bg = plt.imread(background_image_path)
        ax.imshow(
            bg,
            extent=background_extent,
            origin='upper'
        )
    else:
        print(f"Background image not found: {background_image_path}")

    for name, coords in plot_data:
        x_coords, z_coords = zip(*coords)
        ax.scatter(x_coords, z_coords, label=name)

        # Calculate geometric center (centroid) of waypoints
        centroid_x = np.mean(x_coords)
        centroid_z = np.mean(z_coords)

        if not args.no_patrol_labels:
            # Add patrol label at the centroid
            ax.annotate(name,
                        (centroid_x, centroid_z),
                        xytext=(0, 6),
                        textcoords='offset points',
                        ha='center',
                        va='bottom',
                        bbox=dict(facecolor='white', alpha=0.7, edgecolor='none', pad=2),
                        fontsize=6)

    # Overlay AI location radii (open red circles)
    if ai_locations:
        for location in ai_locations:
            position = location.get('Position', [])
            radius = location.get('Radius', 0)
            name = location.get('Name', 'Unknown')
            if len(position) >= 3 and radius > 0:
                circle = Circle(
                    (position[0] + dx, position[2] + dz),
                    radius,
                    fill=False,
                    edgecolor='red',
                    linewidth=1.0,
                    alpha=0.8
                )
                ax.add_patch(circle)
                if args.locations_only or args.label_locations:
                    ax.annotate(
                        name,
                        (position[0] + dx, position[2] + dz),
                        xytext=(0, 6),
                        textcoords='offset points',
                        ha='center',
                        va='bottom',
                        bbox=dict(facecolor='white', alpha=0.7, edgecolor='none', pad=2),
                        fontsize=6
                    )

    # Customize the plot
    ax.set_title("Patrol Waypoints (X and Z Coordinates)")
    ax.set_xlabel("X Coordinate")
    ax.set_ylabel("Z Coordinate")
    if plot_data:
        ax.legend(loc="upper left", bbox_to_anchor=(1, 1))
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')
    if args.focus_region:
        min_x, max_x, min_z, max_z = args.focus_region
    elif args.focus_center:
        width, height = (args.focus_size if args.focus_size else (800.0, 800.0))
        center_x, center_z = args.focus_center
        min_x = center_x - (width / 2.0)
        max_x = center_x + (width / 2.0)
        min_z = center_z - (height / 2.0)
        max_z = center_z + (height / 2.0)
    else:
        min_x, max_x, min_z, max_z = background_extent

    ax.set_xlim(min_x, max_x)
    ax.set_ylim(min_z, max_z)
    plt.tight_layout()

    # Save the plot
    plt.savefig(output_path, bbox_inches='tight', dpi=300)
    plt.close()

    print(f"Plot saved as: {output_path}")


if __name__ == '__main__':
    main()
