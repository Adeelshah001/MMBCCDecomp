/* DivZeroStub_4DEDE @ 0x0804DEDE (10 B, neighbor extent (no ELF size; fixed up after compile)) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e_noiw.c (registry: ldscript BYTE (src/wave3_e_noiw.c)).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DD9C(void);

   /* .set in wave3_d_noiw.c */

/* 0x0804DEDE (8B, tentative): divide-by-zero path — sub_0804DE70 (custom
 * divmod) `beq`s here when the divisor (r1) is 0. Calls sub_0804DD9C,
 * returns 0. */
u32 DivZeroStub_4DEDE(void)
{
    sub_0804DD9C();
    return 0;
}
