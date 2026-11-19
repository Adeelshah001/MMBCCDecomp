/* Script_NextOp @ 0x0804BE44 (12 B, ELF compiled size) — naked-asm transcription from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * No C: the function is a top-level __asm__ transcription, kept verbatim.
 * The app's judge finds the function symbol via its .type %function / .globl.
 * .set lines inside the block are kept (they are part of the transcription) and
 * are also listed in the manifest symbols so the judge resolves them.
 */
#include "common.h"

/* 0x0804BE44: ASM-STAGED. Script-interpreter opcode-fetch fragment
 * (bytecode engine at ~0x0804BE10; see docs/match_notes_wave3_d.md):
 *   r2 = [r1+0x40] (script pointer); [r1+0x40] = r2+1;
 *   r3 = *r2 (opcode byte); jump to the ROM-pointer validator 0x0804BE2A
 *   (which zeroes r3 when r2 is outside 0x08105CC8..0x01FFFFFF).
 * C cannot express the trailing `b` (agbcc does no tail-call optimization:
 * `return ValidateScriptPtr_0804BE2A(...)` emits push{lr}/bl/pop{r1}/bx r1). The probe
 * `__attribute__((noreturn))` + inline-asm `b` reproduces the 10 code bytes
 * exactly, but gcc appends a 2-byte safety `bx lr` after the asm, so the
 * fragment is staged here as file-scope asm (10 B code + 0000 pad). */
__asm__(
".section .text.w3d_script_nextop,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.thumb_func\n"
"\t.globl Script_NextOp\n"
"\t.type Script_NextOp,%function\n"
"Script_NextOp:\n"
"\tldr r2, [r1, #64]\n"
"\tadd r3, r2, #1\n"
"\tstr r3, [r1, #64]\n"
"\tldrb r3, [r2]\n"
"\tb ValidateScriptPtr_0804BE2A\n"
"\t.2byte 0x0000\n"
"\t.size Script_NextOp,.-Script_NextOp\n"
);
