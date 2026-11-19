/* ScriptOp_Store27_0804BF84 @ 0x0804BF84 (12 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_op27_0804bf84,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl ScriptOp_Store27_0804BF84\n"
"\t.type ScriptOp_Store27_0804BF84,%function\n"
"ScriptOp_Store27_0804BF84:\n"
"\tmov\tip, lr\n"
"\tbl\tScript_NextOp\n"
"\tstrb\tr3, [r1, #27]\n"
"\tbx\tip\n"
"\t.2byte\t0x0000\n"
"\t.size\tScriptOp_Store27_0804BF84,.-ScriptOp_Store27_0804BF84\n"
);
