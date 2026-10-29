# Wave 8 Batch L Notes (Worker L)

35 large call-free functions (97-160 bytes). 0 MATCHED, 35 BLOCKED.
All staged C files in `~/workspace/mmbcc-decomp/staging/wave8_L/`.

## Key Idioms Discovered

### Dead `mov ip, r2` (sub_0804D088)
The function has a dead initialization `mov ip, r2` in the prologue (c is never
used; ip is overwritten with 0/255 on all paths before use). Both agbcc and
old_agbcc DCE this. Forced via volatile inline asm:
```c
register u32 f __asm__("ip");
__asm__ volatile("lsl r2, r2, #24\n\tlsr r2, r2, #24\n\tmov ip, r2" ::: "r2", "ip", "cc");
```
This emits exactly `lsls r2,r2,#24; lsrs r2,r2,#24; mov ip,r2`. The `.code 16`
directive appears after but emits no bytes. Placement: after `u8 idx = b;`
init, before `if (a == 4)`, to match ROM order.

### Literal `[0]` index gives register-indexed loads (sub_0804D088)
`((s16 *)((u8 *)base + off))[0]` with a literal 0 compiles to
`movs r7, #0; ldrsh r1, [r0, r7]` (not `ldrsh r1, [r0, #0]`). Same for `ldrsb`.
There is NO `j` variable in the source; the 0 is a literal that agbcc
materializes in a register. Second lookup used r2 (different register).

### Unpinned u8 gives temp-form clamp (sub_0804D088)
`idx = (u8)(idx - 21)` with idx UNPINNED gives:
```
adds r0, r5, #0; subs r0, #21; lsls r0,r0,#24; lsrs r5,r0,#24
```
With idx pinned to r5, it gives in-place `subs r5, #21` (wrong). Do NOT pin
clamped u8 variables.

### s32 for arithmetic shifts (sub_0804D088)
`v1b >> 4` where v1b is u8 gives `lsrs` (logical). ROM has `asrs` (arithmetic).
Declare v1b/v2b as `s32` to get `asrs r0, r6, #4`. The `ldrb` still zero-extends
(values 0-255), but the shift is arithmetic.

## Per-Function Notes

### sub_0804D088 (0x0804d088, 160 bytes) — BLOCKED
Palette fade/blend function. Three tables via pools:
- 0x08105ef0 (mid-function pool, 00 00 pad at 0x804d0ba): byte table for a==4 path
- 0x08105e54: byte step table
- 0x08105ed8: s16 palette table

Logic:
- If a==4: idx = (idx<=20) ? 0 : min((u8)(idx-21), 59); return table1[idx].
- Else: if idx<=35 {f=0; idx=0} else {idx=min((u8)(idx-36),130); f=255};
  v1b=table2[idx]; t1=table3[v1b&15]; v1=t1>>(v1b>>4);
  v2b=table2[idx+1]; t2=table3[v2b&15]; v2=t2>>(v2b>>4);
  return v1 + ((f*(v2-v1))>>8) + 2048.

Branch shapes: `if (idx <= 20)` (not `>`) gives `cmp; bhi`. `if (a == 4)` gives
`cmp; bne`.

Status: Prologue (26 bytes) matches. Mid-function pool matches. a==4 path
matches with unpinned idx. BLOCKED on else-path register allocation:
ROM: r3=step base, r6=v1b→v1, r4=pal base, r2=15, r7=ldrsh index→product.
Mine: r2=step base, r1=v1b, r4=15, r3=pal base, r6=ldrsh index.
Tried: main, old_agbcc, pinning v1b to r6 (worse). The allocator permutes
systematically; needs different C structure.

Staged: `sub_0804D088.c` (v4, closest, 168 bytes vs 160).

### sub_080030C4 (0x080030c4, 108 bytes) — BLOCKED
Struct copy with fixed-point interpolation.
```c
void f(s32 *dest, s32 **src, u16 *unk) {
    u16 r5 = unk ? unk[4] : 0, r6 = unk ? unk[5] : 0;
    if (src) {
        dest[0]=src[0][0]; dest[1]=src[0][1];
        dest[2]=(((src[0][0]>>8)+(src[1][0]>>8)-((s16)r5+120))<<8);
        dest[3]=(((src[0][1]>>8)+(src[1][1]>>8)-((s16)r6+80))<<8);
        dest[4]=src[1][0]; dest[5]=src[1][1];
    } else {
        dest[1]=0; dest[0]=0; dest[3]=0; dest[2]=0; dest[5]=0; dest[4]=0;
    }
}
```
Key: `register s32 **s __asm__("r3") = src;` forces `adds r3, r1, #0` prologue.
`if (s != 0)` (not `==`) gives `beq` to clear block at end.
Clear order (1,0,3,2,5,4) must be written explicitly.

Status: Prologue (22 bytes) matches. BLOCKED on body: ROM does
`ldr r2,[r3,#0]` (a), uses r2, then `ldr r3,[r3,#4]` (b, reusing r3).
Mine loads both upfront. Also `(s16)r5+120` computation order differs.
Tried: a/b locals, s[1] on-demand, s reassignment. Needs exact load scheduling.

