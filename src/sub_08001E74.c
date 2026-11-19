/* Init_1E74 @ 0x08001E74 (70 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_B_old.c (registry: src/wave11_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08001E74 (70 B incl pools): guarded struct init at 0x02002F80.
 * Returns -1 if a > 1, *p != 0, or c > 0x2010; else writes
 * p[1]=a, *(p+8)=b, *(p+20)=c, *(u16*)(p+28)=0, p[0]=2, *(u16*)(p+2)=1. */
int sub_08001E74(u8 a, u32 b, u32 c)
{
    if (a > 1)
        return -1;
    {
        u8 *p = (u8 *)0x02002F80;
        if (p[0] != 0)
            return -1;
        if (c > 0x2010)
            return -1;
        p[1] = a;
        *(u32 *)(p + 8) = b;
        *(u32 *)(p + 20) = c;
        *(u16 *)(p + 28) = 0;
        p[0] = 2;
        *(u16 *)(p + 2) = 1;
        return 0;
    }
}
