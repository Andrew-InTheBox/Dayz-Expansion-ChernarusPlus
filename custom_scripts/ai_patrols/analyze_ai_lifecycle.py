import argparse
import csv
import json
import math
import re
from dataclasses import dataclass, field
from datetime import datetime, timedelta
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
CUSTOM_SCRIPTS_DIR = SCRIPT_DIR.parent
REPO_ROOT = CUSTOM_SCRIPTS_DIR.parent

DEFAULT_RPT_DIR = REPO_ROOT / "config"
DEFAULT_EXPANSION_LOG_DIR = REPO_ROOT / "config" / "ExpansionMod" / "Logs"
DEFAULT_HEATMAP_DIR = REPO_ROOT / "config" / "Heatmap"
DEFAULT_OUTPUT_DIR = SCRIPT_DIR / "output"
DEFAULT_PATROL_SETTINGS = (
    REPO_ROOT / "mpmissions" / "Expansion.chernarusplus" / "expansion" / "settings" / "AIPatrolSettings.json"
)
DEFAULT_MAP_IMAGE = CUSTOM_SCRIPTS_DIR / "assets" / "chernarus-map-background.png"

TIME_RE = re.compile(r"^(?P<h>\d{1,2}):(?P<m>\d{2}):(?P<s>\d{2})\.(?P<ms>\d{1,3})\s+")
RPT_NAME_RE = re.compile(r"DayZServer_x64_(?P<dt>\d{4}-\d{2}-\d{2}_\d{2}-\d{2}-\d{2})\.RPT$", re.I)
VECTOR_RE = re.compile(
    r"<\s*(?P<x>-?\d+(?:\.\d+)?)\s*,\s*(?P<y>-?\d+(?:\.\d+)?)\s*,\s*(?P<z>-?\d+(?:\.\d+)?)\s*>"
)
PATROL_EVENT_RE = re.compile(
    r"\[(?P<kind>AI(?: Object)? Patrol) (?P<patrol_id>\d+)\]\s+"
    r"(?:(?P<action>Loaded|Spawning)\s+(?P<count>\d+)\s+(?:persistent\s+)?"
    r"(?P<name>.+?)\s+\((?P<faction>[^)]+)\)\s+bots\s+at\s+(?P<vector><[^>]+>)|"
    r"(?P<name_wiped>.+?)\s+\((?P<faction_wiped>[^)]+)\)\s+bots were wiped out\s+"
    r"\(spawn position\s+(?P<vector_wiped><[^>]+>),\s+(?P<deceased>\d+)/(?P<total>\d+)\s+deceased\)|"
    r"Despawning\s+(?:(?P<count_despawn>\d+)\s+)?(?P<name_despawn>.+?)\s+\((?P<faction_despawn>[^)]+)\)\s+"
    r"(?:bots|patrol)\s+\(spawn position\s+(?P<vector_despawn><[^>]+>)(?:,\s+(?P<deceased_despawn>\d+)/(?P<total_despawn>\d+)\s+deceased)?\))"
)
KILLFEED_RE = re.compile(
    r"\[Killfeed\]\s+AI\s+(?P<ai_name>.+?)\s+\((?P<patrol_name>[^)]+)\)\s+"
    r"(?P<death_text>.+?)(?:\s+from a distance of\s+(?P<distance_m>\d+)\s+m)?\."
)


@dataclass
class LogEvent:
    source: str
    line_no: int
    raw_time: str
    timestamp: datetime
    uptime_s: float
    event_type: str
    patrol_kind: str = ""
    patrol_id: str = ""
    patrol_name: str = ""
    faction: str = ""
    count: int | None = None
    position: tuple[float, float, float] | None = None
    deceased: int | None = None
    total: int | None = None
    ai_name: str = ""
    death_text: str = ""
    killer_distance_m: int | None = None
    raw_line: str = ""


