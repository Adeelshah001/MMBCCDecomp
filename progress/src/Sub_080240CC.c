/* Sub_080240CC @ 0x080240CC (224 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w52b_080240cc_MATCHED.c (registry: src/w52b_080240cc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void F_0802541C(u32 a, u32 b, u32 c);

extern u8 ClampAdd200(u8 a);

extern void F_080260D4(u32 a, u8 b, u8 c);

extern void F_08026184(u32 a, u32 b);

extern void sub_08023E34(u32 a);

extern void Sub_08024B3C(int a, u8 b, int c, u8 d);

extern void Sub_08024E2C(int a, u8 b, int c, int d);

__attribute__((section(".text.w52b_080240cc")))
void Sub_080240CC(u16 *a, u8 idx)
{
    u32 *base = (u32 *)0x02007090;
    u32 p;
    u8 t;
    u16 i;
    F_0802541C(0x02007090, 0x08227210, 0x1B1);
    p = base[5];
    t = ClampAdd200(idx);
    F_080260D4(p, t, *(u8 *)(0x08227404 + idx));
    {
        u16 *dst;
        s16 ci;
        ci = 0;
        if ((a[0] & 32768) != 0)
            goto cdone;
        dst = (u16 *)(base[14]);
        while (ci <= 3 && !(a[ci] & 32768)) {
            dst[ci] = a[ci];
            ci++;
        }
    cdone:;
    }
    F_08026184(0x020070A8, base[14]);
    sub_08023E34((u32)base);
    for (i = 0; i <= 29; i++)
        Sub_08024B3C(0, (u8)i, 0, (u8)i);
    for (i = 0; i <= 8; i++)
        Sub_08024E2C(1, (u8)i, 1, (u8)i);
    Sub_08024E2C(1, 10, 1, 10);
    Sub_08024E2C(1, 11, 1, 11);
}
