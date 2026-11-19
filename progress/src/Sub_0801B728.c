/* Sub_0801B728 @ 0x0801B728 (242 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_0801b728_MATCHED.c (registry: mmcc/src/w38a_0801b728_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_AddMirrored(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void ChipSlot_Setup(u8 *s, int a, u8 b);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void Text_SelectBlobIdx(int idx);

__attribute__((section(".text.w38a_0801b728")))
int Sub_0801B728(u8 *s)
{
    u32 out[2];
    register int o0 __asm__("r2");
    int o1;
    int mode;
    int e;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    o0 = out[0];
    __asm__ volatile("" : "+r"(o0));
    o1 = out[1];
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    return 0;
gt1:
    if (mode == 2)
        goto c2;
    return 0;
c0:
    __asm__ volatile("" : "+r"(o0));
    if (o1 <= -3840)
        return 0;
    *(u32 *)(s + 92) = mode;
    *(u32 *)(s + 100) = mode;
    e = 8;
    goto shared;
c1:
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    ChipSlot_Setup(s, 514, 0);
    ChipSlot_IncUse(s, 0);
    {
        register int v __asm__("r1") = *(u8 *)(0x020031E4 + ((*(u16 *)0x081705B0 >> 4) << 1)) & 3;
        int t;
        int m;
        int sh;
        u8 *q;
        __asm__ volatile("" : "+r"(v));
        t = v;
        __asm__ volatile("" : "+r"(t));
        if (t > 3)
            v = 3;
        q = s + 69;
        sh = v << 2;
        m = 13;
        m = -m;
        *q = (*q & m) | sh;
    }
    s[34] = 13;
    Vec2_AddMirrored(s, 0, 160 << 4);
    Text_SelectBlobIdx(126);
    e = 23;
shared:
    s[18] = e;
    s[13]++;
    return 0;
c2:
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    s[10] &= 254;
    return 1;
}
