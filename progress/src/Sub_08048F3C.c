/* Sub_08048F3C @ 0x08048F3C (760 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w143a_08048f3c_MATCHED.c (registry: src/w143a_08048f3c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int TblGetByte_24384(int a);

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

extern void EwSet16_128(void);

extern int sub_0804A40C(void);

extern int Sub_08024FDC(u8 *a, u8 *b);

extern int GetEnt_U8_24(int a);

extern int sub_0800B368(u32 a, int b, int c, int d);

extern int Check_B308(void);

extern int GetEnt_U8_19(void);

extern void F_0802508C(int a);

extern u32 T_082343E8[];

extern u32 T_08234448[];

extern u32 T_08234460[];

extern u32 T_08234430[];

extern u32 T_08234478[];

extern u32 T_08234490[];

extern u32 T_082344A8[];

extern u32 G_08233CBC;

extern u32 G_08233CC4;

extern u8 gEwram_02004E40[];

__attribute__((section(".text.w143a_08048F3C_v6")))
int Sub_08048F3C(u8 *s)
{
    int res = 0;
    u8 val = (u8)(TblGetByte_24384(0x1000) - 50);

    EntryMgr_Teardown();
    switch (s[0x46a5]) {
    case 0:
        EwSet16_128();
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
        s[0x46a9] = GetEnt_U8_24(Sub_08024FDC(s + 0x45ac, s + 0x45b4));
        v2 = s[0x46a9];
        if (v2 == 0) {
            if ((u8)sub_0800B368(T_082343E8[val], 0, 0, 0) != 0)
                s[0x46a5] = 3;
        } else if (v2 >= 0) {
            if (v2 <= 4)
                s[0x46a5] = 4;
        }
        break;
    }
    case 3:
        if ((u8)Check_B308() != 0) {
            s[0x46a4] = 4;
            s[0x46a5] = 3;
        }
        break;
    case 4:
        switch (s[0x46a9]) {
        case 3:
            res = (u8)sub_0800B368(T_08234430[val], 0, 0, 0);
            break;
        case 1:
            res = (u8)sub_0800B368(T_08234448[val], 0, 0, 0);
            break;
        case 2:
            res = (u8)sub_0800B368(T_08234460[val], 0, 0, 0);
            break;
        case 4:
            res = (u8)sub_0800B368(T_08234478[val], 0, 0, 0);
            break;
        default:
            break;
        }
        if (res != 0)
            s[0x46a5]++;
        break;
    case 5:
        if ((u8)Check_B308() != 0) {
            if (s[0x46a9] == 2)
                s[0x46a5]++;
            else {
                s[0x46a4] = 0;
                s[0x46a5] = 3;
            }
        }
        break;
    case 6:
        if ((u8)sub_0800B368(T_08234490[val], G_08233CBC, G_08233CC4, 0) != 0)
            s[0x46a5]++;
        break;
    case 7:
        if ((u8)Check_B308() != 0) {
            if ((s8)gEwram_02004E40[8] == 0)
                s[0x46a5]++;
            else {
                s[0x46a4] = 0;
                s[0x46a5] = 3;
            }
        }
        break;
    case 8:
        if ((u8)sub_0800B368(T_082344A8[val], 0, 0, 0) != 0) {
            F_0802508C((u8)GetEnt_U8_19());
            Sub_08024FDC(s + 0x45ac, s + 0x45b4);
            s[0x46a5]++;
        }
        break;
    case 9:
        if ((u8)Check_B308() != 0) {
            s[0x46a4] = 4;
            s[0x46a5] = 3;
        }
        break;
    default:
        break;
    }
    EntryMgr_Setup();
    return 0;
}
