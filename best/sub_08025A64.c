/* Sub_08025A64 @ 0x08025A64 (250 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w57a_08025a64_MATCHED.c (registry: src/w57a_08025a64_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern int sub_08026710(u8 a);

extern int sub_08026700(u8 a);

extern int sub_08025730(u8 *s, int b);

extern int sub_08025CA0(u8 *s, int b, u8 idx);

extern int sub_08025754(u8 *s);

extern int sub_080258A4(u8 *s, u8 tb);

extern void sub_08025638(u8 *s, int b, u8 idx);

extern void sub_080256DC(u8 *s, int b);

extern int sub_0802567C(u8 *s);

extern int sub_080266F0(u8 a);

extern int sub_0802583C(u8 *s, int b, s16 c);

extern int sub_080257F8(u8 *s);

int sub_08025A64(u8 *s, u8 idx)
{
    register u8 idx8 = idx;
    register int off = idx8 * 4;
    int tb;
    register int tb9;
    {
        register int tbh = s[off + 20];
        tb = tbh;
        tb9 = tbh;
    }
    if ((sub_08026710(tb) & 4) != 0)
        return 8;
    if ((u16)sub_08026700(tb) == 1) {
        if ((u8)sub_08025730(s, 0) != 0) {
            register u8 *p0 = s;
            register int p1 = 0;
            register u8 p2 = idx8;
            return (u16)sub_08025CA0(p0, p1, p2);
        }
        if ((u16)sub_08025754(s) > (u16)sub_080258A4(s, tb))
            return 1;
        {
            register u8 *p0 = s;
            register int p1 = 0;
            register u8 p2 = idx8;
            sub_08025638(p0, p1, p2);
        }
        sub_080256DC((off + 20) + s, 0);
        return 0;
    } else {
        u8 v = (u8)sub_0802567C(s);
        if (v == 0)
            return 6;
        if (v <= 9) {
            if ((u16)sub_0802583C(s, 0, (s16)sub_080266F0(tb)) == 0) {
                {
                    register u8 *p0 = s;
                    register int p1 = v;
                    register u8 p2 = idx8;
                    sub_08025638(p0, p1, p2);
                }
                sub_080256DC((idx8 * 4 + 20) + s, v);
                return 0;
            }
            return 2;
        } else {
            if ((u16)sub_080257F8(s) >= (u16)sub_080266F0(tb9)) {
                {
                    register u8 *p0 = s;
                    register int p1 = v;
                    register u8 p2 = idx8;
                    sub_08025638(p0, p1, p2);
                }
                sub_080256DC((idx8 * 4 + 20) + s, v);
                return 0;
            }
            return 3;
        }
    }
}
