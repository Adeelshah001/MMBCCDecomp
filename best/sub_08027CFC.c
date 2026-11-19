/* EntMgr_ClearBit3 @ 0x08027CFC (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern u8 gUnknown_0200B7E0[];

/* 0x08027CFC: ((u8*)0x0200B7E0)[3] &= -7; Teardown(). Tentative.
 * `int mask = -7` (not ~6) forces the movs+rsbs sequence. */
void sub_08027CFC(void)
{
    u8 *p = gUnknown_0200B7E0;
    int mask = -7;
    p[3] &= mask;
    sub_08004F18();
}
