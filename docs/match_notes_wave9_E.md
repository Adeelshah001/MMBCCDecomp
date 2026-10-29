# Wave 9 Batch E — Match Notes (leaves-up bulk batch 2)

5 functions matched byte-identical (old_agbcc). All verified via hardened harness
(build+diff) and confirmed in the built ROM.

## Matched

### 0x080400a8 — Scramble_400A8 (40 bytes)
u16 scramble/hash step operating on EWRAM 0x020070F0+8.
- Idioms: register pins `__asm__("r2")`/`("r1")`/`("r3")`/`("r0")` for p/h/c/v;
  opaque `__asm__ volatile("movs %0, #255" : "=r" (lo))` to get `movs r0,#255`
  (direct `=255` ignores the pin); empty barrier `__asm__ volatile("" : "+r" (t))`
  defeats the shift-combiner for the `lsls#16/lsrs#24` pair.
- Uses existing `gEwram020070F0` symbol from wave3_d.o (no new .set).

### 0x0803FD68 — Classify_3FD68 (52 bytes)
Classifier with mid-function pool (0x2004). Returns 1/4/5 for specific values,
else `xr >> 12`.
- Idioms: goto-chain for the duplicate `cmp r1,#37` (compiler would merge
  if written as if/else); `int sxr = xr;` signed copy forces `bgt` for the
  `>37` test while `>>12` stays logical (`lsrs`) on the u16.
- Disassembler pitfall: objdump misreads the mid-function pool word
  (0x00002004) as code (`movs r0,#4`); always cross-check with hexdump.

### 0x08025654 — TblGet_25654 (40 bytes)
Table lookup with bounds checking:
- idx <= 9: `p = base + 2; p += idx; return *p`
- idx 10-11: `x = idx - 10; p = base + 12; p += x; return *p`
- idx > 11: return 0
- Idiom: `u8 x = idx` kept in r1 throughout; the `(u8)(idx-10)` generates
  `lsls/lsrs #24` pair; `p = base + 2; p += idx` (not `base+2+idx`) gives
  the ROM's `adds r0,r2,#2; adds r0,r0,r1` order.

### 0x08011DD0 — TblSet_11DD0 (32 bytes)
Table set with bounds: if (1 <= x <= 7) `*(u8**)(0x02005260+8)[x] = y`.
- Idioms: empty barrier on `hdr` prevents the compiler from folding
  `0x02005260+8` into the pool (ROM has separate `ldr r0,[pc]` then
  `ldr r0,[r0,#8]`); `u32 xr = x` for the compares.
- Uses existing `gEwram02005260` symbol from wave3_d.o.
- True extent 32 bytes (26 code + 2 pad + 4 pool).

### 0x0800B308 — Check_B308 (24 bytes)
Returns 1 if `(gEwram_02004E40[4] & 15) == 0`, else 0.
- Uses existing `gEwram_02004E40` symbol from wave4_f.o.
- Mid-function pool (4 bytes at 0x800b318); true extent 24 bytes
  (16 code + 4 pool + 4 code).

## Blocked (not in this batch, for reference)
- 0x08011D68 (FlagBit_Set): gcc-2.9 register allocation — mask/val/bit land
  r0/r1/r5 vs ROM's r1/r0/r2. Best attempt in staging/wave9_E/w_l.c.
- 0x08011D34 (FlagBit_Get): prologue needs `lsrs r0,r2,#16; adds r3,r0,#0`
  but compiler emits `lsr r3,r2,#16` directly.
- 0x0800520C (BitCtl_520C): complex 6-pool placement; first part matches
  but branch pools land in wrong spots.

## Coordination
- 0x08010508, 0x08025638, 0x080258D8 were already landed by another worker;
  dropped from this batch to avoid duplication.
- 0x0800800C (Ent_SetFromTbl_800C, main agbcc) and 0x0804DFA8 (Memcpy_DFA8,
  noiw) were matched in staging but not landed per coordination update
  (focusing on the 5 unique old_agbcc functions).
