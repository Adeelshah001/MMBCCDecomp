# Wave 9 Worker A (TAG=A) — Match Notes

Worker: Wave 9 near-miss closers (TAG=A). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}`; `arm-none-eabi-as/ld`
present at start, VANISHED mid-task (VM quirk, as in Wave 8).
Harness: `staging/wave9_A/build.sh` (hardened v3: custom ld script,
non-empty assertions, offset = addr - 0x08000000, full extent incl pools).
Staging (persistent): `~/workspace/mmbcc-decomp/staging/wave9_A/`
(/tmp/wave9_A was cleaned by the system mid-task; harness+refs recreated).
Results: `docs/wave9_A_results.tsv`.

## MATCHED (1)

### ObjInit_1D3C0 @0x0801D3C0 (164 B, old_agbcc, 0 diffs) — LANDED

Wave 8 left this at 4 diffs: else-branch prologue had `movs r1,#0` BEFORE
`movs r0,#1`; ROM has `movs r0,#1` BEFORE `movs r1,#0`.

**Root cause:** old_agbcc's scheduler emits `mov #0` before `mov #1`
regardless of declaration order (probed: `int one=1; int zero=0;` still
emits zero-first). The tie-break is not declaration order, use order, or
register number — it is a systematic scheduler preference.

**Fix (two parts):**
1. **Single volatile asm** emitting both movs in ROM order:
   `__asm__ volatile("movs %0, #1\n\tmovs %1, #0" : "=l"(one), "=l"(zero));`
   with `s[10] |= one;` and `*(u32*)(p+28) = zero;` using the asm-defined
   vars. This defeats the scheduler's zero-first preference.
2. **Memory barrier defeats combiner fold:** The asm caused the combiner to
   fold `p=s; p+=0x50; *(p+28)` into `*(s+108)` (`str r1,[r4,#108]` instead
   of ROM's `adds r0,#80; str r1,[r0,#28]`). Adding
   `__asm__ volatile("" ::: "memory")` between `p += 0x50` and the store
   prevents the fold (verified via RTL dump: combiner deleted the
   `p=s+80` insn in the folding variant, kept it with the barrier).

**Idioms discovered:**
- **Ordered materialization via single asm:** When the scheduler insists on
  a wrong order for independent `movs` immediates, emit them in one
  volatile asm block. The compiler respects the asm's internal order.
- **Memory barrier defeats combiner address fold:** An empty volatile asm
  with `"memory"` clobber between address computation and use prevents the
  combiner from folding `base+off1+off2` into `base+(off1+off2)`, even when
  the two-step C idiom alone doesn't (the asm defining vars can enable the
  fold by changing dataflow).

**Landing:** `mmbcc/src/wave9_a_old.c` (old_agbcc), section
`.text.w9a_0801d3c0`; Makefile SRCS_C + override rule; ldscript slot at
`0x0801d3c0`. Full build green; slot byte-identical (164/164) in built ROM.
Externs `ChipSlot_Setup`/`ChipSlot_IncUse` (matched, no .set needed).

## BLOCKED (2)

### Obj_AddEntry @0x0802D7A0 (340 B) — regalloc diverges

**Status of mask (FIXED):** The BLK-A key works. Shared `int m3=-3` /
`int p3=3` across two sites each gives:
- `movs rX,#3; negs rX,rX` (m3) / `movs rY,#3` (p3)
- `adds r0,rX,#0` copy at FIRST use of each mask
- Full 32-bit `ands r0,r6` (dest r0), not narrowed `& 253`
This fixes the wave2/wave5 `& ~2` narrowing blocker.

**Remaining (regalloc, ~300 diffs):** 10-param function; global allocation
differs.

