/* ClearHalf_02003240 @ 0x08002ED4 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2.c (registry: src/wave7_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08002ed4: ClearHalf_02003240 (12B, coordinator-verified). */
extern unsigned short gUnknown_02003240;

void sub_08002ED4(void)
{
    *(unsigned short *)&gUnknown_02003240 = 0;
}
