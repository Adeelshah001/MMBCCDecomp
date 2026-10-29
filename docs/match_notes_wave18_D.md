# Wave 18 Worker D — Match Notes

## Matched (8)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x08049704 | AllChipCopiesValid_08049704 | 124 | old_agbcc | Pin xx→r5 (u32, C mask first), base→r8 (u32 =0x020070f0). Preheader `q=p` copy + do-while. Callee prototyped (u32,u32). |
| 0x0801f154 | NewNode_0801F154 | 44 | main | Node_PopAndInit(0,1,0,17). `u8 z=0` idiom steers p→r2. |
| 0x0801cdac | NewNode_0801CDAC | 44 | main | Node_PopAndInit(0,0,a,11). First-try. |
| 0x0801f1a8 | NewNode_0801F1A8 | 46 | main+FIXALIGN1 | Node_PopAndInit(0,1,0,12). `.align 1,0` kills GAS 46c0 tail pad. |
| 0x0801f050 | NewNode_0801F050 | 48 | main | Node_PopAndInit(0,1,b,17). First-try. |
| 0x0802030c | NewNode_0802030C | 52 | main | Node_PopAndInit(0,0,0,17). First-try. |
| 0x080203a4 | NewNode_080203A4 | 52 | main | Node_PopAndInit(0,0,0,11). First-try. |
| 0x0801ee14 | NewNode_0801EE14 | 82 | main+FIXALIGN1 | Node_PopAndInit(0,1,c,16). `u8 z=0` forces `movs r0,#0` before `mov r1,r8`. |

## Blocked (7)

| Address | Size | Diffs | Blocker |
|---------|------|-------|---------|
| 0x0800fff4 | 136 | 4 | Twin scheduler: `ldrb` before `mov r2,#1` (ROM has mov first). Double-orrs needs asm barrier. |
| 0x0801009c | 136 | 4 | Twin of 0x0800fff4 (Ewram5160_Init_10508(2) vs (1)). |
| 0x0800909c | 158 | 119 | Complex 6-arg loop, needs heavy pinning. |
| 0x0801d598 | 174 | 165 | Struct math, far off. |
| 0x0801d2c8 | 62 | 21 | Descending alloc (a→r7,b→r6,c→r5,type→r4) not reproduced. |
| 0x080250bc | 74 | 21 | Pool placement: ROM has immediate pool, compiler places later. |
| 0x08017620 | 78 | 9 | Alloc rotation: ROM a→r7,c→r5,d→r6; mine a→r5,c→r6,d→r7. |
| 0x08017d00 | 78 | 9 | Twin of 0x08017620. |
| 0x08022868 | 84 | 21 | Pool placement. |
| 0x0803e9bc | 88 | 63 | Complex pools, multi-branch. |
| 0x08001ebc | 90 | 73 | Multi-return structure. |
| 0x08020340 | 96 | 90 | Pool placement. |

## New Idioms

### u8 z=0 zero-materialization ordering
When the ROM does `movs r0,#0` BEFORE `mov r1,r8` (for `p[16]=a; p[18]=0`), declare `u8 z=0;` at the top of the block and use `p[18]=z`. The compiler materializes the zero first, matching the ROM's instruction order.

### FIXALIGN1 for sub-4-byte-multiple functions
For functions whose size is not a multiple of 4 (e.g., 46 B, 82 B), GAS emits a `46c0` tail pad from `.align 2,0`. Rewrite the leading `.align 2,0` to `.align 1,0` via FIXALIGN1=1 in w18.sh.

### Pinned-high-reg + natural-low-reg hybrid
Pin specific args to high regs (r7, r8) via `register ... __asm__("r7")`, let others allocate naturally. Works when the prologue doesn't use high regs (or saves/restores them).

### Linked-at-address verification
The w18.sh script now links the .o at the true ROM address before objcopy extraction. Critical for `bl` to absolute `.set` symbols (GAS 2.42: `.set` must FOLLOW code).

## Coordinator Landing Addendum (2026-10-23)

### Verification
All 8 claims independently re-verified from scratch (recompile → link at address → objcopy → cmp vs baserom). All 0-diff, full extents including pools.

### Landing fixes applied
1. **Stripped redundant `.globl`/`.set`:** Worker emitted `.globl Node_PopAndInit` + `.set` in 7 files, `.globl Vec2_SetMirrored` + `.set` in 1 file, and `.globl AddTableEntry_082344CC` + `.set` in 1 file. All three are already real C symbols in the build (Node_PopAndInit @ w16b_08017000.o, Vec2_SetMirrored @ vec2.o, AddTableEntry_082344CC @ wave7_g2_old.o) → multiple-definition at link. Removed; kept the `g_082344d6` data `.set` (not a defined symbol). Per landing hygiene: nm-check before keeping any `.set`.
2. **Makefile rewrite:** Worker's LANDING.md used `$(OBJDIR)` and a non-project rule shape. Rewrote all 8 per-file rules in the project's `$(BUILD)` + `$(CPP)/$(AGBCC|OLDAGBCC)/$(AS)` form.
3. **ldscript rewrite:** Worker's slot syntax didn't match project conventions. Rewrote 8 slots in `. = 0xADDR; .text.NAME : { build/FILE.o (.text.NAME); }` form, appended (no reorder).
4. **FIXALIGN1 sed pattern bug (coordinator's):** My Makefile sed used pattern `\.align 2, 0` (literal space) but agbcc emits `.align<TAB>2, 0`. The sed silently never matched → 3 sections (0801f1a8, 080203a4, 0801ee14) linked 2 B oversize with `c046` pad. Caught by post-build size check (46→48, 58→60, 82→84). Fixed pattern to `\.align\s*2, 0`; rebuilt; all 8 sections now exact-size and 0-diff in the built ROM. Lesson: always verify post-build section sizes for FIXALIGN1 functions, not just isolated worker evidence.

### Registry
8 MATCHED rows appended to docs/match_status.tsv (wave 18). No duplicates — all 8 addresses were previously unclaimed.
