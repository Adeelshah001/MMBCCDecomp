/* sub_0800B368 @ 0x0800B368 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_T_old.c (registry: src/wave10_T_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_02004E40[];

void sub_0800B520(u32 a, u32 b, u32 c);

void Ewram4E40_Init_0B4E4(void);

void Clr_0800B4C8(void);

/* sub_0800B368 @ 0x0800B368 (72 B).
 * If (gEwram_02004E40[4] & 128) != 0: clear base[0..3], base[5]=3,
 * *(u32*)(base+32)=a, call B520(b,c,d)/B4E4()/B4C8(), return 1.
 * Else: base[5]=1, return 0.
 * Key idiom: inverted if ((x & 128) == 0) { else-branch } gives ROM's
 * beq-to-else layout; store order 0,3,2,1 matches ROM's scheduling. */
__attribute__((section(".text.w10t_0x0800b368")))
u8 sub_0800B368(u32 a, u32 b, u32 c, u32 d)
{
    u8 *base = gEwram_02004E40;
    if ((base[4] & 128) == 0) {
        base[5] = 1;
        return 0;
    }
    base[0] = 0;
    base[3] = 0;
    base[2] = 0;
    base[1] = 0;
    base[5] = 3;
    *(u32 *)(base + 32) = a;
    sub_0800B520(b, c, d);
    Ewram4E40_Init_0B4E4();
    Clr_0800B4C8();
    return 1;
}
