/* sub_080396B4 @ 0x080396B4 (580 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w130a_080396b4_MATCHED.c (registry: src/w130a_080396b4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

void TblSet_11DD0(int a, u8 b);

u8 AddTableEntry_082344CC(u8 a, u8 b);

void Sub_0804990C(void);

u8 TblGetByte_24384(int a);

u16 Search_080112FC(u8 a, int b);

u8 TblWalkInit_080114B8(u16 a);

s16 Sub_080114E8(int a);

void Fwd_08011bd4(void);

__attribute__((section(".text.w130a_080396b4")))
int sub_080396B4(u8 *s)
{
    u16 keys = *(u16 *)0x02002F50;
    s8 st = (s8)s[0x469D];
    u16 r;

    switch (st) {
    case 0: {
        u8 diff = (u8)(s[0x469B] - s[0x4698] - 1);
        u8 idx;
        u8 *p;
        TblSet_11DD0(1, diff);
        TblSet_11DD0(2, s[0x469A]);
        TblSet_11DD0(3, 0);
        diff = (u8)(s[0x469B] - s[0x4698] - 1);
        idx = AddTableEntry_082344CC(diff, s[0x469A]);
        p = s + idx * 12 + 48;
        if (*p <= 98)
            (*p)++;
        s[0x469E] = 0;
        if (s[21] == 1) {
            Sub_0804990C();
            *(u32 *)(s + 24) |= 4;
            *(u32 *)(s + 28) &= ~4;
        }
        s[0x469D]++;
        /* fallthrough into case 1 */
    }
    case 1: {
        r = Search_080112FC((u8)(TblGetByte_24384(0x1000) - 50), 4);
        if (r == 0) {
            s[0x469D] += 2;
            break;
        }
        if (TblWalkInit_080114B8(r) != 0)
            break;
        s[0x469D]++;
        s[0x469F] = 0;
        /* fallthrough into case 2 */
    }
    case 2: {
        u8 f;
        if ((keys & 8) != 0)
            s[0x469F]++;
        else
            s[0x469F] = 0;
        f = s[0x469F];
        if (f > 30) {
            Fwd_08011bd4();
            s[0x469D]++;
        } else if (Sub_080114E8(f) == 1) {
            s[0x469D]++;
        }
        break;
    }
    case 3: {
        r = Search_080112FC((u8)(TblGetByte_24384(0x1000) - 50), 3);
        if (r == 0) {
            s[0x469C] = 4;
            s[0x469D] = 0;
            break;
        }
        if (TblWalkInit_080114B8(r) != 0)
            break;
        s[0x469D]++;
        s[0x469F] = 0;
        /* fallthrough into case 4 */
    }
    case 4: {
        u8 f;
        if ((keys & 8) != 0)
            s[0x469F]++;
        else
            s[0x469F] = 0;
        f = s[0x469F];
        if (f > 30) {
            Fwd_08011bd4();
        } else if (Sub_080114E8(f) != 1) {
            break;
        }
    }
        {
            u8 *p = s + 0x469C;
            u8 z = 0;
            *p = 5;
            s[0x469D] = z;
        }
        break;
    default:
        break;
    }
    return 0;
}
