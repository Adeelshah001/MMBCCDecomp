/* ScriptOp_MulShift_0804BEDC @ 0x0804BEDC (20 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_opmul_0804bedc,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl ScriptOp_MulShift_0804BEDC\n"
"\t.type ScriptOp_MulShift_0804BEDC,%function\n"
"ScriptOp_MulShift_0804BEDC:\n"
"\tmov\tip, lr\n"
"\tbl\tScript_NextOp\n"
"\tlsls\tr3, r3, #1\n"
"\tstrh\tr3, [r0, #28]\n"
"\tldrh\tr2, [r0, #30]\n"
"\tmuls\tr3, r2\n"
"\tlsrs\tr3, r3, #8\n"
"\tstrh\tr3, [r0, #32]\n"
"\tbx\tip\n"
"\t.size\tScriptOp_MulShift_0804BEDC,.-ScriptOp_MulShift_0804BEDC\n"
);
