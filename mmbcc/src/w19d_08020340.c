/* 0x08020340 (96 B code + 4 B pool = 100 B section): if s16 at *(u8**)0x020053c0+10 > 1,
 * alloc two (0,0,0,18) nodes; node1: [16]=3,[17]=0,[120]=47,[40]=a;
 * node2: [16]=3,[17]=1,[120]=49,[40]=a. Return last p (0 if skipped).
 * - `u8 *p = 0` declared first -> `movs r2,#0` hoisted to top, reused as
 *   bl arg (no movs r2,#0 before first call).
 * - `if (v > 1) {...}` instead of early-return: ROM uses `ble` straight to
 *   the return block, so there is no unconditional `b` barrier mid-function
 *   and the literal pool falls to the END (+0x60), matching ROM.
 * - `u8 z = 0` in block 1 (wave18 zero-first idiom): `movs r1,#0` before
 *   `movs r0,#3`. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19d_08020340")))
u8 *BuildNodePair_08020340(u8 *a)
{
    u8 *p = 0;
    s16 v = *(s16 *)(*(u8 **)0x020053c0 + 10);
    if (v > 1) {
        p = (u8 *)Node_PopAndInit(0, 0, 0, 18);
        if (p != 0) {
            u8 z = 0;
            p[16] = 3;
            p[17] = z;
            p[120] = 47;
            *(u8 **)(p + 40) = a;
        }
        p = (u8 *)Node_PopAndInit(0, 0, 0, 18);
        if (p != 0) {
            p[16] = 3;
            p[17] = 1;
            p[120] = 49;
            *(u8 **)(p + 40) = a;
        }
    }
    return p;
}
