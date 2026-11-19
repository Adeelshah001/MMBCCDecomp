/* Sub_08023110 @ 0x08023110 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08023110_MATCHED.c (registry: mmbcc/src/w36a_08023110_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void ChipSlot_IncUse(u32 *s, u32 a);

extern void ChipSlot_Tick(u32 *s);

__attribute__((section(".text.w36a_08023110")))
void Sub_08023110(u32 *s)
{
    u8 *sub = (u8 *)s[10];
    u32 b = ((u8 *)sub)[31];
    register u32 t __asm__("r0");
    register s32 v0 __asm__("r0");
    register s32 v1 __asm__("r0");
    if (b & 8) {
        t = b & ~8;
        ((u8 *)sub)[31] = (u8)t;
        ChipSlot_IncUse(s, 1);
        ((u8 *)s)[18] = 4;
    } else {
        if (((u8 *)s)[18] != 0) {
            ((u8 *)s)[18]--;
            if ((s8)((u8 *)s)[18] == 0)
                ChipSlot_IncUse(s, 0);
        }
    }
    __asm__ volatile("mov r0, #0\n\tldrsb %0, [%1, r0]" : "=r"(v0) : "r"(sub));
    s[20] = (v0 + 7) * 2048;
    __asm__ volatile("mov r0, #1\n\tldrsb %0, [%1, r0]" : "=r"(v1) : "r"(sub));
    s[21] = v1 * 2048;
    ChipSlot_Tick(s);
}
