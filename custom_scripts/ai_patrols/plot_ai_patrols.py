import json
import base64
import html
import mimetypes
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


def patrol_type(patrol):
    return "Object patrol" if patrol.get("ObjectClassName") else "Waypoint patrol"


def effective_category(patrol):
    category = patrol.get("LoadBalancingCategory", "")
    if category:
        return category
    return "ObjectPatrols (default)" if patrol.get("ObjectClassName") else "Patrols (default)"


def image_data_uri(path):
    mime = mimetypes.guess_type(path.name)[0] or "image/png"
    encoded = base64.b64encode(path.read_bytes()).decode("ascii")
    return f"data:{mime};base64,{encoded}"


def write_interactive_html(path, patrols, ai_locations, source_path):
    """Write a dependency-free, standalone canvas map viewer."""
    path.parent.mkdir(parents=True, exist_ok=True)
    payload = []
    for index, patrol in enumerate(patrols):
        payload.append({
            "id": index,
            "name": patrol.get("Name", "Unknown"),
            "behaviour": patrol.get("Behaviour", "(blank)"),
            "category": effective_category(patrol),
            "type": patrol_type(patrol),
            "faction": patrol.get("Faction", "(blank)"),
            "objectClassName": patrol.get("ObjectClassName", ""),
            "waypoints": [
                [wp[0] + coordinate_offset, wp[2] + coordinate_offset]
                for wp in patrol.get("Waypoints", []) if len(wp) >= 3
            ],
        })

    locations = []
    for location in ai_locations:
        position = location.get("Position", [])
        if len(position) >= 3 and location.get("Radius", 0) > 0:
            locations.append({
                "name": location.get("Name", "Unknown"),
                "x": position[0] + coordinate_offset,
                "z": position[2] + coordinate_offset,
                "radius": location["Radius"],
            })

    background = image_data_uri(background_image_path) if background_image_path.exists() else ""
    generated = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    page = r'''<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>DayZ AI Patrol Explorer</title>
<style>
:root{color-scheme:dark;--panel:#17202a;--line:#34495e;--accent:#4fc3f7}
*{box-sizing:border-box}html,body{height:100%;margin:0;font:14px system-ui,sans-serif;background:#0d1117;color:#e6edf3}
body{display:grid;grid-template-columns:320px 1fr;overflow:hidden}aside{padding:14px;overflow:auto;background:var(--panel);border-right:1px solid var(--line)}
h1{font-size:18px;margin:0 0 6px}h2{font-size:13px;margin:16px 0 6px;color:#9cc9e3}.muted{color:#9aa7b2;font-size:12px}
.actions{display:flex;gap:6px;flex-wrap:wrap;margin:10px 0}button{background:#263747;color:#fff;border:1px solid #496176;border-radius:4px;padding:5px 8px;cursor:pointer}
button:hover{background:#334b60}.filter label,.display label{display:flex;gap:7px;align-items:center;padding:3px 0}.count{margin-left:auto;color:#8fa2b2}
#mapWrap{position:relative;min-width:0;overflow:hidden;background:#111}canvas{display:block;width:100%;height:100%;cursor:grab}canvas.dragging{cursor:grabbing}
#status{position:absolute;left:10px;bottom:10px;background:#0d1117dc;padding:6px 9px;border-radius:4px;pointer-events:none}
#tooltip{position:absolute;display:none;max-width:330px;background:#080b0eee;border:1px solid #758596;border-radius:5px;padding:7px;pointer-events:none;white-space:pre-line}
@media(max-width:760px){body{grid-template-columns:230px 1fr}aside{padding:9px}}
</style></head><body>
<aside><h1>AI Patrol Explorer</h1><div class="muted">__SOURCE__<br>Generated __GENERATED__</div>
<div class="actions"><button id="all">All patrols</button><button id="none">No patrols</button><button id="reset">Reset view</button></div>
<div id="filters"></div>
<h2>Display</h2><div class="display">
<label><input id="routes" type="checkbox" checked> Route lines</label>
<label><input id="points" type="checkbox" checked> Waypoints</label>
<label><input id="labels" type="checkbox" checked> Patrol names</label>
<label><input id="locations" type="checkbox" checked> AI location radii</label>
<label><input id="locationLabels" type="checkbox"> AI location names</label></div>
<p class="muted">Wheel to zoom; drag to pan. Hover a route or waypoint for details. Object-patrol waypoints may be relative to a dynamically spawned object rather than fixed world positions.</p></aside>
<main id="mapWrap"><canvas id="map"></canvas><div id="status"></div><div id="tooltip"></div></main>
<script>
const patrols=__PATROLS__, locations=__LOCATIONS__, bgSrc=__BACKGROUND__, mapSize=15380;
const colors=['#00e5ff','#ffca28','#ef5350','#66bb6a','#ab47bc','#ff7043','#42a5f5','#ec407a','#9ccc65','#ffee58','#26a69a','#bdbdbd'];
const canvas=document.querySelector('#map'),ctx=canvas.getContext('2d'),wrap=document.querySelector('#mapWrap'),tip=document.querySelector('#tooltip'),status=document.querySelector('#status');
const bg=new Image(); bg.src=bgSrc; let scale=1,ox=0,oy=0,drag=false,lastX=0,lastY=0,mouse=null;
const dimensions=[['behaviour','Behaviour'],['category','Category'],['type','Patrol type'],['faction','Faction']];
function values(key){return [...new Set(patrols.map(p=>p[key]))].sort()}
function buildFilters(){const root=document.querySelector('#filters'); dimensions.forEach(([key,title])=>{const box=document.createElement('div');box.className='filter';box.innerHTML=`<h2>${title}</h2>`;values(key).forEach(v=>{const n=patrols.filter(p=>p[key]===v).length,l=document.createElement('label');l.innerHTML=`<input type="checkbox" data-key="${key}" data-value="${escapeHtml(v)}" checked><span>${escapeHtml(v)}</span><span class="count">${n}</span>`;box.appendChild(l)});root.appendChild(box)});root.querySelectorAll('input').forEach(x=>x.onchange=draw)}
function escapeHtml(s){return String(s).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]))}
function enabled(p){return dimensions.every(([k])=>{const x=document.querySelector(`input[data-key="${k}"][data-value="${CSS.escape(p[k])}"]`);return x&&x.checked})}
function resize(){const d=devicePixelRatio||1;canvas.width=wrap.clientWidth*d;canvas.height=wrap.clientHeight*d;ctx.setTransform(d,0,0,d,0,0);resetView()}
function resetView(){const w=wrap.clientWidth,h=wrap.clientHeight;scale=Math.min(w/mapSize,h/mapSize);ox=(w-mapSize*scale)/2;oy=(h-mapSize*scale)/2;draw()}
function screen(x,z){return [ox+x*scale,oy+(mapSize-z)*scale]}
function world(x,y){return [(x-ox)/scale,mapSize-(y-oy)/scale]}
function draw(){const w=wrap.clientWidth,h=wrap.clientHeight;ctx.clearRect(0,0,w,h);if(bg.complete&&bg.naturalWidth)ctx.drawImage(bg,ox,oy,mapSize*scale,mapSize*scale);
 if(document.querySelector('#locations').checked){locations.forEach(l=>{const [x,y]=screen(l.x,l.z);ctx.beginPath();ctx.arc(x,y,l.radius*scale,0,Math.PI*2);ctx.strokeStyle='#ff3030';ctx.lineWidth=1.5;ctx.stroke();if(document.querySelector('#locationLabels').checked)label(l.name,x,y,'#ffd4d4')})}
 let shown=0;patrols.forEach((p,i)=>{if(!enabled(p)||!p.waypoints.length)return;shown++;const c=colors[i%colors.length],pts=p.waypoints.map(q=>screen(q[0],q[1]));if(document.querySelector('#routes').checked&&pts.length>1){ctx.beginPath();ctx.moveTo(...pts[0]);pts.slice(1).forEach(q=>ctx.lineTo(...q));if(p.behaviour==='LOOP')ctx.lineTo(...pts[0]);ctx.strokeStyle=c;ctx.lineWidth=2;ctx.stroke()}
 if(document.querySelector('#points').checked){pts.forEach((q,j)=>{ctx.beginPath();ctx.arc(q[0],q[1],j===0?4:3,0,Math.PI*2);ctx.fillStyle=j===0?'#fff':c;ctx.fill();ctx.strokeStyle='#111';ctx.stroke()})}if(document.querySelector('#labels').checked){const q=pts[Math.floor(pts.length/2)];label(p.name,q[0],q[1]-7,c)}});status.textContent=`${shown} / ${patrols.length} patrols visible`;hover()}
function label(s,x,y,c){ctx.font='11px system-ui';ctx.textAlign='center';ctx.textBaseline='bottom';const m=ctx.measureText(s);ctx.fillStyle='#081018c9';ctx.fillRect(x-m.width/2-3,y-13,m.width+6,15);ctx.fillStyle=c;ctx.fillText(s,x,y)}
function hover(){if(!mouse){tip.style.display='none';return}let best=null,dist=12;patrols.forEach(p=>{if(!enabled(p))return;p.waypoints.forEach((q,i)=>{const s=screen(q[0],q[1]),d=Math.hypot(s[0]-mouse.x,s[1]-mouse.y);if(d<dist){dist=d;best={p,i,q}}})});if(!best){tip.style.display='none';return}const p=best.p;tip.textContent=`${p.name}\nBehaviour: ${p.behaviour}\nCategory: ${p.category}\nType: ${p.type}\nFaction: ${p.faction}\nWaypoint ${best.i+1}/${p.waypoints.length}: ${best.q[0].toFixed(1)}, ${best.q[1].toFixed(1)}${p.objectClassName?'\nObject: '+p.objectClassName:''}`;tip.style.display='block';tip.style.left=Math.min(mouse.x+14,wrap.clientWidth-tip.offsetWidth-8)+'px';tip.style.top=Math.min(mouse.y+14,wrap.clientHeight-tip.offsetHeight-8)+'px'}
canvas.onwheel=e=>{e.preventDefault();const old=world(e.offsetX,e.offsetY),factor=e.deltaY<0?1.18:1/1.18;scale=Math.max(.02,Math.min(2.5,scale*factor));ox=e.offsetX-old[0]*scale;oy=e.offsetY-(mapSize-old[1])*scale;draw()};
canvas.onmousedown=e=>{drag=true;lastX=e.clientX;lastY=e.clientY;canvas.classList.add('dragging')};window.onmouseup=()=>{drag=false;canvas.classList.remove('dragging')};window.onmousemove=e=>{const r=canvas.getBoundingClientRect();mouse={x:e.clientX-r.left,y:e.clientY-r.top};if(drag){ox+=e.clientX-lastX;oy+=e.clientY-lastY;lastX=e.clientX;lastY=e.clientY;draw()}else hover()};canvas.onmouseleave=()=>{mouse=null;tip.style.display='none'};
document.querySelectorAll('.display input').forEach(x=>x.onchange=draw);document.querySelector('#reset').onclick=resetView;document.querySelector('#all').onclick=()=>{document.querySelectorAll('.filter input').forEach(x=>x.checked=true);draw()};document.querySelector('#none').onclick=()=>{document.querySelectorAll('.filter input').forEach(x=>x.checked=false);draw()};
bg.onload=draw;buildFilters();new ResizeObserver(resize).observe(wrap);
</script></body></html>'''
    page = (page.replace("__SOURCE__", html.escape(str(source_path)))
                .replace("__GENERATED__", generated)
                .replace("__PATROLS__", json.dumps(payload).replace("</", "<\\/"))
                .replace("__LOCATIONS__", json.dumps(locations).replace("</", "<\\/"))
                .replace("__BACKGROUND__", json.dumps(background)))
    path.write_text(page, encoding="utf-8")

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
        "--exclude-behaviour",
        action="append",
        default=[],
        metavar="BEHAVIOUR",
        help="Exclude a behaviour from PNG output (repeatable, e.g. ROAMING).",
    )
    parser.add_argument(
        "--html",
        nargs="?",
        const=str(script_dir / "output" / "ai_patrol_explorer.html"),
        metavar="PATH",
        help="Generate a standalone interactive HTML map, optionally at PATH.",
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
            if patrol.get("Behaviour", "").upper() in {
                value.upper() for value in args.exclude_behaviour
            }:
                continue
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

    if args.html:
        html_patrols = data.get("Patrols", []) if patrol_file_path is not None else []
        write_interactive_html(Path(args.html).expanduser().resolve(), html_patrols, ai_locations, patrol_file_path)
        print(f"Interactive map saved as: {Path(args.html).expanduser().resolve()}")
        return

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
    output_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(output_path, bbox_inches='tight', dpi=300)
    plt.close()

    print(f"Plot saved as: {output_path}")


if __name__ == '__main__':
    main()
