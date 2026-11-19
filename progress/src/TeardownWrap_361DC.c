/* TeardownWrap_361DC @ 0x080361DC (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

       /* ROM pointer table 0x0822D69C */
/* Already matched for real: */
extern void EntryMgr_Teardown(void);

/* 0x080361DC (8B, tentative): tail-call wrapper around EntryMgr_Teardown.
 * The push/bl/pop/bx shape (not a direct `b`) is what agbcc -O2
 * -mthumb-interwork emits here. */
__attribute__((section(".text.w3e_teardownwrap_361dc")))
void TeardownWrap_361DC(void)
{
    EntryMgr_Teardown();
}
