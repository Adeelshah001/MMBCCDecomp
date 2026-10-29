#!/usr/bin/env python3
"""SRAM save-hook locator: find code referencing 0x0E000000 (SRAM base).
Method: scan for 4-byte literal 0x0E000000 (literal pools), then disassemble
with capstone around each hit to find the referencing ldr and nearby ldrb/strb.
Read-only. Reports code offsets (file offsets; ROM base = 0x08000000).
"""
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_ARM

ROM_PATH = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
rom = open(ROM_PATH, "rb").read()
N = len(rom)
BASE = 0x08000000

# find literal pool entries = 0x0E000000
pools = []
o = 0
while o < N - 4:
    if rom[o:o+4] == b"\x00\x00\x00\x0E":
        pools.append(o)
    o += 1
print(f"literal 0x0E000000 occurrences: {len(pools)}", flush=True)

md_t = Cs(CS_ARCH_ARM, CS_MODE_THUMB); md_t.detail = True
md_a = Cs(CS_ARCH_ARM, CS_MODE_ARM); md_a.detail = True

def find_refs(pool_off, window=0x200):
    """search backwards for ldr rX,[pc,#imm] whose target == pool_off"""
    refs = []
    start = max(0, pool_off - window)
    # Thumb: scan halfword-aligned
    code = rom[start:pool_off]
    # try thumb first
    for insn in md_t.disasm(code, BASE + start):
        if insn.mnemonic == "ldr" and "pc" in insn.op_str:
            # compute target: pc = (addr+4) & ~3; target = pc + imm
            try:
                imm = int(insn.op_str.split("#")[-1].rstrip("]"), 0)
            except Exception:
                continue
            tgt = ((insn.address + 4) & ~3) + imm
            if tgt - BASE == pool_off:
                refs.append(("thumb", insn.address - BASE, insn.mnemonic + " " + insn.op_str))
    # ARM: word-aligned
    for insn in md_a.disasm(code, BASE + start):
        if insn.mnemonic == "ldr" and "pc" in insn.op_str:
            try:
                imm = int(insn.op_str.split("#")[-1].rstrip("]"), 0)
            except Exception:
                continue
            tgt = (insn.address + 8) & ~3
            # ARM ldr pc-relative: target = (addr+8+imm) with sign
            m = insn.op_str
            tgt = insn.address + 8 + (imm if "+" in m or "#" in m and "-" not in m.split("#")[-1] else -imm)
            # simpler: recompute from bytes
            import struct
            w = struct.unpack("<I", rom[insn.address-BASE:insn.address-BASE+4])[0]
            off12 = w & 0xFFF
            if not (w & 0x00800000): off12 = -off12
            tgt = insn.address + 8 + off12
            if tgt - BASE == pool_off:
                refs.append(("arm", insn.address - BASE, insn.mnemonic + " " + insn.op_str))
    return refs

all_refs = []
for p in pools:
    refs = find_refs(p)
    for mode, coff, txt in refs:
        all_refs.append((coff, mode, p, txt))
all_refs.sort()
print(f"pc-relative ldr refs to SRAM literal pools: {len(all_refs)}", flush=True)

# for each ref, disassemble forward 64 bytes and list sram accesses (ldrb/strb/ldr/str via that reg)
import struct
for coff, mode, poff, txt in all_refs:
    print(f"\npool@file0x{poff:07X} ref@{mode} file0x{coff:07X} ({txt})", flush=True)
    md = md_t if mode == "thumb" else md_a
    code = rom[coff:coff+96]
    # figure out dest reg of the ldr
    m = re_match = None
    import re
    mm = re.match(r"ldr\s+(r\d+)", txt)
    reg = mm.group(1) if mm else "?"
    for insn in md.disasm(code, BASE + coff):
        s = insn.mnemonic + " " + insn.op_str
        if reg != "?" and reg in insn.op_str and insn.mnemonic in ("ldrb", "strb", "ldr", "str", "ldrh", "strh", "adds", "mov", "add"):
            print(f"  0x{insn.address-BASE:07X}: {s}", flush=True)
print("\nDONE", flush=True)
