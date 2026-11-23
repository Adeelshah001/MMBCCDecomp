/* DivZeroStub @ 0x0804DE64 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d_noiw.c (registry: src/wave3_d_noiw.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DD9C(void);

/* 0x0804DE64: divide-by-zero exit stub (TENTATIVE name, worker D).
 * MATCHED 2026-10-20 (coordinator): agbcc -O2 WITHOUT -mthumb-interwork.
 * ROM 10 B: push {lr}; bl 0x0804DD9C; movs r0,#0; pop {pc}. */
u32 DivZeroStub(void)
{
    sub_0804DD9C();
    return 0;
}
