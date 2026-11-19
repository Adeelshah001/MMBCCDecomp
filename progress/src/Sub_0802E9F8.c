/* Sub_0802E9F8 @ 0x0802E9F8 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0802e9f8_MATCHED.c (registry: mmbcc/src/w36b_0802e9f8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct E { u8 f0; u8 f1; u16 f2; u16 f4; u16 f6; u16 f8; u16 f10; };

extern u8 Sub_080241D0(u16 a);

extern u8 sub_080242A8(u16 a, u8 i);

extern u16 TblGet_f00(u8 v);

extern u16 TblGet_f04(u8 v);

extern u16 TblGet_f02(u8 v);

extern u16 TblGet_f08(u8 v);

extern u8 TblGet_f0C(u8 v);

__attribute__((section(".text.w36b_0802e9f8")))
void Sub_0802E9F8(u16 a, struct E *p)
{
    u8 i = 0;
    u16 z = 0;
    for (; i <= 11; i++) {
        u8 v = (i == 0) ? Sub_080241D0(a) : sub_080242A8(a, i);
        p->f0 = v;
        p->f2 = TblGet_f00(v);
        p->f6 = TblGet_f04(v);
        p->f4 = TblGet_f02(v);
        p->f8 = TblGet_f08(v);
        p->f10 = z;
        p->f1 = TblGet_f0C(v);
        p++;
    }
}
