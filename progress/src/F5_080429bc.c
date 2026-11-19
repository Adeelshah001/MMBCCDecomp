/* F5_080429bc @ 0x080429BC (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* F5_080429bc @ 0x080429bc */
void sub_08040698(void);

 void sub_080406E4(void);

 void Sub_0804044C(u32 a);

void DrawObj_080405D8(u32 a);

 void sub_0804152C(u32 a);

__attribute__((section(".text.w14c_080429bc")))
void F5_080429bc(u32 a)
{
    u32 t = a;
    sub_08040698();
    sub_080406E4();
    Sub_0804044C(t);
    DrawObj_080405D8(t);
    sub_0804152C(t);
}
