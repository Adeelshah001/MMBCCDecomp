/* Sub_0804990C @ 0x0804990C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35d_0804990c_MATCHED.c (registry: mmbcc/src/w35d_0804990c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void FlagBit_Set_11D68(u8 w, u8 one);

__attribute__((section(".text.w35d_0804990c")))
void Sub_0804990C(void)
{
    register u8 *base __asm__("r2") = (u8 *)0x020070F0;
    register u8 *tbl __asm__("r3") = (u8 *)0x082344E0;
    register u8 v __asm__("r0");
    u8 vp1;
    u8 w;
    __asm__ volatile("" : "+r"(base), "+r"(tbl));
    v = base[21];
    vp1 = v + 1;
    base[21] = vp1;
    __asm__ volatile("" : "+r"(v));
    {
        u32 idx = v;
        idx += (u32)tbl;
        w = *(u8 *)idx;
    }
    FlagBit_Set_11D68(w, 1);
}
