/* GetLimit_11C50 @ 0x08011C50 (8 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08011C50 (4B + pool, tentative): returns constant 0x4867. Sole caller
 * (sub_08011C80) truncates to u16 and compares `idx >= retval`, so this is
 * some kind of limit/capacity constant. agbcc pool-loads 0x4867. */
u16 sub_08011C50(void)
{
    return 0x4867;
}
