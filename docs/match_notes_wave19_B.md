# Wave 19 Worker B — Match Notes

## Matched (8)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x08017434 | NewNode_08017434 | 36 | main | Node_PopAndInit(0,1,0,1); u8 z=0; p[16..18]=z; p[40]=z |
| 0x080214f4 | NewNode_080214F4 | 36 | main | Node_PopAndInit_20ED4(0,0,0,1); non-void/no-return idiom; disjoint r0 double-pin |
| 0x0801f180 | NewNode_0801F180 | 40 | main | Node_PopAndInit(1,1,0,17); p→r2, a→r4, z→r1 pins |
| 0x080228e0 | NewNode_080228E0 | 46 | main+FIXALIGN1 | Node_PopAndInit_20ED4(1,1,0,5); in-if u32 temps |
| 0x080236b0 | NewNode_080236B0 | 64 | old | Node_PopAndInit_20ED4(0,1,nib,7); cc→r4/dd→r6 pins; nibble via old_agbcc |
| 0x0801d308 | NewNode_0801D308 | 66 | main+FIXALIGN1 | Node_PopAndInit(0,1,0,12); asm memory barrier forces reloads |
| 0x08021cac | NewNode_08021CAC | 100 | main | 3× Node_PopAndInit_20ED4(0,0,0,3) sequential |
| 0x0801d278 | NewNode_0801D278 | 80 | old | Node_PopAndInit(0,0,nib,12); nibble from a[35]; max(a[34]-1,0) |

## New Idioms

### Non-void function with missing return → pop {r1} epilogue
If a function is declared `u8 *` (non-void) but has NO return statement,
agbcc reserves r0 as the return slot and emits `pop {r1}; bx r1` (not
`pop {r0}; bx r0` as for void). 0x080214f4 needed this: body matched as
void except the epilogue; changing the signature to `u8 *` with no return
fixed it. (The missing return is UB but matches the ROM byte-for-byte.)

### Disjoint-lifetime double-pinning of r0
Two `register u8` variables pinned to `r0` in disjoint scopes (e.g. `z`
then `ff` in a nested block) both materialize via `movs r0,#imm`,
reproducing ROM ordering like `movs r0,#0 … movs r0,#255`. Used in
0x080214f4 (`z=0`, then `ff=255`).

### Pinned r7 is NOT pushed by agbcc
`register ... __asm__("r7")` causes agbcc to USE r7 without emitting it in
the push/pop set (miscompile-ish behavior). Never pin r7; leave it for
natural allocation (0x080236b0: pinning cc→r4/dd→r6 and leaving b natural
gave the correct `push {r4-r7,lr}` with b→r7).

### Pinning suppresses u8 truncation shifts
`register u8 x __asm__("rN") = (u8)wide;` emits a plain `add`/`mov`,
dropping the `lsls #24; lsrs #24` truncation. Fix: pin the OTHER variables
and leave the truncated one natural (0x080236b0: aa natural → r5 with
shifts; 0x0801d308: cc natural → r4 with shifts).

### Nibble via u32 temp + old_agbcc
`u32 w = p[i]; u8 nib = (w << 28) >> 28;` under old_agbcc gives
`ldrb r0,[r0]; lsl r2,r0,#28; lsr r2,r2,#28` (load into r0, shift into r2).
Main agbcc merges the load into the dest reg (`ldrb r2,[r0]`). If the ROM
has the split form, the function (or that region) was built with old_agbcc.

### In-if u32 temps force load-load-store-store
For `*(u32*)(p+96)=*(u32*)(d); *(u32*)(p+100)=*(u32*)(d+4);`, declaring
`u32 dw0,dw1;` INSIDE the if-block (after the byte stores) and copying
through them yields `ldr; ldr; str; str` instead of the compiler's default
`ldr; str; ldr; str` interleaving. (0x080228e0, 0x080236b0, 0x0801d278.)

### __asm__ volatile("":::"memory") barrier forces reloads
When the compiler's value tracking reuses a just-stored register instead of
reloading (`*(u32*)(p+88) += ...` → `add r0,r0,r1` without `ldr`), an empty
asm memory barrier between the stores and the adds forces
`ldr r0,[r2,#88]; ldr r1,[r5]; add; str`. Emits a harmless `.code 16`
directive. (0x0801d308.)

### max(byte-1, 0) via shift-and-branch
`int t = (a[i]-1) << 16; u16 v = (u32)t >> 16; if (t < 0) v = 0;`
reproduces `ldrb; subs #1; lsls #16; lsrs; cmp; bge; movs #0`. (0x0801d278.)

## Blocked (0 attempted this wave)

None — all 8 attempted matched. (The 12 off-limits twins/pool functions
were not attempted per task instructions; Wave 19-C has since landed 4 of
them: 0x0800fff4, 0x0801009c, 0x08017620, 0x08017d00.)

## Unattempted (77)

Remaining open targets from the combined D-layer set (excluding the 8
matched above, 10 matched by others, 12 off-limits, 3 wave-8-blocked):

0x08024bc8, 0x08002cb0, 0x08011a78, 0x08010f34, 0x0801029c, 0x0800e3a0,
0x08010308, 0x0801dfc4, 0x080259a4, 0x08004998, 0x08010ec4, 0x0804af20,
0x08011e20, 0x08026740, 0x08016e84, 0x08021d10, 0x08016efc, 0x0800e440,
0x0800e748, 0x08042ae4, 0x080097cc, 0x0802493c, 0x08026184, 0x080263a4,
0x0800a6bc, 0x0801e174, 0x0801f254, 0x08020b60, 0x08003fc8, 0x0801bf10,
0x0801fcd0, 0x080482d8, 0x08042c04, 0x080405d8, 0x080439d8, 0x080460c0,
0x0801c56c, 0x0800571c, 0x0802d6e0, 0x080291ec, 0x0800e2cc, 0x080224e4,
0x08021b3c, 0x0801b0dc, 0x08002a1c, 0x0801c030, 0x08045838, 0x0803f844,
0x08046810, 0x0804a1f0, 0x0802298c, 0x08045914, 0x0803ad48, 0x08041890,
0x080046b0, 0x0803ac4c, 0x080096bc, 0x08006fe8, 0x0801c428, 0x08049560,
0x0800ac8c, 0x080203e0, 0x08001f1c, 0x08002070, 0x0804d8a8, 0x08034f2c,
0x08007840, 0x0803aaa8, 0x080065bc, 0x08006374, 0x0803643c, 0x080176ac,
0x08025ec8, 0x08007134, 0x08009c7c, 0x080099fc, 0x0801e208, 0x08006ad8,
0x080471d8, 0x08046df8, 0x08008bc8.

Notable: 0x0801dfc4 (r8 spill, stack buffer, calls F_0801E87C),
0x08021d10 (in-function pool, linked-list build loop), 0x08024bc8
(complex arithmetic, calls 0x08025730/0x08025a10) were examined but not
attempted due to complexity/time.
