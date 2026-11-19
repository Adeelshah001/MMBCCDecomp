/* Sub_0800BFD0 @ 0x0800BFD0 (232 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w53a_0800bfd0_MATCHED.c (registry: src/w53a_0800bfd0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u8 g_02004f40[];

extern u8 tbl_08329430[];

extern u16 g_020031e8;

extern u8 tbl_0832943c[];

extern u8 tbl_0832afdc[];

extern void sub_0800244C(u8 *a, int b);

extern void Sub_0800288C(u8 *a, int b);

__attribute__((section(".text.w53a_0800bfd0")))
void Sub_0800BFD0(int arg)
{
    u16 au = (u16)arg;
    s16 a;
    g_02004f40[4] = (u8)au;
    a = (s16)au;
    if (a != -1) {
        register u32 *gp __asm__("r8");
        int i4;
        int e20;
        u8 *entry;
        register u8 *base __asm__("r0");
        u16 count;
        register u16 bound __asm__("sl");
        short i;
        gp = (u32 *)0x020038ac;
        __asm__ volatile("" : "+r" (gp));
        i4 = a * 4;
        e20 = a * 20;
        { register u32 poolv __asm__("r1"); poolv = (u32)tbl_08329430; entry = (u8 *)(e20 + poolv); }
        *(u8 **)(g_02004f40 + 16) = entry;
        sub_0800244C(entry, ((g_020031e8 & 12) << 12) + 32);
        { register u8 *t2 __asm__("r3"); t2 = tbl_0832943c; Sub_0800288C((u8 *)(e20 + (u32)t2), 64); }
        base = tbl_0832afdc + *(u32 *)(tbl_0832afdc + i4);
        {
            register u8 *src __asm__("r3");
            src = (u8 *)(i4 + (int)base + 4);
            __asm__ volatile("" : "+r" (src));
            count = *(u16 *)src;
            bound = *(u16 *)(src + 2);
        }
        i = 0;
        if (i < bound) {
            register u32 g __asm__("r9");
            int a4;
            register u8 *ip __asm__("ip");
            { register u32 *at __asm__("r7"); register u32 gtmp __asm__("r7"); at = gp; gtmp = *at; g = gtmp; }
            a4 = i4;
            ip = base;
            do {
                u16 *dst = (u16 *)(g + 0x702);
                short j;
                register u8 *sp __asm__("r3");
                dst += i * 32;
                sp = (u8 *)(a4 + (int)ip + 8);
                sp += i * count * 2;
                j = 0;
                if (j < count) {
                    do {
                        *dst = (u16)(0x2001 + *(u16 *)sp);
                        dst++;
                        sp += 2;
                        j++;
                    } while (j < count);
                }
                i++;
            } while (i < bound);
        }
    }
}
