# Wave 24-D Worker Notes (blocked revisits)

Worker D, 2026-10-23. Staging: `staging/wave24_D/` (C sources, `w24d.sh`
harness, `fix_08002ef4.py`, `addrs_sizes.txt`). Results:
`docs/wave24_D_results.tsv`. Baserom SHA-1 verified
`72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

All targets were still BLOCKED in `docs/match_status.tsv` at session start
(checked 2026-10-23; none had flipped to MATCHED).

## MATCHED (1)

### 0x08002EF4 — F_08002EF4 (48 B true extent incl. pool): 0 diffs
Init stub: calls `F_0804C630` (unmatched; stubbed at 0x0804C631), then
`*(u32*)0x02003244 = (u16)0xAA`, `*(u8*)0x02000818 = 0`,
`*(u8*)0x02000819 = 0`. True extent is 48 B (func_stats said 30, but the
4-word pool at 0x08002F14–0x08002F23 belongs to this section; next function
starts at 0x08002F24).

Two pool-forcing problems, both unreachable in natural C (gcc folds every
form to `movs`/`adds`):
1. `mov r0,#0xAA` must be `ldr r0,=0xAA` + `lsls/lsrs r0,r0,#16`.
2. `add r0,r0,#1` (for 0x02000819) must be a separate `ldr r0,=0x02000819`.

Fixup `staging/wave24_D/fix_08002ef4.py` (Makefile sed-rule equivalent, per
the w23a 0x08002CB0 precedent which landed with a Makefile sed rule):
- `mov r0,#170` → `ldr r0,.LAA_pool` + `.short 0x0400,0x0C00`
  (lsls/lsrs r0,r0,#16; GAS 2.42 rejects the mnemonics in divided syntax,
  `.short` is the established workaround)
- `ldr r0,.L3+4` → `ldr r0,.L818_pool`
- `add r0,r0,#1` → `ldr r0,.L819_pool`
- pool: `.word 170` inserted after 33567300; 33556504 split into labeled
  `.L818_pool`/`.L819_pool`.

Result pool (raw): `44 32 00 02 | aa 00 00 00 | 18 08 00 02 | 19 08 00 02`
= [0x02003244, 0xAA, 0x02000818, 0x02000819] — matches ROM exactly.
Verified via hardened protocol: 48/48 bytes, `cmp -l` 0 diffs, disassembly
eyeballed, pool constants verified as raw LE bytes. Harness supports the
fixup via `FIXUP` env var (`w24d.sh`).

Staging: `staging/wave24_D/w24d_08002ef4.c`, `fix_08002ef4.py`.
Callee `F_0804C630` is unmatched (registry has no row) — needs `.set` stub
at land time.

## BLOCKED (8)

### 0x0804AF20 — F_0804AF20 (112 B): 36 diffs (best)
**KEY CORRECTION:** the tail stores are `strh r7,[r4,#20]` (=a) and
`strh r6,[r4,#22]` (=c). Wave-23's "correction" (=b/=c) misread `0x82a7`:
bit layout is L=bit11, imm5=bits[10:6], Rn=bits[5:3], Rt=bits[2:0] →
Rt=r7=a, not r2=b. The p7/p10 candidates were built on the wrong semantic.

**Live-range correction:** b is NOT live across 4 calls. b is used only in
`Sub200((u8)b)` (1st call); the tail uses a and c. So b dies at the first
`bl` — the "b in r2 across 4 calls" wall from w23a was based on the wrong
tail. (Confirmed: `-Os` without pins already puts b in r2.)

Best C (`w24d_0804af20_best.c`, main agbcc -O2 + `register u32 ld
__asm__("r8") = d`): a→r7, c→r6, d→r8 correct; r8 save/restore correct;
**tail bytes 54–112 match exactly**. Remaining gaps:
- Prologue order: ROM does `ldr r4,[sp,#24]` (d) FIRST, then a/b/c extends,
  `mov r8,r4`, then `adds r4,r0,#0` (p). gcc (main AND old_agbcc, -O2/-O1/
  -Os) always emits `adds r4,r0,#0` (p) first. Unreachable across 10+
  variants: explicit `u16 ld=d` first, local-init reorder, scoped r4 pin
  (optimized away), empty-asm first-use forcing, -O1/-Os. Smells like
  compiler-vintage, but old_agbcc does NOT fix it (same 69 diffs).
- b→r5 vs ROM r2 (in-place extend).
- Loop: zero in r2 vs r3, 0x10000 increment in r3 vs r5 (hoisted before
  loop in mine, materialized inside loop in ROM).

Staging best: `staging/wave24_D/w24d_0804af20_best.c` (36 diffs).
Also tried: `-Os` (a/b/c regs correct without pins, but d→r5 not r8);
`-Os`+r8 pin (worse: a→r6,c→r5); do-while loop (no change).

### 0x08004998 — HexFormat_08004998 (102 B): 47 diffs (best)
Hex-formats u32 p into a 16-byte stack buffer (d digits), calls
`F_080048B4(buf,b,c)`. ROM: p→r4, b→ip(r12), c→r7, pool 0xFFFF0000→r1.

Progress: clobber-reservation `__asm__ volatile("" : "+r"(d16) : : "r7")`
denies r7 at the pool load → pool goes to **r1 (ROM-correct)**.
b→ip and p→r4 already correct in clean C.

BLOCKED (catch-22): c stays in r8 (ROM r7). Denying r7 (to fix the pool)
prevents c→r7 because c is live across the clobber. Denying r8 instead
scrambles c→r9 (worse prologue). Pinning c to r7 miscompiles per w22d
(and the brief: never pin r7). The r1-pool-pin (`register u32 poolr
__asm__("r1")`) is ignored by gcc (folds the constant).

