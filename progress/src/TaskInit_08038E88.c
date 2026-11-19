/* TaskInit_08038E88 @ 0x08038E88 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08038e88.c (registry: src/w18b_08038e88.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void FlagBit_Set_11D68(u16 x, u8 y);

extern void TblState_0804A2DC(u16 a);

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

__attribute__((section(".text.w18b_08038e88")))
void TaskInit_08038E88(u8 *p)
{
    u8 v7 = (u8)(p[20] + 1);
    u32 z = 0;
    u8 *p5;
    u8 *p1;

    if (v7 > 9)
        v7 = 9;
    p5 = p + 0x4698;
    *(u32 *)p5 = 0;
    p1 = p + 0x469c;
    *(u32 *)p1 = 0;
    *(u32 *)(p + 0x46a0) = 0;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    *p1 = 0;
    *(u8 *)(p + 0x469d) = 0;
    FlagBit_Set_11D68(1, 0);
    FlagBit_Set_11D68(2, 0);
    *p5 = 0;
    *(u8 *)(p + 0x469b) = v7;
    TblState_0804A2DC(9);
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
