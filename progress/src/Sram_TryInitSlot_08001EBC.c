/* Sram_TryInitSlot_08001EBC @ 0x08001EBC (90 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22d_08001ebc.c (registry: mmbcc/src/w22d_08001ebc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

typedef struct {
    u8 pad0[13];
    u8 mode;
    u8 pad1[3];
    u8 f17;
    u8 pad2[17];
    u8 f35;
    u8 pad3[8];
    u32 f44;
    u8 pad4[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern u32 Sram_VerifySlot(u32 a0, u32 key);

__attribute__((section(".text.w22d_08001EBC")))
s32 Sram_TryInitSlot_08001EBC(u8 a, u32 b, u32 c)
{
    register u8 *S __asm__("r4");
    u8 s0;

    if (a > 1)
        return -1;
    S = (u8 *)0x02002F80;
    s0 = S[0];
    if (s0 != 0)
        return -1;
    if (Sram_VerifySlot(a, c) == 0)
        return -1;
    if (c > 0x2010)
        return -1;
    S[1] = a;
    *(u32 *)(S + 8) = b;
    *(u32 *)(S + 20) = c;
    *(u16 *)(S + 30) = s0;
    S[0] = 1;
    *(u16 *)(S + 2) = 2;
    return 0;
}
