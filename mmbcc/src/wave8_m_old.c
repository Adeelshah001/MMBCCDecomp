/* Wave 8 batch M: old_agbcc matches. Evidence: docs/match_notes_wave8_M.md */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

__asm__(
    ".globl gEwram_02000ED0\n.set gEwram_02000ED0, 0x02000ED0\n"
);
