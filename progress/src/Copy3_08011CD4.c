/* Copy3_08011CD4 @ 0x08011CD4 (94 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

/* 0x08011cd4: Copy3_08011CD4 (coordinator-verified). */
u32 *TableU32_0820B6A4(u16 idx);

__attribute__((section(".text.w6l4_08011cd4")))
void Copy3_08011CD4(u16 a, u32 *o1, u32 *o2, u32 *o3)
{
    u32 *p = TableU32_0820B6A4(a);
    u32 tmp[3];
    s16 i;

    tmp[0] = 0;
    tmp[1] = 0;
    tmp[2] = 0;
    i = 0;
    while (p[i] != 0) {
        tmp[i] = p[i];
        i++;
        if (i > 2)
            break;
    }
    *o1 = tmp[0];
    *o2 = tmp[1];
    *o3 = tmp[2];
}
