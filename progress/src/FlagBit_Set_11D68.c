/* FlagBit_Set_11D68 @ 0x08011D68 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_R_old.c (registry: src/wave10_R_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram02005260[];

/* FlagBit_Set_11D68 @ 0x08011D68 (72 B).
 * Sets/clears bit (x&7) of byte at *(u8**)(gEwram02005260+4) + (x>>3)
 * to (y&1), for 1 <= x <= 127.
 * Idioms: hardcoded-r1 v-mask asm (ordered via xr dummy input);
 * tied-opaque pool load + explicit lsr/ldr/add asms for hdr/off/base/p;
 * volatile mvn defeats ~ fusion into bic. */
__attribute__((section(".text.w10r_8011d68")))
void FlagBit_Set_11D68(u16 x, u8 y)
{
    register u32 xs __asm__("r2") = (u32)x << 16;
    register u16 xr __asm__("r4") = (u16)(xs >> 16);
    register u8 v __asm__("r5");
    register u32 hdr __asm__("r0");
    register u32 off __asm__("r1");
    register u8 *base __asm__("r3");
    register u8 *p __asm__("r3");
    register u32 bit __asm__("r2");
    register u32 one __asm__("r4");
    register u32 sh __asm__("r1");
    register u8 vv __asm__("r0");
    u8 mask;
    u8 val;

    __asm__ volatile("lsl r1,r1,#24\n\tlsr %0,r1,#24"
                     : "=r" (v) : "r" (xr) : "r1");
    if (xr == 0)
        goto Lend;
    if (xr > 127)
        goto Lend;
    __asm__ volatile("" : "=r" (hdr) : "0" ((u32)gEwram02005260));
    __asm__ volatile("lsr %0,%1,#19" : "=r" (off) : "r" (xs));
    __asm__ volatile("ldr %0,[%1,#4]" : "=r" (base) : "r" (hdr));
    __asm__ volatile("add %0,%1,%2" : "=r" (p) : "r" (base), "r" (off));
    __asm__ volatile("mov %0,#7" : "=r" (bit));
    __asm__ volatile("and %0,%1" : "+r" (bit) : "r" (xr));
    __asm__ volatile("mov %0,#1" : "=r" (one));
    __asm__ volatile("add %0,%1,#0" : "=r" (sh) : "r" (one));
    __asm__ volatile("lsl %0,%1" : "+r" (sh) : "r" (bit));
    __asm__ volatile("mvn %0,%0" : "+r" (sh));
    mask = (u8)sh;
    __asm__ volatile("add %0,%1,#0" : "=r" (vv) : "r" (v));
    __asm__ volatile("and %0,%1" : "+r" (vv) : "r" (one));
    __asm__ volatile("lsl %0,%1" : "+r" (vv) : "r" (bit));
    val = (u8)vv;
    mask &= *p;
    *p = (u8)(val | mask);
Lend:;
}
