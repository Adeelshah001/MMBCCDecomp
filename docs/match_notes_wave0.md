# MMBCCDecomp — Wave-0 match notes (worker dfd64c3d)

Date: 2026-10-20. Baserom SHA-1 verified
`72309736f3820470c6f372d6a05ad1f16bc5a946` before any byte trust.

## Landed

### BIOS veneers — MATCHED (5/5)
`mmbcc/src/bios.c`, section `.text.bios` at `0x0804DB24`.
Idiom (calibrated): `void CpuFastSet(void *s, void *d, unsigned c){
__asm__ volatile("svc #0x0c"); }` → `df0c 4770`, byte-identical.
Svc numbers: CpuFastSet `#0x0c`, CpuSet `#0x0b`, LZ77UnCompVram `#0x12`,
LZ77UnCompWram `#0x11`, RLUnCompVram `#0x15`.

### SRAM primitives — MATCHED (5/6)
`mmbcc/src/sram.c`, section `.text.sram` at `0x0804DB38`.

- **Sram_Memcpy** (`0x0804DB38`, 36 B): MATCHED.
  `s32 n = len-1; if (!len) return; do { *dst++=*src++; n--; } while (n!=-1);`
  (no explicit src copy — that perturbs allocation).
- **Sram_WaitcntInit** (`0x0804DB5C`, 100 B): MATCHED.
- **Sram_Read** (`0x0804DBC0`, 64 B): MATCHED.
  Note arg order: loads from r0, stores to r1 → signature
  `(u8 *src, u8 *dst, u32 len)`; explicit `adds r3,r2,#0` (len copy)
  before WAITCNT is required or the compiler keeps len in r2 and takes
  r3 for the WAITCNT address.
- **Sram_VerifyWorker** (`0x0804DC30`, 100 B): MATCHED.
- **Sram_RetryWrapper** (`0x0804DC94`, 56 B): MATCHED.
  `for (tries=0; tries<=2; tries++) { Sram_Read(...);
  res=Sram_VerifyWorker(...); if (!res) break; } return res;`
  with `u8 tries` (the `(u8)` increment shows as `lsl #24 / lsr #24`).

Key C idioms that worked (agbcc `-O2 -mthumb-interwork`):
- Stack-copy loop is a `for` over a `u16` counter:
  `for (i = ((u32)Next - (u32)Cur)/2; i != 0; i--) *d++ = *s++;`
  produces the `lsl #15; b check` + shifted-counter loop exactly.
  do-while forms emit a pre-loop `lsrs` or inline check instead.
- `& ~1` thumb-bit clear: pure C folds to `and` with -2; used inline
  `bic` (`__asm__ volatile("bic %0,%1" : "+r"(addr) : "r"(1))`).
  (GAS needs `bic`, not `bics`, in Thumb16 inline asm.)
- WAITCNT: pure C yields `ldrh r1,[r2]`; reproduced the ROM's
  `ldrh r0,[r2]` / `ldr r1,=0xFFFC` via register-pinned
  `r2`/`r0` + inline `ldrh` + `v &= m; v |= 3;` with `m` assigned
  *after* the asm (assignment-before hoists the mask load ahead of
  the ldrh, swapping the two `ldr`s).
- Stack call: `register u32 code __asm__("r3")` + inline `add %0,#1`
  gives `mov r3,sp; adds r3,#1; bl _call_via_r3`. Pure-C `| 1`
  gives `orrs` (and `+ 1` flips the prologue to 5 regs).

### _call_via_rN thunks — MATCHED (8/8)
New `mmbcc/asm/thunks.s`, section `.text.thunks` at `0x0804DCCC`.
agbcc compiles Thumb indirect calls as `bl _call_via_rN`; the ROM's
thunk span (`bx rN; nop` × 8, r0–r7) is what the original link
resolved them to. Sram_WaitcntInit/VerifyWorker call via r3, i.e.
`_call_via_r3 @ 0x0804DCD8`. This is shared link infrastructure; the
per-thunk symbols stay available for coordinator assignment. The
`bl` encodings verify: `f000 f890` (WaitcntInit→0x4DCD8),
`f000 f826` (VerifyWorker→0x4DCD8).

