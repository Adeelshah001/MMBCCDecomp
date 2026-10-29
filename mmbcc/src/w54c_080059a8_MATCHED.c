/* W54-C: 0x080059a8 v3 = v2 + three structural fixes:
 * - First-block sel: ==0 branch order (ROM: bne to sel=0 placed after
 *   the join; v2's !=0 form put sel=0 fall-through before the join).
 * - Base selection: explicit goto form (ROM branch form beq else /
 *   movs #20 / b join / else movs #18 / join; v1/v2 if/else AND ternary
 *   both got if-converted to default-override form with no `b`, which
 *   also killed the mid-pool barrier). Pure C, no asm.
 * - hwbase: vE-style "+r" barrier after its init to defeat the
 *   constant folding that collapsed 0x02003670+0x11AE into one pool
 *   word 0x0200481e in v2 (ROM: two pools + runtime adds). C89-safe:
 *   all declarations precede the barrier statement.
 * Rest unchanged from v2 (tbl unpinned; dma block-local, assignment
 * order dma0/dma1/dma2 + volatile reload; loop as v2).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_08002300(int a, int b);
__asm__(".set Sub_08002300, 0x08002300");
extern void Sub_080086AC(int a);
__asm__(".set Sub_080086AC, 0x080086ac");

__attribute__((section(".text.w54c_080059a8")))
void Sub_080059A8(void)
{
    u8 *tbl = (u8 *)0x02004830;
    s16 i;
    if ((tbl[154 * 4] & 16) != 0) {
        register u16 hw __asm__("r2") = *(u16 *)0x02003670;
        register int sel __asm__("r2");
        if ((hw & 224) == 0)
            sel = (hw & 28) >> 2;
        else
            sel = 0;
        {
            register u8 *callptr __asm__("r1") = (u8 *)0x08172094;
            __asm__ volatile("" : "+r" (callptr));
            __asm__ volatile("add %0, %1, %0" : "+r" (callptr) : "r" (sel) : "cc");
            Sub_08002300(*callptr * 20 + 0x0830B340, 0x5940);
        }
    }
    if (tbl[153 * 4] != 0) {
        u8 *hwbase = (u8 *)0x02003670;
        int r2 = ((u32)tbl[154 * 4] << 28) >> 29;
        u8 B;
        u8 d;
        int e;
        __asm__ volatile("" : "+r" (hwbase));
        B = (u8)(((hwbase[0x11AE] & 4) != 0 ? 20 : 18) - r2);
        d = (u8)(B - tbl[153 * 4]);
        e = B - d;
        {
            u32 e2 = (u32)e << 22;
            u32 v1 = (d << 6) + 0x06002000;
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)(tbl + 156 * 4);
            dma[1] = v1;
            dma[2] = (e2 >> 17) | 0x80000000;
            (void)dma[2];
        }
    }
    for (i = 0; i <= 2; i++)
        Sub_080086AC(i * 12 + 0x02004830);
}
