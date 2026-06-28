#!/usr/bin/env python3

"""Validate XML files for well-formedness.

Run with one or more paths (files or directories). Directories are searched
recursively for ``*.xml`` files. Exits non-zero if any files fail to parse.
"""

import argparse
import sys
from pathlib import Path
import xml.etree.ElementTree as ET


def iter_xml_files(paths):
    """Yield XML files from the given list of paths."""
    for base in paths:
        path = Path(base)
        if path.is_file() and path.suffix.lower() == ".xml":
            yield path
        elif path.is_dir():
            for file in sorted(path.rglob("*.xml")):
                yield file


def validate_file(path: Path):
    """Return (ok, error_message)."""
    try:
        ET.parse(path)
        return True, None
    except ET.ParseError as exc:
        return False, str(exc)


def main(argv=None):
    parser = argparse.ArgumentParser(description="Validate XML files for well-formedness.")
    parser.add_argument("paths", nargs="+", help="Files or directories to validate")
    args = parser.parse_args(argv)

    total = 0
    failed = 0

    for xml_file in iter_xml_files(args.paths):
        total += 1
        ok, error = validate_file(xml_file)
        if ok:
            print(f"[OK]   {xml_file}")
        else:
            failed += 1
            print(f"[FAIL] {xml_file} :: {error}")

    if total == 0:
        print("No XML files found.")
        return 1

    if failed:
        print(f"\nValidation finished: {failed} of {total} file(s) have errors.")
        return 1

    print(f"\nValidation finished: all {total} file(s) are well-formed.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
