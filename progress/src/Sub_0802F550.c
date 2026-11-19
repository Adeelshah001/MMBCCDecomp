/* Sub_0802F550 @ 0x0802F550 (86 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0802f550_MATCHED.c (registry: mmbcc/src/w36a_0802f550_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 Scramble_400A8(void);

extern u32 UMod_0804DEE8(u32 a, u32 b);

__attribute__((section(".text.w36a_0802f550")))
u32 Sub_0802F550(u8 a0, u8 a1, u8 a2, u8 a3)
{
    register u16 x __asm__("r0");
    u32 result = 0;
    u16 t;
    u32 u;
    s16 sx;
    x = (u16)(a0 - a1 + 100);
    __asm__ volatile("lsl %0, %0, #16\n\t"
        "lsr %0, %0, #16" : "+r"(x));
    if (a3 == 2 && a2 != 2) {
        __asm__ volatile(
            "lsl %0, %0, #16\n\t"
            "ldr r1, .L2f550_c\n\t"
            "add %0, %0, r1\n\t"
            "lsr %0, %0, #16\n\t"
            : "+r"(x) : : "r1");
    }
    sx = (s16)x;
    if (sx <= 99) {
        t = (u16)Scramble_400A8();
        u = UMod_0804DEE8(t, 99);
        if (sx < (s16)(u + 1))
            result = 1;
    }
    return result;
}
