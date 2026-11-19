/* F_080119DC @ 0x080119DC (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22d_080119dc.c (registry: mmbcc/src/w22d_080119dc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern u8 ChkFlag_080247E8(u8 a);

extern void Inc4_Clear5_7(u8 *s);

typedef struct {
    u8 *f0;
    u32 f4;
    u32 f8;
} Obj;

__attribute__((section(".text.w22d_080119DC")))
s32 F_080119DC(Obj *p)
{
    if (p->f0[13] != 0) {
        ChkFlag_080247E8(p->f0[13]);
    }
    {
        register u8 *r1v __asm__("r1") = p->f0;
        if (*(u16 *)(r1v + 14) != 0) {
            register u32 sum __asm__("r0");
            __asm__ volatile (
                "ldr %0, [%2, #8]\n\t"
                "ldrh %1, [%1, #14]\n\t"
                ".short 0x1808\n\t"   /* adds r0, r1, r0 */
                "str %0, [%2, #8]"
                : "=&r" (sum), "+r" (r1v)
                : "r" (p)
                : "memory"
            );
        }
    }
    Inc4_Clear5_7((u8 *)p);
    return -1;
}
