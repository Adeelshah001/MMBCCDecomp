/* Sub_0800B320 @ 0x0800B320 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0800b320_MATCHED.c (registry: mmbcc/src/w35c_0800b320_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0800B520(u32 *b, u32 c, u32 d);

extern void Ewram4E40_Init_0B4E4(void);

extern void Clr_0800B4C8(void);

__attribute__((section(".text.w35c_0800b320")))
int Sub_0800B320(u32 *a, u32 *b, u32 c, u32 d)
{
    u8 *base = (u8 *)0x02004e40;
    u8 flag = base[4];
    register u8 g __asm__("r0");
    if ((flag & 15) != 0)
        return 0;
    g = 128 & flag;
    if (g == 0) {
        base[5] = 1;
        return 0;
    }
    *(u32 *)(base + 32) = (u32)a;
    sub_0800B520(b, c, d);
    base[5] = 3;
    Ewram4E40_Init_0B4E4();
    Clr_0800B4C8();
    return 1;
}
