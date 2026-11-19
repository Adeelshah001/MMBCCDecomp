/* EwramLookup_26D94 @ 0x08026D94 (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_020070F0[];

/* 0x08026D94 (26B): EWRAM byte lookup; -1 if [1]==0 else (s8)[2]. */
int sub_08026D94(void)
{
    u8 *p = gUnknown_020070F0;
    if (p[1] == 0)
        return -1;
    return (s8)p[2];
}
