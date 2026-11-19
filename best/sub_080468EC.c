/* Dispatch_08233A44_2 @ 0x080468EC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_08233A44[];

/* 0x080468EC */
void sub_080468EC(u8 *s)
{
    u32 *tbl = gUnknown_08233A44;
    u32 idx = s[2];
    ((void (*)(u8 *))tbl[idx])(s);
}
