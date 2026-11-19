/* CopyBlendRegs_04000052 @ 0x08002E50 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08002e50: CopyBlendRegs_04000052 (32B, coordinator-verified). */
extern unsigned short gUnknown_04000052[];

extern unsigned short gUnknown_02003220[];

void CopyBlendRegs_04000052(void)
{
    register unsigned short *dst = gUnknown_04000052;
    register unsigned short *src = gUnknown_02003220;
    dst[0] = src[1];
    dst += 1;
    dst[0] = src[2];
    dst -= 2;
    dst[0] = src[0];
}
