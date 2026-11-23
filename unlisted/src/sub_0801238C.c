/* sub_0801238C @ 0x0801238C (376 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w74a_0801238c_MATCHED.c (registry: mmbcc/src/w74a_0801238c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

u32 sub_0800DD2C(u8 *s, u32 a, u32 b);

u16 sub_08011F50(u8 *s);

void sub_0800D9EC(u8 *s, u32 a);

void sub_0800D9FC(u8 *s);

u32 sub_08017464(u32 a);

u32 sub_08011F68(u8 *s, u32 a);

void sub_0804A378(u32 a);

void sub_0801AA70(u8 a, u8 b, u32 c, s16 d, s16 e, u32 f);

void sub_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);

void sub_0801BBB4(u8 a, u32 b, s16 c, s16 d, u32 e);

extern u8 gUnknown_08223D47[];

extern u8 gUnknown_08223D44[];

extern u8 gUnknown_08223ED8[];

void sub_0801238C(u8 *s)
{
    u8 *q;
    q = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 15);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s)) {
            s[14]++;
            sub_0800D9EC(s, 16);
            if ((u8)(s[17] - 19) <= 5) {
                u8 *bp;
                int ix;
                u8 p0, p1;
                u32 nb;
                u8 *tbl;
                u16 *ent;
                s16 a, b;
                sub_0804A378(131);
                bp = gUnknown_08223D47;
                ix = (s[17] - 19) * 2;
                p0 = bp[ix];
                bp++;
                p1 = bp[ix];
                nb = ((u32)s[35] << 28) >> 28;
                tbl = gUnknown_08223ED8;
                ent = (u16 *)(tbl + *q * 4);
                a = ent[0];
                b = ent[1];
                sub_0801AA70(p0, p1, nb, a, b, *(u32 *)(s + 44));
            } else if ((u8)(s[17] - 16) <= 2) {
                u8 by;
                u32 nb;
                sub_0804A378(146);
                by = gUnknown_08223D44[s[17] - 16];
                nb = ((u32)s[35] << 28) >> 28;
                sub_0801AB94(by, nb, 15360, -6400, *(u32 *)(s + 44));
            } else {
                u8 sv;
                u32 nb;
                u8 *tbl;
                u16 *ent;
                u16 a, b;
                sub_0804A378(131);
                sv = s[17];
                nb = ((u32)s[35] << 28) >> 28;
                tbl = gUnknown_08223ED8;
                ent = (u16 *)(tbl + *q * 4);
                a = ent[0];
                b = ent[1];
                sub_0801BBB4(sv, nb, (s16)(a - 15360),
                              (s16)(b - 11520), *(u32 *)(s + 44));
            }
        }
        break;
    case 2:
        if (sub_08011F50(s)) {
            sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            sub_0800DD2C(s, 0xFFFFC400, 0);
            sub_0800D9EC(s, 0);
            q[4] = 0;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
