/* StateMachine_08035170 @ 0x08035170 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_08035170.c (registry: src/w17d_08035170.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Set_08004E24(u8 x);

extern void EntryMgr_Teardown(void);

extern int Cmp_08004E0C(u8 x);

extern void EntryMgr_Setup(void);

__attribute__((section(".text.w17d_08035170")))
u32 StateMachine_08035170(u8 *p)
{
    u8 t = p[5];
    switch (t) {
    case 0:
        Set_08004E24(0);
        p[5]++;
        /* fallthrough */
    case 1: {
        u32 m;
        u16 *p1;
        EntryMgr_Teardown();
        if ((Cmp_08004E0C(3) << 24) != 0) {
            p1 = (u16 *)0x020031e0;
            m = 0xedff;
            m &= *p1;
            {
                u8 z = 0;
                m &= 0xdbff;
                *p1 = (u16)m;
                p[4] = 4;
                p[5] = z;
            }
        }
        EntryMgr_Setup();
        break;
    }
    default:
        break;
    }
    return 0;
}
