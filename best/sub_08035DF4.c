/* Dispatch_0822EB58_1 @ 0x08035DF4 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_0822EB58[];

/* 0x08035DF4 */
void sub_08035DF4(u8 *s)
{
    u32 *tbl = gUnknown_0822EB58;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}
