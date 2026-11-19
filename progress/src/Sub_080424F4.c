/* Sub_080424F4 @ 0x080424F4 (320 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w139a_080424f4_MATCHED.c (registry: src/w139a_080424f4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u8 gEwram_02004E40[];

extern s8 G_02004CA0[];

extern u32 Tbl_08232A5C[];

extern u32 G_082325D4;

extern u32 G_082325DC;

extern int TblGetByte_241F8(u16 a);

extern s16 Sub200_08024514(u8 v);

extern int TblGetByte_24384(int a);

extern u8 sub_0800B148(u8 a, s16 b, u8 c);

extern int Sub_0800B320(u32 a, u32 b, u32 c, u32 d);

extern u8 Tst_0800B2D8(void);

extern u8 Check_B308(void);

extern u8 CheckAndSet_B2B4(void);

extern u8 Tst_0800B2F0(void);

extern void Setup_08005F44(int a, s8 b, s8 c);

__attribute__((section(".text.w139a_080424f4_v8")))
int Sub_080424F4(u8 *s)
{
    int ret = 0;
    { u8 *gp = gEwram_02004E40; gp[20] |= 1; }
    switch (s[0x46AD]) {
    case 0:
        if (*(u16 *)(s + 0x46A4) == 0) {
            ret = 1;
            break;
        }
        if ((u8)sub_0800B148(1, Sub200_08024514((u8)TblGetByte_241F8(4096)), 5) != 0)
            s[0x46AD]++;
        break;
    case 1:
        if ((u8)Tst_0800B2D8() == 0)
            break;
        {
            int v = TblGetByte_24384(4096);
            u8 idx = (u8)(v - 50);
            int tv = Tbl_08232A5C[idx];
            if ((u8)Sub_0800B320(tv, G_082325D4, G_082325DC, 0) == 0)
                break;
        }
        s[0x46AD]++;
        break;
    case 2:
        if ((u8)Check_B308() == 0)
            break;
        ret = gEwram_02004E40[8];
        if (ret == 0)
            ret = 1;
        else
            ret = 0;
        s[0x46AD]++;
        break;
    case 3:
        if ((u8)CheckAndSet_B2B4() == 0)
            break;
        s[0x46AD]++;
        break;
    case 4:
        if ((u8)Tst_0800B2F0() == 0)
            break;
        s[0x46AC] = 10;
        Setup_08005F44(0, G_02004CA0[0], G_02004CA0[1]);
        break;
    default:
        break;
    }
    return ret;
}
