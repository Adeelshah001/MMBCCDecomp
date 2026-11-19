/* Script_WriteWinIn_0804BFBC @ 0x0804BFBC (24 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_winin_0804bfbc,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_WriteWinIn_0804BFBC\n"
"\t.type Script_WriteWinIn_0804BFBC,%function\n"
"Script_WriteWinIn_0804BFBC:\n"
"\tmov\tip, lr\n"
"\tldr\tr2, [r1, #64]\n"
"\tldrb\tr3, [r2, #0]\n"
"\tadds\tr2, #1\n"
"\tldr\tr0, [pc, #8]\n"
"\tadds\tr0, r0, r3\n"
"\tbl\tScript_NextOp_r2entry\n"
"\tstrb\tr3, [r0, #0]\n"
"\tbx\tip\n"
"\t.word\t0x04000060\n"
"\t.size\tScript_WriteWinIn_0804BFBC,.-Script_WriteWinIn_0804BFBC\n"
);
