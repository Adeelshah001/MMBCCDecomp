/* ArmTrampoline @ 0x0804B970 (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Thumb->ARM trampoline (TENTATIVE name).
 * ROM 0x0804B970 (4 B): adr r2, 0x0804B974; bx r2.
 * Target is ARM code: add r2,r3,r0,lsl r1; add r0,r3,#0; bx lr. */
__attribute__((naked, section(".text.w3b_armtramp")))
void ArmTrampoline(void)
{
    __asm__ volatile("adr r2, 1f\n\tbx r2\n1:");
}
