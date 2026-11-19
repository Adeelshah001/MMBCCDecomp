/* Sub_0802DAF8 @ 0x0802DAF8 (138 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0802daf8_MATCHED.c (registry: mmbcc/src/w36d_0802daf8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern u8 Classify_3FD68(u16 a);

extern u8 sub_0803F920(u16 a);

extern u8 IsSpecialChip_3FACC(u16 a);

__attribute__((section(".text.w36d_0802daf8")))
u32 Sub_0802DAF8(u16 a, u16 b)
{
    u32 r6 = 0;
    u8 r1 = Classify_3FD68(a);
    s32 sb = b;
    u8 res;
    if (b == 962)
        goto callacc;
    if (sb > 962)
        goto gt;
    if (sb < 960)
        goto end;
    res = sub_0803F920(a);
    goto check70;
gt:
    if (b == 9152)
        goto check56;
    if (sb > 9152)
        goto gt2;
    if (b == 5056)
        goto check50;
    goto end;
gt2:
    if (b == 17344)
        goto set7check4;
    goto end;
check50:
    if (r1 == 1)
        goto set6;
    goto check5a;
check56:
    if (r1 == 2)
        goto set6;
    goto check5a;
check5a:
    if (r1 == 5)
        goto set6;
    goto set7;
set7:
    r6 = 7;
    goto end;
set7check4:
    r6 = 7;
    if (r1 != 4)
        goto end;
    goto set6;
callacc:
    res = IsSpecialChip_3FACC(a);
check70:
    r6 = 7;
    if (res == 0)
        goto end;
    goto set6;
set6:
    r6 = 6;
    goto end;
end:
    return r6;
}
