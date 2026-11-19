/* Sub_08011560 @ 0x08011560 (252 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w52d_08011560_MATCHED.c (registry: src/w52d_08011560_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void sub_08010AD8(int a, int b, int c);

extern s16 F_0804A340(void);

extern void LoadCallClear_4A328(void);

extern void TblState_0804A2DC(u16 a);

extern void EwSet8Ret1_20(int a);

extern void Text_SelectBlobIdx(u16 a);

__attribute__((section(".text.w52d_08011560")))
int Sub_08011560(u8 *s)
{
    u8 *r4 = *(u8 **)s;
    u16 x;
    int a1, a2;
    int tailval;
    if (s[5] != 0)
        goto else_block;
    s[5]++;
    if (*(s16 *)(s + 12) == -2) {
        x = r4[12];
        if ((s8)r4[12] > 0) {
            a1 = 255;
            a2 = 2;
            goto shared;
        } else {
            sub_08010AD8(2, -1, 2);
            tailval = 2;
            goto tail;
        }
    }
    x = r4[12];
    if ((s8)r4[12] <= 0)
        goto else_block;
    a1 = 255;
    a2 = 255;
    goto shared;
shared:
    {
        u8 t11 = r4[11];
        s8 sb11 = r4[11];
        if (sb11 != 0)
            a1 = (u8)(t11 - 1);
    }
    if ((r4[10] & 7) != 0)
        a2 = (u8)((r4[10] & 7) - 2);
    sub_08010AD8((u8)(x - 1), (s8)a1, (s8)a2);
    tailval = (s8)r4[12] - 1;
tail:
    *(s16 *)(s + 12) = tailval;
    s[34] = 1;
    return 0;
else_block:
    if (r4[8] != 0) {
        x = (u16)(((u8 *)*(u32 *)s)[8] - 1);
        if ((F_0804A340() << 16) != (x << 16)) {
            LoadCallClear_4A328();
            if (x != 0)
                TblState_0804A2DC((u16)(((u8 *)*(u32 *)s)[8] - 1));
        }
    }
    if ((r4[10] & 16) != 0)
        EwSet8Ret1_20(16);
    if (r4[9] != 0)
        Text_SelectBlobIdx((u16)(((u8 *)*(u32 *)s)[9] - 1));
    {
        u8 n = s[4] + 1;
        int z = 0;
        s[4] = n;
        s[5] = z;
        s[6] = z;
        s[7] = z;
        return z - 1;
    }
}
