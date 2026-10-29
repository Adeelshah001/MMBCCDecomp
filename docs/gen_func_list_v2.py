#!/usr/bin/env python3
"""
gen_func_list_v2.py — Phase 1 proper: recursive-descent disassembly of the
MMBCC 320 KB code region, producing the exact (tiered) function list.

Reads the baserom IN PLACE under a SHA-1 gate. The ROM is never copied into
any repo and never modified.

Outputs (under docs/):
  func_list_v2.txt  — tiered function list (A/B) + demoted section (D)
  byteclass.tsv     — full 0x000000-0x04FFFF coverage: code|pool|data|unknown

Method summary:
  1. Recursive descent from 5 seeds (ARM @0xC0, @0xFC, @0x1BC; Thumb @0x2DC,
     @0x33C) with ARMv4T-exact decoders (Thumb BL has NO J1/J2 bits).
  2. bx rN resolved via the dominating ldr rN,[pc,#imm] on the current path
     (pool word bit0 selects Thumb/ARM target). `mov lr,pc; bx rN` is treated
     as a mode-switching call: target becomes a seed AND fallthrough continues.
  3. Function starts = seeds + bl targets + bx/ldr-pc targets. Bodies are
     assigned by reachability walks that stop at other starts (tail calls).
  4. v1 entries are re-checked: reached => A; unreached + forward-clean =>
     B; pool/mid-function/invalid => D.
"""

import struct
import hashlib
import sys
from collections import deque

ROM_PATH = ('/home/hatch/workspace/megaman-bcc-recomp/rom/'
            'Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba')
EXPECT_SHA1 = '72309736f3820470c6f372d6a05ad1f16bc5a946'
CODE_END = 0x50000          # file offsets 0x000000-0x04FFFF
BASE = 0x08000000
DOCS = '/home/hatch/workspace/mmbcc-decomp/docs'
MIN_CODE = 0xC0            # below this is the ROM header (data)

# --------------------------------------------------------------------------
# SHA-1 gate (read-only access to the baserom)
# --------------------------------------------------------------------------
h = hashlib.sha1()
with open(ROM_PATH, 'rb') as f:
    for chunk in iter(lambda: f.read(1 << 20), b''):
        h.update(chunk)
if h.hexdigest() != EXPECT_SHA1:
    sys.exit('FATAL: baserom SHA-1 mismatch, refusing to run')
rom = open(ROM_PATH, 'rb').read()


def u16(o):
    return struct.unpack_from('<H', rom, o)[0]


def u32(o):
    return struct.unpack_from('<I', rom, o)[0]


# --------------------------------------------------------------------------
# ARMv4T-exact decoders.
# kinds: fall | b | bcond | bl | bx | bxcall(via mov lr,pc, resolved in loop)
#        | term | ldrpool | ldrppc | invalid
# returns (size, kind, target_or_pooladdr, extra)
# --------------------------------------------------------------------------
def dec_thumb(o):
    h = u16(o)
    if 0xF000 <= h <= 0xF7FF:                      # BL first halfword
        if o + 4 > CODE_END:
            return (2, 'invalid', None, None)
        h2 = u16(o + 2)
        if not 0xF800 <= h2 <= 0xFFFF:
            return (2, 'invalid', None, None)
        s = (h >> 10) & 1
        off = ((h & 0x7FF) << 12) | ((h2 & 0x7FF) << 1)
        if s:
            off -= 1 << 23                        # ARMv4T: sign-extend bit22
        return (4, 'bl', o + 4 + off, None)
    if h >= 0xF800:
        return (2, 'invalid', None, None)          # lone BL suffix
    if h >= 0xE800:
        return (2, 'invalid', None, None)          # undefined on ARMv4T
    if h >= 0xE000:                               # b
        off = (h & 0x7FF) << 1
        if off & 0x800:
            off -= 0x1000
        t = o + 4 + off
        return (2, 'term' if t == o else 'b', t, None)
    if h >= 0xDF00:
        return (2, 'fall', None, None)            # swi
    if h >= 0xD000:                               # conditional branch
        off = (h & 0xFF) << 1
        if off & 0x100:
            off -= 0x200
        return (2, 'bcond', o + 4 + off, None)
    if h >= 0xC000:
        return (2, 'fall', None, None)            # ldm/stm
    if h >= 0xBE00:
        return (2, 'invalid', None, None)         # bkpt / undefined
    if h >= 0xBC00:                               # pop
        return (2, 'term' if (h & 0x0100) else 'fall', None, None)
    if h >= 0xB600:
        return (2, 'invalid', None, None)         # undefined on ARMv4T
    if h >= 0xB400:
        return (2, 'fall', None, None)            # push
    if h >= 0xB100:
        return (2, 'invalid', None, None)         # undefined on ARMv4T
    if h >= 0xB000:
        return (2, 'fall', None, None)            # add/sub sp,#imm
    if h >= 0xA000:
        return (2, 'fall', None, None)            # adr
    if h >= 0x9000:
        return (2, 'fall', None, None)            # ldr/str sp-relative
    if h >= 0x8000:
        return (2, 'fall', None, None)            # ldrh/strh
    if h >= 0x6000:
        return (2, 'fall', None, None)            # ldr/str imm offset
    if h >= 0x5000:
        return (2, 'fall', None, None)            # ldr/str reg offset
    if h >= 0x4800:                               # ldr rD,[pc,#imm]
        return (2, 'ldrpool', ((o + 4) & ~3) + ((h & 0xFF) << 2),
                (h >> 8) & 7)
    if h >= 0x4780:
        return (2, 'invalid', None, None)          # blx: ARMv5T only
    if h >= 0x4700:                               # bx
        rm = (h >> 3) & 0xF
        if rm == 14:
            return (2, 'term', None, None)         # bx lr
        if rm == 15:
            return (2, 'term', None, 'bx_pc_anom')  # bx pc: pathological
        return (2, 'bx', None, rm)
    if h >= 0x4400:                               # hi-reg ops
        if ((h >> 8) & 3) == 2:                   # mov
            # ARMv4T: bit6 -> Rs high bit, bit7 -> Rd high bit
            # (verified against arm-none-eabi-as encodings)
            Rs = ((h >> 3) & 7) | (((h >> 6) & 1) << 3)
            Rd = (h & 7) | (((h >> 7) & 1) << 3)
            if Rd == 15:
                if Rs == 14:
                    return (2, 'term', None, None)   # mov pc,lr: return
                return (2, 'bx', None, Rs)            # mov pc,rX: indirect
        return (2, 'fall', None, None)
    # 0x0000-0x43FF: shifts, add/sub, mov/cmp/add/sub imm, ALU.
    # NOTE: 0x0000 (movs r0,r0) is the standard NOP idiom: valid code.
    return (2, 'fall', None, None)


