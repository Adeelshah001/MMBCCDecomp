/* Reinit_350D0 @ 0x080350D0 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_h.c (registry: src/wave4_h.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern void sub_08004F80(void);

/* 0x080350D0: reinit struct, then EntryMgr_Teardown/Setup. Tentative.
 * Returns 0. The large offsets (0x46A8+) force pool loads. */
u32 sub_080350D0(u8 *s)
{
    *(u32 *)(s + 0x46A8) = 0;
    *(u32 *)(s + 0x46AC) = 0;
    s[4] = 1;
    s[5] = 0;
    *(u8 *)(s + 0x46A8) = 0;
    *(u8 *)(s + 0x46A9) = 0;
    sub_08004F18();
    sub_08004F80();
    return 0;
}
