/* Sub_0801AE70 @ 0x0801AE70 (130 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_0801ae70_MATCHED.c (registry: mmbcc/src/w36c_0801ae70_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void Vec2_AddMirrored(u8 *s, u32 a, u32 b);

extern void sub_0800DD08(u32 *out, u8 *s);

extern void ChipInit_080178A8(u8 a, u8 b, s16 c, int d, u32 e);

__attribute__((section(".text.w36c_0801ae70")))
int Sub_0801AE70(u8 *s)
{
    u32 out[2];
    u32 o0;
    register u32 o1 __asm__("r3");
    u8 t13;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08(out, s);
    o0 = out[0];
    o1 = out[1];
    t13 = s[13];
    if (t13 == 0 && (int)o1 > (int)0xfffffb00) {
        u8 *tbl = (u8 *)0x08226723;
        u8 b, v;
        u32 m;
        __asm__ volatile("" : "+r"(tbl));
        b = tbl[s[17]];
        ChipInit_080178A8(b, (((u32)s[35] << 28) >> 28), (s16)o0, 0, *(u32 *)(s + 44));
        *(u32 *)(s + 88) = t13;
        *(u32 *)(s + 96) = t13;
        *(u32 *)(s + 92) = t13;
        *(u32 *)(s + 100) = t13;
        v = s[10] & 253;
        m = 254;
        __asm__ volatile("" : "+r"(m));
        s[10] = v & m;
        return 1;
    }
    return 0;
}
