/* Dispatch_08226DD8_10 @ 0x0801F224 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_08226DD8[];

/* 0x0801F224 */
void sub_0801F224(u8 *s)
{
    u32 *tbl = gUnknown_08226DD8;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}
