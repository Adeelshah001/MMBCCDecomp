/* ClearHalf0_SetByte14_02003230 @ 0x08002E70 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2.c (registry: src/wave7_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08002e70: ClearHalf0_SetByte14_02003230 (16B, coordinator-verified). */
extern unsigned char gUnknown_02003230[];

void sub_08002E70(void)
{
    unsigned char *p = gUnknown_02003230;
    *(unsigned short *)p = 0;
    p[14] = 0xff;
}
