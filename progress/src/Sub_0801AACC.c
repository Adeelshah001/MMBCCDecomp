/* Sub_0801AACC @ 0x0801AACC (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0801aacc_MATCHED.c (registry: mmbcc/src/w36b_0801aacc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef struct { u32 x, y; } Pair;

extern void sub_0800DD08(int *out, u8 *p);

extern void ChipInit_080178A8(u8 a, unsigned b, short c, short d, u32 e);

extern void Sub_1AB34(u8 *p);

__attribute__((section(".text.w36b_0801aacc")))
void Sub_0801AACC(u8 *p)
{
    struct Pair { int a; int b; } tmp;
    u32 *entry;
    {
        register u32 *tbl __asm__("r1") = (u32 *)0x082243d8;
        __asm__ volatile("" : "+r"(tbl));
        entry = (u32 *)((u32)p[9] * 4 + (u32)tbl);
    }
    *(u32 *)(p + 12) = 1;
    *(u32 *)(p + 20) = *(u32 *)(*(u32 *)entry + 4);
    p[10] &= 0xfd;
    p[10] &= 0xfe;
    sub_0800DD08((int *)&tmp, p);
    {
        register int a __asm__("r3") = tmp.a;
        register int b __asm__("r4") = tmp.b;
        {
            register u8 *tbl2 __asm__("r0") = (u8 *)0x082266d8;
            __asm__ volatile("" : "+r"(tbl2));
            ChipInit_080178A8(tbl2[p[16]], ((u32)p[35] << 28) >> 28, (short)a, (short)b, *(u32 *)(p + 44));
        }
    }
    Sub_1AB34(p);
}
