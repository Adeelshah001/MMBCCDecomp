#!/usr/bin/env python3
"""Disassemble the MMBCC save-driver slice to GNU as assembly.

Region (from ANALYSIS.md sections 1.5, 1.6, 2.5):
  0x4DB24-0x4DB38 : 5 BIOS-call veneer wrappers (svc N; bx lr)
  0x4DB38-0x4DCCC : 6 save-driver primitives (all Thumb) + their literal pools

  Veneers (svc immediates read from the ROM, names per ANALYSIS.md):
    0x4DB24 CpuFastSet      (svc 0x0C)
    0x4DB28 CpuSet          (svc 0x0B)
    0x4DB2C LZ77UnCompVram  (svc 0x12)
    0x4DB30 LZ77UnCompWram  (svc 0x11)
    0x4DB34 RLUnCompVram    (svc 0x15)
  Primitives (names from observed behavior, ANALYSIS.md section 2.5):
    0x4DB38 Sram_Memcpy         (byte copy loop)
    0x4DB5C Sram_WaitcntInit    (WAITCNT 0x04000204 |= 3, then dispatch)
    0x4DBC0 Sram_Read           (SRAM -> RAM copy)
    0x4DC00 Sram_VerifyCompare  (byte compare, returns mismatch offset or 0)
    0x4DC30 Sram_VerifyWorker   (WAITCNT |= 3, compare via worker)
    0x4DC94 Sram_RetryWrapper   (write + verify, up to 3 attempts)

Same approach as docs/gen_crt0_asm.py: pool detection via ldr [pc]
before the code walk, branch targets become labels, pools emitted as
.word with reference comments. The `movs rN,rN` GAS quirk (see
gen_crt0_asm.py) is handled the same way.

Output uses its own section (.text.savedrv) so the linker can place it
independently at 0x0804DB24.
"""
import hashlib

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

ROM = "/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba"
OUT = "/home/hatch/workspace/mmbcc-decomp/mmbcc/asm/savedrv.s"
EXPECTED_SHA1 = "72309736f3820470c6f372d6a05ad1f16bc5a946"

START, END = 0x4DB24, 0x4DCCC  # end: byte after Sram_RetryWrapper's `bx r1`

rom = open(ROM, "rb").read()
sha1 = hashlib.sha1(rom).hexdigest()
assert sha1 == EXPECTED_SHA1, f"baserom SHA-1 mismatch: {sha1}"
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)


def u16(o):
    return rom[o] | (rom[o + 1] << 8)


def u32(o):
    return rom[o] | (rom[o + 1] << 8) | (rom[o + 2] << 16) | (rom[o + 3] << 24)


BRANCH_MN = {"b", "bl", "beq", "bne", "bcs", "bcc", "bmi", "bpl", "bvs",
             "bvc", "bhi", "bls", "bge", "blt", "bgt", "ble"}

# Entry points. Veneer svc immediates are read from the ROM below and
# cross-checked against the expected table from ANALYSIS.md section 1.5.
names = {
    0x4DB38: "Sram_Memcpy",
    0x4DB5C: "Sram_WaitcntInit",
    0x4DBC0: "Sram_Read",
    0x4DC00: "Sram_VerifyCompare",
    0x4DC30: "Sram_VerifyWorker",
    0x4DC94: "Sram_RetryWrapper",
}
VENEER_SVC = {  # svc immediate -> wrapper name (ANALYSIS.md section 1.5)
    0x0C: "CpuFastSet",
    0x0B: "CpuSet",
    0x12: "LZ77UnCompVram",
    0x11: "LZ77UnCompWram",
    0x15: "RLUnCompVram",
}

# Read the veneer table: each wrapper is `svc #N; bx lr` (4 bytes).
for va in range(0x4DB24, 0x4DB38, 4):
    w0, w1 = u16(va), u16(va + 2)
    assert (w0 & 0xFF00) == 0xDF00, f"veneer @{va:#x} is not svc: {w0:#06x}"
    assert w1 == 0x4770, f"veneer @{va:#x} is not bx lr: {w1:#06x}"
    svc_imm = w0 & 0xFF
    assert svc_imm in VENEER_SVC, f"unexpected svc #{svc_imm:#x} @{va:#x}"
    names[va] = VENEER_SVC[svc_imm]
print("veneers:", ", ".join(f"{a:#x}={names[a]}" for a in range(0x4DB24, 0x4DB38, 4)))


def label_for(a):
    return names.get(a, f".Lsavedrv_{a:06X}")


def parse_target(op_str):
    return int(op_str.strip().lstrip("#"), 16)