@dataclass
class Lifecycle:
    instance_id: int
    patrol_id: str
    patrol_name: str
    patrol_kind: str
    faction: str
    start_event_type: str
    spawn_time: datetime
    spawn_uptime_s: float
    spawn_position: tuple[float, float, float]
    spawn_line: int
    source_log: str
    configured_min_dist_radius: float | None = None
    configured_waypoint_count: int | None = None
    end_event_type: str = ""
    end_time: datetime | None = None
    end_uptime_s: float | None = None
    end_position: tuple[float, float, float] | None = None
    end_line: int | None = None
    deceased: int | None = None
    total: int | None = None
    killfeed: list[LogEvent] = field(default_factory=list)
    nearest_player_distance_m: float | None = None
    nearest_player_time_delta_s: float | None = None
    nearest_player_uptime_s: float | None = None
    nearest_player_track: int | None = None
    estimated_player_distance_at_spawn_m: float | None = None
    estimated_player_x: float | None = None
    estimated_player_z: float | None = None
    estimated_player_track: int | None = None
    player_bracket_before_delta_s: float | None = None
    player_bracket_after_delta_s: float | None = None
    player_bracket_before_distance_m: float | None = None
    player_bracket_after_distance_m: float | None = None
    player_bracket_gap_s: float | None = None
    min_dist_sample_status: str = "not_checked"
    violates_min_dist_sample: bool | None = None
    violates_min_dist_estimate: bool | None = None
    nearest_ai_track: int | None = None
    nearest_ai_track_distance_m: float | None = None
    nearest_ai_track_time_delta_s: float | None = None
    previous_same_patrol_end_delta_s: float | None = None
    previous_same_patrol_spawn_distance_m: float | None = None


def latest_file(directory: Path, pattern: str) -> Path:
    files = [p for p in directory.glob(pattern) if p.is_file()]
    if not files:
        raise FileNotFoundError(f"No files matching {pattern} found in {directory}")
    return max(files, key=lambda p: p.stat().st_mtime)


def parse_rpt_start(path: Path) -> datetime:
    match = RPT_NAME_RE.match(path.name)
    if not match:
        raise ValueError(f"Could not parse server start timestamp from RPT filename: {path.name}")
    return datetime.strptime(match.group("dt"), "%Y-%m-%d_%H-%M-%S")


def parse_line_time(line: str, base_date: datetime, previous: datetime | None) -> tuple[datetime, str] | tuple[None, None]:
    match = TIME_RE.match(line)
    if not match:
        return None, None
    raw = match.group(0).strip()
    ms_text = match.group("ms")
    microsecond = int(ms_text.ljust(3, "0")) * 1000
    current = base_date.replace(
        hour=int(match.group("h")),
        minute=int(match.group("m")),
        second=int(match.group("s")),
        microsecond=microsecond,
    )
    if previous is not None and current + timedelta(hours=12) < previous:
        current += timedelta(days=1)
    return current, raw


def parse_vector(text: str) -> tuple[float, float, float]:
    match = VECTOR_RE.search(text)
    if not match:
        raise ValueError(f"Could not parse vector: {text}")
    return (float(match.group("x")), float(match.group("y")), float(match.group("z")))


def distance_xz(a: tuple[float, float, float], b: tuple[float, float, float]) -> float:
    return math.hypot(a[0] - b[0], a[2] - b[2])


def read_patrol_settings(path: Path) -> dict[str, dict]:
    with open(path, "r", encoding="utf-8-sig") as file:
        data = json.load(file)
    patrols = {}
    for patrol in data.get("Patrols", []):
        name = patrol.get("Name")
        if not name:
            continue
        waypoints = patrol.get("Waypoints", []) or []
        patrols[name] = {
            "min_dist_radius": patrol.get("MinDistRadius"),
            "waypoint_count": len(waypoints),
            "waypoints": waypoints,
            "loadout": patrol.get("Loadout", ""),
            "faction": patrol.get("Faction", ""),
        }
    return patrols


def parse_expansion_log(path: Path, server_start: datetime) -> list[LogEvent]:
    events: list[LogEvent] = []
    previous_ts: datetime | None = None
    with open(path, "r", encoding="utf-8-sig", errors="replace") as file:
        for line_no, line in enumerate(file, 1):
            timestamp, raw_time = parse_line_time(line, server_start, previous_ts)
            if timestamp is None:
                continue
            previous_ts = timestamp
            uptime_s = (timestamp - server_start).total_seconds()
            patrol_match = PATROL_EVENT_RE.search(line)
            if patrol_match:
                groups = patrol_match.groupdict()
                if groups.get("action"):
                    event_type = "loaded" if groups["action"] == "Loaded" else "spawned"
                    name = groups["name"]
                    faction = groups["faction"]
                    count = int(groups["count"])
                    position = parse_vector(groups["vector"])
                    deceased = None
                    total = None
                elif groups.get("name_wiped"):
                    event_type = "wiped"
                    name = groups["name_wiped"]
                    faction = groups["faction_wiped"]
                    count = None
                    position = parse_vector(groups["vector_wiped"])
                    deceased = int(groups["deceased"])
                    total = int(groups["total"])
                else:
                    event_type = "despawned"
                    name = groups["name_despawn"]
                    faction = groups["faction_despawn"]
                    count = int(groups["count_despawn"]) if groups.get("count_despawn") else None
                    position = parse_vector(groups["vector_despawn"])
                    deceased = int(groups["deceased_despawn"]) if groups.get("deceased_despawn") else None
                    total = int(groups["total_despawn"]) if groups.get("total_despawn") else None

                events.append(
                    LogEvent(
                        source=path.name,
                        line_no=line_no,
                        raw_time=raw_time,
                        timestamp=timestamp,
                        uptime_s=uptime_s,
                        event_type=event_type,
                        patrol_kind=groups["kind"],
                        patrol_id=groups["patrol_id"],
                        patrol_name=name,
                        faction=faction,
                        count=count,
                        position=position,
                        deceased=deceased,
                        total=total,
                        raw_line=line.rstrip("\n"),
                    )
                )
                continue

            kill_match = KILLFEED_RE.search(line)
            if kill_match:
                groups = kill_match.groupdict()
                events.append(
                    LogEvent(
                        source=path.name,
                        line_no=line_no,
                        raw_time=raw_time,
                        timestamp=timestamp,
                        uptime_s=uptime_s,
                        event_type="killfeed",
                        patrol_name=groups["patrol_name"],
                        ai_name=groups["ai_name"],
                        death_text=groups["death_text"],
                        killer_distance_m=int(groups["distance_m"]) if groups.get("distance_m") else None,
                        raw_line=line.rstrip("\n"),
                    )
                )
    return events


