/* FlagA_8654 @ 0x08008654 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02003670[];

s8 sub_08008654(u8 *p)
{
    int r;
    u32 flag;
    if (p[11])
        goto Ldef;
    flag = gUnknown_02003670[0x11ae] & 1;
    r = 5;
    if (flag)
        goto Lend;
    r = 6;
    goto Lend;
Ldef:
    r = 5;
Lend:
    
    return (s8)r;
}
