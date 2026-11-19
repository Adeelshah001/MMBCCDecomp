/* GetByte1_25A08 @ 0x08025A08 (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08025A08 (4B, tentative): returns byte at p[1]. Callers use it as a
 * small-index/flag byte getter. */
u8 sub_08025A08(u8 *p)
{
    return p[1];
}
