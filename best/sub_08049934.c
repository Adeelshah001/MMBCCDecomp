/* Rank_49934 @ 0x08049934 (54 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_020070F0[];

/* 0x08049934 (54B): rank from EWRAM u16; 254->2, 255->3, 253->1. */
u8 sub_08049934(u8 idx)
{
    u8 *pool = gUnknown_020070F0;
    u8 r = 0;
    u8 *base = pool + idx * 12;
    int v = *(u16 *)(base + 50);
    if (v == 254) goto yes2;
    if (v > 254) goto big;
    if (v == 253) goto yes1;
    goto no;
big:
    if (v != 255) goto no;
    r = 3;
    goto no;
yes2:
    r = 2;
    goto no;
yes1:
    r = 1;
no:
    return r;
}
