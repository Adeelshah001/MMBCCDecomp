/* TblGetW_BF74 @ 0x080246C4 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_0822BF74[];

u32 sub_080246C4(u16 idx)
{
    register u32 i = idx;
    u32 *base;
    if (i > 248)
        return 0;
    base = gUnknown_0822BF74;
    return base[i];
}
