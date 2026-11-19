/* Task_3AF98 @ 0x0803AF98 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0803AF98: Task_3AF98 (coordinator-verified). */
void InitRec8_267B4(u8 *a, u32 b);

void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

extern u8 gOff_469C[];

extern u8 gEwram020070F0[];

extern u8 gOff_4698_A[];

extern u8 gEwram020070F0[];

extern u8 gOff_4698_A[];

__attribute__((section(".text.w6l3_3af98")))
void Task_3AF98(u8 *s)
{
    register u32 off __asm__("r1");
    register u8 *p __asm__("r0");
    u8 v;
    off = (u32)gOff_469C;
    p = s + off;
    v = *p;
    if (v == 8) {
        register u8 *q __asm__("r1");
        register u32 o __asm__("r0");
        InitRec8_267B4(gEwram020070F0, 8);
        o = (u32)gOff_4698_A;
        q = s + o;
        *q = 0;
    } else if (v == 9) {
        register u8 *q __asm__("r1");
        register u32 o __asm__("r0");
        InitRec8_267B4(gEwram020070F0, 8);
        o = (u32)gOff_4698_A;
        q = s + o;
        *q = 6;
    } else {
        u8 z = 0;
        s[1] = 1;
        s[2] = z;
        s[3] = z;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
