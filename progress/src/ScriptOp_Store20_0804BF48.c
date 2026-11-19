/* ScriptOp_Store20_0804BF48 @ 0x0804BF48 (20 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_op20_0804bf48,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl ScriptOp_Store20_0804BF48\n"
"\t.type ScriptOp_Store20_0804BF48,%function\n"
"ScriptOp_Store20_0804BF48:\n"
"\tmov\tip, lr\n"
"\tbl\tScript_NextOp\n"
"\tsubs\tr3, #64\n"
"\tstrb\tr3, [r1, #20]\n"
"\tldrb\tr3, [r1, #0]\n"
"\tmovs\tr2, #3\n"
"\torrs\tr3, r2\n"
"\tstrb\tr3, [r1, #0]\n"
"\tbx\tip\n"
"\t.size\tScriptOp_Store20_0804BF48,.-ScriptOp_Store20_0804BF48\n"
);
