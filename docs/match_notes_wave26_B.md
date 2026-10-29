# Wave 26-B Worker Notes (blocked revisits)

Worker B, 2026-10-23. Staging: `staging/wave26_B/` (C sources, `w26b.sh`
harness adapted from w25b.sh, `addrs_sizes.txt`). Results:
`docs/wave26_B_results.tsv`. Baserom SHA-1 verified
`72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Both targets were BLOCKED in `docs/match_status.tsv` at session start
(checked 2026-10-23; none had flipped to MATCHED). **Both MATCHED.**

## MATCHED (2)

### 0x080259A4 — Tbl_SwapAndUpdate_080259A4 (100 B true extent): 0 diffs
Swaps `*(p+20+b*4)` / `*(p+20+c*4)`, then conditional StoreIdx2_25638 calls.

**True extent 100 B** (not 98): 98 code + 2-byte `00 00` pad; next function
at 0x08025A08. (The w25b 98 B figure missed the alignment pad.)

**Why asm:** The C version (w25b, 25 diffs) had the body byte-perfect except
7 localized diffs, all rooted in one cause: gcc 2.9 will NOT emit
`push {r4,r5,r6,r7,lr}` + `mov r7,r8` + `push {r7}` for the
`register u32 b7 __asm__("r7")` pin. Six C-only approaches tried, all failed:
1. clobber-reservation denying r7 (`"" : "+r"(b4) : : "r7"`) — no save.
2. dummy opaque use of incoming r7 before pin assignment — no save, worse code.
3. old_agbcc — same 25 diffs, same prologue.
4. dummy stack frame (`char dummy[16]`) — no save (disproves frame theory).
5. genuine late r7 use via working inline-asm u8 extract — no save
   (disproves live-range theory).
6. b7 live range extended across both calls via end dummy use — no save.

Side discovery: the "r7 pin + clobber" save in 0x08004998 is NOT caused by
the clobber — removing the clobber keeps `push {r4,r5,r6,r7,lr}` (11 diffs
from lost pool steering, but save persists). The trigger remains unknown;
the pin-save behavior is context-dependent and not forceable here.

**Solution:** naked function + single `__asm__ volatile` block transcribing
all 98 code bytes (w23d Script_NextOp precedent; "asm" compiler value).
`bl StoreIdx2_25638` emitted directly (extern symbol, GAS resolves; verified
`f7ff fe2b` / `f7ff fe1e` match ROM). Trailing `.short 0` gives the
`00 00` pad (gcc's default pad is `c0 46` nop — wrong bytes).
Prologue `push {r4,r5,r6,r7,lr}; mov r7,r8; push {r7}` and epilogue
`pop {r3}; mov r8,r3; pop {r4,r5,r6,r7}; pop {r0}; bx r0` byte-exact.
Verified via hardened protocol: 100/100 bytes, `cmp -l` 0 diffs,
disassembly eyeballed insn-by-insn vs ROM.

Staging: `staging/wave26_B/w26b_080259a4.c` (compiler: asm).
Callee: StoreIdx2_25638 (MATCHED, 0x08025638) via extern + stub at link.

### 0x0800E440 — ChipState_F_0800E440 (128 B true extent): 0 diffs
ChipState machine: `*(u16*)(S+24)=1`, switch on S[21]; case 0:
`S[28:31]=ChipInit_0801709C(S[37]?5:3)`, null→`*(u16*)(S+24)=0`+SetByte20(0),
else `S[21]++`; case 1: `Byte12_Gt1(*(u8**)(S+28))`→`S[24]=0`+SetByte20(0);
then `ListIterate_D568` over `0x02005270`/`0x020053C0`.

**True extent 128 B** (not 118): 118 code+epilogue, 2-byte pad at 0x800E4B6,
pool `0x02005270` at 0x800E4B8, pool `0x020053C0` at 0x800E4BC; next
function at 0x0800E4C0. (Two interior pools `0x02005130` at 0x800E454 and
0x800E480 are inside the 118.)

**Sibling-shape transfer:** 0x0800E440 is the same code shape as MATCHED
sibling ChipState_Tick_0800E748 (`mmbcc/src/w24c_0800e748.c`, 128 B, 0
diffs). Direct adaptation with ternary constants 5/3 (not 6/2) and real
`Byte12_Gt1` extern (not a stub) matched first try. Idioms reused:
- inline asm branchy ternary (`cmp %1,#0; beq 1f; movs %0,#5; b 2f;
  1: movs %0,#3; 2:`) — result lands in r0 for the `bl`, defeating gcc's
  speculative-mov codegen that forced the w25b r1-temp.
- `register u8 *S __asm__("r4")` pin gives `adds r0,r4,#0; adds r0,#37;
  ldrb r0,[r0,#0]` for S[37] (no absolute pool fold).
- `volatile u32` S+28 store+reload forces `str r0,[r4,#28]; ldr r1,[r4,#28]`.
- second base `u8 *S2 = (u8 *)0x02005130` defeats pool folding for the
  mid-function literal → `ldr r0,=0x02005130; strh r1,[r0,#24]` (r1=0, not
  a literal 0).
- `u8 z = 0` idiom in case 1: single `movs r0,#0` reused by the
  `bl SetByte20_Clear21to23_02005130`.
- `switch (S[21])` (not if/else chain) gives the compare-dispatch
  (`cmp #0; beq; cmp #1; beq; b end`) and `push {r4,lr}`.

Verified via hardened protocol: 128/128 bytes, `cmp -l` 0 diffs,
disassembly eyeballed, all four `bl` targets and all four pool words
verified as raw LE bytes (`30 51 00 02` x2, `70 52 00 02`, `c0 53 00 02`).

Staging: `staging/wave26_B/w26b_0800e440.c` (compiler: main agbcc).
Callees (all MATCHED, real names): ChipInit_0801709C (u8)→u32*,
Byte12_Gt1 (u8*)→u8, SetByte20_Clear21to23_02005130 (u8),
ListIterate_D568 (u32*). Prototypes match the w24c sibling.

## Idioms / observations for the catalog
1. **Naked-asm is the answer for compiler-impossible prologues**
   (0x080259A4): when gcc 2.9 refuses a save-set across 6+ C approaches,
   transcribe as `__attribute__((naked))` + inline asm (w23d precedent).
   Emit `bl` to externs directly; add explicit `.short 0` pads (gcc pads
   with `c0 46`, not `00 00`).
2. **The 0x08004998 r7-save is not clobber-caused:** removing its
   clobber-reservation keeps the save. Pin-save triggering is
   context-dependent; do not assume the clobber recipe transfers.
3. **Sibling-shape transfer before pinning** (0x0800E440): diff against a
   MATCHED same-family function first — the w24c sibling gave a first-try
   match where 3 waves of pin-tuning got 83 diffs.
4. **True extents need pad+trailing-pool audit:** 0x080259A4 is 100 B
   (98+2pad), 0x0800E440 is 128 B (118+2pad+8pool). Always `od` past the
   nominal end to the next function's `push`.

## Tooling
- `staging/wave26_B/w26b.sh`: hardened harness (from w25b.sh).
- `staging/wave26_B/addrs_sizes.txt`: 080259a4=100, 0800e440=128.
- `staging/wave26_B/exp*_259a4_*.c`, `min_r7*.c`: failed C-only prologue
  experiments (kept for the record).
- `staging/wave26_B/build/`: final verified build artifacts (kept).
