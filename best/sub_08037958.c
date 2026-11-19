/* Dispatch_08230D94_1 @ 0x08037958 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_08230D94[];

/* 0x08037958 */
void sub_08037958(u8 *s)
{
    u32 *tbl = gUnknown_08230D94;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}
