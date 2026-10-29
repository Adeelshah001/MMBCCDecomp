/* Wave 32-C @0x0802D574 Lookup_02D574 -- MATCHED, 0 diffs, old_agbcc.
 * True extent 0x0802D574-0x0802D5A8 (52 B = 50 code + 2 pad), verified
 * against ROM bytes (not a self-measured window).
 * Behavior: branch-chain lookup; v==2 -> 4, v==3 -> 1, v==4 -> 3,
 * v==1 -> 2, else 255.
 * Idioms: goto form for ROM's beq/bgt/beq branch layout; block-scoped
 * pins v2->r1 (s32) + r->r2 (u32) -- pins do NOT cause a frame under
 * old_agbcc (they did under main); s32 v = (u8)a0 gives signed `bgt`
 * for `v > 2` while keeping the lsl/lsr u8 mask; v2 declared before r
 * so `adds r1,r0,#0` precedes `movs r2,#255` (declaration order =
 * emission order); `if (v > 2)` uses r0 (v), inner `v2 ==` uses r1.
 * LANDING NOTE (coordinator): Makefile rule for this TU needs the bx-lr pad sed:
 *   sed -i 's/^\tbx\tlr$$/\tbx\tlr\n\t.short\t0x0000/' $(@:.o=.s)
 * (GAS emits a 46c0 nop to 4-align the 50-B section; the explicit .short keeps
 * the ROM's 2 zero pad bytes.) DO-NOT-LAND: staged for coordinator.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

__attribute__((section(".text.w32c_0802d574")))
u32 Lookup_02D574(u32 a0)
{
    s32 v = (u8)a0;
    register s32 v2 __asm__("r1") = v;
    register u32 r __asm__("r2") = 255;

    if (v == 2)
        goto L4;
    if (v > 2)
        goto Lgt;
    if (v == 1)
        goto L2;
    goto Lend;
Lgt:
    if (v2 == 3)
        goto L1;
    if (v2 == 4)
        goto L3;
    goto Lend;
L2:
    r = 2;
    goto Lend;
L4:
    r = 4;
    goto Lend;
L1:
    r = 1;
    goto Lend;
L3:
    r = 3;
Lend:
    return r;
}