# 1a: find pools via ldr [pc, #imm] (before the code walk skips them)
pools = {}
off = START
while off < END:
    ds = list(md.disasm(rom[off:off + 4], 0x08000000 + off, count=1))
    if not ds:
        off += 2
        continue
    i = ds[0]
    if i.mnemonic == "ldr" and "[pc" in i.op_str:
        try:
            imm = int(i.op_str.split("#")[1].rstrip("]"), 16)
            pa = ((off + 4) & ~3) + imm
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
    ds = list(md.disasm(rom[off:off + 4], 0x08000000 + off, count=1))
    if not ds:
        print(f"!! undecodable at {off:#x}, emitting .short")
        insns.append((off, ".short"))
        off += 2
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

print(f"THUMB {START:#x}-{END:#x}: {len(insns)} entries, "
      f"{len(targets)} branch targets, {len(pools)} pool words")

# 2: rewrite branch operands to labels.
# QUIRK (same as gen_crt0_asm.py): GAS assembles Thumb `movs rN, rN`
# (the 0x0000 NOP idiom) as `adds rN, rN, #0` (0x1C00) instead of
# 0x0000. Emit raw .short to preserve the original bytes.
# QUIRK 2: this GAS (2.42, -mcpu=arm7tdmi, .thumb) wants pre-UAL
# mnemonics for Thumb data-processing: `adds`->`add`, `subs`->`sub`,
# `ands`->`and`, `eors`->`eor`, `orrs`->`orr`, `bics`->`bic`,
# `lsls`->`lsl`, `lsrs`->`lsr`, `asrs`->`asr`, `rors`->`ror`,
# `muls`->`mul`. Each assembles to the identical encoding as the
# `s`-suffixed form (spot-verified with objdump). `movs`/`cmp` are
# accepted as-is. `rsbs Rd, Rn, #0` is only accepted as `neg Rd, Rn`.
# QUIRK 3: branch targets must not carry `#`: `bl #0x804dcd8` is a
# "bad expression", `bl 0x804dcd8` assembles fine.
GAS_MNEMONIC = {
    "adds": "add", "subs": "sub", "ands": "and", "eors": "eor",
    "orrs": "orr", "bics": "bic", "lsls": "lsl", "lsrs": "lsr",
    "asrs": "asr", "rors": "ror", "muls": "mul",
}
rewritten = []
for o, text in insns:
    if text is None or text == ".short":
        rewritten.append((o, text))
        continue
    mn = text.split()[0]
    parts = text.split(None, 1)
    if mn == "movs" and len(parts) == 2:
        regs = [r.strip() for r in parts[1].split(",")]
        if len(regs) == 2 and regs[0] == regs[1]:
            w = u16(o)
            rewritten.append((o, f".short 0x{w:04X} @ movs {regs[0]},{regs[1]} NOP idiom (GAS quirk)"))
            continue
    if mn == "rsbs" and len(parts) == 2:
        ops = [x.strip() for x in parts[1].split(",")]
        assert len(ops) == 3 and ops[2] == "#0", f"unexpected rsbs form @{o:#x}: {text}"
        rewritten.append((o, f"neg {ops[0]}, {ops[1]} @ GAS quirk: rsbs spelling rejected"))
        continue
    if mn in GAS_MNEMONIC:
        text = f"{GAS_MNEMONIC[mn]} {parts[1]}"
        mn = GAS_MNEMONIC[mn]
    if mn in BRANCH_MN:
        try:
            t = parse_target(text.split()[-1]) - 0x08000000
            if START <= t < END:
                text = f"{mn} {label_for(t)}"
            else:
                text = f"{mn} {t + 0x08000000:#x}"
        except ValueError:
            pass
    rewritten.append((o, text))

# 3: events
all_events = []  # (addr, sortkey, line)
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
    elif text == ".short":
        all_events.append((o, 1, f"\t.short 0x{u16(o):04X} @ undecodable, raw"))
    else:
        all_events.append((o, 1, f"\t{text}"))
for pa in sorted(pools):
    refs = ",".join(f"{r:#x}" for r in sorted(pools[pa])[:4])
    all_events.append(
        (pa, 1, f"\t.word 0x{u32(pa):08X} @ pool, referenced from {refs}"))

all_events.sort(key=lambda e: (e[0], e[1]))
lines = [
    '\t.section .text.savedrv,"ax",%progbits',
    "\t.balign 4 @ keep ldr [pc] pools word-aligned",
    "",
]
for n in names.values():
    lines.append(f"\t.global {n}")
lines += ["", "\t.thumb"]
for _, _, line in all_events:
    lines.append(line)

with open(OUT, "w") as f:
    f.write("\n".join(lines) + "\n")
print(f"wrote {OUT} ({len(lines)} lines)")
