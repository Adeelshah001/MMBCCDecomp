/* Sub_08023BC4 @ 0x08023BC4 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08023bc4_MATCHED.c (registry: mmbcc/src/w36b_08023bc4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 SMod_0804DDA0(u32 idx, int n);

__attribute__((section(".text.w36b_08023bc4")))
void Sub_08023BC4(u8 *dst, u8 *base, u32 arg2)
{
    register u8 *b9 __asm__("r9") = base;
    u32 shifted = arg2 << 24;
    u8 i = 0;
    register u32 r8 __asm__("r8") = ((224 << 19) & shifted) >> 24;
    register u32 sl __asm__("sl") = shifted >> 27;
    for (; i <= 13; i++) {
        u8 *out = dst + i;
        u32 idx = i + sl;
        u32 off = SMod_0804DDA0(idx, 14);
        int b = *(b9 + off);
        int res = b << r8;
        *out = res;
        if (r8 != 0) {
            u32 off2 = SMod_0804DDA0(idx + 1, 14);
            u8 *p2 = b9 + off2;
            res |= *p2 >> (8 - (int)r8);
            *out = res;
        }
    }
}
