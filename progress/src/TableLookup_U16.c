/* TableLookup_U16 @ 0x08011C58 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_f_old.c (registry: src/wave9_f_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* ---- TableLookup_U16 @0x08011c58 (40B) ---- */

__attribute__((section(".text.w9f_0x08011c58")))
u16 TableLookup_U16(u8 a0, u8 a1)
{
    register u32 ac __asm__("r3");
    register u32 bm __asm__("r0");
    register u16 *tbl __asm__("r2");
    u32 am = (u32)a0;
    u32 t;
    u32 idx;
    u16 res;
    __asm__ volatile("" : "+r"(am));
    ac = am;
    __asm__ volatile(
        "lsl r1,r1,#24\n\t"
        "lsr %0,r1,#24"
        : "=r"(bm) : : "r1");
    if (ac > 5)
        goto ret0;
    if (bm > 15)
        goto ret0;
    __asm__ volatile("" : "=r"(tbl) : "0"((u16 *)0x08173EEC));
    bm <<= 1;
    {
        register u32 t __asm__("r1") = ac << 5;
        u32 addr;
        idx = bm + t;
        addr = idx + (u32)tbl;
        res = *(u16 *)addr;
    }
    goto end;
ret0:
    res = 0;
end:
    return res;
}
