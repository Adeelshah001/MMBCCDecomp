# Wave 27-D Match Notes (Worker D, bulk leaves-up + blocked revisits)

Worker D, 2026-10-23. Staging: `staging/wave27_D/` (C sources, `verify.sh`
harness adapted from w26d). Results: `docs/wave27_D_results.tsv`.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: all 22 target addresses NOT-IN-REGISTRY (unattempted). No skips.

## BLOCKED (attempted in depth)

### 0x0801C428 — ChipFxTick_0801C428 (280 B true extent, 177 diffs best)

Chip FX animation state machine. p[13]=state, p[18]=timer, p[19]=index.
Switch on p[13]: case 0 (SetBit16, init), case 1 (three ChipInit_0801B98C
calls with s16 table lookups), case 2 (MaxAssign_17, return 1), default
(return 0). Tail: p[13]++, return 0.

**True extent**: 280 B (278 code + 2 pad at 0x801c53e); next func at 0x801c540.

**What matched**: prologue (`push {r4-r7,lr}; mov r7,r8; push {r7}; sub sp,#8`),
switch dispatch (cmp/beq/bgt pattern), `(s8)--p[18]` countdown
(`ldrb; subs; strb; lsls #24; cmp`), nibble via `((u32)*q<<28)>>28` with
`"+r"` barrier (adjacent `lsls/lsrs #28`), `ldrsh` table loads, `mov r8,r2` /
`mov ip,r2` in calls 2/3, pool words (0x082268C8, 0x082268C4).

**Idioms proven by minimal test** (all confirmed):
- `if ((s8)--p[18] != 0)` → `ldrb; subs; strb; lsls #24; cmp` (no reload)
- `int a = tbl[idx*4]` (s16*) → `ldrsh` (but ONLY if the s16-ness survives;
  see blocker)
- `int idx = p[19]+1; p[19] = idx;` avoids uxtb (vs `idx = ++p[19]` which
  emits `lsls/lsrs #24`)
- `u8 n = ((u32)*q<<28)>>28` + `" +r"` barrier → adjacent shifts, no uxtb
  on u8 param passing

**Blocker (precise)**: Call-1 register allocation. ROM: `ldrsh r3,[r1,r5]`
(a1→r3, n1 stays in r2, no save). Mine: `ldrsh r2,[r1,r3]` (a1→r2,
clobbering n1, so gcc emits `mov r8,r2` before and `mov r2,r8` after).
This accounts for the 4-byte size difference (284 vs 280) and most of the
177 diffs. Tried: reordering computations (n1 before t1 load), main vs
old_agbcc (identical), removing barrier. The allocator stubbornly picks r2.

**Prototype discrepancy**: To get `ldrsh` (not `ldrh`), the caller must be
compiled with `ChipInit_0801B98C(u8,u8,u8,s16,s16,u8*)`. The MATCHED callee
has `(u8,u8,u8,u16,u16,u8*)`. With u16 params, gcc optimizes s16→u16 to
`ldrh` (only low 16 bits needed). The s16 prototype is ABI-compatible
(same 32-bit passing; callee does `(s32)(s16)d` internally), but it's a
prototype mismatch the coordinator must adjudicate.

Staged: `staging/wave27_D/w27d_0801c428_v7.c` (best), v1-v6 drafts.

### 0x08049560 — GfxSetup_08049560 (280 B true extent, 235 diffs best)

Gfx blit-request setup. u16 sum of F_080247C4(1..248), then 13
Gfx_BlitRequest / GatedDispatch calls, then `*(0x02004CE0+40)=16` and
`*(0x02004CE0+42)=((s8)p[0x46A6]<<4)+8`.

**True extent**: 280 B (278 code + 2 pad at 0x8049676).

**What matched**: the F_080247C4 accumulation loop
(`r5=0,r4=1; bl; adds; lsls/lsrs #16; adds; lsls/lsrs #24; cmp #248; bls`),
all 13 call sequences and arguments, pool words, the 0x02004CE0 tail.

**Blocker (precise)**: The prologue does TWO `strh` to `sp+4`:
`*(u16*)(sp+4)=0` then `*(u16*)(sp+4)=(u16)0xFFFF8000` (pool).
gcc eliminates `local=0` as a dead store. With `volatile u16 local`, both
stores are emitted but register allocation differs:
- ROM: `movs r1,#0; add r0,sp,#4; strh r1,[r0]` then
  `ldr r0,[pc]; adds r1,r0,#0; add r0,sp,#4; strh r1,[r0]`
- Mine: `add r1,sp,#4; movs r0,#0; strh r0,[r1]` then
  `ldr r1,[pc]; add r0,sp,#4; strh r1,[r0]`
