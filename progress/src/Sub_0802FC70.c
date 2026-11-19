/* Sub_0802FC70 @ 0x0802FC70 (138 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0802fc70_MATCHED.c (registry: mmbcc/src/w36d_0802fc70_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 Classify_3FD68(u16 a);

extern u32 Obj_AddEntry(u8 *s, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i);

__attribute__((section(".text.w36d_0802fc70")))
u32 Sub_0802FC70(u8 *s, u8 a, u8 b)
{
    u32 r5 = 0;
    u16 v;
    u8 r2;
    u8 f29;
    if (a == 0)
        v = *(u16 *)(*(u32 *)(s + (168 << 1) + b * 4) + 8);
    else
        v = *(u16 *)(*(u32 *)(s + (182 << 1) + b * 4) + 8);
    r2 = Classify_3FD68(v);
    f29 = s[29];
    if (f29 == 3) {
        if (r2 == 1) {
            s[29] = 0;
            goto call;
        }
    }
    if ((u8)f29 == 1) {
        if (r2 == 2) {
            s[29] = 0;
            goto call;
        }
    }
    if ((u8)f29 == 4) {
        if (r2 == 3) {
            s[29] = r2;
            r5 = 1;
        }
    }
    if (r5 == 0)
        goto end;
call:
    return Obj_AddEntry(s, 0, 2, 0, 2, 0, 0, 0, 84, 5);
end: ;

}
