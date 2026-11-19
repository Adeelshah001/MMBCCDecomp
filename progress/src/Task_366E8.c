/* Task_366E8 @ 0x080366E8 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2_old.c (registry: src/wave5_h2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

s8 _call_via_r1(u8 *p, u32 v);

extern u32 gRom_0823010C[];

__attribute__((section(".text.w5h_366e8")))
void Task_366E8(u8 *p)
{
    u32 *tbl = gRom_0823010C;
    s8 idx = (s8)p[0x4699];
    u32 tbl_val = tbl[idx];
    if (_call_via_r1(p, tbl_val) != 0) {
        u32 z = 0;
        p[1] = 3;
        p[2] = z;
        p[3] = z;
    }
}
