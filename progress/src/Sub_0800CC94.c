/* Sub_0800CC94 @ 0x0800CC94 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800cc94_MATCHED.c (registry: mmbcc/src/w36b_0800cc94_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Q { u16 a; u16 b; u16 c; u16 d; u16 e; u16 f; };

extern void Sub_0800CF10(u8 *p, u8 v, int one);

extern void sub_080006DC(int a, u32 b, int c);

__attribute__((section(".text.w36b_0800cc94")))
void Sub_0800CC94(void)
{
    s8 v = *(s8 *)(0x08173530 + *(u8 *)0x02000ec0 * 2);
    if (v >= 0) {
        Sub_0800CF10((u8 *)0x02000ec0, (u8)v, 1);
        ((struct Q *)0x020031e0)->a |= 0x3800;
    } else {
        ((struct Q *)0x020031e0)->a &= 0xc7ff;
        sub_080006DC(0, ((((struct Q *)0x020031e0)->f & 0x1f00) << 3) + 0x06000000, 0x1000);
    }
}
