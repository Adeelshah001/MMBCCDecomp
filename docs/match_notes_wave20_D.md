
## 0x0804AF20 (112 B) — BLOCKED (u16 increment idiom)
**Status:** 73 diffs. Structure solved, single idiom wall.
**What works:** 5 args (u8 *p, u16 a/b/c, u16 d on stack→r8); zero-fill loop;
Sub200_08024514 x2, TblGetByte_24384 x2 calls; all strh stores match.
**Wall:** ROM's u16 loop-counter increment is `lsls r0,#16; movs r5,#128;
lsls r5,#9; adds r0,r5; lsrs r0,#16` ((i<<16)+0x10000 materialization).
Main and old agbcc both emit simple `adds r0,#1; lsls #16; lsrs #16`.
The (0x80<<9) materialization resists all C forms tried (do-while, for,
i++, i+=1, i=(u16)(i+1), i<28 vs i<=27, volatile).
**Next angle:** Find C pattern triggering agbcc's complex u16 increment,
or inline-asm the exact 5-instruction sequence in Thumb mode.

## Wave 20-D Matches (7 landed)

### 0x08005F44 (110 B) — MATCHED
Setup function. Key idioms: pinned `register u8 t __asm__("r6")=1`; opaque
divided-syntax `add %0,%1,#0` (GAS 2.42 rejects `adds` in divided mode, `add`
assembles to same 1c30); u32 runtime mask negation; explicit int temps.

### 0x080247E8 (48 B) — MATCHED
ChkFlag_080247E8. Pinned `register u8 *p __asm__("r5")` forces pool load to top;
mid-function pool at +0x24.

### 0x0801029C (86 B) — MATCHED
Setup_0801029C. Pinned r4/r5; opaque `add %0,%0,#3`; pinned r0 for q3.
FIXALIGN1 section-only (pool .align must stay 2).

### 0x08010EC4 (110 B) — MATCHED
Entry setup with 5 args. Pinned `register u8 *base __asm__("r2")` prevents
base+24 folding; explicit `int a12=a*12`; pinned `register u8 *q __asm__("r1")`;
divided-syntax `add %0,%1,%2` forces adds r4,r0,r1 order. FIXALIGN1.

### 0x0800EB30 / 0x0800EC3C (64 B each) — MATCHED (twins)
Setup wrappers: (s8)Setup_0800FFF4/0801009C(a-f); if==1 call
SetByte20_Clear21to23_02005130(4 vs 11), return 1. Twin constant differs.

### 0x0802611C (40 B) — MATCHED
Loop calling sub_080257BC(p + i*144, a) for i=0..2. Strength-reduced multiply.

## New Idioms for Catalog
1. **Pinned base prevents constant folding**: `register u8 *base __asm__("r2")`
   stops compiler from folding `base+24` to pool load.
2. **Divided-syntax add order**: `__asm__("add %0,%1,%2" : "=r"(d) : "r"(a), "r"(b))`
   forces `adds d,a,b` operand order (compiler swaps otherwise).
3. **Twin constant variation**: Twins may differ only in an immediate constant
   (4 vs 11) — verify each twin's constants independently.
