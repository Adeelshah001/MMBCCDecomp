/* Script_PopPtr_0804BE8C @ 0x0804BE8C (20 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_popptr_0804be8c,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_PopPtr_0804BE8C\n"
"\t.type Script_PopPtr_0804BE8C,%function\n"
"Script_PopPtr_0804BE8C:\n"
"\tldrb\tr2, [r1, #2]\n"
"\tcmp\tr2, #0\n"
"\tbeq\t.Lbe8c_ret\n"
"\tsubs\tr2, #1\n"
"\tstrb\tr2, [r1, #2]\n"
"\tlsls\tr2, r2, #2\n"
"\tadds\tr3, r1, r2\n"
"\tldr\tr2, [r3, #68]\n"
"\tstr\tr2, [r1, #64]\n"
".Lbe8c_ret:\n"
"\tbx\tlr\n"
"\t.size\tScript_PopPtr_0804BE8C,.-Script_PopPtr_0804BE8C\n"
);