def dec_arm(o):
    w = u32(o)
    if (w & 0x0F000000) == 0x0F000000:
        return (4, 'fall', None, None)            # swi
    cond = w >> 28
    if cond == 0xF:
        return (4, 'invalid', None, None)
    if ((w >> 24) & 0xF) in (0xC, 0xD, 0xE):
        return (4, 'invalid', None, None)         # coprocessor: no hw support
    if (w & 0x0FFFFFF0) == 0x012FFF10:            # bx
        rm = w & 0xF
        if rm == 14:
            return (4, 'term', None, None)
        if rm == 15:
            return (4, 'term', None, 'bx_pc_anom')
        return (4, 'bx', None, rm)
    if (w & 0x0FFFFFF0) == 0x012FFF20:
        return (4, 'invalid', None, None)          # bxj: ARMv5
    if (w & 0x0F000000) == 0x0A000000:            # b
        off = w & 0xFFFFFF
        if off & 0x800000:
            off -= 0x1000000
        t = o + 8 + (off << 2)
        if t == o and cond == 0xE:
            return (4, 'term', None, None)     # `b .`: halt
        # NB: conditional self-branch (`bne .` spin-wait) must fall through
        return (4, 'b' if cond == 0xE else 'bcond', t, None)
    if (w & 0x0F000000) == 0x0B000000:            # bl
        off = w & 0xFFFFFF
        if off & 0x800000:
            off -= 0x1000000
        return (4, 'bl', o + 8 + (off << 2), None)
    if ((w >> 26) & 3) == 1 and not ((w >> 25) & 1):   # ldr/str immediate
        if ((w >> 16) & 0xF) == 15:               # Rn == pc
            L = (w >> 20) & 1
            rd = (w >> 12) & 0xF
            U = (w >> 23) & 1
            imm = w & 0xFFF
            pa = o + 8 + (imm if U else -imm)
            if L:
                return (4, 'ldrppc' if rd == 15 else 'ldrpool', pa, rd)
            return (4, 'invalid', None, None)     # str [pc] is UNDEFINED
    if ((w >> 25) & 7) == 4:                      # ldm/stm
        if ((w >> 20) & 1) and (w & (1 << 15)):
            return (4, 'term', None, None)        # ldm {..,pc}
        return (4, 'fall', None, None)
    if (w & 0x0FFFFFFF) == 0x01A0F00E:
        return (4, 'term', None, None)            # mov pc,lr
    return (4, 'fall', None, None)


MOV_LR_PC = {('ARM', 0xE1A0E00F), ('T', 0x46FE)}

# Register tags for bx resolution: curmap[reg] = (kind, pool_addr, value)
# kind 'pool': from ldr rN,[pc,#imm]  |  kind 'pop': from pop {..,rN}
TAG_POOL, TAG_POP = 'pool', 'pop'


