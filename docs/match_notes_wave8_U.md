# Wave 8 Worker U Match Notes

35 functions, 28 MATCHED, 7 BLOCKED. Staging: `staging/wave8_U/` (one .c per function).

## MATCHED (28)

### Prior session (21)
Matched in the prior session per the context checkpoint; verified with hardened protocol (byte-identical cmp, non-empty assertions, unquoted -j.text, full-extent cmp). Idioms documented in the checkpoint summary.

- **0x08004e0c** (24): Mid-function literal pool idiom (old_agbcc dumps pool at barrier after unconditional branch).
- **0x0800b2d8** (24): Mid-function literal pool; G1 had BLOCKED.
- **0x0800b2f0** (24): Mid-function literal pool; G1 had BLOCKED.
- **0x0800b4c8** (24): Negated-variable mask (`int m9=9; p[19]&=-m9` forces movs+negs).
- **0x080110b0** (24): Pinned registers (x→r0,y→r2,d→r3,m→r4); G1 BLOCKED → cracked.
- **0x08004e24** (26): Movs-first ternary (`w=2; if(v==0) w=1`); G1 recipe.
- **0x08010478** (26): Pool 0x02005168.
- **0x0801052c** (26): Pool 0x02004CA0.
- **0x0800b2b4** (36): Ands-dest control via inline asm (`movs %0,#C` / `and %0,%1`); G1 BLOCKED → cracked.
- **0x08010454** (36): G1 re-derivation (`if((p[16]&2)==0) return 0` gives beq).
- **0x0802520c** (36): Ordering barrier (`__asm__ volatile("": "+r"(x))`).
- **0x0802526c** (36): Prior match.
- **0x0804b310** (36): Ordering barrier.
- **0x080021c4** (38): Volatile marker + delayed pool; pools 0x02002FB0/0x11111111/0x040000D4/0x85006000.
- **0x08004b94** (38): Whole-loop asm for `((i<<16)+0x10000)>>16` increment; pool 0x02003668.
- **0x08026f98** (38): Inner {} blocks, branchless nonzero (`(x|-x)>>31`); pools 0x020031E0/0x02003670/0x11AC.
- **0x0802c7b4** (38): Explicit `static const u16 pad=0` (linker emits c0 46, ROM has 00 00).
- **0x080475d4** (38): Whole-loop asm; G1 recipe; pool 0x0200B7A8.
- **0x08010374** (40): F-BLOCKED → cracked; `if(*q==0)` for beq; opaque asm + pinned v→r2/w→r0; pool 0x02005160.
- **0x08010f88** (40): s8 loads; split stores for movs placement; pool 0x020051B0.
- **0x08010fb4** (40): s8 variable forces ldrsb; pool 0x020051C8.

### New matches (7)

**0x0800db40** (44, old): Byte processor. Indexed `ldrsb r0,[r3,r0]` requires variable index (`int i=0; s8 c=q[i]`). Pinned `pp` to r2 (`adds r2,r0,#0`). ROM modifies p in place (`adds r2,#69`), so use `pp += 69` not `pp[69]`. The `((unsigned)pp[31]<<28)>>28` gives `lsls/lsrs` for &0xF.

**0x08004424** (46, old): List pop (head@16, tail@24). Key: redundant `ldr r0,[r3,#24]` (for `head->f4=list->tail` then `list->tail->next=head`) — defeated CSE with `__asm__ volatile("" ::: "memory")` barrier. Unified return via `if (head != 0) { ... } return head` (beq to `adds r0,r2,#0`). The `movs r1,#0` interleaves after `subs` for cnt--. Explicit u16 pad (48-byte extent).

**0x08004454** (46, old): List pop variant (x20@20 not tail@24). `head->f4 = list+20` (not list->tail); `head->next = list->x20`; `list->x20->f4 = head`. Same barrier + unified return idioms.

**0x0800c8bc** (46, old): Fill u16 array with 0xFFF8. Whole-loop asm (like 4b94) but with dual increment: `lsls r0,r3,#16; movs r3,#128; lsls r3,r3,#9; adds r0,r0,r3; lsrs r3,r0,#16; asrs r0,r0,#16` (unsigned i in r3, signed in r0 for `blt`). Two `strh` per iter (r5 then r4). Pool 0x0000FFF8 (constant, not address). Dummy u32 param for r0 ABI.

**0x0804a660** (48, old): Copy 4 u16s to 0x0200BD20+132..138; zero bytes at +126/+127. Compiler does pointer-induction (`adds r2,#6` then `#2`) — defeated with struct-based dst (`typedef struct { u8 pad[132]; u16 v0,v1,v2,v3; }`). The `*p=0; p--; *p=0` gives `adds r2,#127; strb; subs r2,#1; strb`.

**0x0800b6f4** (50, old): Set p[18] nibble + table lookup. Pool 0x0817310C loaded LATE (after first strb) — delay via inner block. `int m15=15` stays in r5 (callee-saved, live across); `int m16=16` with `-m16` gives `movs r3,#16; negs r3,r3`. The `p[18] &= m15` is `ands r3,r5` on the live register (not a reload).

**0x08025578** (122, old): FilterCopy. Pool 0x082297E8 (delayed). `u8 * volatile p4` in struct (but compiler still hoisted — the real fix was correcting struct offsets: p4@4, p8@8, not 0/4). Swapped if/else (`if (b==0)` first) to get `bne` to Loop2 instead of `beq`. The `tbl += cnt-1` for backward loop. Explicit u16 pad (124-byte extent with mid-function pool).

## BLOCKED (7)

**0x080002dc** (34) / **0x08000300** (40): Hand-written context-switch asm (hi-reg save/restore with `mov r8,rX` etc.). Per G1 precedent, needs `.s` file, not C. Not attempted in C.

**0x08000ca8** (34): Tail-call `bl 0x0800e9c4` (≈5KB away, beyond 4KB branch range). No literal pool in the 34 bytes. Cannot be expressed in C — the `bl` needs a pool entry or long-branch stub that C won't generate.

**0x08011c58** (40): Table lookup with `adds r3,r0,#0` prologue (save a to r3 before b truncates r0). Tried: plain C (no save), `u8 ac=a` (no save), pin ac→r3 (causes spill: `mov ip,r3; mov r3,r8; push {r3}`), inline asm prologue (spill + wrong scheduling). The allocator won't emit the bare `adds r3,r0,#0` without pins, and pins break it. Pool 0x08173EEC.

**0x0800d3a0** (118): Complex config function. ROM uses r4,r3,r5 for variables, r6 for poolA (0x02004F80). My C gives `push {r4-r7,lr}` with different allocation. The `if (x==0)` / `else` with mid-function pool, plus dead `if (r3==2)` branch, plus `(u8)(-(s8)r4)` — too many interacting constraints. Tried one C version; register allocation diverged immediately.

**0x08047538** (154): Jump-table switch implementing `x/5` for s8 x in 0..25 (26-entry table at 0x08047550, pool at 0x0804754c). Cases: 0→0, 6→1, 11→2, 16→3, 21→4, 25→5, else→0. Writing a 26-case switch in C is unlikely to reproduce the exact dense table + case-body layout (`movs r2,#N; b` per case).

**0x0803f480** (956): Very large function with jump table. Not attempted; out of scope for leaf-function batch.
