/* F_08000624 @ 0x08000624 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Wave 15 worker B: bulk leaves-up rows 0-90 (main agbcc, 17 functions)
 * Coordinator-landed after independent clean-room re-verification (0 diffs).
 * Evidence: docs/match_notes_wave15_B.md, docs/wave15_B_results.tsv.
 */
extern void Fwd_08002f40(void);

__attribute__((section(".text.w15b_08000624")))
void F_08000624(void)
{
    Fwd_08002f40();
}
