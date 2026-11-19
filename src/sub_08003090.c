/* InitTriple_03090 @ 0x08003090 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08003090 (10B + pool, tentative): p[0] = a; p[1] = 0x0816E2CC;
 * p[2] = c (r2/b unused). The pool word points at a ROM struct
 * {0,0,0x08000400,0x20001000,...}. Same caller (sub_08005434) as
 * StoreTwoHalves_030BC and SetField204_04164 — a struct-init family. */
void sub_08003090(u32 *p, u32 a, u32 b, u32 c)
{
    p[0] = a;
    p[1] = 0x0816E2CC;
    p[2] = c;
}
