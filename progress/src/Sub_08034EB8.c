/* Sub_08034EB8 @ 0x08034EB8 (114 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08034eb8_MATCHED.c (registry: mmbcc/src/w36b_08034eb8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblGet_f0A(u8 b);

extern u32 Scramble_400A8(void);

extern u32 SMod_0804DDA0(u32 a, u32 b);

__attribute__((section(".text.w36b_08034eb8")))
u8 Sub_08034EB8(u8 *base, u8 arg1)
{
    register u8 *b8 __asm__("r8");
    u8 buf[12];
    u8 target;
    u8 count;
    u8 res;
    u8 i;
    b8 = base;
    target = arg1;
    count = 0;
    res = count;
    for (i = 1; i <= 11; i++) {
        u8 *elem = i * 12 + b8;
        if ((u8)TblGet_f0A(*elem) == target && *elem != 0) {
            buf[count] = *elem;
            count++;
        }
    }
    if (count != 0) {
        u16 rnd = Scramble_400A8();
        u32 idx = SMod_0804DDA0(rnd, count);
        res = buf[idx];
    }
    return res;
}
