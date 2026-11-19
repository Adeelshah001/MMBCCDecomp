/* ChipInit_0802278C @ 0x0802278C (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_0802278c.c (registry: src/w17d_0802278c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D728(u32 a, u16 b, u8 c);

extern void sub_0800D9EC(u8 *s, u8 idx);

void sub_0802278C(u8 *p)
{
    register u32 z = 0;
    u8 b;
    *(u32 *)(p + 0x6c) = z;
    b = 2;
    b |= p[10];
    b |= 1;
    p[10] = b;
    sub_0800D728((u32)p, 0x2e12, 0);
    sub_0800D9EC(p, p[17]);
    *(u32 *)(p + 0x50) = 0xf0 << 7;
    *(u32 *)(p + 0x54) = 0xa0 << 7;
    {
        register u8 *q = p;
        int m;
        q += 0x45;
        m = -13;
        *q &= m;
    }
    p[0x22] = (u8)z;
}
