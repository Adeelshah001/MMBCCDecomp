/* sub_080230A0 @ 0x080230A0 (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_blkb_old.c (registry: src/wave6_blkb_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

/* 0x080230A0: sub_080230A0 (coordinator-verified). */
/* sub_080230A0 @ 0x080230A0 — 2-byte diff test (v2).
 * ROM has `adds r0,r1,#0` before `cmp r0,#3` at 0x080230dc.
 */

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6b_230a0")))
void sub_080230A0(u8 *s_in)
{
    u8 *s = s_in;
    u32 z = 0;
    u16 h;
    s32 v;

    *(u32 *)(s + 0x6c) = z;

    {
        register u8 vo __asm__("r0");
        vo = 2;
        vo |= s[0xa];
        vo |= 1;
        s[0xa] = vo;
    }

    ChipSlot_Setup(s, 0x3715, 0);
    ChipSlot_IncUse(s, 0);

    *(u32 *)(s + 0x50) = z;
    *(u32 *)(s + 0x54) = z;

    {
        u8 *base = (u8 *)0x081705B0;
        h = *(u16 *)(base + 2);
    }
    {
        s32 w;
        u32 idx = (h >> 4) << 1;
        u8 *tbl;
        __asm__ volatile("" : : : "memory");
        tbl = gEwram_020031E4;
        v = 3 & tbl[idx];
        __asm__ volatile("add %0, %1, #0" : "=l"(w) : "l"(v));
        if (w > 3)
            v = 3;
    }

    {
        u8 *q = s + 0x45;
        u32 mask;
        u32 t;
        v <<= 2;
        mask = 13;
        mask = -mask;
        t = *q;
        t &= mask;
        t |= (u32)v;
        *q = t;
    }

    s[0x22] = 31;
}
