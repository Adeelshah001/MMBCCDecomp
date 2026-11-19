/* Sub_0801E890 @ 0x0801E890 (172 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40a_0801e890_MATCHED.c (registry: mmbcc/src/w40a_0801e890_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, int b, u8 c);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void Step_0801e93c(u8 *s);

__attribute__((section(".text.w40a_0801e890")))
void Sub_0801E890(u8 *s)
{
    u8 *t;
    int v;
    {
        u8 *q;
        int tmp;
        int w;
        u8 t10;
        register int one __asm__("r1");
        register u8 *base1 __asm__("r1");
        u32 *tp;
        register u8 *base2 __asm__("r1");
        base1 = (u8 *)0x082243d8;
        __asm__ volatile("" : "+r"(base1));
        tp = (u32 *)(s[9] * 4 + (u32)base1);
        one = 1;
        *(u32 *)(s + 12) = one;
        *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 4);
        *(u32 *)(s + 108) = 0;
        t10 = 2 | s[10];
        t10 = t10 | one;
        s[10] = t10;
        {
            register u32 base __asm__("r4");
            register int off __asm__("r0");
            int idx;
            u32 e;
            int sv;
            u8 a;
            u8 b;
            u8 c;
            base = 0x08226aec;
            __asm__ volatile("" : "+r"(base));
            idx = s[16];
            off = idx << 1;
            off += idx;
            e = off + base;
            sv = 128 << 3;
            sv |= *(u8 *)e;
            {
                u32 p2 = base + 2;
                b = *(u8 *)(off + p2);
            }
            ChipSlot_Setup(s, sv, b);
            idx = s[16];
            off = idx << 1;
            off += idx;
            base = base + 1;
            ChipSlot_IncUse(s, *(u8 *)(off + base));
        }
        s[18] = 0;
        v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
        w = v;
        __asm__ volatile("" : "+r"(w));
        if (w > 3)
            v = 3;
        q = s + 69;
        {
            int sh = v << 2;
            tmp = (s[69] & -13) | sh;
        }
        *q = tmp;
    }
    {
        u8 t34 = s[17] + 14;
        s[34] = t34;
    }
    Step_0801e93c(s);
}
