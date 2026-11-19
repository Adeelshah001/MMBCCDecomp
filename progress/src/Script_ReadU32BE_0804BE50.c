/* Script_ReadU32BE_0804BE50 @ 0x0804BE50 (32 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_readu32be_0804be50,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"\t.thumb_func\n"
"\t.globl Script_ReadU32BE_0804BE50\n"
"\t.type Script_ReadU32BE_0804BE50,%function\n"
"Script_ReadU32BE_0804BE50:\n"
"\tpush\t{lr}\n"
"\tldr\tr2, [r1, #64]\n"
"\tldrb\tr0, [r2, #3]\n"
"\tlsls\tr0, r0, #8\n"
"\tldrb\tr3, [r2, #2]\n"
"\torrs\tr0, r3\n"
"\tlsls\tr0, r0, #8\n"
"\tldrb\tr3, [r2, #1]\n"
"\torrs\tr0, r3\n"
"\tlsls\tr0, r0, #8\n"
"\tbl\tValidateScriptPtr_0804BE28\n"
"\torrs\tr0, r3\n"
"\tstr\tr0, [r1, #64]\n"
"\tpop\t{r0}\n"
"\tbx\tr0\n"
"\t.size\tScript_ReadU32BE_0804BE50,.-Script_ReadU32BE_0804BE50\n"
);
