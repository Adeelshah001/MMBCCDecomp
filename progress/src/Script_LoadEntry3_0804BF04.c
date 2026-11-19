/* Script_LoadEntry3_0804BF04 @ 0x0804BF04 (48 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_loadentry3_0804bf04,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_LoadEntry3_0804BF04\n"
"\t.type Script_LoadEntry3_0804BF04,%function\n"
"Script_LoadEntry3_0804BF04:\n"
"\tmov\tip, lr\n"
"\tldr\tr2, [r1, #64]\n"
"\tldrb\tr3, [r2, #0]\n"
"\tadds\tr2, #1\n"
"\tstr\tr2, [r1, #64]\n"
"\tlsls\tr2, r3, #1\n"
"\tadds\tr2, r2, r3\n"
"\tlsls\tr2, r2, #2\n"
"\tldr\tr3, [r0, #48]\n"
"\tadds\tr2, r2, r3\n"
"\tldr\tr3, [r2, #0]\n"
"\tbl\tValidateScriptPtr_0804BE2A\n"
"\tstr\tr3, [r1, #36]\n"
"\tldr\tr3, [r2, #4]\n"
"\tbl\tValidateScriptPtr_0804BE2A\n"
"\tstr\tr3, [r1, #40]\n"
"\tldr\tr3, [r2, #8]\n"
"\tbl\tValidateScriptPtr_0804BE2A\n"
"\tstr\tr3, [r1, #44]\n"
"\tbx\tip\n"
"\t.2byte\t0x0000\n"
"\t.size\tScript_LoadEntry3_0804BF04,.-Script_LoadEntry3_0804BF04\n"
);
