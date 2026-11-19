/* F_080249B8 @ 0x080249B8 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w32c_080249b8.c (registry: staging/wave32_C/w32c_080249b8_MATCHED.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_080258D8(u8 *p, u16 idx);

extern void sub_080259A4(u8 *p, u16 b, u16 c);

u32 sub_080249B8(u8 *p, u8 a, u8 b)
{
    if (a > 29 || b > 29)
        return 1;
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        register u32 c432 = (216 << 1);
        register u8 *e = q + c432;
        register u8 t = *e;
        if (sub_080258D8(q + (u32)t * 144, a))
            goto upd;
    }
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        register u32 c432 = (216 << 1);
        register u8 *e = q + c432;
        register u8 t = *e;
        if (!sub_080258D8(q + (u32)t * 144, b))
            goto ret0;
    }
upd:
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        register u32 c432 = (216 << 1);
        register u8 *e = q + c432;
        register u8 t = *e;
        sub_080259A4(q + (u32)t * 144, a, b);
    }
ret0:
    return 0;
}