def thumb_clobber(h):
    """Regs overwritten with unknown values by a 'fall'-kind Thumb insn
    (ldr-literal and pop are handled separately via tags)."""
    if h <= 0x1FFF:
        return {h & 7}
    if h <= 0x3FFF:
        if 0x2800 <= h <= 0x2FFF:      # cmp: no write
            return set()
        return {(h >> 8) & 7}
    if h <= 0x43FF:
        if ((h >> 6) & 0xF) in (8, 10, 11):   # tst/cmp/cmn
            return set()
        return {h & 7}
    if h <= 0x46FF:
        if ((h >> 8) & 3) == 1:       # cmp
            return set()
        return {(h & 7) | ((h >> 4) & 8)}
    if h <= 0x5FFF:
        if ((h >> 9) & 7) in (3, 4, 5, 6, 7):  # loads
            return {h & 7}
        return set()
    if h <= 0x8FFF:
        return {h & 7} if (h >> 11) & 1 else set()
    if h <= 0x9FFF:
        return {(h >> 8) & 7} if (h >> 11) & 1 else set()
    if h <= 0xAFFF:                   # adr
        return {(h >> 8) & 7}
    if h <= 0xBFFF:                   # add/sub sp, push, pop, undef
        return set()
    if h <= 0xCFFF:                   # ldm/stm
        if (h >> 11) & 1:             # ldm: loads reg list
            return {r for r in range(8) if (h >> r) & 1}
        return set()
    if h <= 0xDEFF:                   # conditional branches
        return set()
    return {0, 1, 2, 3}                # 0xDF00+: swi, BIOS clobbers r0-r3


def arm_clobber(w, kind):
    if kind == 'bl':
        return {14}
    if ((w >> 26) & 3) == 0:           # data processing / mrs / msr
        if (w & 0x0DBFF000) == 0x0129F000:   # msr: no Rd write
            return set()
        if (w >> 21) & 0xF in (8, 9, 10, 11):  # tst/teq/cmp/cmn
            return set()
        return {(w >> 12) & 0xF}
    if ((w >> 26) & 3) == 1:           # ldr/str
        if (w >> 20) & 1:
            return {(w >> 12) & 0xF}
        return set()
    if ((w >> 25) & 7) == 4:           # ldm/stm
        if (w >> 20) & 1:
            return {r for r in range(16) if (w >> r) & 1}
        return set()
    if (w & 0x0FC000F0) == 0x00000090:  # mul
        return {(w >> 16) & 0xF}
    if (w & 0x0F000000) == 0x0F000000:  # swi
        return {0, 1, 2, 3}
    return set()


def rom2file(v):
    """Convert a ROM-address word (as stored in a literal pool) to a file
    offset and mode. Returns (fileoff, mode) or (None, None) if the word is
    not a plausible code-region pointer (guards against stale regmap
    values: I/O regs, WRAM, garbage)."""
    t = (v & ~1) - BASE
    if MIN_CODE <= t < CODE_END:
        return (t, 'T' if (v & 1) else 'ARM')
    return (None, None)

# --------------------------------------------------------------------------
# Phase 1a: recursive-descent discovery
# --------------------------------------------------------------------------
insns = {}        # (addr, mode) -> (size, kind, target, extra)
pools = {}        # pool word addr -> set of referrer addrs
pool_vals = {}    # pool word addr -> word value (first seen)
bl_targets = set()
bx_targets = set()
anomalies = []

SEEDS = [(0xC0, 'ARM'), (0xFC, 'ARM'), (0x1BC, 'ARM'), (0x2A4, 'ARM'),
         (0x2DC, 'T'), (0x33C, 'T')]

seen = set()
work = deque()


def push(a, m, regmap):
    if (a, m) not in seen and MIN_CODE <= a < CODE_END:
        seen.add((a, m))
        work.append((a, m, regmap))


for s in SEEDS:
    push(s[0], s[1], {})

