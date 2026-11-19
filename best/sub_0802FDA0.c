/* sub_0802FDA0 @ 0x0802FDA0 (414 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w83a_0802fda0_MATCHED.c (registry: mmbcc/src/w83a_0802fda0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

void sub_08034CA0(u8 *s);

void sub_0800EE50(void);

void sub_0800EDE4(s16 a);

void sub_0800EDF0(s16 a);

u8 sub_0802FF40(u8 *s);

u8 sub_0803048C(u8 *s);

u8 F_08030AD4(u8 *s);

u8 sub_08033DE4(u8 *s);

u8 sub_080344F0(u8 *s);

u8 sub_0803449C(u8 *s);

u8 sub_08033AC8(u8 *s);

void sub_0800EA4C(u32 a);

extern u8 gUnknown_02005160[];

extern u8 gUnknown_02005168[];

extern u16 gUnknown_02002F50[];

u8 sub_0802FDA0(u8 *s)
{
    u8 r = 0;
    sub_08034CA0(s);
    gUnknown_02005160[58] = s[28];
    if ((s[6] & 16) == 0 && (gUnknown_02002F50[2] & 2) != 0)
        sub_0800EE50();
    if ((s[6] & 1) == 0) {
        sub_0800EDE4(*(s16 *)(s + 34));
        sub_0800EDF0(*(s16 *)(s + 178));
    } else {
        sub_0800EDE4(*(s16 *)(s + 12));
        sub_0800EDF0(*(s16 *)(s + 14));
    }
    switch (s[2]) {
    case 0:
        goto ea4c;
    case 1:
        r = sub_0802FF40(s);
        goto tail17;
    case 2:
        r = sub_0803048C(s);
        if (r == 0)
            break;
        s[2] = 0;
        s[3] = 0;
        break;
    case 3:
        r = F_08030AD4(s);
        goto tail35;
    case 4:
        goto ea4c;
    case 5:
        r = sub_08033DE4(s);
    tail35: {
        u8 *p;
        if (r == 0)
            break;
        p = gUnknown_02005168;
        p[7] = 0;
        p += 20;
        p[7] = 0;
        s[2] = 0;
        s[3] = 0;
        break;
    }
    case 7:
        r = sub_0803449C(s);
    tail17:
        if (r == 0)
            break;
        if (r == 11) {
            s[2] = 0;
            s[3] = 0;
            break;
        }
        {
            u8 b = 0;
            u8 a = 2;
            s[2] = a;
            s[3] = b;
        }
        break;
    case 8: {
        u8 t = sub_08033AC8(s);
        switch (t) {
        case 1:
            r = 8;
            break;
        case 2:
            s[0] = 0;
            s[1] = 0;
            r = 9;
            break;
        case 3:
            s[0] = 0;
            s[1] = 0;
            r = 10;
            break;
        default:
            break;
        }
        if (t != 0) {
            s[1] = 0;
            s[11] = 0;
        }
        break;
    }
    case 6: {
        u8 t = sub_080344F0(s);
        switch (t) {
        case 11:
            r = 11;
            break;
        case 1:
            r = 6;
            break;
        case 2:
            if (s[7] <= 9)
                s[7]++;
            s[0] = 0;
            s[1] = 0;
            r = 9;
            break;
        case 3:
            s[0] = 0;
            s[1] = 0;
            r = 10;
            break;
        default:
            break;
        }
        if (t != 0) {
            s[2] = 0;
            s[3] = 0;
        }
        break;
    }
    default:
    ea4c:
        sub_0800EA4C(0);
        break;
    }
    return r;
}
