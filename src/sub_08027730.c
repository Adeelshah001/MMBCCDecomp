/* EntMgr_Reinit1 @ 0x08027730 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern void sub_08004F80(void);

/* 0x08027730: s[1]=1; s[3]=0; s[2]=0; Teardown(); Setup(). Tentative.
 * The `u8 zero` local forces the zero into r2 (not reusing r1). */
void sub_08027730(u8 *s)
{
    u8 zero = 0;
    s[1] = 1;
    s[3] = zero;
    s[2] = zero;
    sub_08004F18();
    sub_08004F80();
}