while work:
    a, m, regmap = work.popleft()
    pc = a
    curmap = dict(regmap)
    prev_mov_lr_pc = False
    while True:
        if (pc, m) in seen and (pc, m) != (a, m):
            break
        if not (MIN_CODE <= pc < CODE_END):
            anomalies.append(('pc_out_of_range', '%06X' % pc, m))
            break
        if m == 'T' and (pc & 1):
            anomalies.append(('misaligned', '%06X' % pc, m))
            break
        if m == 'ARM' and (pc & 3):
            anomalies.append(('misaligned', '%06X' % pc, m))
            break
        seen.add((pc, m))
        size, kind, tgt, extra = dec_thumb(pc) if m == 'T' else dec_arm(pc)
        if kind == 'invalid':
            anomalies.append(('invalid', '%06X' % pc, m))
            break
        insns[(pc, m)] = (size, kind, tgt, extra)

        is_mov_lr_pc = ((m, u32(pc) if m == 'ARM' else u16(pc))
                        in MOV_LR_PC)

        if kind in ('fall',):
            raw = u32(pc) if m == 'ARM' else u16(pc)
            if m == 'T' and 0xBC00 <= raw <= 0xBDFF and not (raw & 0x0100):
                # pop {regs} (no pc): popped regs hold the caller's
                # saved values; `bx rN` on one of them is a return.
                for r in range(8):
                    if (raw >> r) & 1:
                        curmap[r] = (TAG_POP, None, None)
            elif m == 'ARM' and ((raw >> 25) & 7) == 4 and ((raw >> 20) & 1) \
                    and not (raw & (1 << 15)):
                # ARM ldm without pc: same treatment
                for r in range(16):
                    if (raw >> r) & 1:
                        curmap[r] = (TAG_POP, None, None)
            else:
                clob = (thumb_clobber(raw) if m == 'T'
                        else arm_clobber(raw, kind))
                for r in clob:
                    curmap.pop(r, None)
            prev_mov_lr_pc = is_mov_lr_pc
            pc += size
            continue
        if kind == 'ldrpool':
            pa, rd = tgt, extra
            if MIN_CODE <= pa <= CODE_END - 4:
                pools.setdefault(pa, set()).add(pc)
                if pa not in pool_vals:
                    pool_vals[pa] = u32(pa)
                curmap[rd] = (TAG_POOL, pa, u32(pa))
            else:
                anomalies.append(('pool_out_of_range', '%06X' % pc,
                                  '%06X' % pa))
            prev_mov_lr_pc = is_mov_lr_pc
            pc += size
            continue
        if kind == 'ldrppc':
            pa = tgt
            if MIN_CODE <= pa <= CODE_END - 4:
                v = u32(pa)
                pools.setdefault(pa, set()).add(pc)
                if pa not in pool_vals:
                    pool_vals[pa] = v
                t2, m2 = rom2file(v)
                if t2 is not None:
                    bx_targets.add((t2, m2))
                    push(t2, m2, {})
                else:
                    anomalies.append(('ldrppc_target_not_code', '%06X' % pc,
                                      '%08X' % v))
            else:
                anomalies.append(('ldrppc_out_of_range', '%06X' % pc,
                                  '%06X' % pa))
            break                               # ldr pc never falls through
        if kind == 'bl':
            t2 = (tgt & ~1) if m == 'T' else tgt
            m2 = m
            if MIN_CODE <= t2 < CODE_END:
                bl_targets.add((t2, m2))
                push(t2, m2, {})
            else:
                anomalies.append(('bl_out_of_range', '%06X' % pc,
                                  '%06X' % (t2 & 0xFFFFFF), m))
            prev_mov_lr_pc = is_mov_lr_pc
            pc += size
            continue
        if kind == 'b':
            t2 = tgt & ~1
            if MIN_CODE <= t2 < CODE_END:
                push(t2, m, dict(curmap))
            else:
                anomalies.append(('b_out_of_range', '%06X' % pc,
                                  '%06X' % (t2 & 0xFFFFFF)))
            break
        if kind == 'bcond':
            t2 = tgt & ~1
            if MIN_CODE <= t2 < CODE_END:
                push(t2, m, dict(curmap))
            else:
                anomalies.append(('bcond_out_of_range', '%06X' % pc,
                                  '%06X' % (t2 & 0xFFFFFF)))
            prev_mov_lr_pc = is_mov_lr_pc
            pc += size
            continue
        if kind == 'bx':
            rm = extra
            tag = curmap.get(rm)
            if tag is not None and tag[0] == TAG_POOL:
                _, pa, v = tag
                t2, m2 = rom2file(v)
                if t2 is not None:
                    bx_targets.add((t2, m2))
                    push(t2, m2, {})
                    if prev_mov_lr_pc:
                        # `mov lr,pc; bx rN`: mode-switching call. The
                        # target is a new function AND execution continues
                        # here after it returns.
                        insns[(pc, m)] = (size, 'bxcall', tgt, extra)
                        prev_mov_lr_pc = is_mov_lr_pc
                        pc += size
                        continue
                else:
                    anomalies.append(('bx_pool_not_code', '%06X' % pc,
                                      '%08X' % v, m, 'r%d' % rm))
            elif tag is not None and tag[0] == TAG_POP:
                pass    # `pop {..,rN}; bx rN`: ordinary return
            else:
                # Indirect branch through untracked register (callback
                # argument, IRQ trampoline @0x2A4, ...): function exit.
                anomalies.append(('bx_indirect', '%06X' % pc, m,
                                  'r%d' % rm))
            break
        if kind == 'term':
            if extra == 'bx_pc_anom':
                anomalies.append(('bx_pc', '%06X' % pc, m))
            break
        anomalies.append(('unknown_kind', '%06X' % pc, kind))
        break

