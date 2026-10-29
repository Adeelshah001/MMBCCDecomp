# Wave 8 match notes — worker M (TAG=M)

## 0x0800069c — Ewram_BumpAlloc (MATCHED, old_agbcc -O2 -mthumb-interwork)
EWRAM bump allocator rooted at 0x02000ED0: v=*(u16*)(base+0x2002),
w=*(u16*)(base+0x2000) cursor. Returns ((u32)v<<12)+base+w*4 and bumps the
cursor by (a+3)>>2 when (0x400-w)>=(a+3)>>2 unsigned, else 0.
Idioms: statement order mirrors ROM evaluation (v-load, v<<12, cursor,
w, t=base+w*4, ret, room=0x400-w, q=(a+3)>>2); 0x2002 pool-loads as a
separate pool word after the base (agbcc emits it naturally); main agbcc
reordered the loads (scheduler diff), old_agbcc matches byte-exact.

## 0x08002568 — EntList_Add1 / 0x080025c4 — EntList_Add2 (MATCHED, main agbcc)
Appends a 12-byte entry to the EWRAM list at 0x02002FB0. n=*(u32*)base
(signed int: `ble` not `bls`); if (n>15) return -1. Entry e=base+n*12:
e[4]=(e[4]&-4)|1 (|2 in the twin); *(u32*)(e+4)=(*(u32*)(e+4)&3)|(a2<<2);
*(u32*)(off+(base+8))=a1; *(u32*)(off+(base+12))=a0; count++; return 0.
Idioms: base pinned to r5 (`register u8 *base __asm__("r5")`) forces the
ROM's a2->r4/base->r5 allocation; the -4 mask via opaque inline asm
(`movs %0,#4; neg %0,%0`) + `m &= b` defeats the &0xFC range fold;
`"add %0,%1,%2"` asm forces operand order (gcc canonicalizes `off+p`
to the wrong order); if/else (not early-return) puts the -1 block first
so the literal pool lands mid-function; `a2 <<= 2` reuses r4 for the
shift; `off += (u32)p` reuses r2 for the second store address.

## 0x08004258 — ChipSlot_StateUpdate (BLOCKED)
ChipSlot state updater (callee of ChipSlot_IncUse). p[4]=idx, p[5]=0,
cnt=*(u8*)(tbl[idx]+1)+1 -> p[6], v=*(s8*)(tbl[p[4]]+3), p[7] selected by
(v>=0)?0 : ((s8)cnt==2)?2 : ((s8)cnt==1)?((v==-1)?3:4) : 1.
BLOCKED: old_agbcc with simple C gets the r5 reload naturally
(`ldrb r5,[r3,#4]`) and is byte-close, but three diffs remain:
(1) c==2 case does `strb r1,[r3,#7]` (cnt reg) vs ROM `strb r0` (the
sign-extended c reg); (2) tail-merging: compiler commons the p[7]
stores to a single strb via jumps, ROM has a separate strb+b in each
of the 3/4/1 branches (volatile stores did not defeat it); (3) `blt`
vs ROM `bge` for the v>=0 test (block ordering). Tried main/old,
register pins (disruptive), if/else and ternary forms.

## Summary
Worker M (TAG=M), Wave 8 batch M (68 medium call-free functions, 49-96 B).
Result: 3 MATCHED, 65 BLOCKED (5 with detailed analysis, 60 not attempted
due to time constraints).

MATCHED:
- 0x0800069c Ewram_BumpAlloc (old_agbcc)
- 0x08002568 EntList_Add1 (main)
- 0x080025c4 EntList_Add2 (main)

Key idioms discovered:
- Pinned base register (`register u8 *base __asm__("r5")`) to force
  specific callee-saved allocation (a2->r4, base->r5).
- Opaque -4 mask via inline asm (`movs %0,#4; neg %0,%0`) + `m &= b`
  to defeat the compiler's `& -4` -> `& 252` range fold on u8 values.
- `"add %0,%1,%2"` inline asm to force operand order when gcc
  canonicalizes `off+p` to the wrong order.
- if/else (instead of early return) to place the error block first,
  moving the literal pool mid-function.
- `a2 <<= 2` to reuse the arg register for the shift.
- `off += (u32)p` to reuse r2 for the second store address.

BLOCKED with analysis:
- 0x08004258 ChipSlot_StateUpdate: tail-merging, strb reg, branch order.
- 0x08001754 TblHash_Combine: shift-mask and lookup order.
- 0x0800c5b8/0x0800cbf0 FillPairs: shift-add-shift idiom + reg alloc.
- 0x0802d574 Lookup_02D574: r1/r2 allocation swap.

The 60 "Not attempted" entries have disassemblies in
staging/wave8_M/disasm/ and are ready for other workers.
Staging C sources for all attempts are in staging/wave8_M/c/.
