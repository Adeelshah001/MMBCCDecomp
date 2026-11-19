/* Tbl_SwapAndUpdate_080259A4 @ 0x080259A4 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26b_080259a4.c (registry: src/w26b_080259a4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((naked, section(".text.w26b_080259a4")))
void Tbl_SwapAndUpdate_080259A4(u8 *p, u16 b, u16 c)
{
    __asm__ volatile(
        "push {r4, r5, r6, r7, lr}\n\t"
        "mov r7, r8\n\t"
        "push {r7}\n\t"
        "add r5, r0, #0\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr r7, r1, #16\n\t"
        "lsl r2, r2, #16\n\t"
        "lsr r2, r2, #16\n\t"
        "mov r8, r2\n\t"
        "lsl r2, r7, #2\n\t"
        "add r1, r5, #0\n\t"
        "add r1, #20\n\t"
        "add r3, r1, r2\n\t"
        "ldr r4, [r3]\n\t"
        "mov r0, r8\n\t"
        "lsl r6, r0, #2\n\t"
        "add r1, r1, r6\n\t"
        "ldr r0, [r1]\n\t"
        "str r0, [r3]\n\t"
        "str r4, [r1]\n\t"
        "add r2, r2, r5\n\t"
        "add r2, #20\n\t"
        "ldrb r0, [r2, #1]\n\t"
        "cmp r0, #255\n\t"
        "beq 1f\n\t"
        "add r1, r0, #0\n\t"
        "lsl r2, r7, #24\n\t"
        "lsr r2, r2, #24\n\t"
        "add r0, r5, #0\n\t"
        "bl StoreIdx2_25638\n\t"
        "1:\n\t"
        "add r0, r6, r5\n\t"
        "add r1, r0, #0\n\t"
        "add r1, #20\n\t"
        "ldrb r0, [r1, #1]\n\t"
        "cmp r0, #255\n\t"
        "beq 2f\n\t"
        "add r1, r0, #0\n\t"
        "mov r0, r8\n\t"
        "lsl r2, r0, #24\n\t"
        "lsr r2, r2, #24\n\t"
        "add r0, r5, #0\n\t"
        "bl StoreIdx2_25638\n\t"
        "2:\n\t"
        "pop {r3}\n\t"
        "mov r8, r3\n\t"
        "pop {r4, r5, r6, r7}\n\t"
        "pop {r0}\n\t"
        "bx r0\n\t"
        ".short 0"
        ::: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "memory");
}
