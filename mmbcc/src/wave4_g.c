/* MMBCCDecomp — Wave 4 batch G staged matches (worker G).
 * MATCHED 2026-10-20. 1/37 functions byte-identical (main agbcc -O2
 * -mthumb-interwork unless noted). 3 BLOCKED (see docs/match_notes_wave4_g.md).
 *
 * Functions (all names tentative — inferred from behavior only):
 *  0x08000CD4 TaskMgr_Update   (130 B) task/object manager; iterates 3 entries
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). Remove each .set when that symbol gets
 * a real definition (duplicate-symbol otherwise).
 *
 * Landing notes:
 * - TaskMgr_Update (0x08000CD4): compiled section is 152 B (130 code + 22 pool);
 *   ROM has 130 B code with pool at 0x08000D58 (after function). The pool is
 *   shared/placed by the linker; verify pool placement on landing.
 * - Calls sub_080002dc (0x080002DC) which is UNMATCHED — forward reference;
 *   coordinator must ensure it resolves on landing.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u8 gIwram_030005c0[];
void Task_Register(int index, void *handler);
void sub_080002dc(u8 *a, u32 b, u32 c, u8 *d);

/* 0x08000CD4: Task/object manager. Iterates 3 entries (0x18 bytes each) at
 * 0x030023C8. Each entry: +0 u8 state, +1 u8 flag, +2 u16 counter, +4/+8 u32 args.
 * If state&9==0 and state&4!=0: decrement counter; when it hits 0 set state=2.
 * If state==2 and +1!=0: Task_Register(cnt, *(entry+4)). Then calls
 * sub_080002dc(entry, *(entry+4), *(entry+8), 0x02000800). Repeats while
 * *(u32*)0x030023C4 != 0. Tentative name.
 *
 * The `t4` inline asm is required: pure C `(s0 & 4)` puts the AND dest in the
 * variable's register (r1), but ROM has `ands r0,r1` (dest r0 = const reg).
 * The asm forces `movs r0,#4; and r0,r1` (encodes as 0x4008, same as ands).
 */
__attribute__((section(".text.w4g_taskmgrupdate")))
void TaskMgr_Update(void)
{
    u8 *base = gIwram_030005c0;
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
                    sub_080002dc(entry, *(u32 *)(entry + 4), *(u32 *)(entry + 8), (u8 *)0x02000800);
                }
            }
            (*cnt)++;
            entry += 0x18;
        } while (*cnt <= 2);
        (*(u32 *)(base + 0x1e00))++;
    } while (*flag != 0);
}

__asm__(
    ".globl gIwram_030005c0\n.set gIwram_030005c0, 0x030005c0\n"
    ".globl sub_080002dc\n.set sub_080002dc, 0x080002DC\n"
);
