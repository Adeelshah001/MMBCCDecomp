# Wave 21 Worker C — Match Notes (land 0x08047CC0 + blocked revisits)

## Landed: 0x08047CC0 — sub_08047CC0 (36 B, main agbcc)

Staged source: `staging/wave20_C/final/w20c_08047cc0.c` (Wave-20 worker C,
dead-reg reuse idiom: `register u32 off __asm__("r3") = 0x46B4;` then
`off = 0;` before the store, hoisting `movs r3,#0` above the first `strb`).
Wave-20 left it unlanded because its callees
`EntryMgr_Teardown @0x08004F18` / `EntryMgr_Setup @0x08004F80` were not in
the build; both are now MATCHED in `src/entrymgr.c` (old_agbcc, wave 2).

### 36 B vs 32 B discrepancy — resolved from the ROM
- The wave-4 BLOCKED registry row and `staging/wave20_C/addrs_sizes.txt`
  both said **32 B**; that missed the 4-byte literal pool.
- ROM bytes at 0x47CC0–0x47CE3:
  `00 b5 02 7b 06 4b c1 18 00 23 0a 70 01 21 01 71 43 71` (16 B code)
  `bd f7 21 f9 bd f7 53 f9 00 20 02 bc 08 47` (16 B code, incl. two `bl`s)
  `b4 46 00 00` (pool word 0x46B4 @ 0x47CE0).
  Next function `sub_08047CE4` starts at 0x08047CE4 (func_list_v2.txt).
- True extent: **36 B = 32 code + 4 pool**. The wave-20 standalone harness
  compared only 32 B (it read the stale size), so its "0-diff" did not cover
  the pool. The landed comment in the staged file header ("32 B") was
  corrected to 36 B (comment-only change; codegen unaffected).

### Hardened re-verification (Wave 21, staging/wave21_C/w21.sh)
- Fresh compile: `cpp -I mmbcc/include` → main agbcc
  `-O2 -mthumb-interwork -Wimplicit -Wparentheses` →
  `as -mthumb -mcpu=arm7tdmi`; linked at true address 0x08047CC0 with
  EntryMgr externs as absolute symbols (stubs.s).
- `.o` / `.elf` / `.bin` all non-empty; `.bin` exactly 36 B.
- ROM extract: file offset 0x47CC0, 36 B. **0 diffs.**
- Disassembly of the 36 B matches the ROM decode byte-for-byte
  (`push {lr}; ldrb r2,[r0,#12]; ldr r3,[pc,#24]; adds r1,r0,r3;`
  `movs r3,#0; strb r2,[r1]; movs r1,#1; strb r1,[r0,#4];`
  `strb r3,[r0,#5]; bl 0x08004F18; bl 0x08004F80; movs r0,#0;`
  `pop {r1}; bx r1; .word 0x46B4`).

### Landing
- `mmbcc/src/w20c_08047cc0.c` (staged content, header comment fixed to 36 B).
- Makefile: `SRCS_C` += `src/w20c_08047cc0.c`; per-file rule (main agbcc,
  same shape as the other w20c rules).
- ldscript: `. = 0x08047cc0; .text.w20c_08047cc0 : { build/w20c_08047cc0.o (.text.w20c_08047cc0); } /* sub_08047CC0 (36 B) */`
- Hygiene: externs `EntryMgr_Teardown/Setup` resolve from `build/entrymgr.o`
  (already in build) — no `.set` needed, none added.
- Full `make clean all`: green (exit 0).
- Post-build verification in `mmbcc/mmbcc.gba`:
  - region 0x47CC0–0x47CE4: **0-diff vs baserom**;
  - neighbor before: `Dispatch_08233C54_4 @0x08047CA4` (28 B) unchanged, 0-diff;
  - neighbor after: `Task_47CE4 @0x08047CE4` still BLOCKED (fill, as before);
  - ELF section `.text.w20c_08047cc0`: VMA 0x08047CC0, size 0x24 — ends
    exactly at 0x08047CE4, no overlap with neighbors.
- Registry: new MATCHED row appended (append-only; supersedes the wave-4
  BLOCKED row for this address).

**Count: 719 / 1674 C-matched** (+1), 732 byte-identical total.

## Blocked revisits (Task 2)

Idioms in play (Wave-20 A/B/C/D): split-shift interleave via dual barriers;
scoped register-denial; early-zero materialization; index-as-pointer adds
ordering; u32 pin to pushed callee-saved reg is safe (r7 the only
miscompile); volatile forces redundant loads; dead-register reuse via
pin+reassign; natural u8 temp; pin-one-forces-another; mid-function pool via
`.short nop`; pinned base prevents folding; divided-syntax add ordering.

### MATCHED: 0x08043630 — F_08043630 (76 B, main agbcc)

Wave-15 near-miss (2-byte allocator diff: `movs r0,#0; strb r0` vs ROM
`movs r3,#0; strb r3`). True extent 76 B = 62 code + 2 pad + 12 pool
(3 pools @0x43670/0x43674/0x43678: 0x02004830, 0x26A, 0x26B); next function
at 0x0804367C.

Attempts: v1 (pin o2->r3 + barriers) miscompiled — pin pressure gave
`push {r4,r5,lr}` and dropped the 0x26A init (pinning pathology). v2
(natural C + early-zero idiom) matched everything except a 4-byte
`lsls/lsrs` u8-return truncation. v3: declaring the callee as
`u32 CountNonzeroStride(u8 *s)` (actual: u8) suppresses the zero-extend —
**0 diffs over full 76 B**.

