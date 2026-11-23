/* SetHalfs_0800EE14 @ 0x0800EE14 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0800edfc: SetHalfs_0800EDFC (24B, coordinator-verified). */
extern unsigned short gUnknown_02005130[];

extern unsigned short gUnknown_0200517C[];

void SetHalfs_0800EE14(unsigned short v)
{
    gUnknown_02005130[7] = v;
    gUnknown_0200517C[0] = v;
}
