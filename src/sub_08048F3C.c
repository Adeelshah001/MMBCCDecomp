/* Sub_08048F3C @ 0x08048F3C (760 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w143a_08048f3c_MATCHED.c (registry: src/w143a_08048f3c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_08024384(int a);

extern void sub_08004F18(void);

extern void sub_08004F80(void);

extern void sub_0804A3FC(void);

extern int sub_0804A40C(void);

extern int sub_08024FD8(u8 *a, u8 *b);

extern int sub_08024FF4(int a);

extern int sub_0800B368(u32 a, int b, int c, int d);

extern int sub_0800B308(void);

extern int sub_0802500C(void);

extern void sub_0802508C(int a);

extern u32 gUnknown_082343E8[];

extern u32 gUnknown_08234448[];

extern u32 gUnknown_08234460[];

extern u32 gUnknown_08234430[];

extern u32 gUnknown_08234478[];

extern u32 gUnknown_08234490[];

extern u32 gUnknown_082344A8[];

extern u32 gUnknown_08233CBC;

extern u32 gUnknown_08233CC4;

extern u8 gUnknown_02004E40[];

int sub_08048F3C(u8 *s)
{
    int res = 0;
    u8 val = (u8)(sub_08024384(0x1000) - 50);

    sub_08004F18();
    switch (s[0x46a5]) {
    case 0:
        sub_0804A3FC();
        s[0x46a5]++;
        break;
    case 1: {
        s8 t = (s8)sub_0804A40C();
        if (t == -2) {
            s8 *p = (s8 *)(s + 0x46a7);
            if (*p > 0) {
                s[0x46a5]--;
                s[0x46a7]--;
            } else {
                s[0x46a5]++;
            }
        } else if (t == -1) {
        } else {
            s[0x46a5]++;
        }
        break;
    }
    case 2: {
        int v2;
        s[0x46a9] = sub_08024FF4(sub_08024FD8(s + 0x45ac, s + 0x45b4));
        v2 = s[0x46a9];
        if (v2 == 0) {
            if ((u8)sub_0800B368(gUnknown_082343E8[val], 0, 0, 0) != 0)
                s[0x46a5] = 3;
        } else if (v2 >= 0) {
            if (v2 <= 4)
                s[0x46a5] = 4;
        }
        break;
    }
    case 3:
        if ((u8)sub_0800B308() != 0) {
            s[0x46a4] = 4;
            s[0x46a5] = 3;
        }
        break;
    case 4:
        switch (s[0x46a9]) {
        case 3:
            res = (u8)sub_0800B368(gUnknown_08234430[val], 0, 0, 0);
            break;
        case 1:
            res = (u8)sub_0800B368(gUnknown_08234448[val], 0, 0, 0);
            break;
        case 2:
            res = (u8)sub_0800B368(gUnknown_08234460[val], 0, 0, 0);
            break;
        case 4:
            res = (u8)sub_0800B368(gUnknown_08234478[val], 0, 0, 0);
            break;
        default:
            break;
        }
        if (res != 0)
            s[0x46a5]++;
        break;
    case 5:
        if ((u8)sub_0800B308() != 0) {
            if (s[0x46a9] == 2)
                s[0x46a5]++;
            else {
                s[0x46a4] = 0;
                s[0x46a5] = 3;
            }
        }
        break;
    case 6:
        if ((u8)sub_0800B368(gUnknown_08234490[val], gUnknown_08233CBC, gUnknown_08233CC4, 0) != 0)
            s[0x46a5]++;
        break;
    case 7:
        if ((u8)sub_0800B308() != 0) {
            if ((s8)gUnknown_02004E40[8] == 0)
                s[0x46a5]++;
            else {
                s[0x46a4] = 0;
                s[0x46a5] = 3;
            }
        }
        break;
    case 8:
        if ((u8)sub_0800B368(gUnknown_082344A8[val], 0, 0, 0) != 0) {
            sub_0802508C((u8)sub_0802500C());
            sub_08024FD8(s + 0x45ac, s + 0x45b4);
            s[0x46a5]++;
        }
        break;
    case 9:
        if ((u8)sub_0800B308() != 0) {
            s[0x46a4] = 4;
            s[0x46a5] = 3;
        }
        break;
    default:
        break;
    }
    sub_08004F80();
    return 0;
}
