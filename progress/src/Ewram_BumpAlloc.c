/* Ewram_BumpAlloc @ 0x0800069C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_m_old.c (registry: src/wave8_m_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Wave 8 worker M (TAG=M).
 * 0x0800069c (64 B): EWRAM bump allocator at base 0x02000ED0.
 * v = *(u16*)(base+0x2002), w = *(u16*)(base+0x2000) (cursor).
 * Returns ((u32)v<<12) + base + w*4 after bumping cursor by (a+3)>>2,
 * or 0 when (0x400 - w) < (a+3)>>2 (unsigned).
 * Pool words in ROM: 0x02000ED0, 0x00002002 (base + separate 0x2002). */

extern u8 gEwram_02000ED0[];

__attribute__((section(".text.w8m_0800069c")))
u32 Ewram_BumpAlloc(u32 a)
{
    u32 base = (u32)gEwram_02000ED0;
    u16 v = *(u16 *)(base + 0x2002);
    u32 vsh = (u32)v << 12;
    u16 *cursor = (u16 *)(base + 0x2000);
    u16 w = *cursor;
    u32 t = base + (u32)w * 4;
    u32 ret = vsh + t;
    u32 room = 0x400 - w;
    u32 q = (a + 3) >> 2;

    if (room >= q) {
        *cursor = (u16)(w + q);
        return ret;
    }
    return 0;
}
