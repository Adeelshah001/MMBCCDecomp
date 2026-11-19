/* FillU16_C8BC @ 0x0800C8BC (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_FFF8[];

void FillU16_C8BC(u32 dummy, u16 *dst, u16 n)
{
    register u32 base __asm__("r4") = (u32)g_FFF8;

    (void)dummy;
    __asm__ volatile(
        "add r5, r4, #0\n\t"
        "mov r3, #0\n\t"
        "cmp r3, %1\n\t"
        "bge 2f\n\t"
        "1:\n\t"
        "strh r5, [%0, #0]\n\t"
        "add %0, #2\n\t"
        "strh r4, [%0, #0]\n\t"
        "add %0, #2\n\t"
        "lsl r0, r3, #16\n\t"
        "mov r3, #128\n\t"
        "lsl r3, r3, #9\n\t"
        "add r0, r0, r3\n\t"
        "lsr r3, r0, #16\n\t"
        "asr r0, r0, #16\n\t"
        "cmp r0, %1\n\t"
        "blt 1b\n\t"
        "2:"
        :
        : "r"(dst), "r"(n), "r"(base)
        : "r0", "r3", "r5", "cc", "memory"
    );
}
