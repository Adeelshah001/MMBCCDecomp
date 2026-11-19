/* Wrap_0800ec7c @ 0x0800EC7C (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0800ec7c_MATCHED.c (registry: src/w36a_0800ec7c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern s8 Sub_08010138(u8 a, u32 b, s16 c, s16 d, s16 e, s16 f, s8 g);

extern void SetByte20_Clear21to23_02005130(u8 v);

extern u8 Base_08173A04[];

__attribute__((section(".text.w36a_0800ec7c")))
s8 Wrap_0800ec7c(u8 a, u32 b, s16 c, s16 d, s16 e, s16 f, s8 g)
{
    s8 r = Sub_08010138(Base_08173A04[a], b, c, d, e, f, g);
    if (r == 1) {
        SetByte20_Clear21to23_02005130(12);
        return 1;
    }
    return r;
}