def build_lifecycles(
    events: list[LogEvent],
    patrol_settings: dict[str, dict],
    only_roaming: bool,
) -> list[Lifecycle]:
    lifecycles: list[Lifecycle] = []
    active: dict[tuple[str, str], Lifecycle] = {}
    instance_id = 1

    for event in events:
        if event.event_type == "killfeed":
            candidates = [
                lifecycle
                for lifecycle in active.values()
                if lifecycle.patrol_name == event.patrol_name
            ]
            if candidates:
                max(candidates, key=lambda item: item.spawn_uptime_s).killfeed.append(event)
            continue

        if not event.patrol_name:
            continue
        if only_roaming and not event.patrol_name.startswith("roaming"):
            continue

        key = (event.patrol_id, event.patrol_name)
        if event.event_type in {"loaded", "spawned"}:
            if key in active:
                close_lifecycle(active.pop(key), event, forced_type="superseded_by_spawn")
            settings = patrol_settings.get(event.patrol_name, {})
            lifecycle = Lifecycle(
                instance_id=instance_id,
                patrol_id=event.patrol_id,
                patrol_name=event.patrol_name,
                patrol_kind=event.patrol_kind,
                faction=event.faction,
                start_event_type=event.event_type,
                spawn_time=event.timestamp,
                spawn_uptime_s=event.uptime_s,
                spawn_position=event.position,
                spawn_line=event.line_no,
                source_log=event.source,
                configured_min_dist_radius=settings.get("min_dist_radius"),
                configured_waypoint_count=settings.get("waypoint_count"),
            )
            active[key] = lifecycle
            lifecycles.append(lifecycle)
            instance_id += 1
        elif event.event_type in {"wiped", "despawned"}:
            lifecycle = active.pop(key, None)
            if lifecycle is None:
                if event.event_type == "despawned":
                    # Shutdown/despawn cleanup can appear after a patrol was already wiped.
                    # Keep the log line in the raw events export, but do not create a fake lifecycle.
                    continue
                settings = patrol_settings.get(event.patrol_name, {})
                lifecycle = Lifecycle(
                    instance_id=instance_id,
                    patrol_id=event.patrol_id,
                    patrol_name=event.patrol_name,
                    patrol_kind=event.patrol_kind,
                    faction=event.faction,
                    start_event_type="unknown",
                    spawn_time=event.timestamp,
                    spawn_uptime_s=event.uptime_s,
                    spawn_position=event.position,
                    spawn_line=event.line_no,
                    source_log=event.source,
                    configured_min_dist_radius=settings.get("min_dist_radius"),
                    configured_waypoint_count=settings.get("waypoint_count"),
                )
                lifecycles.append(lifecycle)
                instance_id += 1
            close_lifecycle(lifecycle, event)

    add_previous_spawn_context(lifecycles)
    return lifecycles


def close_lifecycle(lifecycle: Lifecycle, event: LogEvent, forced_type: str | None = None) -> None:
    lifecycle.end_event_type = forced_type or event.event_type
    lifecycle.end_time = event.timestamp
    lifecycle.end_uptime_s = event.uptime_s
    lifecycle.end_position = event.position
    lifecycle.end_line = event.line_no
    lifecycle.deceased = event.deceased
    lifecycle.total = event.total


