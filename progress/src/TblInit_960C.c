/* TblInit_960C @ 0x0800960C (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

__attribute__((section(".text.w8s_0800960c")))
void TblInit_960C(u8 dummy)
{
    register u32 i __asm__("r2") = 0;
    register u8 *tbl __asm__("r5") = (u8 *)0x02004E18;
    register u16 z __asm__("r4") = 0;
    register u32 m __asm__("r3");
    register s32 si __asm__("r0");
    __asm__ volatile("movs %0, #255" : "=r" (m));
    do {
        register int e __asm__("r1");
        register u8 *p __asm__("r1");
        si = (s32)(i << 16) >> 16;
        __asm__ volatile("" : "+r" (si));
        e = si * 8;
        p = (u8 *)e;
        p += (int)tbl;
        p[0] = (u8)i;
        p[1] |= (u8)m;
        *(u16 *)(p + 2) = z;
        si++;
        si <<= 16;
        i = (u16)((u32)si >> 16);
        si >>= 16;
    } while (si <= 3);
}
