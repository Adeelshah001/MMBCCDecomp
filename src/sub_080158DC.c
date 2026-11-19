/* sub_080158DC @ 0x080158DC (364 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w194f_080158dc_MATCHED.c (registry: src/w194f_080158dc_MATCHED.c).
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

u32 sub_080174A4(u32 a, u32 b);

u32 sub_08017474(u32 a);

u32 sub_08017464(u32 a);

u32 sub_08011F68(u8 *s, u32 a);

void sub_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);

extern u8 gUnknown_08223ED8[];

void sub_080158DC(u8 *s)
{
    u8 buf[4];
    u8 *q;
    register u8 *bp = &buf[0];
    *bp = 48;
    q = s + 124;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s)) {
            sub_0800DD2C(s, 0x1400, 0);
            sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (sub_08011F50(s)) {
            sub_0800D9EC(s, 15);
            s[14]++;
        }
        break;
    case 3:
        if (sub_08011F50(s)) {
            u8 bb;
            u32 nb;
            u8 *tbl;
            u16 *ent;
            u16 a;
            u16 b;
            sub_080174A4(*(u32 *)(s + 44), 3);
            bb = buf[s[17]];
            nb = ((u32)s[35] << 28) >> 28;
            tbl = gUnknown_08223ED8;
            ent = (u16 *)(tbl + *q * 4);
            a = ent[0];
            b = ent[1];
            sub_0801AB94(bb, nb, (s16)(a + 0x2200), (s16)(b - 0xF00),
                          *(u32 *)(s + 44));
            sub_0800D9EC(s, 16);
            s[14]++;
        }
        break;
    case 4:
        if (sub_08011F50(s))
            s[14]++;
        break;
    case 5:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            sub_0800D9EC(s, 2);
            s[14]++;
        }
        break;
    case 6:
        if (sub_08011F50(s)) {
            sub_0800DD2C(s, 0xFFFFC400, 0);
            sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 7:
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
