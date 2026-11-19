/* GuardedListInit_0800E650 @ 0x0800E650 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800e650.c (registry: src/w15c_0800e650.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 IsZero_02005160_080103cc(void);

extern void SetByte20_Clear21to23_02005130(u8 x);

extern void ListIterate_D568(u8 *p);

__attribute__((section(".text.w15c2_0800E650")))
void GuardedListInit_0800E650(void)
{
    u16 *p = (u16 *)0x02005130;
    u8 z = 0;
    p[12] = 1;
    if ((s8)IsZero_02005160_080103cc() == 1) {
        p[12] = z;
        SetByte20_Clear21to23_02005130(z);
    }
    ListIterate_D568(*(u8 **)0x02005270);
    ListIterate_D568(*(u8 **)0x020053C0);
}
