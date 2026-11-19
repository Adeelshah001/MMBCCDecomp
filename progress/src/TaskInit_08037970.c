/* TaskInit_08037970 @ 0x08037970 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18b_08037970.c (registry: src/w18b_08037970.c).
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

__attribute__((section(".text.w18b_08037970")))
void TaskInit_08037970(u8 *p)
{
    u32 z = 0;
    u8 *p2;
    u8 i;

    *(u32 *)(p + 0x4698) = 0;
    p2 = p + 0x469c;
    *(u32 *)p2 = 0;
    *(u32 *)(p + 0x46a0) = 0;
    *(u32 *)(p + 0x46a4) = 0;
    p[1] = 1;
    p[3] = 0;
    p[2] = 0;
    *p2 = 0;
    *(u8 *)(p + 0x469d) = 0;
    FlagBit_Set_11D68(1, 0);
    FlagBit_Set_11D68(2, 0);
    FlagBit_Set_11D68(54, 0);
    TblState_0804A2DC(9);
    {
        u32 pp = (u32)p;
        i = 0;
        do {
            *(u8 *)(i + pp + 0x45ac) = 8;
            i = (u8)(i + 1);
        } while (i <= 3);
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
