/* Sub_08010B30 @ 0x08010B30 (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08010b30_MATCHED.c (registry: mmbcc/src/w36b_08010b30_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef u8 (*Func)(u8 *s);

extern Func Table2[];

extern void EntryMgr_Teardown(void);

extern void ListIterate_D568(u32 x);

extern void Sub_0800D59C(u32 x);

extern void Sub_0801112C(u8 x);

extern void EntryMgr_Setup(void);

__attribute__((section(".text.w36b_08010b30")))
void Sub_08010B30(void)
{
    u8 *base = (u8 *)0x020051b0;
    if ((1 & base[15]) == 0) {
        EntryMgr_Teardown();
        base[4] = ((Func *)0x08173eb8)[base[4]](base);
        if (base[20] != 0) {
            base[20]--;
        }
        ListIterate_D568(*(u32 *)0x020053c0);
        Sub_0800D59C(*(u32 *)0x020053c0);
        Sub_0801112C(base[2]);
        EntryMgr_Setup();
    } else {
        base[4] = Table2[base[4]](base);
    }
}
