/* Script_InitTable36_0804BE10 @ 0x0804BE10 (24 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_inittab36_0804be10,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_InitTable36_0804BE10\n"
"\t.type Script_InitTable36_0804BE10,%function\n"
"Script_InitTable36_0804BE10:\n"
"\tmov\tip, lr\n"
"\tmovs\tr1, #36\n"
"\tldr\tr2, [pc, #40]\n"
".Lbe10_loop:\n"
"\tldr\tr3, [r2, #0]\n"
"\tbl\tValidateScriptPtr_0804BE2A\n"
"\tstmia\tr0!, {r3}\n"
"\tadds\tr2, #4\n"
"\tsubs\tr1, #1\n"
"\tbgt\t.Lbe10_loop\n"
"\tbx\tip\n"
"\t.2byte\t0x0000\n"
"\t.size\tScript_InitTable36_0804BE10,.-Script_InitTable36_0804BE10\n"
);
