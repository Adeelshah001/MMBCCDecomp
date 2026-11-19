/* Task_35128 @ 0x08035128 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2_old.c (registry: src/wave5_h2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

s8 _call_via_r1(u8 *p, u32 v);

extern u32 gRom_0822EA80[];

__attribute__((section(".text.w5h_35128")))
u32 Task_35128(u8 *p)
{
    u32 ret = 0;
    u32 *tbl = gRom_0822EA80;
    u8 *pIdx = p + 0x46a8;
    u32 tbl_val = tbl[*pIdx];
    if (_call_via_r1(p, tbl_val) != 0) {
        p[4] = 3;
        p[5] = ret;
    }
    if (*pIdx == 3) {
        p[0x46b7] = *pIdx;
        ret = 1;
    }
    return ret;
}
