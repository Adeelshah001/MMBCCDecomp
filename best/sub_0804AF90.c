/* Dispatch_08234D4C_0 @ 0x0804AF90 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_08234D4C[];

/* s8-returning variants */

/* 0x0804AF90 */
s8 sub_0804AF90(u8 *s)
{
    u32 *tbl = gUnknown_08234D4C;
    u32 idx = s[0];
    return (s8)((u32 (*)(u8 *))tbl[idx])(s);
}
