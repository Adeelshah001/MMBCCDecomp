/* Sub_08042998 @ 0x08042998 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08042998_MATCHED.c (registry: staging/wave34_C/w34c_08042998_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0804039C(u8 *s);

extern void sub_080404D0(u8 *s);

extern void sub_08040698(u8 *s);

extern void sub_080406E4(void);

extern void sub_0804152C(u8 *s);

__attribute__((section(".text.w34c_08042998")))
void Sub_08042998(u8 *s)
{
    sub_0804039C(s);
    sub_080404D0(s);
    sub_08040698(s);
    sub_080406E4();
    sub_0804152C(s);
}
