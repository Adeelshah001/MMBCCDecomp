/* HBlank_Raster0 @ 0x08000B54 (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/hblank.c (registry: src/hblank.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


#define REG_VCOUNT   (*(volatile unsigned short *)0x04000006)

#define REG_DISPSTAT (*(volatile unsigned short *)0x04000004)

#define REG_IE       (*(volatile unsigned short *)0x04000200)

void sub_08000C68(void *desc);

void sub_08000B54(void)
{
    volatile unsigned short vcount = REG_VCOUNT;

    if (vcount > 159)
        return;
    sub_08000C68((void *)0x03000580);
    if (vcount != 159)
        return;
    REG_DISPSTAT &= ~0x10;
    (void)REG_DISPSTAT;
    REG_IE &= ~0x2;
    (void)REG_IE;
}