print('discovery: %d insns, %d pools, %d bl-targets, %d bx-targets, %d anomalies'
      % (len(insns), len(pools), len(bl_targets), len(bx_targets),
         len(anomalies)),
      file=sys.stderr)

# --------------------------------------------------------------------------
# Phase 1b: validate call targets (forward-decode sanity), then assign
# function starts and bodies.
# --------------------------------------------------------------------------
def validate_target(t, m):
    """True if (t,m) forward-decodes to a terminator without invalid
    encodings (bounded recursive descent over not-yet-owned bytes)."""
    seen_l = set()
    wk = [(t, m)]
    n = 0
    while wk:
        pc, pm = wk.pop()
        while True:
            if (pc, pm) in seen_l:
                break
            if not (MIN_CODE <= pc < CODE_END):
                return False
            seen_l.add((pc, pm))
            n += 1
            if n > 6000:
                return False
            if pm == 'T' and (pc & 1):
                return False
            if pm == 'ARM' and (pc & 3):
                return False
            size, kind, tgt2, _ = (dec_thumb(pc) if pm == 'T'
                                   else dec_arm(pc))
            if kind == 'invalid':
                return False
            if kind in ('term',):
                break
            if kind in ('fall', 'ldrpool'):
                pc += size
                continue
            if kind == 'bl':
                pc += size
                continue
            if kind == 'b':
                pc = tgt2 & ~1
                continue
            if kind == 'bcond':
                wk.append((tgt2 & ~1, pm))
                pc += size
                continue
            # bx / bxcall / ldrppc: indirect; stop this path as "ok so far"
            break
    return True


starts = {}   # addr -> mode (tier A function starts)
for a, m in SEEDS:
    starts[a] = m
for (t, m) in sorted(bl_targets):
    if (t, m) not in insns:
        anomalies.append(('bl_target_not_decoded', '%06X' % t, m))
        continue
    if not validate_target(t, m):
        anomalies.append(('bl_target_failed_validation', '%06X' % t, m))
    if t in starts and starts[t] != m:
        anomalies.append(('mode_conflict', '%06X' % t, starts[t], m))
    else:
        starts[t] = m
for (t, m) in sorted(bx_targets):
    if (t, m) not in insns:
        anomalies.append(('bx_target_not_decoded', '%06X' % t, m))
        continue
    if not validate_target(t, m):
        anomalies.append(('bx_target_failed_validation', '%06X' % t, m))
    if t in starts and starts[t] != m:
        anomalies.append(('mode_conflict', '%06X' % t, starts[t], m))
    else:
        starts[t] = m

print('tier-A starts: %d' % len(starts), file=sys.stderr)

# --- reachability walk per start; stop at other starts (tail calls) ---
owner = {}    # (addr, mode) -> start addr
funcs = {}    # start -> {'mode': m, 'body': set((addr, mode))}
for s in sorted(starts):
    m = starts[s]
    if (s, m) not in insns:
        anomalies.append(('start_not_decoded', '%06X' % s, m))
        continue
    body = set()
    stack = [(s, m)]
    while stack:
        pc, pm = stack.pop()
        if (pc, pm) in owner or (pc, pm) in body:
            continue
        if (pc, pm) not in insns:
            continue
        owner[(pc, pm)] = s
        body.add((pc, pm))
        size, kind, tgt, _ = insns[(pc, pm)]

        def crossable(qpc):
            # Don't cross into another function start (seeds and call
            # targets are hard boundaries, even on fallthrough: e.g. the
            # IRQ dispatcher falls through into the ArmTrampoline @0x2A4,
            # which is a distinct known function).
            return qpc == s or qpc not in starts

        if kind in ('fall', 'ldrpool', 'bl', 'bxcall'):
            if crossable(pc + size):
                stack.append((pc + size, pm))
        elif kind == 'bcond':
            if crossable(pc + size):
                stack.append((pc + size, pm))
            t2 = tgt & ~1
            if crossable(t2):
                stack.append((t2, pm))
        elif kind == 'b':
            t2 = tgt & ~1
            if crossable(t2):
                stack.append((t2, pm))
        # term / bx / ldrppc: no successors
    funcs[s] = {'mode': m, 'body': body}

orphans = [k for k in insns if k not in owner]
for k in orphans:
    anomalies.append(('orphan_insn', '%06X' % k[0], k[1]))
print('tier-A functions: %d, orphans: %d' % (len(funcs), len(orphans)),
      file=sys.stderr)

