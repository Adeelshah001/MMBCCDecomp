/* InitRec28_4AF20 @ 0x0804AF20 (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24a_0804af20.c (registry: src/w24a_0804af20.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08024514(u8 v);

u8 sub_08024384(u16 a);

void sub_0804AF20(u8 *p, u16 a, u16 b, u16 c, u16 d)
{
    u8 *q = p;
    u16 i;
    u32 t;
    for (i = 0; i < 28; i = (t = ((u32)i << 16) + 0x10000) >> 16) {
        *q++ = 0;
    }
    *(u16 *)(p + 12) = sub_08024514((u8)b);
    *(u16 *)(p + 14) = sub_08024514((u8)d);
    *(u16 *)(p + 8) = sub_08024384(a);
    *(u16 *)(p + 10) = sub_08024384(c);
    *(u16 *)(p + 20) = a;
    *(u16 *)(p + 22) = c;
}
