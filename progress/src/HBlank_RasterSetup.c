/* HBlank_RasterSetup @ 0x08000AD4 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/hblank.c (registry: src/hblank.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

#define REG_DISPSTAT (*(volatile unsigned short *)0x04000004)

#define REG_IE       (*(volatile unsigned short *)0x04000200)

#define HBLANK_DESC0 ((void *)0x03000580)

#define HBLANK_ISR_TABLE ((unsigned int *)0x0816E22C)

void StridedCopy(void *desc);

__attribute__((section(".text.hblank_setup")))
void HBlank_RasterSetup(void)
{
    short sel = 0;
    unsigned int *desc = (unsigned int *)HBLANK_DESC0;
    unsigned int *desc2;

    if (desc[2] != 0) {
        desc[3] = desc[0];
        StridedCopy(desc);
        sel = 1;
    }
    desc2 = desc;
    desc2 += 7;
    if (desc2[2] != 0) {
        desc2[3] = desc[7];
        StridedCopy(desc2);
        sel += 2;
    }
    if (sel != 0) {
        unsigned int *vec;
        unsigned int *t;

        REG_DISPSTAT |= 0x10;
        (void)REG_DISPSTAT;
        vec = (unsigned int *)desc - 0x60;
        t = HBLANK_ISR_TABLE;
        asm volatile("" : "+r" (t)); /* keep table load before sel*4 (see note) */
        vec[1] = t[sel];
        REG_IE |= 0x2;
        (void)REG_IE;
    }
}
