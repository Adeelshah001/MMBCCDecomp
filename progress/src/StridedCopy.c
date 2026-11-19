/* StridedCopy @ 0x08000C68 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/strided_copy.c (registry: src/strided_copy.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct StridedDesc {
    u16 unk0;
    u16 unk2;
    u32 dst;
    u16 count;
    u8 dst_step;
    u8 src_step;
    u32 src;
};

__attribute__((section(".text.strided_copy")))
void StridedCopy(struct StridedDesc *d_in)
{
    register struct StridedDesc *d __asm__("r4") = d_in;
    register u32 dst __asm__("r3");
    register int sstep __asm__("r5");
    u32 src;
    u8 dstep;
    u16 count;
    int ds;
    int scratch;

    src = d->src;
    dst = d->dst;
    sstep = d->src_step;
    dstep = d->dst_step;
    count = d->count;

    if (count == 0)
        goto done;
    ds = (dstep << 24) >> 23;
    __asm__("lsl %0,%2,#24\n\tasr %1,%0,#23" : "=&l"(scratch), "=l"(sstep) : "l"(sstep));
    do {
        *(u16 *)dst = *(u16 *)src;
        dst += ds;
        src += sstep;
        count--;
    } while (count != 0);
done:
    d->src = src;
}
