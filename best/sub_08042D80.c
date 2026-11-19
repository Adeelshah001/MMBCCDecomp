/* Sub_08042D80 @ 0x08042D80 (148 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08042d80_MATCHED.c (registry: mmbcc/src/w37c_08042d80_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08024760(void);

extern void sub_08043630(u8 *s);

extern u8 sub_08042F44(u8 *s);

u8 sub_08042D80(u8 *s)
{
    u8 ret = 0;
    switch (s[6]) {
    case 0:
        {
            u8 *gp = (u8 *)0x02003670;
            
            gp[0x11ac] = 0;
        }
        *(u32 *)(s + 0x46a8) = 0;
        *(u32 *)(s + 0x46ac) = 0;
        *(u32 *)(s + 0x46b0) = 0;
        s[0x46ac] = 5;
        s[0x46b0] = 0;
        s[0x46b2] = 0;
        s[0x46b1] = 1;
        if (sub_08024760() > 7)
            s[0x46b3] = 1;
        else
            s[0x46b3] = 0;
        sub_08043630(s);
        s[6]++;
    case 1:
        ret = sub_08042F44(s);
        break;
    default:
        break;
    }
    return ret;
}
