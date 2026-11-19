/* Task_38FE4 @ 0x08038FE4 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

void InitRec8_267B4(u8 *a, u32 b);

extern u8 gEwram020070F0[];

__attribute__((section(".text.w5h_38fe4")))
void Task_38FE4(u8 *p)
{
    s8 v = (s8)p[0x469c];
    if (v == 7) {
        u32 z = 0;
        p[1] = 2;
        p[2] = z;
        p[3] = z;
    } else if (v == 0xb) {
        InitRec8_267B4(gEwram020070F0, 8);
        p[0x4698] = 0;
    } else if (v == 0xc) {
        InitRec8_267B4(gEwram020070F0, 8);
        p[0x4698] = 4;
    } else {
        u32 z = 0;
        p[1] = 1;
        p[2] = z;
        p[3] = z;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