Plus volatile adds 48 bytes overhead (328 vs 280). The `0xFFFF8000` pool
constant is required (can't be materialized via movs).

Staged: `staging/wave27_D/w27d_08049560_v1.c`.

## BLOCKED (triaged, not attempted in depth)

### 0x0800AC8C — sub_0800AC8C (296 B true extent)
Complex bit-manipulation state machine. Calls Ewram4E40_Init_0B4E4,
Clr_0800B4C8. Tests `(p[21]&15) vs (p[21]>>4)`, u16 compares, intricate
bit set/clear on p[30]/p[31], switch on low nibble (cases 1-4). Pools:
2× 0x02004E40, 0x08173064. Requires significant effort.

### 0x080203E0 — sub_080203E0 (308 B true extent)
Complex two-pass string parser. Heavy r8/r9/sl/ip usage. Calls
Node_PopAndInit (0x8017000). Parses chars via table lookup, builds two
accumulators, then a second pass with Node_PopAndInit. Requires
significant effort.

### 0x08001F1C — sub_08001F1C (334 B true extent)
SRAM state machine. Switch on p[3] (cases 0-3, default). Case 1 does a
checksum loop and calls Sram_RetryWrapper (0x804dc94). Complex.

### 0x08027400 — sub_08027400 (358 B)
Jump-table dispatch (switch on p[3], cases 0-4, default → 0x8027560).
Jump table at 0x8027424 (5 entries). Calls NewNode_08021CAC,
SelBlob_Ret, etc. Triaged only.

### 0x0803AAA8 — sub_0803AAA8 (412 B)
Bit-flag tests on u16 at pool address, builds value in r2, switch on r2
(cases 1,2,64,128), calls 0x804a378. Triaged only.

## BLOCKED (not attempted — time)

0x08002070, 0x0804d8a8, 0x08034f2c, 0x08007840, 0x080176ac, 0x08025ec8,
0x0804b124, 0x08009c7c, 0x080099fc, 0x0801e208, 0x0800f4f8, 0x0800ef40,
0x08046df8, 0x080471d8, 0x08008bc8.
All registry-checked CLEAR before starting.

## Blocked revisit candidates (identified, not fully attempted)

### 0x08016E84 — F_08016E84 (114 B, w25d BLOCKED, 49 diffs)
w25d used inline-asm `ldrsh` (believing "agbcc never emits ldrsh").
w26d PROVED natural `ldrsh` works for `s16 v = tbl[i]` when the value is
used as s16. This function does `ldrsh r1,[r0,r3]` / `ldrsh r2,[r0,r3]`
then calls 0x80174c4 (which takes s16 params per w26d's sub_080174CC).
**Revisit angle**: replace inline-asm with natural `s16` locals; the s16
params should preserve ldrsh without the temp-reg allocation issues.

### 0x080224E4 / 0x08021B3C — BlendCopy (206 B, w26d BLOCKED, ~40 diffs)
Register allocation rotation: gcc insists srcA→r9, srcB→r8, mask→ip;
ROM has srcA→r8, srcB→ip, mask→r9. w26d tried -O1/-Os, reordering.
**Revisit angle**: clobber-reservation idiom (w21a) to deny specific
registers during the loop body, or the r7-pin + clobber combo (w25b).

### 0x0801C428 — ChipFxTick_0801C428 (my own BLOCKED, 177 diffs)
**Revisit angle**: The call-1 r2-vs-r3 allocation might yield to
clobber-reservation denying r2 at the ldrsh (but n1 lives in r2 — catch-22).
Or the coordinator may accept the s16-prototype version if the 4-byte
size delta can be closed.

## Idioms discovered / confirmed

1. **`int idx = p[19]+1; p[19] = idx;` avoids uxtb**: `idx = ++p[19]` on a u8
   emits `lsls/lsrs #24` (zero-extend) because the `++` result is truncated
   to u8. The two-statement form keeps the full int value in the register.
2. **`(s8)--p[18]` countdown**: `ldrb; subs; strb; lsls #24; cmp` with no
   reload — the decremented value is tested directly as s8.
3. **Barrier-pinned nibble**: `u8 n = ((u32)*q<<28)>>28;` +
   `__asm__ volatile("" : "+r"(n))` gives adjacent `lsls/lsrs #28` and no
   uxtb when passing as u8 param.
4. **s16 locals force ldrsh ONLY if s16-ness survives to use**: If the s16
   is passed as u16 param, gcc optimizes to `ldrh`. The caller must see s16
   params (or the value must be used in a signed context).
5. **Dead-store elimination kills `local=0`**: When a u16 local is assigned
   0 then overwritten with a pool constant, gcc eliminates the 0 store.
   `volatile` forces it but changes register allocation.

## Tooling
- `staging/wave27_D/verify.sh` — hardened harness (from w26d).
- `staging/wave27_D/*_rom.bin` — ROM extracts for disassembly.
- `staging/wave27_D/mint*.c` — minimal idiom tests (kept).
- `staging/wave27_D/w27d_0801c428_v*.c` — 7 drafts for 0x0801c428.
- Staging dir left intact.
