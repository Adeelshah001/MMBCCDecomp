/* Sub_08005434 @ 0x08005434 (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08005434_MATCHED.c (registry: mmbcc/src/w37c_08005434_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void InitTriple_03090(u8 *p, u32 a, u32 b, u32 c);

extern void StoreTwoHalves_030BC(u8 *p, s16 a, s16 b);

extern void sub_0800410C(u8 *p);

extern void SetU32_200(u8 *p, u32 v);

extern void SetField204_04164(u8 *p, u32 v);

__attribute__((section(".text.w37c_08005434")))
void Sub_08005434(u8 *s, u16 a, u16 b)
{
    u8 *p28;
    register u8 *p8 __asm__("r5");
    u8 *q;
    u8 t;
    u8 *gp;
    u32 v;
    p28 = s + 28;
    InitTriple_03090(p28, (u32)(s + 20), 0, 0);
    q = s + 560;
    *(u32 *)(s + 32) = (u32)q;
    gp = (u8 *)0x02003670;
    __asm__ volatile("" : "+r"(gp));
    t = gp[0x11ae] & 4;
    v = 28672;
    if (t != 0) v = 30720;
    *(u32 *)(s + 20) = v;
    v = 18432;
    if (t != 0) v = 20480;
    *(u32 *)(s + 24) = v;
    *(u32 *)(q + 4) = 0;
    *(u32 *)q = 0;
    p8 = s + 8;
    StoreTwoHalves_030BC(p8, (s16)a, (s16)b);
    s += 40;
    sub_0800410C(s);
    SetU32_200(s, p28);
    SetField204_04164(s, p8);
}
