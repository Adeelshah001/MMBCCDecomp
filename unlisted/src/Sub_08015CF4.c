/* Sub_08015CF4 @ 0x08015CF4 (668 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w138b_08015cf4_MATCHED.c (registry: src/w138b_08015cf4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

extern void sub_0800DD2C(u8 *s, s32 a, s32 b);

extern int sub_080174A4(u32 a, int b);

extern void sub_0800D9EC(u8 *s, int a);

extern void sub_0800D9FC(u8 *s);

extern int sub_08017474(u32 a);

extern s16 sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, int a);

extern void sub_08017478(u32 a, int b);

extern void sub_08017464(u32 a);

extern void sub_08017D00(int a, int b, s16 c, s16 d, u8 *e);

extern void sub_0801EE14(int a, int b, int c, s32 d, int e);

extern void sub_0804A378(int a);

extern u8 gUnknown_02003670[];

extern u8 gUnknown_08223EB4[];

extern u8 gUnknown_08223ED4[];

extern u8 gUnknown_08224060[];

struct DPair {
    u16 a;
    s16 b;
};

extern struct DPair gUnknown_08223ED8[];

void Sub_08015CF4(u8 *s)
{
    u8 *p = s + 124;

    switch (s[14]) {
    case 0:
        if (p[7] == 0)
            sub_080174A4(*(u32 *)(s + 44), 1);
        sub_0800DD2C(s, (int)0xffffc400, 0);
        sub_0800D9EC(s, 0);
        if (gUnknown_08223EB4[s[17]] == 23) {
            sub_08017D00(gUnknown_08223ED4[gUnknown_08224060[p[0]]],
                ((u32)s[35] << 28) >> 28,
                (s16)(gUnknown_08223ED8[p[0]].a - 14080),
                gUnknown_08223ED8[p[0]].b, *(u32 *)(s + 44));
        } else {
            sub_08017D00(gUnknown_08223EB4[s[17]],
                ((u32)s[35] << 28) >> 28,
                (s16)(gUnknown_08223ED8[p[0]].a - 14080),
                gUnknown_08223ED8[p[0]].b, *(u32 *)(s + 44));
        }
        if (p[7] != 0)
            s[14] = 2;
        else
            s[14]++;
        break;
    case 2:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) == 0)
            break;
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            s[14] = 5;
            break;
        }
        gUnknown_02003670[0x11AF] = (gUnknown_02003670[0x11AF] & 0xF) | 0x40;
        s[33] = 6;
        sub_0800D9EC(s, 3);
        s[14]++;
        break;
    case 3:
        if (sub_08011F50(s) == 0)
            break;
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 1) {
            if ((u8)sub_08017474(*(u32 *)(s + 44)) <= 5) {
                s[33] = 6;
                sub_0800D9EC(s, 3);
                break;
            }
        }
        if (p[7] == 2) {
            sub_0800D9EC(s, 7);
            s[14] = 6;
            break;
        }
        s[14]++;
        break;
    case 4:
        if (sub_08011F50(s) != 0) {
            sub_0800D9EC(s, 0);
            s[14]++;
        }
        break;
    case 1:
    case 5:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            sub_08017478(*(u32 *)(s + 44), 8);
            sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            sub_0800DD2C(s, (int)0xffffc400, 0);
            sub_0800D9EC(s, 0);
            p[4] = 0;
            sub_08011F68(s, 0);
        }
        break;
    case 6: {
        u8 *q = s + 33;
        u32 z = 0;
        *q = 60;
        s[18] = 40;
        sub_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, (int)0xffffc400, z);
        s[14]++;
        break;
    }
    case 7:
        if (--s[18] == 0) {
            sub_0800D9EC(s, 2);
            sub_0804A378(127);
            s[14]++;
        }
        break;
    case 8:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            u8 t = s[10] & 0xFE;
            u32 z = 0;
            s[10] = t;
            sub_08017478(*(u32 *)(s + 44), 8);
            sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = z;
            sub_0800DD2C(s, (int)0xffffc400, 0);
            sub_0800D9EC(s, 0);
            p[4] = z;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
