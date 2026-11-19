/* Sub_0802F364 @ 0x0802F364 (490 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60b_0802f364_MATCHED.c (registry: src/w60b_0802f364_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblGetByte_24384(u16 a);

extern u8 sub_080244B0(u16 a, int b);

extern u16 Scramble_400A8(void);

extern u8 UMod_0804DEE8(u16 a, int b);

extern u8 Eq2260000(u16 a);

extern u8 sub_0803FE44(u16 a);

__attribute__((section(".text.w60b_0802f364")))
int Sub_0802F364(u8 *s, u8 kind)
{
    u32 nibLo;
    u32 b;
    u16 hp;
    u8 *base;
    int t7;
    register int t4 __asm__("r4");
    register int res __asm__("r9");
    register u32 nh __asm__("sl");

    if (kind == 0)
        b = s[394];
    else
        b = s[395];
    res = 0;
    hp = kind == 0 ? *(u16 *)(s + 20) : *(u16 *)(s + 22);
    if (s[6] & 16)
        return res;
    if (kind == 0 && *(u16 *)(s + 20) == 4096)
        return res;
    if (kind == 0)
        nibLo = ((u32)s[404] << 28) >> 28;
    else
        nibLo = ((u32)s[408] << 28) >> 28;
    if (kind == 0)
        nh = s[404] >> 4;
    else
        nh = s[408] >> 4;
    if (kind == 0)
        base = s + 32;
    else
        base = s + 176;
    if ((hp >> 12) == 2) {
        switch ((u8)TblGetByte_24384(hp) - 50) {
        case 0: t7 = 60; t4 = 60; break;
        case 1: t7 = 70; t4 = 70; break;
        case 2: t7 = 30; t4 = 30; break;
        case 3: t7 = 70; t4 = 70; break;
        case 4: t7 = 80; t4 = 80; break;
        case 5: t7 = 80; t4 = 80; break;
        default: t7 = 50; t4 = 50; break;
        }
    } else {
        { u8 tmp7 = sub_080244B0(kind == 0 ? *(u16 *)(s + 20) : *(u16 *)(s + 22), 0);
          __asm__ volatile("add %0, %1, #0" : "=r" (t7) : "r" (tmp7) : "cc"); }
        { u8 tmp4 = sub_080244B0(kind == 0 ? *(u16 *)(s + 20) : *(u16 *)(s + 22), 1);
          __asm__ volatile("add %0, %1, #0" : "=r" (t4) : "r" (tmp4) : "cc"); }
    }
    if (UMod_0804DEE8(Scramble_400A8(), 100) <= 49) {
        if (base[120] != 0 && nh == 0 && b >= (u32)t4 &&
            Eq2260000(*(u16 *)(base + 128)) != 0) {
            if (kind == 0)
                s[404] = (s[404] & 15) | 16;
            else
                s[408] = (s[408] & 15) | 16;
            res = 1;
        }
    }
    if (UMod_0804DEE8(Scramble_400A8(), 100) <= 49) {
        if (res == 0) {
        register u8 *p132 __asm__("r1") = base + 132;
        if (*p132 != 0 && nibLo == 0 && b >= (u32)t7 &&
            sub_0803FE44(*(u16 *)(p132 + 8)) != 0) {
            if (kind == 0) { u8 *dst = s + 404; int m = ~15; *dst = (*dst & m) | 1; }
            else { u8 *dst = s + 408; int m = ~15; *dst = (*dst & m) | 1; }
            res = 2;
        }
        }
    }
    return res;
}
