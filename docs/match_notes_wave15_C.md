# Wave 15-C Match Notes (TAG=C coordinator direct work, rows 91–125)

35 functions attempted (rows 91–125 of wave15_layer.tsv). 27 MATCHED, 8 BLOCKED.
Registry check 2026-10-22: none of rows 91–180 in match_status.tsv (verified via grep -i).

## New idioms established this wave

### 1. Extern-array blocks constant folding (0x0800ec18)
`u8 *p = (u8 *)0x02005130; p += 37;` folds to a single `ldr r2, =0x02005155`.
Using `extern u8 g_02005130[];` + `u32 addr = (u32)g_02005130; u8 *p = (u8 *)addr;`
gives the ROM's `ldr r0, [pc]; adds r2, r0, #0; adds r2, #37` because the
link-time constant cannot be folded. The `u32` intermediate is essential —
without it the compiler still merges.

### 2. u32 temp for (s8) call result (0x0800ecd8)
ROM: `bl; lsls r0,r0,#24; asrs r0,r0,#24; cmp r0,#1; bne PAST_MOVS`
(the bne jumps PAST `movs r0,#1`, so r0 already holds the return value).
C: `u32 r = (u32)(s8)F_0801025C(a, (s8)b); if (r == 1) { SetByte20(13); return 1; } return r;`
Declaring r as u32 (not s8) keeps it in r0 without re-extension.

### 3. Shared zero temp (0x0800e400 family)
ROM: `movs r0,#0; strh r0,[r4,#24]; bl SetByte20` (r0 reused, no second movs).
C: `u8 z = 0; p[12] = z; SetByte20_Clear21to23_02005130(z);`

### 4. Int-decl callee idiom (0x08003078)
ROM compares the call result with NO (u16) extension even though the callee
returns u16. Declaring the extern as `u32 TblValidate_300C(u16 x)` matches —
the original TU likely saw an implicit/int declaration.

### 5. Branchy boolean via early return (0x08003078)
`return f(x) != 0` booleanizes to negs/orrs/lsrs. The ROM's
`cmp; beq L0; movs r0,#1; b L1; L0: movs r0,#0` comes from:
```c
if (TblValidate_300C(x) == 0) return 0; return 1;
```

### 6. do-while with signed counter (0x08000d6c)
ROM: `ble` (signed) and `i++` BEFORE `p += 24`.
C: `int i = 0; do { ...; i++; p += 24; } while (i <= 2);`

### 7. Anti-folding temp for double-AND (0x0801c3fc/0801c540, old_agbcc)
`p[10] = (p[10] & 253) & 254` folds to `& 252`. ROM does two separate ands.
C: `{ u8 b = p[10]; b &= 253; b &= 254; p[10] = b; }` (old_agbcc).

### 8. Late pool load via direct global access (0x0800eac4)
`u8 *q = g_02005168;` as a local loads the pool EARLY. ROM loads it late.
C: use `g_02005168[10] = ...` directly — the compiler loads the pool at first use.

### 9. Reused pool pointer in r3 (0x0800eb70)
```c
u8 *q = g_02005130;   // q in r3, live across two uses
u8 *p = q; p += 37;   // adds r2,r3,#0; adds r2,#37
...
u8 *r = q; r += 36;   // adds r0,r3,#0; adds r0,#36
```
The `p = q` copies are genuine (not optimized away) because q is reused.

## Per-function notes

### MATCHED

**0x08000624 Fwd_08000624** (10B, main): pure forwarder to F_08002F40.
`void F(void) { F_08002F40(); }` → push{lr}/bl/pop{r0}/bx r0.

**0x08000630 Fwd_08000630** (10B, main): pure forwarder to F_08002F4C.

**0x0804c814 Fwd_0804C814** (10B, main): pure forwarder to ClearSignBit.

**0x0800e400 GuardedListInit_0800E400** (50B, main): template for the 10-function
family. Sets *(u16*)0x02005148 = 1; if ((s8)IsZero_02005160_08010088()==1)
clears it and calls SetByte20(0); then ListIterate_D568 on *(u8**)0x02005270
and *(u8**)0x020053C0. Family members differ only in the checker function
(and two use a pointer/byte arg via q+=10 / q+=43).

**0x0800e650/0800e690/0800e7c8/0800e808/0800e848/0800e888** (50B, main):
same template with IsZero_02005160 at 0x080103cc, 0x080104f4, 0x08010124,
0x08010248, 0x080102f4, 0x080102f4.

**0x0800e8c8** (54B, main): template + `u8 *q=(u8*)p; q+=10;`
checker = FlagByte_CopyOrNeg1(q). **0x0800e90c** (56B, main): q+=43,
checker = Test_08010454(*q). **0x0800e950** (56B, main): q+=43,
checker = FlagBitClear_10498(*q).

