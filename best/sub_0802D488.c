/* Sub_0802D488 @ 0x0802D488 (50 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_0802d488_MATCHED.c (registry: mmbcc/src/w35b_0802d488_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_0802D574(void);

int sub_0802D488(u8 a, u8 b)
{
    register u32 aa = ((u32)a << 24) >> 24;
    register u32 bb = ((u32)b << 24) >> 24;
    register int r = 0;
    if (aa == 5)
    {
        if (bb == 3 || bb == 1)
            r = 3;
    }
    else
    {
        if (aa == sub_0802D574())
            r = 6;
    }
    return r;
}
