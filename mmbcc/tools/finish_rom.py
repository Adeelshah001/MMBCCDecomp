#!/usr/bin/env python3
"""finish_rom.py — post-link ROM fixup for the MMBCC decomp.

1. Pads the linked binary to the full 8 MiB (8,388,608 bytes) with 0xFF.
2. Applies the header-checksum quirk: the baserom stores 0x7B at 0xBD
   while the computed GBA checksum is 0x94 (shipped that way on the
   original cartridge — see ANALYSIS.md §1.1). gbafix writes the computed
   value, so we patch it back to 0x7B here for byte-identity.
3. Prints the resulting SHA-1.
"""
import hashlib
import sys

ROM_SIZE = 8388608
path = sys.argv[1]

with open(path, "r+b") as f:
    data = f.read()
    if len(data) > ROM_SIZE:
        sys.exit(f"error: linked ROM {len(data)} bytes exceeds {ROM_SIZE}")
    f.write(b"\xFF" * (ROM_SIZE - len(data)))
    f.seek(0xBD)
    f.write(b"\x7B")

sha1 = hashlib.sha1(open(path, "rb").read()).hexdigest()
print(f"{path}: {ROM_SIZE} bytes, sha1={sha1}")