def add_previous_spawn_context(lifecycles: list[Lifecycle]) -> None:
    previous_by_name: dict[str, Lifecycle] = {}
    for lifecycle in sorted(lifecycles, key=lambda item: item.spawn_uptime_s):
        previous = previous_by_name.get(lifecycle.patrol_name)
        if previous:
            if previous.end_uptime_s is not None:
                lifecycle.previous_same_patrol_end_delta_s = lifecycle.spawn_uptime_s - previous.end_uptime_s
            lifecycle.previous_same_patrol_spawn_distance_m = distance_xz(
                lifecycle.spawn_position, previous.spawn_position
            )
        previous_by_name[lifecycle.patrol_name] = lifecycle


def load_heatmap(path: Path) -> dict:
    with open(path, "r", encoding="utf-8-sig") as file:
        return json.load(file)


def nearest_player_sample(
    player_tracks: list[list[list[float]]],
    position: tuple[float, float, float],
    uptime_s: float,
    max_time_delta_s: float,
) -> tuple[float | None, float | None, float | None, int | None]:
    best = None
    for track_index, track in enumerate(player_tracks):
        for point in track:
            if len(point) < 3:
                continue
            delta = abs(float(point[1]) - uptime_s)
            if delta > max_time_delta_s:
                continue
            dist = math.hypot(float(point[0]) - position[0], float(point[2]) - position[2])
            candidate = (dist, delta, float(point[1]), track_index)
            if best is None or candidate < best:
                best = candidate
    if best is None:
        return None, None, None, None
    return best


def estimate_player_at_spawn(
    player_tracks: list[list[list[float]]],
    position: tuple[float, float, float],
    uptime_s: float,
    max_time_delta_s: float,
) -> dict | None:
    best = None
    for track_index, track in enumerate(player_tracks):
        points = [point for point in track if len(point) >= 3]
        points.sort(key=lambda point: float(point[1]))
        before = None
        after = None
        for point in points:
            point_uptime = float(point[1])
            if point_uptime <= uptime_s:
                before = point
            elif point_uptime > uptime_s:
                after = point
                break

        if before is None or after is None:
            continue

        before_uptime = float(before[1])
        after_uptime = float(after[1])
        before_delta = uptime_s - before_uptime
        after_delta = after_uptime - uptime_s
        if before_delta > max_time_delta_s or after_delta > max_time_delta_s:
            continue

        gap = after_uptime - before_uptime
        if gap <= 0:
            continue

        ratio = (uptime_s - before_uptime) / gap
        est_x = float(before[0]) + (float(after[0]) - float(before[0])) * ratio
        est_z = float(before[2]) + (float(after[2]) - float(before[2])) * ratio
        estimated_distance = math.hypot(est_x - position[0], est_z - position[2])
        before_distance = math.hypot(float(before[0]) - position[0], float(before[2]) - position[2])
        after_distance = math.hypot(float(after[0]) - position[0], float(after[2]) - position[2])
        candidate = {
            "estimated_distance": estimated_distance,
            "estimated_x": est_x,
            "estimated_z": est_z,
            "track_index": track_index,
            "before_delta": before_delta,
            "after_delta": after_delta,
            "before_distance": before_distance,
            "after_distance": after_distance,
            "gap": gap,
        }
        if best is None or estimated_distance < best["estimated_distance"]:
            best = candidate
    return best


def nearest_ai_track(
    ai_tracks: list[list[list[float]]],
    position: tuple[float, float, float],
    uptime_s: float,
    max_time_delta_s: float,
) -> tuple[int | None, float | None, float | None]:
    best = None
    for track_index, track in enumerate(ai_tracks):
        if not track:
            continue
        point = track[0]
        if len(point) < 3:
            continue
        delta = abs(float(point[1]) - uptime_s)
        if delta > max_time_delta_s:
            continue
        dist = math.hypot(float(point[0]) - position[0], float(point[2]) - position[2])
        candidate = (dist, delta, track_index)
        if best is None or candidate < best:
            best = candidate
    if best is None:
        return None, None, None
    return best[2], best[0], best[1]


