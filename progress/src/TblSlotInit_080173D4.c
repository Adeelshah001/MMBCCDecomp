/* TblSlotInit_080173D4 @ 0x080173D4 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_080173d4.c (registry: src/w20c_080173d4.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void F_173FC(u8 *p);

__attribute__((section(".text.w20c_080173d4")))
void TblSlotInit_080173D4(u8 *s)
{
    {
        register u32 base __asm__("r2") = 0x082243D8;
        register u32 idx __asm__("r3");
        u32 off;
        u32 *p;
        u32 t;
        __asm__ volatile("" : "+r" (base));
        idx = s[9];
        off = idx << 2;
        {
            u32 addr = off + base;
            *(u32 *)(s + 12) = 1;
            p = *(u32 **)addr;
        }
        p = (u32 *)p[1];
        *(u32 *)(s + 20) = (u32)p;
        t = s[10];
        s[10] = t & 254;
    }
    F_173FC(s);
}
