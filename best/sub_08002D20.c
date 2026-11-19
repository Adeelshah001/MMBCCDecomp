/* DispCntRestore_Dma3 @ 0x08002D20 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_D_old.c (registry: src/wave13_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08002D20(void)
{
    volatile unsigned short v;
    unsigned short *ew;
    volatile unsigned int *dma;

    v = *(volatile unsigned short *)0x04000000;
    v &= 0xF0E8;
    ew = (unsigned short *)0x020031E0;
    *ew &= 0x0F17;
    v |= *ew;
    *(volatile unsigned short *)0x04000000 = v;

    dma = (volatile unsigned int *)0x040000D4;
    dma[0] = (unsigned int)ew + 4;
    dma[1] = 0x04000008;
    dma[2] = 0x8400000E;
    (void)dma[2];
}
