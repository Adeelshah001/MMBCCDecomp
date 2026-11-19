/* Sub_08045E40 @ 0x08045E40 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08045e40_MATCHED.c (registry: staging/wave34_C/w34c_08045e40_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08043890(u8 *s);

extern void DrawObj_080439D8(u8 *s);

extern void sub_08044FB8(u8 *s);

extern void sub_08045A5C(u8 *s);

__attribute__((section(".text.w34c_08045e40")))
void Sub_08045E40(u8 *s)
{
    sub_08043890(s);
    DrawObj_080439D8(s);
    sub_08044FB8(s);
    sub_08045A5C(s);
}
