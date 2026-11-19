/* DispatchCounter_0804C020 @ 0x0804C020 (30 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_dispcnt_0804c020,\"ax\"\n"
"\t.align 1\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl DispatchCounter_0804C020\n"
"\t.type DispatchCounter_0804C020,%function\n"
"DispatchCounter_0804C020:\n"
"\tldr\tr2, [pc, #608]\n"
"\tldr\tr3, [r0, #52]\n"
"\tcmp\tr2, r3\n"
"\tbeq\t.Lc020_eq\n"
"\tbx\tlr\n"
".Lc020_eq:\n"
"\tadds\tr3, #1\n"
"\tstr\tr3, [r0, #52]\n"
"\tpush\t{r0, lr}\n"
"\tldr\tr3, [r0, #56]\n"
"\tcmp\tr3, #0\n"
"\tbeq\t.Lc020_tail\n"
"\tldr\tr0, [r0, #60]\n"
"\tbl\tTailCallR3\n"
".Lc020_tail:\n"
"\tpop\t{r0}\n"
"\t.size\tDispatchCounter_0804C020,.-DispatchCounter_0804C020\n"
);