Staging best: `staging/wave24_D/w24d_08004998_best.c` (47 diffs).

### 0x080259A4 — Tbl_SwapAndUpdate_080259A4 (98 B): 76 diffs (best)
Swaps `*(p+20+b*4)` / `*(p+20+c*4)`, then conditional `StoreIdx2_25638`
calls. ROM uses 5 callee-saved regs: r4 (swap temp), r5 (p), r6 (c*4),
r7 (b), r8 (c).

Progress: three pins — `b→r7`, `c→r8`, `c4→r6` — achieve p→r5, b→r7,
c→r8, c4→r6 all correct (r7 pin did NOT miscompile here). Key structural
find: ROM keeps `c*4` in r6 (computed after the swap load, from r8);
reordering C to compute b*4/ab before c4 was essential.

BLOCKED: temp regs for b*4/ab differ (mine r0/r2, ROM r2/r3); 96 vs 98
bytes (2-byte shortfall, cause not chased). The 5-reg allocation is
partially achieved but temp selection resists.

Staging best: `staging/wave24_D/w24d_080259a4_best.c` (76 diffs).

### 0x08026740 — Task_Clock_08026740 (112 B): 24 diffs (best, was 58)
Clock task. **Branch inversion fixed:** the two `> 58` branches must have
if/else swapped — `if (S[17] <= 58) { S[17]++; } else { /* hours */ }` —
so gcc emits `bhi` (ROM) instead of `bls`. 58→24 diffs.

BLOCKED: `ldrh r0,[r4,#18]` vs ROM `ldrh r2,[r4,#18]` for the hours
compare (bytes 57–60); 8 extra bytes at end (pool for 0x0822D8EC placed
at 0x80267B4 with padding vs ROM 0x80267B0). `u16 hrs` temp did not move
the load to r2. Same 24 diffs under old_agbcc.

Staging best: `staging/wave24_D/w24d_08026740.c` (24 diffs).

### 0x0800E440 — ChipState_F_0800E440 (118 B): 87 diffs (best, was 109)
ChipState machine. **Progress:** `switch (S[21])` (instead of if/else
chain) gets `push {r4,lr}` (was `{r4,r5,lr}`) and the `beq`/`bhi`
dispatch branches correct.

BLOCKED: ternary `(S[37]!=0)?5:3` still compiles to `mov r1,#3; cmp;
beq; mov r1,#5` + pool load for S+37 (0x02005155), vs ROM's `cmp; beq→
movs r0,#3; movs r0,#5` with `adds r0,r4,#0; adds r0,#37`. gcc folds
`S+37` to an absolute address and pool-loads it; `s37` temp and if/else
forms did not change codegen. 87 diffs across the body.

Staging best: `staging/wave24_D/w24d_0800e440.c` (87 diffs).
Callees: ChipInit_0801709C, Byte12_Gt1_080170c4, SetByte20_Clear21to23_02005130
(0x0800E1F0), ListIterate_D568 — check registry for real names at land time.

### 0x08011AC8 — Sub_08011AC8 (154 B): 122 diffs (verified)
Verified the w17d base (`staging/wave17_D/b_08011ac8.c`): 122 diffs.
3-state machine, nested branches diverge. No new angles tried (time).

### 0x0800CC24 — InitRegs_0CC24 (78 B): 69 diffs (verified)
Verified the w14b v2 (`staging/wave14_B/w14b_0800cc24_v2.c`): 69 diffs
(was 70). r7=0x10000 idiom not cracked. No new angles tried (time).

### 0x08002960 — BlendMasked_2960 (78 B): 73 diffs (verified)
Verified the w14b v1 (`staging/wave14_B/w14b_08002960_v1.c`): 73 diffs
(was 74), but 120 vs 78 bytes — the C is structurally too big. In-loop
spill not cracked. No new angles tried (time).

## Idioms / observations for the catalog
1. **Tail-correction before register work:** 0x0804AF20's "allocator wall"
   evaporated once the tail was read correctly (b dies at 1st call).
   Always re-verify the disassembly reading before fighting the allocator.
2. **Clobber-reservation for pool steering** (0x08004998): denying r7 at
   the pool load moved the pool to r1 — a new use of the w21a idiom.
   Catch-22 documented when the denied reg is also the wanted home.
3. **r7 pin is not always poison** (0x080259A4): `register u32 b7
   __asm__("r7")` worked fine here, contrary to the blanket "never pin
   r7" rule — the miscompile may be context-dependent.
4. **Branch inversion via if/else swap** (0x08026740): when gcc inverts
   `bhi`→`bls`, swapping the if/else bodies (changing `>` to `<=`)
   restores the ROM's branch.
5. **Switch beats if/else chain for dispatch** (0x0800E440): reduced
   callee-saved pressure from {r4,r5} to {r4}.
6. **True extents:** 0x08002EF4's section is 48 B (not 30); always verify
   pool inclusion via disassembly, not func_stats.

## Tooling
- `staging/wave24_D/w24d.sh`: hardened harness (adapted from w23a.sh)
  with `FIXUP` env hook (python script applied to .s between agbcc and as)
  and corrected `addrs_sizes.txt` (0x08002EF4: 48).
- `staging/wave24_D/fix_08002ef4.py`: the verified post-agbcc fixup.
- `staging/wave24_D/build/`: build artifacts (kept, not deleted).
- Binutils was missing at session start (known PATH outage); reinstalled
  via `sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb`.
