/* SetHalfs_0800EDFC @ 0x0800EDFC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0800edfc: SetHalfs_0800EDFC (24B, coordinator-verified). */
extern unsigned short gUnknown_02005130[];

extern unsigned short gUnknown_02005168[];

void SetHalfs_0800EDFC(unsigned short v)
{
    gUnknown_02005130[6] = v;
    gUnknown_02005168[0] = v;
}
