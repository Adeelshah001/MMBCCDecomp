/* SetSlot_IfLE29 @ 0x08025934 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080256D4(u8 *s, u8 v);

/* 0x08025934: if (a > 29) return 1; SetU8_0_FF1(s+a*4+20, b); return 0.
 * Tentative. The (a*4+0x14) parens are required for the exact
 * `lsls; adds #0x14; adds r3` order. */
u8 sub_08025934(u8 *s, u8 a, u8 b)
{
    if (a > 0x1d)
        return 1;
    sub_080256D4(s + (a * 4 + 0x14), b);
    return 0;
}
