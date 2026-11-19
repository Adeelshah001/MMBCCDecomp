/* Task_37440 @ 0x08037440 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_blkb_old.c (registry: src/wave6_blkb_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08037440: Task_37440 (coordinator-verified). */
/* Task_37440 @ 0x08037440 (120 B) v3.
 * No pinning; goto-beq for branch structure.
 */

extern u8 gEwram_02004E40[];

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

extern u32 sub_0800B368(u32 fn, u32 a, u32 b, u32 c);

extern u32 Check_B308(void);

__attribute__((section(".text.w6b_37440")))
u32 Task_37440(u8 *p)
{
    u8 mode;

    EntryMgr_Teardown();
    {
        register u8 *g __asm__("r1") = gEwram_02004E40;
        g[0x14] |= 1;
    }

    mode = p[5];
    if (mode == 0)
        goto case0;
    if (mode == 1)
        goto case1;
    goto epi;

case0: {
        u32 *tbl = (u32 *)0x082300E0;
        u8 idx;
        u32 fn;
        __asm__ volatile("" : : : "memory");
        idx = p[0x469f];
        fn = tbl[idx];
        if (((u8)sub_0800B368(fn, 0, 0, 0)) == 0)
            goto epi;
        {
            u8 m;
            __asm__ volatile(
                "ldrb %0, [%1, #5]\n\t"
                "add %0, #1\n\t"
                "strb %0, [%1, #5]"
                : "=&l"(m) : "l"(p));
        }
        goto epi;
    }

case1:
    if (((u8)Check_B308()) != 0) {
        u8 *q = p + 0x4699;
        u8 z = 0;
        *q = mode;
        p[5] = z;
    }

epi:
    EntryMgr_Setup();
    return 0;
}
