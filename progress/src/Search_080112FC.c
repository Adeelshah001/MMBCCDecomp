/* Search_080112FC @ 0x080112FC (248 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_table.c (registry: src/w17c_table.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

 typedef signed short s16;

extern void FlagBit_Set_11D68(u16 x, u8 y);

extern u32 FlagBit_Get_11D34(u16 x);

extern u16 TableLookup_U16(u8 a0, u8 a1);

extern u8 *TableLookup_11C80(u16 idx);

extern u8 TblByte_11DB0(u16 idx);

/* 0x080112fc (248 B): flag-init + table walk. */
__attribute__((section(".text.w17c_080112fc")))
u16 Search_080112FC(u8 a, u8 b)
{
    u16 i = 3;
    u16 cur;
    u8 *p;
    do {
        if (a + 3 == i)
            FlagBit_Set_11D68(i, 1);
        else
            FlagBit_Set_11D68(i, 0);
        i++;
    } while (i <= 8);
    cur = TableLookup_U16(a, b);
    if (cur == 0)
        return 0;
    goto loop;
adv:
    if (*(s16 *)(p + 4) == 0)
        return 0;
    cur = *(u16 *)(p + 4);
loop:
    p = TableLookup_11C80(cur);
    {
        s8 v0 = (s8)p[0];
        if (v0 > 0) {
            if ((u8)FlagBit_Get_11D34((u16)v0) == 0)
                goto adv;
        } else if (v0 < 0) {
            if ((u8)FlagBit_Get_11D34((u16)(-(s8)p[0])) == 1)
                goto adv;
        }
    }
    {
        s8 v1 = (s8)p[1];
        if (v1 > 0) {
            if ((u8)FlagBit_Get_11D34((u16)v1) == 0)
                goto adv;
        } else if (v1 < 0) {
            if ((u8)FlagBit_Get_11D34((u16)(-(s8)p[1])) == 1)
                goto adv;
        }
    }
    {
        s8 v2 = (s8)p[2];
        if (v2 > 0) {
            if (TblByte_11DB0((u16)v2) < p[3])
                goto adv;
        } else if (v2 < 0) {
            if (TblByte_11DB0((u16)(-(s8)p[2])) >= p[3])
                goto adv;
        }
    }
    return cur;
}
