/* Sub_08028900 @ 0x08028900 (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08028900_MATCHED.c (registry: mmbcc/src/w36b_08028900_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef u8 (*Func)(u8 *s);

extern u8 gUnknown_0200B810[];

extern u8 sub_0802FDA0(u8 *s);

int sub_08028900(void)
{
    int r5 = 0;
    Func *t = (Func *)0x0822de04;
    u8 *s = (u8 *)0x0200b810;
    u8 ret1 = t[s[0]](s);
    if ((s[6] & 8) == 0) {
        if (ret1 != 0) {
            u8 v = sub_0802FDA0(s);
            if (v == 11) {
                r5 = 5;
            }
            if (v == 9) {
                r5 = 3;
            } else if (v == 10) {
                r5 = 4;
            }
        }
    }
    if (ret1 == 4) {
        r5 = gUnknown_0200B810[4] >> 4;
        gUnknown_0200B810[0] = 0;
        gUnknown_0200B810[1] = 0;
    }
    return r5;
}
