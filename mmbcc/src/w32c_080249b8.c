/* Wave 32-C @0x080249B8 TblPairSwap_080249B8 -- MATCHED, 0 diffs, main agbcc.
 * True extent 0x080249B8-0x08024A30 (120 B = 118 code + 2 pad), verified
 * against ROM bytes (not a self-measured window).
 * Behavior: if (a > 29 || b > 29) return 1;
 *   q = *(p+20) + (*(u8 *)(*(p+20) + 432)) * 144;
 *   if (CheckPair_258D8(q, a) || CheckPair_258D8(q, b))
 *       Tbl_SwapAndUpdate_080259A4(q, a, b);
 *   return 0.
 * Two-index pair check + swap-and-update dispatch; sibling of F_0802493C.
 * Idioms: goto shape for ROM branch layout (bne upd / beq ret0 / fall-through);
 *   triple block-scoped pin (c432->r1, e->r2, t->r3) defeats the gcc temp
 *   rotation (r7/r1/r2) -- pure C, NO .s patch needed;
 *   sibling q-computation (u8 t = *(q + (216 << 1)); q + (u32)t * 144);
 *   recomputed q blocks (no temp kept across calls).
 * LANDING NOTE (coordinator): Makefile rule for this TU needs the bx-r1 pad sed:
 *   sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)
 * (GAS emits a 46c0 nop to 4-align the 118-B section; the explicit .short keeps
 * the ROM's 2 zero pad bytes.) DO-NOT-LAND: staged for coordinator.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 CheckPair_258D8(u8 *p, u16 idx);
extern void Tbl_SwapAndUpdate_080259A4(u8 *p, u16 b, u16 c);

__attribute__((section(".text.w32c_080249b8")))
u32 F_080249B8(u8 *p, u8 a, u8 b)
{
    if (a > 29 || b > 29)
        return 1;
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        register u32 c432 __asm__("r1") = (216 << 1);
        register u8 *e __asm__("r2") = q + c432;
        register u8 t __asm__("r3") = *e;
        if (CheckPair_258D8(q + (u32)t * 144, a))
            goto upd;
    }
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        register u32 c432 __asm__("r1") = (216 << 1);
        register u8 *e __asm__("r2") = q + c432;
        register u8 t __asm__("r3") = *e;
        if (!CheckPair_258D8(q + (u32)t * 144, b))
            goto ret0;
    }
upd:
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        register u32 c432 __asm__("r1") = (216 << 1);
        register u8 *e __asm__("r2") = q + c432;
        register u8 t __asm__("r3") = *e;
        Tbl_SwapAndUpdate_080259A4(q + (u32)t * 144, a, b);
    }
ret0:
    return 0;
}
