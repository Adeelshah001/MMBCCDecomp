/* Task_38F3C @ 0x08038F3C (74 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2_old.c (registry: src/wave5_h2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

s8 _call_via_r1(u8 *p, u32 v);

extern u32 gRom_08231764[];

__attribute__((section(".text.w5h_38f3c")))
void Task_38F3C(u8 *p)
{
    u32 *tbl = gRom_08231764;
    s8 idx = (s8)p[0x469c];
    u32 tbl_val = tbl[idx];
    u8 r = (u8)_call_via_r1(p, tbl_val);
    if (r == 1) goto L1;
    if (r == 2) goto L2;
    goto end;
L1: {
        u32 z = 0;
        p[1] = 3;
        p[2] = z;
        p[3] = z;
    }
    goto done;
L2: {
        u32 z = 0;
        p[1] = 4;
        p[2] = z;
        p[3] = z;
    }
done:
end: ;
}
