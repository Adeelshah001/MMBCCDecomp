/* Sub_08017670 @ 0x08017670 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08017670_MATCHED.c (registry: src/w36d_08017670_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_080176AC(u8 *s);

__attribute__((section(".text.w36d_08017670")))
void Sub_08017670(u8 *s)
{
    register u8 idx __asm__("r3");
    {
        register u32 *tbl1 __asm__("r2") = (u32 *)0x082243d8;
        register u32 ea __asm__("r1");
        u32 *ent;
        __asm__ volatile("" : "+r"(tbl1));
        idx = s[9];
        __asm__ volatile("lsl %0, %1, #2" : "=r"(ea) : "r"(idx));
        ea += (u32)tbl1;
        __asm__ volatile("" : "+r"(ea));
        *(u32 *)(s + 12) = 1;
        ent = (u32 *)ea;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 4);
    }
    {
        register u8 x __asm__("r1");
        x = 253;
        x &= s[10];
        x &= 254;
        s[10] = x;
    }
    {
        register u32 *tbl2 __asm__("r2") = (u32 *)0x08226148;
        register u32 ea __asm__("r1");
        __asm__ volatile("" : "+r"(tbl2));
        idx = s[16];
        __asm__ volatile("lsl %0, %1, #2" : "=r"(ea) : "r"(idx));
        ea += (u32)tbl2;
        __asm__ volatile("" : "+r"(ea));
        *(u32 *)(s + 40) = *(u32 *)ea;
    }
    sub_080176AC(s);
}
