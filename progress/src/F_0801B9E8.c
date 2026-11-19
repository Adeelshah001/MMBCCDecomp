/* F_0801B9E8 @ 0x0801B9E8 (172 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w42a_0801b9e8_MATCHED.c (registry: mmbcc/src/w42a_0801b9e8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Wrapper_D770(u8 *a, u32 b, u32 c);

extern void ChipSlot_IncUse(u8 *a, u32 b);

extern void Sub_0801BA94(u8 *a);

__attribute__((section(".text.w42a_0801b9e8")))
void F_0801B9E8(u8 *s)
{
    register u8 *tbl2 __asm__("r4");
    u32 idx;
    u32 *slot;
    u32 *tbase;
    tbase = (u32 *)0x082243d8;
    __asm__ volatile("" ::: "memory");
    slot = tbase + s[9];
    {
        register u32 one __asm__("r1") = 1;
        *(u32 *)(s + 12) = one;
        *(u32 *)(s + 20) = *(u32 *)(*slot + 4);
        *(u32 *)(s + 108) = 0;
        s[10] = (s[10] | 2) | one;
    }
    tbl2 = (u8 *)0x08226838;
    {
        u8 *addr;
        register u32 v __asm__("r2");
        register u32 arg __asm__("r1");
        addr = (u8 *)(s[16] * 2 + (u32)tbl2);
        v = 2048;
        __asm__ volatile("add %0, %1, #0" : "=r" (arg) : "r" (v));
        arg |= *addr;
        Wrapper_D770(s, arg, 0);
    }
    {
        u32 off;
        u8 *addr2;
        off = s[16] * 2;
        __asm__ volatile("" ::: "memory");
        tbl2++;
        addr2 = (u8 *)(off + (u32)tbl2);
        ChipSlot_IncUse(s, *addr2);
    }
    s[18] = 0;
    *(u32 *)(s + 92) = 0xfffffa00;
    *(u32 *)(s + 100) = 128;
    {
        int idx;
        int t;
        u8 *p69;
        u32 sh;
        u32 m;
        idx = (*(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1))) & 3;
        __asm__ volatile("add %0, %1, #0" : "=r" (t) : "r" (idx));
        if (t > 3)
            idx = 3;
        p69 = s + 69;
        sh = idx << 2;
        m = *p69 & ~12;
        *p69 = m | sh;
    }
    s[34] = 14;
    Sub_0801BA94(s);
}
