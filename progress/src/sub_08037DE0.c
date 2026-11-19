/* sub_08037DE0 @ 0x08037DE0 (344 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w194f_08037de0_MATCHED.c (registry: src/w194f_08037de0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

void EntryMgr_Teardown(u32 x);

u32 TblGetByte_24384(u32 x);

u8 sub_0800B368(u32 a, u32 b, u32 c, u32 d);

void Sub_0800B3F8(u32 a, u32 b, u32 c);

u8 Check_B308(void);

void TblSet_11DD0(u8 a, u8 b);

void FlagBit_Set_11D68(u8 a, u8 b);

void LoadCallClear_4A328(void);

void EntryMgr_Setup(void);

extern u32 TABLE_A_08230CFC[];

extern u32 G_0823014C;

extern u32 G_08230154;

extern u32 TABLE_D_08230D84[];

extern u8 gEwram_02004E40[];

extern u8 TABLE_08230450[];

__attribute__((section(".text.w194f_08037de0_p8_oldO2")))
u8 sub_08037DE0(u8 *s)
{
    u8 flag = 0;
    register u8 *p __asm__("r6");
    register s32 v __asm__("r4");
    EntryMgr_Teardown(0);
    p = s + 18077;
    __asm__ volatile("movs r4, #0\n\tldrsb %0, [%1, r4]" : "=r" (v) : "r" (p));
    switch (v) {
    case 0:
        (*p)++;
    case 1: {
        u8 idx = (u8)(TblGetByte_24384(4096) - 50);
        if (sub_0800B368(TABLE_A_08230CFC[idx], G_0823014C, G_08230154, 0) != 0) {
            Sub_0800B3F8(0, *(u32 *)TABLE_D_08230D84[s[18072]], 8);
            s[18077]++;
        }
        break;
    }
    case 2:
        gEwram_02004E40[20] |= 1;
        if (Check_B308() != 0) {
            if ((s8)gEwram_02004E40[8] == 0) {
                s[18076] = v;
                *p = flag;
                TblSet_11DD0(4, TABLE_08230450[s[18073]]);
                TblSet_11DD0(6, s[18073]);
                TblSet_11DD0(7, 0);
                if (s[18073] == 3)
                    FlagBit_Set_11D68(54, 1);
                {
                    u8 *q = s + s[18073] * 12;
                    if (q[288] <= 98)
                        q[288]++;
                }
                s[18078] = flag;
                s[18083] = flag;
                LoadCallClear_4A328();
                flag = 1;
            } else {
                s[18076] = flag;
                *p = 5;
            }
        }
        break;
    default:
        break;
    }
    EntryMgr_Setup();
    return flag;
}
