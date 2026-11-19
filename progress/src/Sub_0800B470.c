/* Sub_0800B470 @ 0x0800B470 (86 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0800b470_MATCHED.c (registry: mmbcc/src/w36a_0800b470_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08007DE8(u32 a, u32 b);

extern void Sub_08007C04(u32 a, u32 b);

__attribute__((section(".text.w36a_0800b470")))
void Sub_0800B470(u16 idx)
{
    u8 *s = (u8 *)0x02004e40;
    register u8 b __asm__("r1");
    register u32 v __asm__("r0");
    b = s[21];
    v = ((u32)b << 28) >> 28;
    switch (v) {
    case 0:
        idx = 0;
        break;
    case 1:
    case 3:
        sub_08007DE8(idx, 0);
        break;
    case 2:
    case 4:
        Sub_08007C04(idx, 0);
    default:
        break;
    }
    *(u16 *)(s + 6) = idx;
}
