import re
from math import floor
from pathlib import Path

FILE_PATH = Path("mpmissions/dayzOffline.enoch/expansion_ce/expansion_types.xml")
PREFIX = "Expansion_Landrover_"


def round_half_up(value: float) -> int:
    return int(floor(value + 0.5))


def halve(value: int) -> int:
    return round_half_up(value / 2)


def main() -> None:
    text = FILE_PATH.read_text().splitlines(keepends=True)

    updated_lines = []
    current_type = None
    nominal_value = None
    changed = []

    for line in text:
        type_match = re.search(r'<type name="([^"]+)">', line)
        if type_match:
            current_type = type_match.group(1)
            nominal_value = None

        if current_type and current_type.startswith(PREFIX):
            nominal_match = re.search(r"(<nominal>)(\d+)(</nominal>)", line)
            if nominal_match:
                nominal_value = int(nominal_match.group(2))
                if nominal_value > 0:
                    new_nominal = halve(nominal_value)
                    prefix = line[: nominal_match.start(1)]
                    suffix = line[nominal_match.end(3) :]
                    line = (
                        f"{prefix}{nominal_match.group(1)}"
                        f"{new_nominal}{nominal_match.group(3)}{suffix}"
                    )
                    changed.append((current_type, "nominal", nominal_value, new_nominal))

            min_match = re.search(r"(<min>)(\d+)(</min>)", line)
            if min_match and nominal_value and nominal_value > 0:
                min_value = int(min_match.group(2))
                new_min = halve(min_value)
                prefix = line[: min_match.start(1)]
                suffix = line[min_match.end(3) :]
                line = f"{prefix}{min_match.group(1)}{new_min}{min_match.group(3)}{suffix}"
                changed.append((current_type, "min", min_value, new_min))

        updated_lines.append(line)

        if "</type>" in line:
            current_type = None
            nominal_value = None

    FILE_PATH.write_text("".join(updated_lines))

    for entry in changed:
        print(f"{entry[0]}: {entry[1]} {entry[2]} -> {entry[3]}")

    print(f"Updated {len(changed)} values across {len({c[0] for c in changed})} types.")


if __name__ == "__main__":
    main()
