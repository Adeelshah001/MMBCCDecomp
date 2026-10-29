#!/usr/bin/env python3
"""Disassemble the MMBCC crt0 region to GNU as assembly.

Regions (from ANALYSIS.md section 1.2):
  0xC0-0x2D4 : ARM   (crt0, IntrWait, IRQ dispatcher, ARM trampoline)
  0x2D4-0x2DC: data  (alignment padding between ARM/Thumb)
  0x2DC-0x33C: Thumb (crt0 helpers; Thumb entry is at 0x33C)

Linear disassembly; branch targets become labels; PC-relative literal
pools become .word. Output is assembled with arm-none-eabi-as and
byte-diffed against the ROM for verification.
"""
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROM = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
OUT = "/home/hatch/workspace/mmbcc-decomp/mmbcc/asm/crt0.s"

# (start, end, mode) — mode "ARM", "THUMB", or "DATA"
REGIONS = [
    (0xC0, 0x2D4, "ARM"),
    (0x2D4, 0x2DC, "DATA"),
    (0x2DC, 0x33C, "THUMB"),
]

rom = open(ROM, "rb").read()
md_arm = Cs(CS_ARCH_ARM, CS_MODE_ARM)
md_thumb = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

def u32(o):
    return rom[o] | (rom[o+1] << 8) | (rom[o+2] << 16) | (rom[o+3] << 24)

BRANCH_MN = {"b", "bl", "beq", "bne", "bcs", "bcc", "bmi", "bpl", "bvs",
             "bvc", "bhi", "bls", "bge", "blt", "bgt", "ble"}

names = {0xC0: "Init", 0xFC: "IntrWait",
         0x1BC: "IrqDispatcher", 0x2A4: "ArmTrampoline",
         0x2DC: "crt0_thumb_helpers"}

def label_for(a):
    return names.get(a, f".Lcrt0_{a:06X}")

def parse_target(op_str):
    return int(op_str.strip().lstrip("#"), 16)

all_events = []  # (addr, sortkey, line)

for START, END, mode in REGIONS:
    if mode == "DATA":
        for o in range(START, END, 4):
            all_events.append((o, 1, f"\t.word 0x{u32(o):08X} @ padding"))
        continue

    md = md_arm if mode == "ARM" else md_thumb

    # 1a: find pools via ldr [pc, #imm] (before the code walk skips them)
    pools = {}
    off = START
    while off < END:
        ds = list(md.disasm(rom[off:off+4], 0x08000000 + off, count=1))
        if not ds:
            off += 2 if mode == "THUMB" else 4
            continue
        i = ds[0]
        if i.mnemonic == "ldr" and "[pc" in i.op_str:
            try:
                imm = int(i.op_str.split("#")[1].rstrip("]"), 16)
                if mode == "THUMB":
                    pa = ((off + 4) & ~3) + imm
                else:
                    pa = off + 8 + imm
                if START <= pa < END:
                    pools.setdefault(pa, set()).add(off)
            except (IndexError, ValueError):
                pass
        off += i.size

    # 1b: walk, skipping pool words
    insns = []
    targets = set()
    off = START
    while off < END:
        if off in pools:
            insns.append((off, None))
            off += 4
            continue
        ds = list(md.disasm(rom[off:off+4], 0x08000000 + off, count=1))
        if not ds:
            print(f"!! undecodable at {off:#x} ({mode}), emitting .word")
            insns.append((off, None))
            off += 2 if mode == "THUMB" else 4
            continue
        i = ds[0]
        text = f"{i.mnemonic} {i.op_str}".strip()
        insns.append((off, text))
        if i.mnemonic in BRANCH_MN:
            try:
                t = parse_target(i.op_str) - 0x08000000
                if START <= t < END:
                    targets.add(t)
            except ValueError:
                pass
        off += i.size

    print(f"{mode} {START:#x}-{END:#x}: {len(insns)} entries, "
          f"{len(targets)} branch targets, {len(pools)} pool words")

    # 2: rewrite branch operands to labels.
    # QUIRK: GAS assembles Thumb `movs rN, rN` (the 0x0000 NOP idiom) as
    # `adds rN, rN, #0` (0x1C00) instead of 0x0000. Emit raw .short to
    # preserve the original bytes.
    rewritten = []
    for o, text in insns:
        if text is None:
            rewritten.append((o, None))
            continue
        mn = text.split()[0]
        parts = text.split(None, 1)
        if mn == "movs" and len(parts) == 2:
            regs = [r.strip() for r in parts[1].split(",")]
            if len(regs) == 2 and regs[0] == regs[1]:
                w = u32(o) & 0xFFFF
                rewritten.append((o, f".short 0x{w:04X} @ movs {regs[0]},{regs[1]} NOP idiom (GAS quirk)"))
                continue
        if mn in BRANCH_MN:
            try:
                t = parse_target(text.split()[-1]) - 0x08000000
                if START <= t < END:
                    text = f"{mn} {label_for(t)}"
            except ValueError:
                pass
        rewritten.append((o, text))

    # 3: events for this region
    # (walk None-entries that ARE pools are covered by the pools loop below)
    walk_pool_addrs = set(pools)
    label_addrs = {a for a in (targets | set(names) | {START}) - walk_pool_addrs
                   if START <= a < END}
    for a in sorted(label_addrs):
        all_events.append((a, 0, f"{label_for(a)}:"))
    for o, text in rewritten:
        if text is None:
            if o in walk_pool_addrs:
                continue  # emitted by the pools loop with ref comments
            all_events.append((o, 1, f"\t.word 0x{u32(o):08X}"))
        else:
            all_events.append((o, 1, f"\t{text}"))
    for pa in sorted(pools):
        refs = ",".join(f"{r:#x}" for r in sorted(pools[pa])[:4])
        all_events.append(
            (pa, 1, f"\t.word 0x{u32(pa):08X} @ pool, referenced from {refs}"))

directive = {"ARM": "\t.arm", "THUMB": "\t.thumb"}
all_events.sort(key=lambda e: (e[0], e[1]))
lines = ["\t.text", "", "\t.global Init"]
cur_mode = None
for a, _, line in all_events:
    m = next(m for s, e, m in REGIONS if s <= a < e)
    if m != cur_mode and m != "DATA":
        lines.append(directive[m])
        cur_mode = m
    lines.append(line)

with open(OUT, "w") as f:
    f.write("\n".join(lines) + "\n")
print(f"wrote {OUT} ({len(lines)} lines)")
