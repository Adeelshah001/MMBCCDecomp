/* Sub_0801BDE4 @ 0x0801BDE4 (186 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_0801bde4_MATCHED.c (registry: mmbcc/src/w38c_0801bde4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;
typedef signed int s32;

extern void sub_0800DD08(u32 *out, u8 *src);

extern void SetBit16(u8 *p, int bit);

extern void Text_SelectBlobIdx(int v);

extern void ChipInit_0801B98C(int a, u8 b, int c, s16 d, s16 e, u8 *f);

extern void MaxAssign_17(u8 *p, int v);

__attribute__((section(".text.w38c_0801bde4")))
u8 Sub_0801BDE4(u8 *s)
{
    u32 out[2];
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
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
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    Text_SelectBlobIdx(146);
    s[18] = 1;
    goto tail;
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    {
        u8 b = s[17];
        int nib = ((u32)s[35] << 28) >> 28;
        s16 d = (s16)(x + (152 << 6));
        register u32 pool __asm__("r7");
        pool = 0xffffe600;
        ChipInit_0801B98C(1, b, nib, d, (s16)(y + (s32)pool),
            *(u8 **)(s + 44));
    }
    s[18] = 15;
    goto tail;
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
