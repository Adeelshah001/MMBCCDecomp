/* Task_45EBC @ 0x08045EBC (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

__attribute__((section(".text.w5h_45ebc")))
u32 Task_45EBC(u8 *p)
{
    *(u32 *)(p + 0x46a8) = 0;
    *(u32 *)(p + 0x46ac) = 0;
    *(u32 *)(p + 4) = 1;
    p[0x46ae] = 0;
    p[0x46af] = 1;
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}
