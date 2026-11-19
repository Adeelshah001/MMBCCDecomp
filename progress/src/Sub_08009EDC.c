/* Sub_08009EDC @ 0x08009EDC (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08009edc_MATCHED.c (registry: mmbcc/src/w37c_08009edc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern u16 TblGet_f0E(u16 v);

extern void Memcpy16(void *dst, void *src, u32 n);

extern void sub_080006DC(u16 v, void *dst, u32 n);

extern void sub_08009F78(u8 a, u16 b);

__attribute__((section(".text.w37c_08009edc")))
void Sub_08009EDC(u8 a, u16 b)
{
    u16 idx;
    u8 *p;
    register u8 *base1 __asm__("r2");
    u8 *base2;
    u16 *p1;
    u16 t1;
    u16 t2;
    u8 *vr;
    u8 *dst;
    s16 i;
    idx = TblGet_f0E(b);
    p = (u8 *)0x0832b6c0 + idx * 20;
    base1 = (u8 *)0x08172140;
    __asm__ volatile("" : "+r"(base1));
    p1 = (u16 *)(a * 2 + (u32)base1);
    base2 = (u8 *)0x0817386c;
    __asm__ volatile("" : "+r"(base2));
    t1 = *p1;
    t2 = *(u16 *)(t1 * 2 + (u32)base2);
    vr = (u8 *)0x06010000 + t2 * 32;
    dst = p + *(u32 *)p;
    i = 0;
    do {
        Memcpy16(dst, vr, 256);
        dst += 256;
        vr += 1024;
        i++;
    } while (i <= 6);
    sub_080006DC(0, vr, 256);
    sub_08009F78(a, b);
}
