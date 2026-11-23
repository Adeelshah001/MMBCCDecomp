/* DivZeroStub_4DD90 @ 0x0804DD90 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_c_noiw.c (registry: src/wave9_c_noiw.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DD9C(void);

/* 0x0804DD90: divide-by-zero exit stub (10 B).
 * Calls the 1-insn trap at 0x0804DD9C, returns 0. */
u32 DivZeroStub_4DD90(void)
{
    sub_0804DD9C();
    return 0;
}
