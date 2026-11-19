/* Sub_08018D18 @ 0x08018D18 (260 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w57d_08018d18_MATCHED.c (registry: src/w57d_08018d18_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_AddMirrored(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *d, u8 *s);

extern void ChipInit_080178A8(int a, int b, int c, int d, u32 e);

extern u8 TestBit16(u32 v, int bit);

extern u8 GetField17_U8(u32 v);

__attribute__((section(".text.w57d_08018d18")))
int Sub_08018D18(u8 *s)
{
    int out[2];
    register int a __asm__("r2");
    register int b __asm__("r3");
    register int thr __asm__("r5");
    Vec2_AddMirrored(s, *(int *)(s + 88), *(int *)(s + 92));
    *(int *)(s + 88) += *(int *)(s + 96);
    *(int *)(s + 92) += *(int *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    a = out[0];
    b = out[1];
    __asm__ volatile("" : : "r"(b));
    switch (s[13]) {
    case 0:
        thr = -5120;
        goto shared;
    case 1:
        thr = 5120;
        goto shared;
    case 2:
        thr = 15360;
        if (a <= thr)
            return 0;
        ChipInit_080178A8(70, ((unsigned)s[35] << 28) >> 28, thr, -2560, *(u32 *)(s + 44));
        if ((u8)TestBit16(*(u32 *)(s + 44), 0) != 0) {
            s[13] = 3;
            return 0;
        } else {
            s[10] &= ~2;
            s[10] &= ~1;
            s[13] = 5;
            return 0;
        }
    case 3:
        thr = 25600;
    shared:
        if (a <= thr)
            return 0;
        ChipInit_080178A8(69, ((unsigned)s[35] << 28) >> 28, thr, -2560, *(u32 *)(s + 44));
        s[13]++;
        return 0;
    case 4:
        if (a > 30720)
            return 1;
        /* fall through */
    case 5:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 5)
            return 1;
        return 0;
    default:
        return 0;
    }
}
