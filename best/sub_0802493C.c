/* F_0802493C @ 0x0802493C (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22b_0802493c.c (registry: src/w22b_0802493c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_080258D8(u8 *p, u16 idx);

extern u8 sub_080258C0(u8 *s, u16 idx);

extern void sub_08025994(u8 *s, u16 idx);

extern void sub_080254E0(u8 *s, u8 idx);

u32 sub_0802493C(u8 *p, u8 a)
{
    u8 r1;
    u8 r2;

    if (a > 29)
        return 1;
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        u8 b = *(q + (216 << 1));
        r1 = sub_080258D8(q + (u32)b * 144, a);
        if (r1 == 0)
            return 0;
        if (r1 == 2)
            return 5;
    }
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        u8 b = *(q + (216 << 1));
        r2 = sub_080258C0(q + (u32)b * 144, a);
    }
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        u8 b = *(q + (216 << 1));
        sub_08025994(q + (u32)b * 144, a);
    }
    sub_080254E0(p, r2);
    return 0;
}
