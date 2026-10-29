#!/usr/bin/env python3
"""MMBCCDecomp Phase 1: function boundary list v1.

Scans the code region (0x000000-0x04FFFF) for ARM/Thumb function prologues,
validates via bl-target harvesting, and emits a function list.
Method: prologue signatures + ARMv4T-validated disassembly, per ANALYSIS.md.
"""
import sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROM = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
CODE_END = 0x50000
OUT = "/home/hatch/workspace/mmbcc-decomp/docs/func_list_v1.txt"

rom = open(ROM, "rb").read()
assert len(rom) == 8388608

md_arm = Cs(CS_ARCH_ARM, CS_MODE_ARM)
md_arm.detail = True
md_thumb = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
md_thumb.detail = True

def u16(o): return rom[o] | (rom[o+1] << 8)
def u32(o): return rom[o] | (rom[o+1] << 8) | (rom[o+2] << 16) | (rom[o+3] << 24)

# --- 1. prologue candidates ---
thumb_cands = set()
arm_cands = set()
for o in range(0, CODE_END, 2):
    h = u16(o)
    # Thumb push {rX, lr} with at least r4-r7 or lr: 0xB500-0xB5FF, require lr or r4+
    if (h & 0xFF00) == 0xB500 and (h & 0x5100):
        thumb_cands.add(o)
for o in range(0, CODE_END, 4):
    w = u32(o)
    # ARM stmdb sp!, {...} : cond=E, 0xE92Dxxxx, require lr or r4+ in reglist
    if (w & 0xFFFF0000) == 0xE92D0000 and (w & 0x00005F00):
        arm_cands.add(o)

print(f"thumb prologue candidates: {len(thumb_cands)}")
print(f"arm prologue candidates:   {len(arm_cands)}")

# --- 2. harvest bl targets (Thumb + ARM), ARMv4T encodings ---
bl_targets = set()
# Thumb BL (ARMv4T): hw1 = 11110 S imm10 (0xF000-0xF7FF),
#                    hw2 = 11111 imm11    (0xF800-0xFFFF)
# (no J1/J2 bits on ARMv4T — those are Thumb-2)
for o in range(0, CODE_END - 2, 2):
    h1 = u16(o)
    if 0xF000 <= h1 <= 0xF7FF:
        h2 = u16(o + 2)
        if 0xF800 <= h2 <= 0xFFFF:
            s = (h1 >> 10) & 1
            imm10 = h1 & 0x3FF
            imm11 = h2 & 0x7FF
            off = (imm10 << 12) | (imm11 << 1)
            if s:
                off -= 1 << 24
            tgt = 0x08000000 + o + 4 + off
            if 0x08000000 <= tgt < 0x08000000 + CODE_END:
                bl_targets.add((tgt - 0x08000000) & ~1)
# ARM bl: 0xEBxxxxxx
for o in range(0, CODE_END - 4, 4):
    w = u32(o)
    if (w & 0xFF000000) == 0xEB000000:
        off = w & 0xFFFFFF
        if off & 0x800000: off -= 0x1000000
        tgt = 0x08000000 + o + 8 + (off << 2)
        if 0x08000000 <= tgt < 0x08000000 + CODE_END:
            bl_targets.add(tgt - 0x08000000)

print(f"bl targets in code region: {len(bl_targets)}")

# --- 3. validated function starts ---
# A prologue candidate is "validated" if it is a bl target or (for entry-ish)
# explicitly known. Keep all candidates but flag validation.
funcs = []
for o in sorted(thumb_cands):
    funcs.append((o, 'T', o in bl_targets))
for o in sorted(arm_cands):
    funcs.append((o, 'A', o in bl_targets))
# Known entries that may lack standard prologues
for o, m in [(0xC0, 'A'), (0xFC, 'A'), (0x1BC, 'A'), (0x2A4, 'A'), (0x33C, 'T')]:
    if not any(f[0] == o for f in funcs):
        funcs.append((o, m, o in bl_targets))
funcs.sort()

validated = sum(1 for f in funcs if f[2])
print(f"total function entries: {len(funcs)} ({validated} bl-validated)")

# --- 4. estimate sizes: disassemble from each entry to terminator ---
def func_size(off, mode):
    md = md_thumb if mode == 'T' else md_arm
    step = 2 if mode == 'T' else 4
    pos = off
    count = 0
    while pos < CODE_END and count < 20000:
        chunk = rom[pos:pos+4]
        insns = list(md.disasm(chunk, 0x08000000 + pos, count=1))
        if not insns:
            break
        ins = insns[0]
        mn = ins.mnemonic
        ops = ins.op_str
        # terminators
        if mn == 'bx' and 'lr' in ops: return pos + step - off
        if mn == 'pop' and 'pc' in ops: return pos + step - off
        if mn == 'b':
            try: tgt = int(ops.strip(), 16)
            except ValueError: tgt = -1
            if tgt == ins.address: return pos + step - off  # infinite loop
        # ARMv4T sanity: reject Thumb-2-only / coprocessor encodings
        if mn in ('cbz', 'cbnz', 'mrc', 'mcr', 'cdp', 'ldc', 'stc', 'swp'):
            break
        pos += ins.size
        count += 1
        # stop at next known function start (don't run into neighbor)
        if pos != off and any(f[0] == pos for f in funcs):
            break
    return pos - off

with open(OUT, "w") as f:
    f.write("# MMBCC func_list v1: offset mode bl_validated est_size\n")
    f.write(f"# code region 0x000000-0x{CODE_END:06X}, rom base 0x08000000\n")
    for off, mode, val in funcs:
        sz = func_size(off, mode)
        f.write(f"{off:06X} {mode} {'Y' if val else 'n'} {sz}\n")

sizes = []
with open(OUT) as f:
    for line in f:
        if line.startswith("#"): continue
        sizes.append(int(line.split()[3]))
print(f"wrote {OUT}: {len(sizes)} entries")
print(f"size stats: min={min(sizes)} max={max(sizes)} total_code_bytes~{sum(sizes)}")