ROM homes:
- work->r7, a1->r6, a2->spill[sp,#0], a3->ip, a4->spill[sp,#4],
  a5->spill[sp,#8], a6->spill[sp,#12], a7->sl, a8->r8, a9->r9
- m3(-3)->r3, p3(3)->r2; `sub sp,#24`

Mine (old_agbcc, best):
- work->r5, a1->r7, a2->spill, a3->ip, a4->spill, a5->spill,
  a6->sl, a7->spill[sp,#16], a8->spill[sp,#20], a9->r9
- m3->r1 (or r2 with late assignment), p3->r2; `sub sp,#24`

**Angles tried:**
1. **Late mask assignment** (wave6_blkA idiom): Moved `m3=-3` to Block A,
   `p3=3` to Block B (instead of function top). Result: m3 moved r1->r2,
   but ROM wants r3. p3 stayed r2. Did not fix.
2. **Pinning** (r7/r6/sl/r8/r9 for work/a1/a7/a8/a9): Disrupts allocation,
   +20 B (360 vs 340), more spills. Not viable.
3. **a4 type correction:** Changed `u16 a4` to `u8 a4` (ROM does
   `lsls #24; lsrs #24`, not `#16`). Fixed the prologue extend, but not
   the allocation.

**Why it's hard:** The 10 params have overlapping live ranges. The
allocator must choose 3 of {a5,a6,a7,a8,a9} for {sl,r8,r9} and spill 2.
ROM chooses a7,a8,a9; mine chooses a6,a9 (plus spills). The choice depends
on global heuristics (spill costs, live range splitting) that small tweaks
don't control. The mask regs (m3->r3 vs r1) are similarly global.

**Next angles (for future worker):** Try declaring params in different
order; try splitting the function (if semantics allow); try main agbcc
with a formulation tuned for its allocator; or accept that this needs a
different compiler version.

### ComputeFields @0x0804CFD4 (180 B) — 100 B matching, Block 2 blocked

**Progress:** First 100 bytes (Block 1) match with 0 diffs.

**Fixed via:**
1. **pp->r2:** `register u8 *pp __asm__("r2");` with opaque
   `__asm__ volatile("add %0, %1, #0" : "=r"(pp) : "r"(p));`
   (Direct `=p` init ignores pin per wave8_S idiom; `adds` mnemonic
   rejected by GAS in inline asm, use `add`.)
2. **Load order p[19],p[18]:** Compiler reorders loads by address. Fixed
   via opaque `ldrb` inits:
   `__asm__ volatile("ldrb %0, [%1, #19]" : "=r"(v19) : "r"(pp));`
   with `register u32 v19 __asm__("r3");` (u32, not u8, to avoid extra
   zero-extends).
3. **v19->r3, v18->r1, adds-copy:** `register u32 v18 __asm__("r1");`
   with opaque ldrb; then
   `__asm__ volatile("add %0, %1, #0" : "=r"(t) : "r"(v19));`
   where `t` is `register u32 __asm__("r0")`, giving ROM's
   `adds r0,r3,#0` before `muls r0,r1`.
4. **rv4->r4 direct:** `register u32 rv4 __asm__("r4");` with opaque
   `ldrb`, giving ROM's `ldrb r4,[r2,#24]` without the extra
   `adds r4,r0,#0` copy.

**Remaining (Block 2, byte 100+):** 
ROM:
```
804d038: ldrb r1,[r2,#0]   ; p[0] -> r1
804d03a: movs r0,#4
804d03c: ands r0,r1
804d03e: adds r3,r1,#0     ; save p[0] to r3
804d040: cmp r0,#0
```
Mine loads p[0] to r4 (not r1), does `mov r0,#4` BEFORE ldrb (not after),
and uses `add` (not `adds`). The `adds r3,r1,#0` save-for-later needs
the same opaque-copy treatment, but the scheduler order (ldrb before mov)
and the r1 allocation need work.

**Blocked by:** Toolchain outage (`arm-none-eabi-as` vanished, VM quirk).
Could not verify further variants. Staging at
`staging/wave9_A/cfd4_v9_r4pin.c` (100 B matching, 184 B total).

**Next angles:** Pin b0->r1 with opaque ldrb; force ldrb-before-mov via
barrier or dependency; opaque `adds r3,r1,#0` copy after ands.

## Idioms catalog additions

1. **Ordered materialization via single asm:** One volatile asm emitting
   multiple `movs` in the desired order defeats scheduler reordering of
   independent immediates.
2. **Memory barrier vs combiner fold:** `__asm__ volatile("" ::: "memory")`
   between address computation and memory use prevents the combiner from
   folding `base+off1+off2`, even when the asm defining the vars enables
   the fold.
3. **Opaque ldrb init for pinned regs:** 
   `register u32 v __asm__("rX"); __asm__ volatile("ldrb %0, [%1, #N]" : "=r"(v) : "r"(base));`
   forces both the register and the load order (defeats address-order
   scheduling). Use u32 (not u8) to avoid extra zero-extends.
4. **`add` not `adds` in inline asm:** GAS rejects `adds Rd,Rn,#imm` in
   inline asm (Thumb16 mode); use `add`. The encoding is identical to
   ROM's `adds`.

## Environment note

`arm-none-eabi-as`/`ld` vanished from `/usr/bin` mid-task (VM quirk, same
as Wave 8). `agbcc` still works. Could not assemble/link for verification
after the outage. The MATCHED ObjInit_1D3C0 was fully verified (0 diffs,
landed, build green) BEFORE the outage.
