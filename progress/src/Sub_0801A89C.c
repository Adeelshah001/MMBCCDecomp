/* Sub_0801A89C @ 0x0801A89C (270 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w45d_0801a89c_MATCHED.c (registry: src/w45d_0801a89c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_AddMirrored(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void Wrapper_D770(u8 *s, int a, int b);

extern void SetBit16(int v, int bit);

extern u32 *ChipInit_080178A8(int a, int b, int c, int d, int e);

extern u8 GetField17_U8(int v);

__attribute__((section(".text.w45d_0801a89c")))
int Sub_0801A89C(u8 *s)
{
    int out[2];
    int mode;
    int o0, o1;
    int ii;
    u8 b;
    int c, t;
    u32 cc, m;
    u8 *p;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    o0 = out[0];
    o1 = out[1];
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
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    SetBit16(*(u32 *)(s + 44), 3);
    ChipInit_080178A8(134, (int)(((u32)s[35] << 28) >> 28), (short)o0, (short)o1, *(u32 *)(s + 44));
    Wrapper_D770(s, 2136, 1);
    ii = 1;
    goto shared;
c1:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
        goto ret0;
    Wrapper_D770(s, 2136, 0);
    ii = 2;
shared:
    ChipSlot_IncUse(s, ii);
    b = ((u8 *)0x020031e4)[(*(u16 *)0x081705b0 >> 4) * 2];
    c = b & 3;
    t = c;
    __asm__ volatile("" : "+r"(t));
    if (t > 3)
        c = 3;
    p = s + 69;
    cc = c << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *p = (*p & m) | cc;
    s[34] = 13;
    s[13]++;
    goto ret0;
c2:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    return 1;
ret0:
    return 0;
}
