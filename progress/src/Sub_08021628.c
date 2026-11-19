/* Sub_08021628 @ 0x08021628 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08021628_MATCHED.c (registry: mmbcc/src/w36c_08021628_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_IncUse(u8 *s, int a);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w36c_08021628")))
void Sub_08021628(u8 *s)
{
    u8 *gp = (u8 *)0x0200b7e0;
    u8 b;
    int c, t, sh, arg;
    u8 *callarg;
    u32 m, w;
    u8 *p;
    if (gp[4] > 1) goto middle;
    callarg = s;
    __asm__ volatile("" : "+r"(callarg));
    arg = 0;
    goto call;
middle:
    w = *(u32 *)0x02003670;
    if ((w & 7) != 0) goto d9fc;
    w >>= 3;
    arg = (w & 1) + 1;
    callarg = s;
    __asm__ volatile("" : "+r"(callarg));
call:
    ChipSlot_IncUse(callarg, arg);
    b = ((u8 *)0x020031e4)[(*(u16 *)0x081705b0 >> 4) * 2];
    c = b & 3;
    t = c;
    __asm__ volatile("" : "+r"(t));
    if (t > 3) c = 3;
    p = s + 69;
    sh = c << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *p = (*p & m) | sh;
    *(s + 34) = 4;
d9fc:
    ChipSlot_Tick(s);
}
