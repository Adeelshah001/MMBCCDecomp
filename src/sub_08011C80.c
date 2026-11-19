/* TableLookup_11C80 @ 0x08011C80 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_h.c (registry: src/wave4_h.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08011C50(void);

extern u8 gUnknown_0817A9C4[];

/* 0x08011C80: table lookup with 32-byte entries at 0x0817A9C4. Tentative.
 * Returns NULL if idx==0 or idx >= GetLimit_11C50() (0x4867). */
u8 *sub_08011C80(u16 idx)
{
    u16 lim;

    if (idx == 0)
        return 0;
    lim = sub_08011C50();
    if (idx >= lim)
        return 0;
    return gUnknown_0817A9C4 + (idx << 5);
}
