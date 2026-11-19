/* sub_080289C4 @ 0x080289C4 (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w67a_080289c4_MATCHED.c (registry: staging/w67a_fresh/w67a_080289c4_RECOMMENDED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void sub_08029504(u8 *s);

void Sub_0800E994(void);

void sub_0800EA14(u8 v);

void Set_0EA30(u8 v);

void BitCtl_520C(void);

void EwSet8_68(u8 v);

u8 TblGetByte_24384(u16 v);

void EwramSet2_02005138(u8 a, u8 b);

void Sub_0802E9F8(u16 a, u8 *p);

u8 TblGet_f0D(u8 v);

extern u8 g_02005168[];

__attribute__((section(".text.w67a_080289c4")))
u8 sub_080289C4(u8 *s)
{
    u8 i;
    u8 t;
    u8 v1, v2;
    u16 z = 0;

    s[4] = z;
    s[28] = z;
    s[6] &= 0xF8;
    s[2] = z;
    s[3] = z;
    { register u8 w __asm__("r0") = 0; s[24] = w; }
    s[5] = 50;
    sub_08029504(s);
    *(u16 *)(s + 18) = z;
    s[392] = 2;
    s[393] = 2;
    i = 0;
    {
        u32 *a = (u32 *)(s + 336);
        u32 zero = 0;
        u32 *b = (u32 *)(s + 364);
        u8 *c = s + 320;
        u8 *d = s + 328;
        for (; i <= 6; i++) {
            u32 *ap = a + i; *ap = zero;
            b[i] = zero;
            c[i] = zero;
            d[i] = zero;
        }
    }
    t = s[6] & 8;
    if (t == 0) {
        Sub_0800E994();
        sub_0800EA14(s[29]);
        Set_0EA30(s[10]);
        s[2] = 1;
        s[3] = t;
        BitCtl_520C();
    }
    if ((s[6] & 16) != 0)
        EwSet8_68(1);
    v1 = TblGetByte_24384(*(u16 *)(s + 20));
    v2 = TblGetByte_24384(*(u16 *)(s + 22));
    EwramSet2_02005138(v1, v2);
    Sub_0802E9F8(*(u16 *)(s + 20), s + 32);
    Sub_0802E9F8(*(u16 *)(s + 22), s + 176);
    {
        u8 tmp = TblGet_f0D(s[32]);
        u8 tz = 0;
        s[8] = tmp;
        s[9] = TblGet_f0D(s[176]);
        s[404] = tz;
        s[408] = tz;
        s[400] = tz;
        s[0] = 2;
        s[1] = tz;
        s[394] = tz;
        s[395] = tz;
        {
            u8 *ep = g_02005168;
            ep[12] = tz;
            ep += 20;
            ep[12] = tz;
        }
        s[412] = tz;
        s[416] = tz;
    }
    return 1;
}
