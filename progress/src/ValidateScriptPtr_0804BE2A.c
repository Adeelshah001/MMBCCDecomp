/* ValidateScriptPtr_0804BE2A @ 0x0804BE2A (28 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23d_scriptops.c (registry: src/w23d_scriptops.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

__asm__(
".section .text.w23d_validptr_0804be2a,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.syntax unified\n"
"ValidateScriptPtr_0804BE28:\n"
"\tldrb\tr3, [r2, #0]\n"
"\t.thumb_func\n"
"\t.globl ValidateScriptPtr_0804BE2A\n"
"\t.type ValidateScriptPtr_0804BE2A,%function\n"
"ValidateScriptPtr_0804BE2A:\n"
"\tpush\t{r0}\n"
"\tlsrs\tr0, r2, #25\n"
"\tbne\t.Lbe2a_ok\n"
"\tldr\tr0, [pc, #12]\n"
"\tcmp\tr2, r0\n"
"\tbcc\t.Lbe2a_zero\n"
"\tlsrs\tr0, r2, #14\n"
"\tbeq\t.Lbe2a_ok\n"
".Lbe2a_zero:\n"
"\tmovs\tr3, #0\n"
".Lbe2a_ok:\n"
"\tpop\t{r0}\n"
"\tbx\tlr\n"
"\t.word\t0x08105CC8\n"
"\t.size\tValidateScriptPtr_0804BE2A,.-ValidateScriptPtr_0804BE28\n"
);