# --- possible tail-called functions merged into callers ---
# `b T` where T is not a start but looks like a prologue with no fallthrough
# into it: a real function entered only via unconditional branch.
tailcall_candidates = []
for (pc, pm), (size, kind, tgt, _) in insns.items():
    if kind != 'b':
        continue
    t = tgt & ~1
    if t in starts or (t, pm) not in insns:
        continue
    h = u16(t)
    is_push = (pm == 'T' and 0xB400 <= h <= 0xB5FF)
    if not is_push:
        continue
    prev = (t - 2, pm)
    no_fall = prev not in insns or insns[prev][1] in ('term', 'b', 'bxcall')
    if no_fall:
        tailcall_candidates.append((pc, t))
print('possible tail-called (b-only) functions merged: %d'
      % len(tailcall_candidates), file=sys.stderr)

# --------------------------------------------------------------------------
# Phase 1c: reconcile v1 entries. Reached => A. Unreached + forward-clean
# (bounded recursive descent over unowned bytes, every path terminating,
# no invalid encodings) => B. Pool / mid-function / invalid => D.
# --------------------------------------------------------------------------
def parse_v1(path):
    entries = []
    seen_o = set()
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            off = int(parts[0], 16)
            if off in seen_o:      # v1 has a duplicated 0002A4 row
                continue
            seen_o.add(off)
            entries.append((off, parts[1], parts[2]))
    return entries


v1 = parse_v1(DOCS + '/func_list_v1.txt')
v1_offsets = set(o for o, _, _ in v1)
v1_by_off = {o: (t, m) for o, t, m in v1}
print('v1 entries (deduped): %d' % len(v1), file=sys.stderr)

all_pools = set(pools)   # grows as B checks confirm new pools


def fwd_check(off, mode):
    """Bounded recursive descent from (off,mode) over unowned, non-pool
    bytes. Success: every path ends in a terminator (or a resolved indirect
    jump), no invalid encodings, no region escape.
    Returns (ok, reason, info)."""
    seen_l = set()
    wk = [(off, mode, {})]
    body = set()          # (pc, mode, size)
    blt = set()
    bxt = set()
    lpools = {}
    indirect_exits = []   # pcs of unresolvable bx treated as exits
    n = 0
    while wk:
        a, m, rm0 = wk.pop()
        pc = a
        curmap = dict(rm0)
        while True:
            if (pc, m) in seen_l:
                break
            if not (MIN_CODE <= pc < CODE_END):
                return (False, 'left_region', {})
            if (pc, m) in owner:
                return (False, 'runs_into_%06X' % owner[(pc, m)], {})
            if pc in v1_offsets and pc != off:
                return (False, 'contains_v1_%06X' % pc, {})
            if (pc & ~3) in all_pools:
                return (False, 'overlaps_pool', {})
            if m == 'T' and (pc & 1):
                return (False, 'misaligned', {})
            if m == 'ARM' and (pc & 3):
                return (False, 'misaligned', {})
            seen_l.add((pc, m))
            n += 1
            if n > 30000:
                return (False, 'too_long', {})
            size, kind, tgt, extra = (dec_thumb(pc) if m == 'T'
                                      else dec_arm(pc))
            if kind == 'invalid':
                return (False, 'invalid_at_%06X' % pc, {})
            body.add((pc, m, size))
            if kind in ('fall',):
                raw = u32(pc) if m == 'ARM' else u16(pc)
                if m == 'T' and 0xBC00 <= raw <= 0xBDFF \
                        and not (raw & 0x0100):
                    for r in range(8):
                        if (raw >> r) & 1:
                            curmap[r] = (TAG_POP, None, None)
                elif m == 'ARM' and ((raw >> 25) & 7) == 4 \
                        and ((raw >> 20) & 1) and not (raw & (1 << 15)):
                    for r in range(16):
                        if (raw >> r) & 1:
                            curmap[r] = (TAG_POP, None, None)
                else:
                    clob = (thumb_clobber(raw) if m == 'T'
                            else arm_clobber(raw, kind))
                    for r in clob:
                        curmap.pop(r, None)
                pc += size
                continue
            if kind == 'ldrpool':
                pa, rd = tgt, extra
                if MIN_CODE <= pa <= CODE_END - 4:
                    v = u32(pa)
                    lpools[pa] = v
                    curmap[rd] = (TAG_POOL, pa, v)
                pc += size
                continue
            if kind == 'ldrppc':
                pa = tgt
                if MIN_CODE <= pa <= CODE_END - 4:
                    v = u32(pa)
                    lpools[pa] = v
                    t2, m2 = rom2file(v)
                    if t2 is not None:
                        bxt.add((t2, m2))
                break
            if kind == 'bl':
                t2 = (tgt & ~1) if m == 'T' else tgt
                if MIN_CODE <= t2 < CODE_END:
                    blt.add((t2, m))
                pc += size
                continue
            if kind == 'b':
                wk.append(((tgt & ~1), m, dict(curmap)))
                break
            if kind == 'bcond':
                wk.append(((tgt & ~1), m, dict(curmap)))
                pc += size
                continue
            if kind == 'bx':
                rm = extra
                tag = curmap.get(rm)
                if tag is not None and tag[0] == TAG_POOL:
                    _, pa, v = tag
                    t2, m2 = rom2file(v)
                    if t2 is None:
                        return (False, 'bx_pool_not_code', {})
                    bxt.add((t2, m2))
                    break
                if tag is not None and tag[0] == TAG_POP:
                    break           # `pop {..,rN}; bx rN`: return
                # Unresolvable indirect branch (callback argument, switch
                # dispatch, IRQ trampoline): legitimate function exit.
                # Body up to here verified clean; do not fail the check.
                indirect_exits.append(pc)
                break
            if kind == 'term':
                break
            if kind == 'bxcall':
                # should not occur here (no mov-lr-pc tracking); be safe
                pc += size
                continue
            return (False, 'unknown_kind_%s' % kind, {})
    return (True, 'ok', {'body': body, 'blt': blt, 'bxt': bxt,
                         'pools': lpools, 'indirect': indirect_exits})


