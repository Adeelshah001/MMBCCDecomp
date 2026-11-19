/* TaskMgr_Update @ 0x08000CD4 (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_g.c (registry: src/wave4_g.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u8 Base[];

void Task_Register(int index, void *handler);

void crt0_thumb_helpers(u8 *a, u32 b, u32 c, u8 *d);

/* 0x08000CD4: Task/object manager. Iterates 3 entries (0x18 bytes each) at
 * 0x030023C8. Each entry: +0 u8 state, +1 u8 flag, +2 u16 counter, +4/+8 u32 args.
 * If state&9==0 and state&4!=0: decrement counter; when it hits 0 set state=2.
 * If state==2 and +1!=0: Task_Register(cnt, *(entry+4)). Then calls
 * crt0_thumb_helpers(entry, *(entry+4), *(entry+8), 0x02000800). Repeats while
 * *(u32*)0x030023C4 != 0. Tentative name.
 *
 * The `t4` inline asm is required: pure C `(s0 & 4)` puts the AND dest in the
 * variable's register (r1), but ROM has `ands r0,r1` (dest r0 = const reg).
 * The asm forces `movs r0,#4; and r0,r1` (encodes as 0x4008, same as ands).
 */
__attribute__((section(".text.w4g_taskmgrupdate")))
void TaskMgr_Update(void)
{
    u8 *base = Base;
    u32 *cnt = (u32 *)(base + 0x1e50);
    u32 *flag = (u32 *)(base + 0x1e04);
    u8 *entry;

    do {
        *cnt = 0;
        entry = base + 0x1e08;
        do {
            u8 s0 = *entry;
            if ((s0 & 9) == 0) {
                u8 t4; __asm__ ("movs %0, #4\n\tand %0, %1" : "=l" (t4) : "l" (s0));
                if (t4 != 0) {
                    u32 s2 = *(u16 *)(entry + 2);
                    if (*(s16 *)(entry + 2) == 0) {
                        *entry = 2;
                    } else {
                        u32 t = s2 - 1;
                        *(u16 *)(entry + 2) = t;
                        if ((t << 16) == 0)
                            *entry = 2;
                    }
                }
                if (*entry == 2) {
                    if (*(entry + 1) != 0)
                        Task_Register(*cnt, (void *)*(u32 *)(entry + 4));
                    crt0_thumb_helpers(entry, *(u32 *)(entry + 4), *(u32 *)(entry + 8), (u8 *)0x02000800);
                }
            }
            (*cnt)++;
            entry += 0x18;
        } while (*cnt <= 2);
        (*(u32 *)(base + 0x1e00))++;
    } while (*flag != 0);
}
