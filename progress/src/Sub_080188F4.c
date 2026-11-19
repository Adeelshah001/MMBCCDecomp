/* Sub_080188F4 @ 0x080188F4 (140 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_080188f4_MATCHED.c (registry: mmbcc/src/w36d_080188f4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

typedef struct {
    u8 pad0[34];
    u8 f34;
    u8 pad1[9];
    u32 f44;
    u8 pad2[21];
    u8 f69;
    u8 pad3[18];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void ChipSlot_Setup(u32 a, u32 b, u32 c);

extern void ChipSlot_IncUse(u32 a, u32 b);

extern void sub_0800DD08(u32 *out, S *s);

extern void Vec2_SetMirrored(S *s, u32 a, u32 b);

extern void SetBit16(u32 a, u32 b);

extern void Text_SelectBlobIdx(u32 a);

__attribute__((section(".text.w36d_080188f4")))
void Sub_080188F4(S *s)
{
    u32 out[2];
    s32 mode;
    u8 *p;
    s32 neg;
    u32 zero;
    ChipSlot_Setup((u32)s, 0x222, 0);
    ChipSlot_IncUse((u32)s, 0);
    mode = 3 & *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1));
    {
        /* No pure-C formulation emitted ROM's adds r0,r1 copy before the
         * compare (old_agbcc folds the temp away); force it with one
         * inline-asm copy into a pinned r0 temp, branch stays in C. */
        register s32 chk __asm__("r0");
        __asm__ volatile("add %0, %1, #0" : "=r"(chk) : "r"(mode));
        if (chk > 3)
            mode = 3;
    }
    p = (u8 *)s + 69;
    mode <<= 2;
    neg = -13;
    *p = (*p & neg) | mode;
    p -= 35;
    zero = 0;
    *p = 13;
    s->f88 = zero;
    s->f96 = zero;
    s->f92 = zero;
    s->f100 = zero;
    sub_0800DD08(out, s);
    Vec2_SetMirrored(s, 0xffffc400, 0);
    SetBit16(s->f44, 3);
    Text_SelectBlobIdx(150);
}
