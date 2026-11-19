/* CtrTick_4AD4C @ 0x0804AD4C (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

struct Ew0200BD20 { u8 _00[128]; u16 f128; };

extern struct Ew0200BD20 gEwram_0200BD20;

extern u8 gEwram_02002EE0[];

__attribute__((section(".text.w8s_0804ad4c")))
s32 CtrTick_4AD4C(void)
{
    u8 *bd = (u8 *)&gEwram_0200BD20;
    u8 *flg = gEwram_02002EE0;
    s32 *ctr = (s32 *)(bd + 120);
    if ((*flg & 48) == 48)
        goto L1;
    *ctr = *ctr + 1;
    if (*ctr <= 59)
        goto Lret0;
    return -1;
L1:
    *ctr = 0;
Lret0:
    return 0;
}