**0x0800eb24 SetFlag_0800EB24** (12B, main): SetByte20_Clear21to23_02005130(3).

**0x0800c5ec / 0800c69c FillWrap** (16B, main): twins.
`void F(u16 d, u16 *base, u32 c) { FillTilemap_C3A0(base, (u16)c); }`

**0x08003078 NotZero_08003078** (24B, main): see idioms 4+5.

**0x0800ecd8 F_0800ECD8** (30B, main): see idiom 2.

**0x08000d6c TaskScan_08000D6C** (32B, main): see idiom 6. Pool 0x030023c8.

**0x0800ec18 FlagByteSet_0800EC18** (32B, main): see idiom 1.

**0x0800eac4 CopyBytes_0800EAC4** (40B, main): see idiom 8.

**0x0800eaf4 CondCopy_0800EAF4** (42B, old_agbcc): `if (p[4] != x || p[5] != y)`
short-circuit; y saved in r3 via `adds r3,r1,#0`.

**0x0800eba0 Store5_0800EBA0** (42B, main): 5 args (r0-r3 + stack);
pool kept in ip across stores to offsets 38/39/40/11/42 of 0x02005130.

**0x0800eb70 FlagStore_0800EB70** (44B, main): see idiom 9.

**0x0801c3fc / 0801c540 ChipInit** (38B, old_agbcc): see idiom 7.
Wrapper_D770(p, 0x82a, 0); ChipSlot_IncUse(p, 0).

**0x080246fc IdxLookup_080246FC** (38B, main): `if (x > 248) return 0;`
then `(u8)DerefIdx_08025564(pp, (u8)x)`. Pool 0x02007090 (after code).

## BLOCKED (with precise diffs)

**0x0801e14c SlotCopy_0801E14C** (34B): 6 diffs at bytes 14-16.
ROM: `ldr r1,[pc]` (pool 0x082243d4) BEFORE `ldrb r2,[r4,#9]`.
Mine always schedules ldrb/lsls first. Tried: single expression, split
statements with `u32 base/idx`, `__asm__ volatile("")` barrier, `&g_082243D4[p[9]]`
u32-array indexing, old_agbcc. The scheduler will not put the ldr first.

**0x080173d4 TblSlotInit_080173D4** (36B): 4 diffs. Same scheduler issue
(ROM: ldr pool, ldrb, lsls, adds; mine: ldrb, lsls, ldr, adds).
Notably this one is `push {lr}` only (no r4) and does `p[10] &= 254` inline.

**0x0801787c SlotClear_0801787C** (38B): 20 diffs. Same scheduler issue,
plus DecIfNonZero_18 prologue.

**0x08027c84 RecInit_08027C84** (36B): 10 diffs. ROM loads all three pools
up front (r2=0x020070f0, r1=0x0822dd84, r3=0x4698). With locals-declared-first
I get r2,r1 loaded then `adds r0,r0,r1` (WRONG reg — uses q2 not q3 for
`p+0x4698`) and the third pool loaded late. Compiler misallocates the u32
q3=0x4698. Tried old_agbcc (same).

**0x0804c820 ClearLoop_0804C820** (36B): 29 diffs. ROM: `ldr r0,[pc]` (=7),
`lsls r0,r0,#16; lsrs r0,r0,#16`, then the loop. The pooled constant 7 with a
(u16) extension has no clean C source — `(u16)7` gives `movs r0,#7`.
The loop itself (`ldr r0,[r5]; bl; adds r5,#12; subs r4,#1; cmp/bne`) is clear.

**0x0804c7b4 TblLookup_0804C7B4** (42B): 2 diffs at bytes 21,23.
ROM: `adds r1,r1,r2; ldr r2,[r1]`. Mine: `adds r2,r2,r1; ldr r2,[r2]`.
Pinning p1 to r2 fixes the early `ldr r2` but forces the adds into r2.
Tried: unpinned (wrong early ldr), explicit `u32 off/addr` temps.

**0x0800edb0 TestStore_0800EDB0** (46B): 26 diffs. agbcc booleanizes
`if ((a<<24)==0) b=0; else b=1` to negs/orrs/lsrs#31; ROM is branchy
(lsls; cmp; bne; movs r1,#0; b; movs r1,#1). Tried: plain if/else, braces,
ternary, goto, `u32 t` temp, old_agbcc — all booleanize or worse.

**0x0804bde0 ListWalk_0804BDE0** (46B): 30 diffs. ROM: `tst r0,r1; beq`
and `orrs r1,r0`. Mine: `ands r0,r1; cmp r0,#0` and `orrs r0,r1`.
Tried: temp u8, `(u32)` cast. The tst-vs-ands and orrs operand order
resist all formulations tried.
