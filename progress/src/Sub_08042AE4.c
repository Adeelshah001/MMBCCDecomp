/* Sub_08042AE4 @ 0x08042AE4 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21b_08042ae4.c (registry: src/w21b_08042ae4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 EwGet16_18(void);

extern void F_080248AC(u32);

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

__attribute__((section(".text.w21b_08042AE4")))
u32 Sub_08042AE4(u8 *a)
{
    u32 off = 18099;
    *(u32 *)(a + 18088) = 0;
    *(u32 *)(a + 18092) = 0;
    *(u32 *)(a + 18096) = 0;
    a[7] = a[4];
    a[4] = 1;
    a[5] = 0;
    a[6] = 0;
    a[18092] = 5;
    a[18096] = 0;
    a[18098] = 0;
    a[18097] = 1;
    if (EwGet16_18() > 7) {
        a[off] = 1;
    } else {
        a[off] = 0;
    }
    F_080248AC(0);
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}
