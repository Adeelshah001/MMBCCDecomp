/* Sub_0801DD48 @ 0x0801DD48 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_0801dd48_MATCHED.c (registry: src/w36bulk_0801dd48_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Tick(u8 *o);

__attribute__((section(".text.w36bulk_0801dd48")))
void Sub_0801DD48(u8 *o)
{
    u8 *q = *(u8 **)(o + 40);
    if (o[13] == 0) {
        if (q[12] <= 1) {
            int sum;
            u32 a = *(u32 *)(q + 80);
            u32 b = *(u32 *)(q + 84);
            *(u32 *)(o + 80) = a;
            *(u32 *)(o + 84) = b;
            __asm__ volatile("" : "+r"(o));
            sum = *(int *)(o + 80) + *(int *)(o + 96);
            *(int *)(o + 80) = sum;
            *(int *)(o + 84) += *(int *)(o + 100);
            {
                u8 *t = q;
                t += 35;
                if ((t[0] & 15) == 1)
                    *(int *)(o + 80) = -sum;
            }
        } else {
            o[13]++;
        }
    }
    if ((u8)(o[119] - 3) <= 1) {
        u8 *p = *(u8 **)(o + 44);
        (*p)++;
        __asm__ volatile("" ::: "memory");
        {
            u32 *tbl = (u32 *)0x082243d8;
            register u32 *ep __asm__("r0");
            u32 off;
            __asm__ volatile("" : "+r"(tbl));
            off = o[9] * 4;
            ep = (u32 *)(off + (u32)tbl);
            *(u32 *)(o + 12) = 2;
            *(u32 *)(o + 20) = *(u32 *)(*ep + 8);
        }
    }
    ChipSlot_Tick(o);
}
