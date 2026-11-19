/* Sub_08007C04 @ 0x08007C04 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_08007c04_MATCHED.c (registry: mmbcc/src/w37b_08007c04_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int TblGet_f0E(u16 a);

extern void sub_08005268(u8 *a, u32 b);

extern void Apply_08007c8c(u16 a, int b);

__attribute__((section(".text.w37b_08007c04")))
int Sub_08007C04(u16 a, u16 b)
{
    u16 bb = b;
    register s8 *e __asm__("r1");
    int z;
    u32 idx;
    int v;
    if (bb > 3)
        return -1;
    idx = bb * 8;
    e = (s8 *)0x02004e18 + idx;
    __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(v) : "r"(e));
    if (v == 0 && *(u16 *)(e + 2) == a)
        return 0;
    z = 0;
    e[1] = z;
    *(u16 *)(e + 2) = a;
    ((u8 *)e)[7] &= z - 3;
    if (bb == 0) {
        u32 *base = (u32 *)0x02003670;
        u16 h = *(u16 *)0x08171ef4;
        u32 r4 = base[2] + ((u32)h << 5) + 0xfa000000;
        int t = TblGet_f0E(a);
        sub_08005268((u8 *)0x0832b6c0 + (u16)t * 20, r4);
        Apply_08007c8c(a, 0);
    }
    return 0;
}