def enrich_with_heatmap(
    lifecycles: list[Lifecycle],
    heatmap: dict,
    max_time_delta_s: float,
) -> None:
    player_tracks = heatmap.get("m_WayPoints", []) or []
    ai_tracks = heatmap.get("m_AIWayPoints", []) or []
    for lifecycle in lifecycles:
        dist, delta, sample_uptime, track_index = nearest_player_sample(
            player_tracks,
            lifecycle.spawn_position,
            lifecycle.spawn_uptime_s,
            max_time_delta_s,
        )
        lifecycle.nearest_player_distance_m = dist
        lifecycle.nearest_player_time_delta_s = delta
        lifecycle.nearest_player_uptime_s = sample_uptime
        lifecycle.nearest_player_track = track_index
        estimate = estimate_player_at_spawn(
            player_tracks,
            lifecycle.spawn_position,
            lifecycle.spawn_uptime_s,
            max_time_delta_s,
        )
        if estimate is not None:
            lifecycle.estimated_player_distance_at_spawn_m = estimate["estimated_distance"]
            lifecycle.estimated_player_x = estimate["estimated_x"]
            lifecycle.estimated_player_z = estimate["estimated_z"]
            lifecycle.estimated_player_track = estimate["track_index"]
            lifecycle.player_bracket_before_delta_s = estimate["before_delta"]
            lifecycle.player_bracket_after_delta_s = estimate["after_delta"]
            lifecycle.player_bracket_before_distance_m = estimate["before_distance"]
            lifecycle.player_bracket_after_distance_m = estimate["after_distance"]
            lifecycle.player_bracket_gap_s = estimate["gap"]

        if dist is None:
            lifecycle.min_dist_sample_status = f"no_player_sample_within_{int(max_time_delta_s)}s"
            lifecycle.violates_min_dist_sample = None
        elif lifecycle.configured_min_dist_radius is None:
            lifecycle.min_dist_sample_status = "no_configured_min_dist_radius"
            lifecycle.violates_min_dist_sample = None
        else:
            lifecycle.violates_min_dist_sample = dist < float(lifecycle.configured_min_dist_radius)
            if lifecycle.estimated_player_distance_at_spawn_m is not None:
                lifecycle.violates_min_dist_estimate = (
                    lifecycle.estimated_player_distance_at_spawn_m < float(lifecycle.configured_min_dist_radius)
                )
            lifecycle.min_dist_sample_status = (
                "inside_configured_radius" if lifecycle.violates_min_dist_sample else "outside_configured_radius"
            )

        track, track_dist, track_delta = nearest_ai_track(
            ai_tracks,
            lifecycle.spawn_position,
            lifecycle.spawn_uptime_s,
            max_time_delta_s,
        )
        lifecycle.nearest_ai_track = track
        lifecycle.nearest_ai_track_distance_m = track_dist
        lifecycle.nearest_ai_track_time_delta_s = track_delta


