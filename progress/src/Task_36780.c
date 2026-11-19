/* Task_36780 @ 0x08036780 (96 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_k.c (registry: src/wave4_k.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void LoadCallClear_4A328(void);

void InitRec8_267B4(u8 *a, u32 b);

void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

extern u8 gEwram020070F0[];

/* 0x08036780: mode-to-value map. Tentative. */
__attribute__((section(".text.w4k_t36780")))
void Task_36780(u8 *p)
{
    InitRec8_267B4(gEwram020070F0, 8);
    LoadCallClear_4A328();
    if (p[0x469F] == 0) {
        p[0x4698] = 1;
    } else if (p[0x469F] == 1) {
        p[0x4698] = 2;
    } else if (p[0x469F] == 2) {
        p[0x4698] = 3;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
