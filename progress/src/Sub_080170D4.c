/* Sub_080170D4 @ 0x080170D4 (236 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w53b_080170d4_MATCHED.c (registry: src/w53b_080170d4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *Tbl_082243D8[];

extern u16 gRom_081705B0;

extern u8 gEwram_02003670[];

extern u8 gEwram_020031E4[];

extern u8 *Node_PopAndInit(int a, int b, int c, int d);

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, u8 n);

extern void Sub_080171C0(u8 *s);

__attribute__((section(".text.w53b_080170d4")))
void Sub_080170D4(u8 *s)
{
    int v;
    u8 *q;
    u32 *e;
    {
        register u32 *base __asm__("r1") = Tbl_082243D8;
        int idx = s[9];
        int off = idx << 2;
        u32 *t = (u32 *)(off + (u32)base);
        {
            register u32 one __asm__("r1");
            one = 1;
            *(u32 *)(s + 12) = one;
            e = *t;
            *(u32 *)(s + 20) = e[1];
            *(u32 *)(s + 108) = 0;
            {
                register u8 t10 __asm__("r3") = s[10];
                s[10] = (t10 | 2) | one;
            }
        }
    }
    {
        register u8 t17 __asm__("r0") = s[17];
        if (t17 <= 1) {
            q = Node_PopAndInit(0, 0, 0, 0);
            if (q != 0) {
                *(u8 **)(q + 40) = s;
                q[16] = s[16];
                q[17] = s[17] + 1;
            }
        }
    }
    ChipSlot_Setup(s, 1536, 0);
    ChipSlot_IncUse(s, s[16]);
    if (*(u32 *)(s + 40) != 0) {
        u8 *p65 = s + 65;
        int m = -13;
        *p65 = (*p65 & m) | 4;
    }
    {
        register int j __asm__("r0") = (gRom_081705B0 >> 4) * 2;
        v = gEwram_020031E4[j] & 3;
    }
    {
        int c;
        __asm__ volatile("add %0, %1, #0" : "=r" (c) : "r" (v));
        if (c > 3)
            v = 3;
    }
    {
        u8 *p69 = s + 69;
        int sh = v << 2;
        int m = -13;
        *p69 = (*p69 & m) | sh;
    }
    {
        u8 *p34 = s + 34;
        int z = 0;
        *p34 = z;
        {
            int fl = gEwram_02003670[0x11ae] & 4;
            u32 v80 = 152 << 9;
            if (fl != 0)
                v80 = 160 << 9;
            *(u32 *)(s + 80) = v80;
        }
        *(u32 *)(s + 84) = 240 << 6;
        s[18] = z;
    }
    Sub_080171C0(s);
}
