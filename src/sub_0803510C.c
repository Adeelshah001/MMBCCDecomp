/* EntMgr_Reinit45 @ 0x0803510C (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern void sub_08004F80(void);

/* 0x0803510C: Teardown(); s[4]=2; s[5]=0; Setup(); return 0. Tentative. */
u32 sub_0803510C(u8 *s)
{
    sub_08004F18();
    {
        u8 zero = 0;
        s[4] = 2;
        s[5] = zero;
    }
    sub_08004F80();
    return 0;
}
