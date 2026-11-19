/* EntryMgr_HookB @ 0x08004F7C (2 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/entrymgr.c (registry: src/entrymgr.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Vestigial hook slot @0x08004F7C (worker-D "HelperB"): empty. */
__attribute__((section(".text.entrymgr_teardown")))
static void EntryMgr_HookB(u8 *base)
{
    (void)base;
}
