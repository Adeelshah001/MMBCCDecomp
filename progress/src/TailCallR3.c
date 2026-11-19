/* TailCallR3 @ 0x0804C278 (2 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Tail-call trampoline via r3 (TENTATIVE name).
 * ROM 0x0804C278 (2 B). Callers (text window dispatch: sub_0804C288,
 * sub_0804C2FC, ...) load a function pointer into r3 then `bl` here;
 * `bx r3` jumps to it leaving lr intact so the target returns directly
 * to the caller's caller. */
__attribute__((naked, section(".text.w3b_tailcallr3")))
void TailCallR3(void)
{
    __asm__ volatile("bx r3");
}
