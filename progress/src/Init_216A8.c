/* Init_216A8 @ 0x080216A8 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_h.c (registry: src/wave4_h.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);

/* 0x080216A8: init with ChipSlot_Setup(s, 0x1600, 0). Tentative.
 * The two-step `v=2; v|=s[0xA]; v|=1` is required for the exact
 * `movs r0,#2; ldrb r1; orrs; movs r1,#1; orrs` sequence. */
__attribute__((section(".text.w4h_init216a8")))
void Init_216A8(u8 *s)
{
    *(u32 *)(s + 0x6C) = 0;
    {
        u8 v = 2;
        v |= s[0xA];
        v |= 1;
        s[0xA] = v;
    }
    ChipSlot_Setup(s, 0xB0 << 5, 0);
    *(u32 *)(s + 0x50) = 0;
    *(u32 *)(s + 0x54) = 0;
}
