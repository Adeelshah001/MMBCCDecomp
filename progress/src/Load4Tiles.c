/* Load4Tiles @ 0x080097CC (148 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24b_080097cc.c (registry: src/w24b_080097cc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Memcpy16(u8 *src, u8 *dst, u32 size);

extern u32 gTileBaseTbl[];

extern u32 *gTileIdxTbl[];

__attribute__((section(".text.w24b_080097cc")))
void Load4Tiles(u8 a, u16 b, u16 c, u8 d, u8 e)
{
    u32 off = c;
    u8 *dst;
    u32 *row;
    u32 ent;
    u32 base;

    off += (u32)e << 5;
    off += d;
    off <<= 5;
    dst = (u8 *)(0x06010000 + off);
    base = gTileBaseTbl[a];
    row = gTileIdxTbl[a];
    ent = row[b];
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[0] << 5)), dst, 32);
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[1] << 5)), (u8 *)(0x06010020 + off), 32);
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[2] << 5)), (u8 *)(0x06010400 + off), 32);
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[3] << 5)), (u8 *)(0x06010420 + off), 32);
}