tier = {}        # off -> 'A' | 'B'
tier_note = {}   # off -> note string
tier_mode = {}   # off -> 'T' | 'ARM'
demoted = []     # (off, reason)
b_info = {}      # B start -> info dict from fwd_check

for off, vtier, vmode in v1:
    m = 'T' if vmode == 'T' else 'ARM'
    if off in funcs:
        tier[off] = 'A'
        tier_mode[off] = funcs[off]['mode']
        tier_note[off] = ('v1:%s->A' % vtier) if vtier != 'A' else ''
        continue
    if (off, m) in owner:
        demoted.append((off, 'mid-function(sub_%08X)' % (BASE +
                                                        owner[(off, m)])))
        continue
    if (off & ~3) in all_pools or off in all_pools:
        demoted.append((off, 'literal-pool-word'))
        continue
    ok, reason, info = fwd_check(off, m)
    if ok:
        tier[off] = 'B'
        tier_mode[off] = m
        tier_note[off] = 'v1:%s' % vtier
        b_info[off] = info
        for (pc, pm, _s) in info['body']:
            owner[(pc, pm)] = off
        for pa, v in info['pools'].items():
            pools.setdefault(pa, set()).add(off)
            pool_vals.setdefault(pa, v)
            all_pools.add(pa)
    else:
        demoted.append((off, reason))

print('after v1 reconcile: A=%d B=%d D=%d'
      % (sum(1 for v in tier.values() if v == 'A'),
         sum(1 for v in tier.values() if v == 'B'),
         len(demoted)), file=sys.stderr)

# --- B-extra pass: follow bl/bx targets out of confirmed B functions ---
demoted_set = set(o for o, _ in demoted)
for _round in range(20):
    changed = False
    for s in sorted(b_info):
        note_parent = 'sub_%08X' % (BASE + s)
        for (t, m) in sorted(b_info[s]['blt'] | b_info[s]['bxt']):
            if t in starts or t in tier:
                continue
            if (t, m) in owner:
                anomalies.append(('B_calls_mid_function', '%06X' % s,
                                  '%06X' % t,
                                  'sub_%08X' % (BASE + owner[(t, m)])))
                continue
            if (t & ~3) in all_pools:
                anomalies.append(('B_target_is_pool', '%06X' % s,
                                  '%06X' % t))
                continue
            if t in demoted_set:
                anomalies.append(('B_target_demoted', '%06X' % s,
                                  '%06X' % t))
                continue
            if not (MIN_CODE <= t < CODE_END):
                continue
            ok, reason, info = fwd_check(t, m)
            if ok:
                tier[t] = 'B'
                tier_mode[t] = m
                tier_note[t] = 'via-B:%s' % note_parent
                b_info[t] = info
                for (pc, pm, _s) in info['body']:
                    owner[(pc, pm)] = t
                for pa, v in info['pools'].items():
                    pools.setdefault(pa, set()).add(t)
                    pool_vals.setdefault(pa, v)
                    all_pools.add(pa)
                changed = True
            else:
                anomalies.append(('B_target_failed', '%06X' % s,
                                  '%06X' % t, reason))
    if not changed:
        break

nA = sum(1 for v in tier.values() if v == 'A')
nB = sum(1 for v in tier.values() if v == 'B')
# A functions found only by descent (not in v1)
for s in sorted(funcs):
    if s not in tier:
        tier[s] = 'A'
        tier_mode[s] = funcs[s]['mode']
        tier_note[s] = 'descent-only'