def lifecycle_row(lifecycle: Lifecycle) -> dict:
    killfeed_text = " | ".join(
        f"line {event.line_no}: {event.ai_name} {event.death_text}"
        for event in lifecycle.killfeed
    )
    return {
        "instance_id": lifecycle.instance_id,
        "patrol_id": lifecycle.patrol_id,
        "patrol_name": lifecycle.patrol_name,
        "patrol_kind": lifecycle.patrol_kind,
        "faction": lifecycle.faction,
        "start_event_type": lifecycle.start_event_type,
        "spawn_time": lifecycle.spawn_time.isoformat(sep=" "),
        "spawn_uptime_s": round(lifecycle.spawn_uptime_s, 3),
        "spawn_x": lifecycle.spawn_position[0],
        "spawn_y_or_alt": lifecycle.spawn_position[1],
        "spawn_z": lifecycle.spawn_position[2],
        "spawn_line": lifecycle.spawn_line,
        "end_event_type": lifecycle.end_event_type,
        "end_time": lifecycle.end_time.isoformat(sep=" ") if lifecycle.end_time else "",
        "end_uptime_s": round(lifecycle.end_uptime_s, 3) if lifecycle.end_uptime_s is not None else "",
        "lifetime_s": round(lifecycle.end_uptime_s - lifecycle.spawn_uptime_s, 3)
        if lifecycle.end_uptime_s is not None
        else "",
        "end_line": lifecycle.end_line or "",
        "deceased": lifecycle.deceased if lifecycle.deceased is not None else "",
        "total": lifecycle.total if lifecycle.total is not None else "",
        "configured_min_dist_radius": lifecycle.configured_min_dist_radius
        if lifecycle.configured_min_dist_radius is not None
        else "",
        "configured_waypoint_count": lifecycle.configured_waypoint_count
        if lifecycle.configured_waypoint_count is not None
        else "",
        "nearest_player_distance_m": round(lifecycle.nearest_player_distance_m, 3)
        if lifecycle.nearest_player_distance_m is not None
        else "",
        "nearest_player_time_delta_s": round(lifecycle.nearest_player_time_delta_s, 3)
        if lifecycle.nearest_player_time_delta_s is not None
        else "",
        "nearest_player_uptime_s": round(lifecycle.nearest_player_uptime_s, 3)
        if lifecycle.nearest_player_uptime_s is not None
        else "",
        "nearest_player_track": lifecycle.nearest_player_track
        if lifecycle.nearest_player_track is not None
        else "",
        "estimated_player_distance_at_spawn_m": round(lifecycle.estimated_player_distance_at_spawn_m, 3)
        if lifecycle.estimated_player_distance_at_spawn_m is not None
        else "",
        "estimated_player_x": round(lifecycle.estimated_player_x, 3)
        if lifecycle.estimated_player_x is not None
        else "",
        "estimated_player_z": round(lifecycle.estimated_player_z, 3)
        if lifecycle.estimated_player_z is not None
        else "",
        "estimated_player_track": lifecycle.estimated_player_track
        if lifecycle.estimated_player_track is not None
        else "",
        "player_bracket_before_delta_s": round(lifecycle.player_bracket_before_delta_s, 3)
        if lifecycle.player_bracket_before_delta_s is not None
        else "",
        "player_bracket_after_delta_s": round(lifecycle.player_bracket_after_delta_s, 3)
        if lifecycle.player_bracket_after_delta_s is not None
        else "",
        "player_bracket_before_distance_m": round(lifecycle.player_bracket_before_distance_m, 3)
        if lifecycle.player_bracket_before_distance_m is not None
        else "",
        "player_bracket_after_distance_m": round(lifecycle.player_bracket_after_distance_m, 3)
        if lifecycle.player_bracket_after_distance_m is not None
        else "",
        "player_bracket_gap_s": round(lifecycle.player_bracket_gap_s, 3)
        if lifecycle.player_bracket_gap_s is not None
        else "",
        "min_dist_sample_status": lifecycle.min_dist_sample_status,
        "violates_min_dist_sample": lifecycle.violates_min_dist_sample
        if lifecycle.violates_min_dist_sample is not None
        else "",
        "violates_min_dist_estimate": lifecycle.violates_min_dist_estimate
        if lifecycle.violates_min_dist_estimate is not None
        else "",
        "nearest_ai_track": lifecycle.nearest_ai_track if lifecycle.nearest_ai_track is not None else "",
        "nearest_ai_track_distance_m": round(lifecycle.nearest_ai_track_distance_m, 3)
        if lifecycle.nearest_ai_track_distance_m is not None
        else "",
        "nearest_ai_track_time_delta_s": round(lifecycle.nearest_ai_track_time_delta_s, 3)
        if lifecycle.nearest_ai_track_time_delta_s is not None
        else "",
        "previous_same_patrol_end_delta_s": round(lifecycle.previous_same_patrol_end_delta_s, 3)
        if lifecycle.previous_same_patrol_end_delta_s is not None
        else "",
        "previous_same_patrol_spawn_distance_m": round(lifecycle.previous_same_patrol_spawn_distance_m, 3)
        if lifecycle.previous_same_patrol_spawn_distance_m is not None
        else "",
        "killfeed_count": len(lifecycle.killfeed),
        "killfeed": killfeed_text,
        "source_log": lifecycle.source_log,
    }


def event_row(event: LogEvent) -> dict:
    return {
        "source": event.source,
        "line_no": event.line_no,
        "timestamp": event.timestamp.isoformat(sep=" "),
        "uptime_s": round(event.uptime_s, 3),
        "event_type": event.event_type,
        "patrol_kind": event.patrol_kind,
        "patrol_id": event.patrol_id,
        "patrol_name": event.patrol_name,
        "faction": event.faction,
        "count": event.count if event.count is not None else "",
        "x": event.position[0] if event.position else "",
        "y_or_alt": event.position[1] if event.position else "",
        "z": event.position[2] if event.position else "",
        "deceased": event.deceased if event.deceased is not None else "",
        "total": event.total if event.total is not None else "",
        "ai_name": event.ai_name,
        "death_text": event.death_text,
        "killer_distance_m": event.killer_distance_m if event.killer_distance_m is not None else "",
        "raw_line": event.raw_line,
    }


