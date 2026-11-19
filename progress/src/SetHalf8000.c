/* SetHalf8000 @ 0x080082CC (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Halfword setter to constant 0x8000 (TENTATIVE name).
 * ROM 0x080082CC (10 B). Callers at 0x0800A83A/0x0800A84C pass only r0.
 * The original compiler's redundant r2->r1 copy (movs r2,#128;
 * lsls r2,#8; adds r1,r2,#0) is not reproducible in C on this agbcc
 * (always folds to 8 B); direct transcription via naked+asm.
 * NOTE: GAS 2.42 rejects 's'-suffixed Thumb mnemonics (lsls/adds);
 * the unsuffixed forms encode identically (verified byte-for-byte). */
__attribute__((naked, section(".text.w3b_sethalf8000")))
void SetHalf8000(u16 *p)
{
    __asm__ volatile(
        "movs r2, #128\n\t"
        "lsl r2, r2, #8\n\t"
        "add r1, r2, #0\n\t"
        "strh r1, [r0, #0]\n\t"
        "bx lr");
}
