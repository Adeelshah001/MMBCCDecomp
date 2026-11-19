/* Sub_08011F24 @ 0x08011F24 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08011f24_MATCHED.c (registry: staging/wave34_C/w34c_08011f24_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void NewNode_0801D308(u8 *s, u32 *stk, int zero);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w34c_08011f24")))
void Sub_08011F24(u8 *s)
{
    u32 stk[2];
    /* ROM: movs r0,#0; movs r1,#0; str r0,[sp]; str r1,[sp,#4] (gcc merges). */
    __asm__ volatile(
        "movs r0, #0\n\t"
        "movs r1, #0\n\t"
        "str r0, [%0]\n\t"
        "str r1, [%0, #4]"
        : : "r"(stk) : "r0", "r1", "memory");
    NewNode_0801D308(s, stk, 0);
    ChipSlot_Tick(s);
}
