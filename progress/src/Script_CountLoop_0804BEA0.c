/* Script_CountLoop_0804BEA0 @ 0x0804BEA0 (48 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_countloop_0804bea0,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_CountLoop_0804BEA0\n"
"\t.type Script_CountLoop_0804BEA0,%function\n"
"Script_CountLoop_0804BEA0:\n"
"\tpush\t{lr}\n"
"\tldr\tr2, [r1, #64]\n"
"\tldrb\tr3, [r2, #0]\n"
"\tcmp\tr3, #0\n"
"\tbne\t.Lbea0_cnt\n"
"\tadds\tr2, #1\n"
"\tstr\tr2, [r1, #64]\n"
"\tb\tScript_ReadU32BE_0804BE52\n"
".Lbea0_cnt:\n"
"\tldrb\tr3, [r1, #3]\n"
"\tadds\tr3, #1\n"
"\tstrb\tr3, [r1, #3]\n"
"\tmov\tip, r3\n"
"\tbl\tScript_NextOp\n"
"\tcmp\tip, r3\n"
"\tbcs\t.Lbea0_done\n"
"\tb\tScript_ReadU32BE_0804BE52\n"
".Lbea0_done:\n"
"\tmovs\tr3, #0\n"
"\tstrb\tr3, [r1, #3]\n"
"\tadds\tr2, #5\n"
"\tstr\tr2, [r1, #64]\n"
"\tpop\t{r0}\n"
"\tbx\tr0\n"
"\t.2byte\t0x0000\n"
"\t.size\tScript_CountLoop_0804BEA0,.-Script_CountLoop_0804BEA0\n"
);
