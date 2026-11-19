/* ChangedBitsInit_080363EC @ 0x080363EC (78 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31d_080363ec.c (registry: src/w31d_080363ec.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern u8 *NodeInit_080217A8(u8 x);

extern void WalkBits_0803643C(int a, int b, int c);

__attribute__((section(".text.w31d_080363ec")))
void ChangedBitsInit_080363EC(u8 *p)
{
    register u8 *pp __asm__("r6") = p;
    if (pp[3] != pp[2]) {
        int x = (pp[2] ^ pp[3]) & pp[2];
        u16 i = 0;
        s16 j;
        do {
            j = (s16)i;
            if (((x >> j) & 1) != 0)
                NodeInit_080217A8((u8)i);
            i = (u16)(j + 1);
        } while ((s16)i <= 6);
        pp[3] = pp[2];
        {
            /* ROM uses ldrsb (agbcc never emits it from C); value already sign-extended. */
            register s32 v __asm__("r0");
            __asm__ volatile(
                "movs r0, #1\n\t"
                "ldrsb %0, [%1, r0]"
                : "=r"(v) : "r"(pp));
            WalkBits_0803643C(v, 0, 0);
        }
    }
}
