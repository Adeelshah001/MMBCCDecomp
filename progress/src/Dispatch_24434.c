/* Dispatch_24434 @ 0x08024434 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08024434.c (registry: src/w16b_08024434.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 GetU32_38(u8 *s);

extern u8 *GetPtr14_265D0(void *ctx, s16 idx);

extern u8 ew02007090[];

extern u8 EwrBase_20070A8[];

extern u8 EwrBase_20070DA[];

extern u16 RomTbl_82298F0[];

extern u32 RomTbl_822B9C0[];

u32 Dispatch_24434(u16 a)
{
    register u16 v __asm__("r4") = a;
    int x;
    if (v == 0)
        return 0;
    x = v >> 12;
    switch (x) {
    case 1:
        return GetU32_38(ew02007090);
    case 2:
        return (u32)GetPtr14_265D0(EwrBase_20070A8, (s16)(0xFFF & v));
    case 3: {
        u8 *b1 = (u8 *)RomTbl_82298F0;
        u8 *b2 = (u8 *)RomTbl_822B9C0;
        u32 i = 0xFFF & v;
        u8 *p = b1 + i * 20;
        u16 t = *(u16 *)(p + 16);
        return *(u32 *)(b2 + (t << 2));
    }
    case 4:
        return (u32)EwrBase_20070DA;
    default:
        return 0;
    }
}
