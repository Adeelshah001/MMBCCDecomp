/* Memset_11C14 @ 0x08011C14 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_B_old.c (registry: src/wave11_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* 0x08011C14 (60 B incl pool): two memset loops via pp base 0x02005260.
 * Zeroes 16 bytes at pp[1] and 8 bytes at pp[2]. */
void sub_08011C14(void)
{
    u32 *pp = (u32 *)0x02005260;
    s16 i;
    for (i = 0; i <= 15; i++)
        ((u8 *)pp[1])[i] = 0;
    for (i = 0; i <= 7; i++)
        ((u8 *)pp[2])[i] = 0;
}
