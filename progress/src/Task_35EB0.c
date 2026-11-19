/* Task_35EB0 @ 0x08035EB0 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_k_old.c (registry: src/wave4_k_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u32 Set_08004E24(u32 v);

u32 Cmp_08004E0C(u32 v);

void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

extern u16 gEwram_020031E0[];

/* 0x08035EB0: mode dispatch, mask-clear variant. Tentative. OLD_AGBCC. */
__attribute__((section(".text.w4k_t35eb0")))
void Task_35EB0(u8 *p)
{
    switch (p[2]) {
    case 0:
        Set_08004E24(0);
        p[2]++;
    case 1: {
        EntryMgr_Teardown();
        if ((u8)Cmp_08004E0C(3) != 0) {
            u8 z = 0;
            u16 v;
            p[1] = 4;
            p[3] = z;
            p[2] = z;
            { u16 *g = gEwram_020031E0; v = 0xEDFF; v &= g[0]; v &= 0xDBFF; g[0] = v; }
        }
        EntryMgr_Setup();
        break;
    }
    }
}