def write_csv(path: Path, rows: list[dict]) -> None:
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    with open(path, "w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)


def write_summary(
    path: Path,
    rpt_path: Path,
    expansion_log_path: Path,
    heatmap_path: Path,
    patrol_settings_path: Path,
    server_start: datetime,
    events: list[LogEvent],
    lifecycles: list[Lifecycle],
    heatmap_time_window_s: float,
) -> None:
    violations = [item for item in lifecycles if item.violates_min_dist_sample is True]
    estimated_violations = [item for item in lifecycles if item.violates_min_dist_estimate is True]
    checked = [item for item in lifecycles if item.violates_min_dist_sample is not None]
    estimated_checked = [item for item in lifecycles if item.violates_min_dist_estimate is not None]
    respawns = [item for item in lifecycles if item.previous_same_patrol_end_delta_s is not None]
    lines = [
        "AI lifecycle analysis",
        "",
        f"RPT: {rpt_path}",
        f"Expansion log: {expansion_log_path}",
        f"Heatmap: {heatmap_path}",
        f"Patrol settings: {patrol_settings_path}",
        f"Server start inferred from RPT filename: {server_start.isoformat(sep=' ')}",
        f"Heatmap player-distance sample window: +/- {heatmap_time_window_s:.0f}s",
        "",
        f"Parsed events: {len(events)}",
        f"Lifecycle instances: {len(lifecycles)}",
        f"Lifecycle instances with player-distance checks: {len(checked)}",
        f"Potential MinDistRadius sample violations: {len(violations)}",
        f"Estimated exact-spawn MinDistRadius violations: {len(estimated_violations)} of {len(estimated_checked)} bracketed estimates",
        f"Respawn instances with previous same-patrol context: {len(respawns)}",
        "",
        "Potential MinDistRadius sample violations:",
    ]
    if violations:
        for lifecycle in violations:
            lines.append(
                f"- {lifecycle.patrol_name} instance {lifecycle.instance_id} at "
                f"{lifecycle.spawn_time.time()} nearest sample {lifecycle.nearest_player_distance_m:.1f}m "
                f"from player track {lifecycle.nearest_player_track} "
                f"(sample delta {lifecycle.nearest_player_time_delta_s:.1f}s"
                f"{format_estimate_summary(lifecycle)}, configured radius {lifecycle.configured_min_dist_radius})"
            )
    else:
        lines.append("- none found in sampled heatmap player positions")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def format_estimate_summary(lifecycle: Lifecycle) -> str:
    if lifecycle.estimated_player_distance_at_spawn_m is None:
        return ", no bracketed exact-spawn estimate"
    return (
        f", estimated at spawn {lifecycle.estimated_player_distance_at_spawn_m:.1f}m"
        f" from track {lifecycle.estimated_player_track}"
        f", bracket -{lifecycle.player_bracket_before_delta_s:.1f}s/+{lifecycle.player_bracket_after_delta_s:.1f}s"
        f" distances {lifecycle.player_bracket_before_distance_m:.1f}m/{lifecycle.player_bracket_after_distance_m:.1f}m"
    )


def plot_map(path: Path, lifecycles: list[Lifecycle], map_image_path: Path) -> None:
    import matplotlib.pyplot as plt
    from matplotlib.lines import Line2D

    fig, ax = plt.subplots(figsize=(12, 10))
    if map_image_path.exists():
        image = plt.imread(map_image_path)
        ax.imshow(image, extent=(0, 15380, 0, 15380), origin="upper")

    for lifecycle in lifecycles:
        x, _, z = lifecycle.spawn_position
        if lifecycle.violates_min_dist_estimate:
            color = "red"
            size = 44
        elif lifecycle.violates_min_dist_sample:
            color = "orange"
            size = 34
        else:
            color = "yellow"
            size = 28

        ax.scatter([x], [z], color=color, s=size, edgecolor="black", linewidth=0.4, alpha=0.9, zorder=4)
        if lifecycle.end_position:
            ex, _, ez = lifecycle.end_position
            ax.plot([x, ex], [z, ez], color=color, linewidth=0.7, alpha=0.5)

        if (
            lifecycle.violates_min_dist_estimate
            and lifecycle.estimated_player_x is not None
            and lifecycle.estimated_player_z is not None
        ):
            ax.scatter(
                [lifecycle.estimated_player_x],
                [lifecycle.estimated_player_z],
                color="deepskyblue",
                marker="x",
                s=70,
                linewidth=1.5,
                zorder=5,
            )
            ax.plot(
                [x, lifecycle.estimated_player_x],
                [z, lifecycle.estimated_player_z],
                color="deepskyblue",
                linestyle=":",
                linewidth=1.0,
                alpha=0.8,
                zorder=3,
            )

    legend_items = [
        Line2D(
            [0],
            [0],
            marker="o",
            color="none",
            markerfacecolor="red",
            markeredgecolor="black",
            markersize=8,
            label="AI spawn: estimated player inside radius",
        ),
        Line2D(
            [0],
            [0],
            marker="o",
            color="none",
            markerfacecolor="orange",
            markeredgecolor="black",
            markersize=7,
            label="AI spawn: nearest sample inside radius",
        ),
        Line2D(
            [0],
            [0],
            marker="o",
            color="none",
            markerfacecolor="yellow",
            markeredgecolor="black",
            markersize=7,
            label="AI spawn: outside radius",
        ),
        Line2D(
            [0],
            [0],
            marker="x",
            color="deepskyblue",
            linestyle=":",
            markersize=8,
            label="Estimated player position at AI spawn",
        ),
    ]

    ax.legend(handles=legend_items, loc="upper left", framealpha=0.85, fontsize=8)
    ax.set_title("AI lifecycle spawn points and estimated player proximity")
    ax.set_xlabel("X")
    ax.set_ylabel("Z")
    ax.set_aspect("equal", adjustable="box")
    ax.set_xlim(0, 15380)
    ax.set_ylim(0, 15380)
    ax.grid(True, alpha=0.25)
    plt.tight_layout()
    plt.savefig(path, bbox_inches="tight", dpi=300)
    plt.close()


def main() -> None:
    parser = argparse.ArgumentParser(
        description=(
            "Build a lifecycle dataset for Expansion AI patrols by joining the newest "
            "RPT, ExpansionMod log, Heatmap JSON, and AIPatrolSettings.json."
        )
    )
    parser.add_argument("--rpt", type=Path, help="RPT file to use. Defaults to newest config/*.RPT.")
    parser.add_argument("--expansion-log", type=Path, help="Expansion log to use. Defaults to newest ExpLog_*.log.")
    parser.add_argument("--heatmap", type=Path, help="Heatmap JSON to use. Defaults to newest config/Heatmap/*.json.")
    parser.add_argument("--patrol-settings", type=Path, default=DEFAULT_PATROL_SETTINGS)
    parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT_DIR)
    parser.add_argument("--heatmap-time-window-s", type=float, default=180.0)
    parser.add_argument("--include-non-roaming", action="store_true")
    parser.add_argument("--plot-map", action="store_true", help="Also write a simple map overlay PNG.")
    parser.add_argument("--map-image", type=Path, default=DEFAULT_MAP_IMAGE)
    args = parser.parse_args()

    rpt_path = args.rpt or latest_file(DEFAULT_RPT_DIR, "*.RPT")
    expansion_log_path = args.expansion_log or latest_file(DEFAULT_EXPANSION_LOG_DIR, "ExpLog_*.log")
    heatmap_path = args.heatmap or latest_file(DEFAULT_HEATMAP_DIR, "*.json")
    server_start = parse_rpt_start(rpt_path)

    patrol_settings = read_patrol_settings(args.patrol_settings)
    events = parse_expansion_log(expansion_log_path, server_start)
    lifecycles = build_lifecycles(
        events,
        patrol_settings,
        only_roaming=not args.include_non_roaming,
    )
    heatmap = load_heatmap(heatmap_path)
    enrich_with_heatmap(lifecycles, heatmap, args.heatmap_time_window_s)

    args.output_dir.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime("%Y%m%d%H%M%S")
    lifecycle_csv = args.output_dir / f"{stamp}_ai_lifecycles.csv"
    events_csv = args.output_dir / f"{stamp}_ai_lifecycle_events.csv"
    lifecycle_json = args.output_dir / f"{stamp}_ai_lifecycles.json"
    summary_txt = args.output_dir / f"{stamp}_ai_lifecycle_summary.txt"

    lifecycle_rows = [lifecycle_row(item) for item in lifecycles]
    event_rows = [
        event_row(event)
        for event in events
        if args.include_non_roaming or event.patrol_name.startswith("roaming") or event.event_type == "killfeed"
    ]
    write_csv(lifecycle_csv, lifecycle_rows)
    write_csv(events_csv, event_rows)
    lifecycle_json.write_text(json.dumps(lifecycle_rows, indent=2), encoding="utf-8")
    write_summary(
        summary_txt,
        rpt_path,
        expansion_log_path,
        heatmap_path,
        args.patrol_settings,
        server_start,
        event_rows,
        lifecycles,
        args.heatmap_time_window_s,
    )

    print(f"RPT: {rpt_path}")
    print(f"Expansion log: {expansion_log_path}")
    print(f"Heatmap: {heatmap_path}")
    print(f"Lifecycle CSV: {lifecycle_csv}")
    print(f"Events CSV: {events_csv}")
    print(f"Lifecycle JSON: {lifecycle_json}")
    print(f"Summary: {summary_txt}")

    if args.plot_map:
        map_png = args.output_dir / f"{stamp}_ai_lifecycle_map.png"
        plot_map(map_png, lifecycles, args.map_image)
        print(f"Map plot: {map_png}")


if __name__ == "__main__":
    main()
