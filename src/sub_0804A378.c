/* Text_SelectBlobIdx @ 0x0804A378 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/text_idx.c (registry: src/text_idx.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

s16 sub_0800303C(u16 idx);

s16 sub_0804A378(u16 idx)
{
    return sub_0800303C(idx);
}
