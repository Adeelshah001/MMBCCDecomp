/* Func_080275F8 @ 0x080275F8 (288 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w49d_080275f8_MATCHED.c (registry: src/w49d_080275f8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void Sub_08023FD0(u8 *p, u8 v);

extern u16 Search_080112FC(u8 a, u8 b);

extern void FlagBit_Set_11D68(int a, int b);

extern void InitRec8_267B4(u8 *p, int v);

extern u8 TblWalkInit_080114B8(u16 v);

extern void Fwd_08011bd4(void);

extern s16 Sub_080114E8(u8 v);

__attribute__((section(".text.w49d_080275f8")))
void Func_080275F8(u8 *s) {
    u16 g = *(u16 *)0x02002F50;
    u8 mode = s[1];
    switch (mode) {
    case 0:
        Sub_08023FD0(s + 0x465C, s[11]);
        *(u32 *)(s + 24) |= 1;
        *(u32 *)(s + 28) &= ~1;
        s[12] = mode;
        s[1]++;
        /* fallthrough */
    case 1: {
        u16 t = Search_080112FC(s[11], 1);
        if (t == 0) {
            FlagBit_Set_11D68(30, 1);
            InitRec8_267B4((u8 *)0x020070F0, 8);
            s[0x4698] = 0;
            break;
        }
        if (TblWalkInit_080114B8(t) != 0)
            break;
        s[1]++;
        s[0x469C] = 0;
        /* fallthrough */
    }
    case 2:
        if ((u16)(g & 8) != 0) {
            s[0x469C]++;
        } else {
            s[0x469C] = 0;
        }
        {
            u8 v = s[0x469C];
            if (v > 30) {
                FlagBit_Set_11D68(30, 1);
                Fwd_08011bd4();
                InitRec8_267B4((u8 *)0x020070F0, 8);
                s[0x4698] = 0;
                break;
            }
            if (Sub_080114E8(v) != 1)
                break;
            InitRec8_267B4((u8 *)0x020070F0, 8);
            s[0x4698] = 0;
            FlagBit_Set_11D68(30, 1);
            break;
        }
    default:
        break;
    }
}
