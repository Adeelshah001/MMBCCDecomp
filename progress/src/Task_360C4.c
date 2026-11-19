/* Task_360C4 @ 0x080360C4 (200 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_g2.c (registry: src/wave5_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

/* Task_360C4 @0x080360C4 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 200 bytes in built ROM.
 * Task mode handler: Teardown, switch on p[3] (5 cases):
 * case0 polls sub_0800B148(1,(s16)Sub200_08024514((u8)TblGetByte_241F8(0x1000)),0);
 * case1 nested (u8) checks via Tst_0800B2D8/Sub_0800B320(0x0822EB44,0,0,0);
 * case2 falls through to case3; case4 resets p[0x4699]/p[4] and p[3]=1
 * on (u8)Tst_0800B2F0. Then Setup, return 0.
 * Idioms: literal-0 for stack-passed 5th arg reproduces ROM's
 * `ldr;ldr;mov r4,#0;str r4,[sp]` scheduling. */
void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

u32 TblGetByte_241F8(u32 v);

u32 Sub200_08024514(u32 v);

u32 sub_0800B148(u32 a, u32 b, u32 c);

u32 Tst_0800B2D8(void);

u32 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);

u32 Check_B308(void);

u32 CheckAndSet_B2B4(void);

u32 Tst_0800B2F0(void);

__attribute__((section(".text.w5g_360c4")))
u32 Task_360C4(u8 *p)
{
    EntryMgr_Teardown();
    switch (p[3]) {
    case 0: {
        u8 v = (u8)TblGetByte_241F8(0x1000);
        s16 s = (s16)Sub200_08024514(v);
        if ((u8)sub_0800B148(1, s, 0))
            p[3]++;
        break;
    }
    case 1:
        if ((u8)Tst_0800B2D8()) {
            if ((u8)Sub_0800B320(0x0822EB44, 0, 0, 0))
                p[3]++;
        }
        break;
    case 2:
        if ((u8)Check_B308())
            p[3]++;
    case 3:
        if ((u8)CheckAndSet_B2B4())
            p[3]++;
        break;
    case 4:
        if ((u8)Tst_0800B2F0()) {
            p[0x4699] = 0;
            p[4] = 0;
            p[3] = 1;
        }
        break;
    }
    EntryMgr_Setup();
    return 0;
}
