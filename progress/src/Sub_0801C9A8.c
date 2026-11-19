/* Sub_0801C9A8 @ 0x0801C9A8 (284 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w47c_0801c9a8_MATCHED.c (registry: src/w47c_0801c9a8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_AddMirrored(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void SetBit16(int v, int bit);

extern u32 *ChipInit_080178A8(int a, int b, int c, int d, int e);

extern u32 *ChipInit_0801B98C(int a, int b, int c, int d, int e, int f);

extern u8 GetField17_U8(int v);

extern void MaxAssign_17(int v, int val);

__attribute__((section(".text.w47c_0801c9a8")))
int Sub_0801C9A8(u8 *s)
{
    int out[2];
    int mode;
    int seven;
    u8 dec;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    if (s[19] != 0) {
        dec = --s[19];
        if (dec != 0)
            goto dispatch;
        seven = 7;
        s[19] = 7;
        {
            register short *tbl __asm__("r1");
            int nib;
            int idx;
            short tv;
            nib = (int)(((u32)s[35] << 28) >> 28);
            tbl = (short *)0x0822696c;
            __asm__ volatile("" : "+r" (tbl));
            idx = seven & s[14];
            tv = tbl[idx];
            ChipInit_0801B98C(7, 1, nib, tv, dec, *(u32 *)(s + 44));
        }
        s[14] = (s[14] + 1) & seven;
    }
dispatch:
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
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    SetBit16(*(u32 *)(s + 44), 3);
    ChipSlot_IncUse(s, 1);
    s[18] = 6;
    s[19] = 1;
    goto inc;
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    ChipInit_080178A8(122, (int)(((u32)s[35] << 28) >> 28), 240 << 6, 0, *(u32 *)(s + 44));
inc:
    s[13]++;
    goto ret0;
c2:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
        goto c3;
    {
        int z = 0;
        int f = 15;
        s[18] = f;
        s[19] = z;
    }
    s[13]++;
c3:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    MaxAssign_17(*(u32 *)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
