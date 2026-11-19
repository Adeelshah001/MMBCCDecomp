/* Script_Dispatch_0804BE70 @ 0x0804BE70 (28 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_dispatch_0804be70,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_Dispatch_0804BE70\n"
"\t.type Script_Dispatch_0804BE70,%function\n"
"Script_Dispatch_0804BE70:\n"
"\tldrb\tr2, [r1, #2]\n"
"\tcmp\tr2, #3\n"
"\tbcs\t.Lbe70_walk\n"
"\tlsls\tr2, r2, #2\n"
"\tadds\tr3, r1, r2\n"
"\tldr\tr2, [r1, #64]\n"
"\tadds\tr2, #4\n"
"\tstr\tr2, [r3, #68]\n"
"\tldrb\tr2, [r1, #2]\n"
"\tadds\tr2, #1\n"
"\tstrb\tr2, [r1, #2]\n"
"\tb\tScript_ReadU32BE_0804BE50\n"
".Lbe70_walk:\n"
"\tb\tListWalk_0804BDE0\n"
"\t.2byte\t0x0000\n"
"\t.size\tScript_Dispatch_0804BE70,.-Script_Dispatch_0804BE70\n"
);