### savedrv.s
All 11 labels removed; file is now an empty `.text.savedrv` section
stub so the ldscript slot still resolves.

### ldscript.ld (Wave-0 slots only)
Added after `.text.savedrv`:
```
. = 0x0804DB24; .text.bios   : { build/bios.o (.text.bios); }
. = 0x0804DB38; .text.sram   : { build/sram.o (.text.sram); }
. = 0x0804DCCC; .text.thunks : { build/thunks.o (.text.thunks); }
```

## BLOCKED

### Sram_VerifyCompare (`0x0804DC00`, 48 B) — 15-byte diff
Byte-level diff (ROM vs build, file offsets `0x4DC0A`, `0x4DC1A`–`0x4DC27`):
ROM lays the mismatch-return block *before* the loop-continue block:
```
cmp r1,r0 | beq +1 -> continue | subs r0,r3,#1 | b return
continue: subs r4,#1 | cmp r4,r2 | bne loop
```
Every C formulation tried (`if/else`, `goto`, `break`,
`__builtin_expect`, for-loop, old_agbcc) emits the continue block
first with `bne` to an out-of-line mismatch block (or swaps r4/r5).
This is a basic-block ordering choice in gcc 2.95 that no source
formulation tried could flip. Function is functionally identical;
kept in `src/sram.c` and documented (not reverted to asm — the
section layout can't host a single mid-slice asm function without
a dedicated slot).

## NOT ATTEMPTED (left as ASM, byte-identical)

Boot chain in `mmbcc/asm/crt0.s` — C cannot reproduce these:
- **Init** (`0x080000C0`): ARM, `msr cpsr_fc` mode switches, `bx`.
- **IntrWait** (`0x080000FC`): ARM BIOS-style interrupt wait.
- **IrqDispatcher** (`0x080001BC`): ARM, `mrs spsr`, dispatch table.
- **ArmTrampoline** (`0x080002A4`): ARM interworking trampoline.
- **Task_Switch** (`0x08000328`): Thumb tail of crt0.s —
  `mov sp,r0`, pop-all-regs incl. hi regs, `bx lr`. Not expressible
  in C (explicit SP/LR manipulation).
- **crt0_thumb_helpers** (`0x0800033C`): Thumb context-switch
  helpers (`mov sp,r2`, `mov lr,r1`, hi-reg save/restore).
crt0.s untouched; ASM status already byte-identical.

## Verification
- `make` green.
- Region `0x0804DB24`–`0x0804DCCC` (424 B): 409/424 bytes identical;
  the 15 diff bytes are all inside Sram_VerifyCompare (`0x4DC0A`,
  `0x4DC1A`–`0x4DC27`).
- Thunk span `0x0804DCCC`–`0x0804DCEC` (32 B): identical.
- `make compare` (full ROM) still fails — expected: only the Wave-0
  slice is landed.

## Behavior discoveries for the recomp track
- Sram_WaitcntInit/VerifyWorker copy the *following* slice of ROM
  (Sram_Memcpy / Sram_VerifyCompare machine code) to an IWRAM stack
  buffer and execute it there: the SRAM timing window runs from fast
  RAM, not ROM. The copy length is derived at runtime as
  `(u32)NextFunc - (u32)CurFunc` (36 B / 48 B), halfword-copied.
- The `bl 0x0804DCD8` in the old asm was agbcc's `_call_via_r3`
  (ARMv4T has no `blx`); the thunk span is compiler-generated, not
  hand-written.
- Sram_RetryWrapper = read → verify, up to 3 attempts total, returns
  the verify result (NULL on success, else mismatch pointer).
- Sram_Read's register behavior shows arg0 is the *source*:
  effective signature `(src, dst, len)`.