Staged: `sub_080030C4.c` (112 bytes vs 108).

### sub_08042A64 (0x08042a64, 100 bytes) — BLOCKED
### sub_080459F8 (0x080459f8, 100 bytes) — BLOCKED
Byte-identical twins (verified via `cmp` — zero differences). One match covers both.

Bounds/overlap check. Pools: 0x02007036 (base), 0x0000ac11 (offset).
```c
u32 f(u8 a, u8 b, u8 c, u8 d) {
    u8 bb=b, dd=d; u8 *base=0x02007036;
    if (c==0 || dd==0) return 0;
    s32 sa=(s8)a;
    if (sa + c <= *(s8*)(base+0xac11)) return 0;
    s32 sb=(s8)bb;
    s8 b1=*(s8*)(base+0xac11), b2=*(s8*)(base+0xac12);
    if (sb + dd <= b2) return 0;
    if (sa >= b1+28) return 0;
    if (sb < b2+20) return 1;
    return 0;
}
```
ROM prologue: `lsrs r4,r1,#24` (b→r4), `lsrs r5,r3,#24` (d→r5),
`ldr r7,[pc]` (base→r7), `asrs r6,r0,#24` ((s8)a→r6).
The `(s8 *)(base+0xac11)` with literal [0] gives `movs r3,#0; ldrsb r3,[r0,r3]`.

Status: BLOCKED on allocation. ROM: b→r4, d→r5, base→r7, sa→r6.
Mine: b→r5, d→r3, base→r6, sa→r4 (or variants). Pinning b/d to r4/r5 made it
worse (112 bytes). Pinning base to r7 gave right size (100) but wrong push
({r4,r5,lr} not {r4,r5,r6,r7,lr}) and still wrong allocation.
Tried: main, old, o1, os, nointerwork. Needs allocator nudging.

Staged: `sub_08042A64.c`.

### T_0804DE70 (0x0804de70, 110 bytes) — BLOCKED
Unsigned division (binary long division, 4-bits-at-a-time unrolled).
Unusual features:
- `push {r4}` appears AFTER `movs r3,#1; movs r2,#0` (not at function start).
- `beq 0x804dede` jumps PAST the function end (0x804dede is next function's start).
- Returns via `mov pc, lr` (46f7), not `bx lr` → nointerwork.
- n_bl=0.

The `beq` past the end suggests the generator misidentified the boundary, OR
it's a shared epilogue. The division logic:
1. If divisor==0: beq past end (???)
2. Align: while (div < (1<<28) && div < dividend) {div<<=4; bit<<=4}
3. Then: bit<<=3; while (div < (1<<31) && div < dividend) {div<<=1; bit<<=1}
4. Loop: 4 unrolled subtract-and-or steps, then bit>>=4, div>>=4.

Status: BLOCKED. My C gives 124 bytes vs 110. The mid-prologue push and
past-end beq indicate the premise may be wrong. Recommend coordinator review
the boundary.

Staged: `T_0804DE70.c`.

### sub_0800BEE0 (0x0800bee0, 98 bytes) — BLOCKED
Bitfield manipulation on struct at 0x0200404f.
- If *(u16*)(base+20) == a: return.
- *(u16*)(base+6) = a.
- If b==128: *(base+9) = (*(base+9)&3)|128; *(base+10) &= -7.
- Else: if b>128: *(base+10)|=8; else: *(base+10)&=-9; then *(base+10)=(*(base+10)&-7)|4.

Key: uses `-7`/`-9` (via `movs; negs`), NOT `~7`/`~9`. (Brief idiom confirmed.)

Status: BLOCKED. My C gives 88 bytes vs 98. ROM pushes {r4,r5,r6} and uses
them; mine optimizes to fewer registers. Needs allocation forcing.

Staged: `sub_0800BEE0.c`.

### sub_0804D180 (0x0804d180, 104 bytes) — BLOCKED
Byte struct manipulation with (u8) conversion dance.
- v2=s[2], v3=s[3] via `lsls; lsrs` (keeps shifted versions in r2/r0).
- If v2>=v3: if ((v2>>1)<v3) s[27]=255 else s[27]=15.
- Else: if ((v3>>1)<v2) s[27]=255 else s[27]=240.
- s[10] = (s[2]+s[3])>>4, clamped to 15 (but NOT clamped if s[27]==255).
- s[25] = (s[6]*s[10]+15)>>4 (asrs).
- s[27] &= s[28].

The `(v2>>1)` is computed as `(v2<<24)>>25` (keeps the shifted value).
Status: BLOCKED. My C gives 84-92 bytes vs 104; compiler optimizes the dance
away and merges branches. Tried: main, old, o1, os. Needs optimization barrier
or exact source structure.

Staged: `sub_0804D180.c`.

## Unattempted (29 functions)
The remaining 29 functions were not attempted in depth due to time. They are
listed in wave8_L_results.tsv as BLOCKED. Disassemblies are in
`staging/wave8_L/*.asm`.
