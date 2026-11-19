/* GetS16_7C @ 0x080174E4 (8 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* 0x080174E4: adds r0,#0x78 / movs r1,#4 / ldrsh [r0,r1] — the p[2] form.
 * Writing *(s16*)(s+0x7C) directly folds to adds #0x7C and does NOT match. */
s16 sub_080174E4(u8 *s)
{
    s16 *p = (s16 *)(s + 0x78);
    return p[2];
}
