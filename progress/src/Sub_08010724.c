/* Sub_08010724 @ 0x08010724 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08010724_MATCHED.c (registry: staging/wave34_C/w34c_08010724_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void CondRectFill_080062B4(int a, int b, int c, int d, void *e, int f, u32 g);

__attribute__((section(".text.w34c_08010724")))
void Sub_08010724(void)
{
    CondRectFill_080062B4(0, 19, 30, 1, (void *)0x0000020d, 5, *(u32 *)0x08173e28);
}