Winning shape:
```c
u32 y; u8 *base; u8 *p; u8 *q; u8 z;
sub_08005A9C(8);
y = CountNonzeroStride(s);          /* u32 decl: no return extend */
base = (u8 *)0x02004830;
__asm__ volatile("" : "+r" (base)); /* barrier defeats the 3-pool fold */
p = base + 0x26A;
z = 0;                              /* early-zero: r0=y live, r3 dead -> movs r3,#0 */
*p = (u8)y;
q = base + 0x26B;
*q = z;
sub_08042E14(s); sub_08043430(s); Gfx_Blit3(s); sub_08045838(s);
```
Produces ROM's `ldr r1; ldr r3; adds r2,r1,r3; movs r3,#0; strb r0,[r2];
ldr r0; adds r1,r1,r0; strb r3,[r1]` exactly, including the
`pop {r4}; pop {r0}; bx r0` epilogue.

Landing: `mmbcc/src/w21c_08043630.c`, Makefile SRCS_C + per-file rule
(main agbcc), ldscript slot at 0x08043630. Unmatched callees via
file-local `.globl`/`.set` + `.thumb_func` (0x08005A9C/0x08042E14/
0x08043430/0x08045838); CountNonzeroStride/Gfx_Blit3 resolve from the
build. NOTE: `sub_08005A9C` is `.set`-defined in `src/wave7_b.c` but as a
LOCAL absolute symbol (lowercase `a` in nm) — invisible cross-object, so
the file-local `.set` is required (caught at link by W21-A, drive-by fix;
zero code change). Full build green; region 0x43630–0x4367C 0-diff vs
baserom in `mmbcc/mmbcc.gba`.

### MATCHED: 0x08001E30 — Sram_08001E30 (66 B code, main agbcc + FIXALIGN1)

Wave-6 L4 blocker (37-byte diff): "ROM holds `a` in r6 and materialized
`0xE0000000` in r5 across two Sram_RetryWrapper calls; natural C puts `a`
in r5 and recomputes the base per call."

ROM shape (68 B span 0x1E30–0x1E74; 66 code + 2 `00` fill):
`push {r4,r5,r6,lr}; sub sp,#4; lsls r0,#24; lsrs r6,r0,#24` (a→r6);
`movs r0,#0; str r0,[sp]` (u32 tmp=0); `cmp r6,#1; bhi fail`;
`lsls r1,r6,#13; movs r5,#0xE0; lsls r5,#20; adds r1,r1,r5` (base→r5);
two `Sram_RetryWrapper(sp, addr, 4)` calls (0x0804DC94); `orrs r4,r0`;
`b` / fail: `movs r0,#1; negs r0,r0` (-1); `add sp,#4;
pop {r4,r5,r6}; pop {r1}; bx r1`.

Attempts: v1 natural C → au in r5, base rematerialized in r0 per call.
v2 (pin au->r6 only) → extend/base-shift correct but base still remat.
v3 (pin au+base) → 18 diffs: base init hoisted above bhi, adds operand
order swapped, `adds r6,#2` clobbered au. v4/v5 (barrier variants) →
register swaps. v6 (pin au->r6 + st->r4 + base->r5, late base init,
flipped operands) → 8 diffs: only the shift/base-init ORDER
(`lsls r1,r6,#13` must precede `movs r5; lsls r5`). v7 (+ sh1 temp hoists
the shift above base init) → 2 diffs: trailing `c046` vs ROM `0000`
(inter-function fill). FIXALIGN1 → **0 diffs over 66 B code**.

Winning shape:
```c
register u32 au __asm__("r6") = a;
u32 tmp = 0;
register int st __asm__("r4");
u32 sh1;
if (au > 1) return -1;
sh1 = au << 13;
{
    register u32 base __asm__("r5") = ((u32)0xE0 << 20);
    st = (int)Sram_RetryWrapper((u8 *)&tmp, (u8 *)(sh1 + base), 4);
    st |= (int)Sram_RetryWrapper((u8 *)&tmp, (u8 *)(((au + 2) << 13) + base), 4);
}
return st;
```
Pinning a u32 to pushed callee-saved r6 did NOT suppress the
`lsls/lsrs` zero-extend (the w19 suppression was u8→u8 specific).
`0xE0<<20` gives ROM's `movs r5,#0xE0; lsls r5,#20` materialization.

Landing: `mmbcc/src/w21c_08001e30.c`, Makefile SRCS_C + per-file rule
(main agbcc + FIXALIGN1 sed), ldscript slot at 0x08001E30. Callee
`Sram_RetryWrapper@0x0804DC94` resolves from `src/sram.c` (no .set).
Full build green; region 0x1E30–0x1E74 0-diff vs baserom (66 B section +
2 B 00 objcopy gap fill).

**Count: 721 / 1674 C-matched** (+3 total: 47cc0, 43630, 01e30), 734
byte-identical total.

### BLOCKED (still): 0x0804BDE0 — ListWalk_0804BDE0 (48 B)

Progress: `orrs r1,r0` operand order SOLVED via explicit `u8 v` variable
(v3: `u8 v = *node; if (v & 0xC7) { v |= 0x40; *node = v; }` gives
`ldrb r1,[r4]; movs r0,#0xC7; ...; movs r0,#0x40; orrs r1,r0;
strb r1,[r4]`). Constant hoisting (v1: `push {r4-r7,lr}` with 0xC7/0x40
in r7/r6) defeated by avoiding the `u32 v` temp.

Remaining wall (4 B): `ands r0,r1; cmp r0,#0` vs ROM `tst r0,r1`.
No `tst` precedent exists in any matched object in the project; wave-15
already exhausted formulations (temp u8, u32 cast, explicit `!= 0`,
swapped operands, old_agbcc). The `tst` instruction resists all C
patterns tried — likely needs inline-asm or a different compiler vintage.
Best: `staging/wave21_C/c3_0804bde0.c` (main agbcc, 48 B, 32 diffs all
from the ands/cmp vs tst + branch-offset cascade).
