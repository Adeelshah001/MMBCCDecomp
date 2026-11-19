/* InitLinkedNode @ 0x0800440C (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 *gUnknown_0200081C;

/* 0x0800440C: *0x0200081C = s; *(s+12) = s+20. Tentative.
 * The separate `t = s; t += 20` is required for the exact
 * `adds r1,r0,#0; adds r1,#20` sequence. */
void sub_0800440C(u8 *s)
{
    u8 *t;
    gUnknown_0200081C = s;
    t = s;
    t += 20;
    *(u8 **)(s + 12) = t;
}
