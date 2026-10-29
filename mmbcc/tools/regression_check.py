#!/usr/bin/env python3
"""Full regression: compare every placed ldscript section against the baserom.
Classifies each section: CLEAN (0 diffs), TAIL2B (accepted c046-vs-0000
2-byte section-tail artifact), DIRTY (anything else). Prints summary + dirty list.

Usage: make mmbcc.elf   # then:  python3 tools/regression_check.py
"""
import re, subprocess, os, sys

DECOMP = os.path.expanduser('~/workspace/mmbcc-decomp')
ROM = os.path.expanduser('~/workspace/megaman-bcc-recomp/rom/'
                         'Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba')
ELF = os.path.join(DECOMP, 'mmbcc', 'mmbcc.elf')

slots = []
for line in open(os.path.join(DECOMP, 'mmbcc', 'ldscript.ld')):
    m = re.search(r'\.\s*=\s*(0x[0-9a-fA-F]+);\s*\.text\.([A-Za-z0-9_]+)', line)
    if m:
        slots.append((int(m.group(1), 16), '.text.' + m.group(2)))

if not os.path.exists(ELF):
    print('ELF not found — run `make mmbcc.elf` first', file=sys.stderr)
    sys.exit(2)
if len(slots) == 0:
    print('no slots parsed from ldscript.ld', file=sys.stderr)
    sys.exit(2)

rom = open(ROM, 'rb').read()

# Parse objdump -h ONCE (full section names; readelf truncates them).
secinfo = {}
out = subprocess.run(['arm-none-eabi-objdump', '-h', ELF],
                     capture_output=True, text=True).stdout
for line in out.splitlines():
    parts = line.split()
    if len(parts) >= 6 and parts[1].startswith('.text'):
        secinfo[parts[1]] = int(parts[3], 16)  # size

clean, tail2b, dirty = [], [], []
for addr, sec in slots:
    if sec not in secinfo:
        dirty.append((addr, sec, 'SECTION-NOT-FOUND'))
        continue
    elf_bytes = subprocess.run(
        ['arm-none-eabi-objcopy', '-O', 'binary', '-j', sec, ELF, '/dev/stdout'],
        capture_output=True).stdout
    ro = rom[addr - 0x08000000: addr - 0x08000000 + len(elf_bytes)]
    if elf_bytes == ro:
        clean.append((addr, sec))
    elif (len(elf_bytes) >= 2 and elf_bytes[:-2] == ro[:-2]
          and elf_bytes[-2:] == b'\xc0\x46' and ro[-2:] == b'\x00\x00'):
        tail2b.append((addr, sec))
    else:
        ndiff = sum(1 for a, b in zip(elf_bytes, ro) if a != b)
        dirty.append((addr, sec, '%d-diffs len=%d' % (ndiff, len(elf_bytes))))

print('sections: %d | clean: %d | tail2b-accepted: %d | dirty: %d'
      % (len(slots), len(clean), len(tail2b), len(dirty)))
for addr, sec, why in dirty:
    print('  DIRTY 0x%08x %s: %s' % (addr, sec, why))
sys.exit(1 if dirty else 0)
