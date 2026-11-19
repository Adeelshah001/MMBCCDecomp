/* Sub_0801E0D0 @ 0x0801E0D0 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_0801e0d0_MATCHED.c (registry: mmbcc/src/w36c_0801e0d0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void _call_via_r1(u8 *s, u32 e);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w36c_0801e0d0")))
void Sub_0801E0D0(u8 *s)
{
    u8 *gp = (u8 *)0x020051b0;
    if ((((int)gp[3] >> s[16]) & 1) == 0) {
        u32 *tbl = (u32 *)0x082243d8;
        u8 idx;
        u32 *e;
        __asm__ volatile("" : "+r"(tbl));
        idx = s[9];
        e = (u32 *)((idx << 2) + (u32)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*e + 8);
    } else {
        u32 *tbl = (u32 *)0x08226a60;
        u8 idx;
        u32 *e;
        s8 t;
        u8 res;
        register u8 *dst __asm__("r2");
        __asm__ volatile("" : "+r"(tbl));
        idx = s[13];
        e = (u32 *)((idx << 2) + (u32)tbl);
        _call_via_r1(s, *e);
        t = (s8)(((s32)(*(u32 *)(s + 84) << 13) >> 24) + 6);
        if (t > 31) t = 31;
        if (t < 0) t = 0;
        res = 31 - t;
        dst = s + 34;
        *dst = res;
        ChipSlot_Tick(s);
    }
}
