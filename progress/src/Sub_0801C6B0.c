/* Sub_0801C6B0 @ 0x0801C6B0 (194 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_0801c6b0_MATCHED.c (registry: mmbcc/src/w38c_0801c6b0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;
typedef signed int s32;

extern void Vec2_AddMirrored(u8 *s, s32 a, s32 b);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void ChipInit_0801EBF0(int a, int b, int c, s16 d, s16 e);

extern void ChipInit_0801B98C(int a, u8 b, int c, s16 d, s16 e, u8 *f);

extern int GetField17_U8(u8 *p);

extern void MaxAssign_17(u8 *p, int v);

__attribute__((section(".text.w38c_0801c6b0")))
u8 Sub_0801C6B0(u8 *s)
{
    u32 out[2];
    s32 x, y;
    int mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto ret0;
gt1:
    if (mode == 2)
        goto c2;
    goto ret0;
c0:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    ChipInit_0801EBF0(57, 0, ((u32)s[35] << 28) >> 28,
        (s16)x, (s16)y);
    ChipInit_0801B98C(6, s[17], ((u32)s[35] << 28) >> 28,
        (s16)x, (s16)y, *(u8 **)(s + 44));
    s[13]++;
    goto ret0;
c1:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5) {
        s[18] = 15;
        s[13]++;
    }
    /* fall through to c2 (ROM has no branch here) */
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
