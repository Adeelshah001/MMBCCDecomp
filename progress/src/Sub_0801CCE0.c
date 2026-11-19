/* Sub_0801CCE0 @ 0x0801CCE0 (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0801cce0_MATCHED.c (registry: mmbcc/src/w36b_0801cce0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct S { u8 pad0[9]; u8 f9; u8 pad10[2]; u32 f12; u8 f16; u8 pad17[3]; u32 f20; u8 pad24[20]; u32 f44; };

typedef u8 (*Func)(struct S *s);

extern void ChipSlot_Tick(struct S *s);

extern void DecIfNonZero_18(u32 x);

__attribute__((section(".text.w36b_0801cce0")))
void Sub_0801CCE0(struct S *s)
{
    Func *t1 = (Func *)0x082269ac;
    u8 ret = t1[s->f16](s);
    ChipSlot_Tick(s);
    if (ret != 0) {
        u32 *t2 = (u32 *)0x082243d8;
        u32 *addr = t2 + s->f9;
        s->f12 = 2;
        s->f20 = ((u32 *)*(u32 **)addr)[2];
        DecIfNonZero_18(s->f44);
        s->f44 = 0;
    }
}
