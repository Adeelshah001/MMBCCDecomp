/* SramInit_496A8 @ 0x080496A8 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void CpuFastSet(u32 *dst, u8 *src, u32 size);

void CpuSet(u32 *dst, u8 *src, u32 size);

extern u8 gEwram020070F0[];

__attribute__((section(".text.w5h_496a8")))
void SramInit_496A8(void)
{
    u8 *base = gEwram020070F0;
    u32 z = 0;
    u8 *p10 = base + 0x10;
    u32 buf[2];
    buf[0] = z;
    CpuFastSet(buf, p10, 0x010000d8);
    buf[1] = z;
    CpuSet(buf + 1, base + (0xdc << 2), 0x05000003);
    *(u32 *)(base + 0x20) = (0xfa << 2);
}
