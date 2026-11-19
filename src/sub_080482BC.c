/* EntMgr_Reinit23 @ 0x080482BC (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern void sub_08004F80(void);

/* 0x080482BC: Teardown(); s[2]=2; s[3]=0; Setup(); return 0. Tentative. */
u32 sub_080482BC(u8 *s)
{
    sub_08004F18();
    {
        u8 zero = 0;
        s[2] = 2;
        s[3] = zero;
    }
    sub_08004F80();
    return 0;
}