nA = sum(1 for v in tier.values() if v == 'A')
print('final: A=%d B=%d D=%d (A+B=%d)' % (nA, nB, len(demoted), nA + nB),
      file=sys.stderr)

# --------------------------------------------------------------------------
# Outputs
# --------------------------------------------------------------------------
CRT0_NAMES = {0xC0: 'Init', 0xFC: 'IntrWait', 0x1BC: 'IrqDispatcher',
              0x2A4: 'ArmTrampoline', 0x2DC: 'crt0_thumb_helpers'}


def sym(off):
    return CRT0_NAMES.get(off, 'sub_%08X' % (BASE + off))


def model(off):
    if off in funcs:
        return funcs[off]['mode']
    return tier_mode.get(off, 'T')


with open(DOCS + '/func_list_v2.txt', 'w') as f:
    f.write('# MMBCC func_list v2 (tiered, recursive-descent)\n')
    f.write('# tier A: reached by recursive descent from entry (confirmed) | '
            'B: unreached but forward-disassembles cleanly (probable)\n')
    f.write('# D (below): demoted v1 entries (pool noise / mid-function / '
            'invalid)\n')
    f.write('# offset tier mode(T=Thumb/R=ARM) symbol [# note]\n')
    for off in sorted(tier):
        t = tier[off]
        m = 'R' if model(off) == 'ARM' else 'T'
        note = tier_note.get(off, '')
        line = '%06X %s %s %s' % (off, t, m, sym(off))
        if note:
            line += ' # ' + note
        f.write(line + '\n')
    f.write('# --- demoted ---\n')
    for off, reason in sorted(demoted):
        f.write('%06X D %s\n' % (off, reason))

# --- byteclass.tsv: full coverage of 0x000000-0x04FFFF, no gaps/overlaps ---
CLS_UNKNOWN, CLS_CODE, CLS_POOL, CLS_DATA = 0, 1, 2, 3
CLS_NAME = {0: 'unknown', 1: 'code', 2: 'pool', 3: 'data'}
bc = bytearray(CODE_END)          # default unknown
for i in range(0x0, 0xC0):
    bc[i] = CLS_DATA              # ROM header
pool_code_conflicts = 0
for (pc, pm) in owner:
    size = insns.get((pc, pm), (None,))[0]
    if size is None:
        # B-function bodies store (pc,pm,size) separately; handled below
        continue
    for i in range(pc, pc + size):
        bc[i] = CLS_CODE
# B bodies (their insns are not in `insns`)
for s, info in b_info.items():
    for (pc, pm, size) in info['body']:
        for i in range(pc, pc + size):
            bc[i] = CLS_CODE
for pa in all_pools:
    for i in range(pa, pa + 4):
        if 0 <= i < CODE_END:
            if bc[i] == CLS_CODE:
                pool_code_conflicts += 1
            else:
                bc[i] = CLS_POOL

with open(DOCS + '/byteclass.tsv', 'w') as f:
    f.write('# start-end class over file 0x000000-0x04FFFF (no gaps/overlaps)\n')
    f.write('# class: code | pool | data | unknown\n')
    start = 0
    cur = bc[0]
    for i in range(1, CODE_END):
        if bc[i] != cur:
            f.write('%06X-%06X %s\n' % (start, i - 1, CLS_NAME[cur]))
            start = i
            cur = bc[i]
    f.write('%06X-%06X %s\n' % (start, CODE_END - 1, CLS_NAME[cur]))

# --- stats ---
tot = CODE_END
counts = {n: 0 for n in CLS_NAME.values()}
for b in bc:
    counts[CLS_NAME[b]] += 1
print('byteclass: ' +
      ' '.join('%s=%.1f%%' % (n, 100.0 * counts[n] / tot)
                for n in ('code', 'pool', 'data', 'unknown')),
      file=sys.stderr)
print('pool/code byte conflicts: %d' % pool_code_conflicts, file=sys.stderr)

# --- v1 -> v2 transition matrix ---
trans = {}
for off, vt, _vm in v1:
    v2t = tier.get(off, 'D')
    trans[(vt, v2t)] = trans.get((vt, v2t), 0) + 1
print('v1->v2 transitions:', file=sys.stderr)
for k in sorted(trans):
    print('  %s -> %s: %d' % (k[0], k[1], trans[k]), file=sys.stderr)
print('descent-only A (not in v1): %d'
      % sum(1 for s in funcs if s not in v1_by_off), file=sys.stderr)

print('anomalies (%d):' % len(anomalies), file=sys.stderr)
from collections import Counter
ac = Counter(a[0] for a in anomalies)
for k, c in ac.most_common():
    print('  %s: %d' % (k, c), file=sys.stderr)
