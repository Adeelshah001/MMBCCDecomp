/* Sub_0803FF80 @ 0x0803FF80 (220 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w43a_0803ff80_MATCHED.c (registry: mmbcc/src/w43a_0803ff80_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern u8 sub_0803F920(u16 a);

extern u8 IsSpecialChip_3FACC(u16 a);

__attribute__((section(".text.w43a_0803ff80")))
u32 Sub_0803FF80(u16 a, u16 b)
{
    register s32 a2 __asm__("r5") = a;
    s32 sa = a;
    u32 res = 0;
    register int cat __asm__("r1") = b >> 12;
    s32 lim = 961;
    u8 h;
    if (sa > lim)
        goto big;
    lim -= 1;
    if (sa >= lim)
        goto helper1early;
    if (sa == 930)
        goto invcat;
    if (sa > 930)
        goto mid;
    if (sa == 96)
        goto chip96;
    goto end;
mid:
    if (sa == 931)
        goto cat0;
    if (sa == 932)
        goto helper1mid;
    goto end;
big:
    if (sa == 5056)
        goto cat1;
    if (sa > 5056)
        goto huge;
    if (sa == 962)
        goto helper2;
    if (sa == 5024)
        goto cat1;
    goto end;
huge:
    if (a2 == 9152)
        goto cat2;
    if (a2 == 17344)
        goto cat4;
    goto end;
invcat:
    res = 1;
    if (cat == 0)
        res = 2;
    goto end;
cat0:
    res = 1;
    if (cat != 0)
        res = 2;
    goto end;
helper1mid:
    h = sub_0803F920(b);
    res = 1;
    if (h == 0)
        res = 2;
    goto end;
helper1early:
    h = sub_0803F920(b);
    res = 1;
    if (h != 0)
        res = 2;
    goto end;
helper2:
    h = IsSpecialChip_3FACC(b);
    res = 1;
    if (h != 0)
        res = 2;
    goto end;
cat1:
    res = 1;
    if (cat == 1)
        res = 2;
    goto end;
cat2:
    res = 1;
    if (cat == 2)
        res = 2;
    goto end;
cat4:
    res = 1;
    if (cat == 4)
        res = 2;
    goto end;
chip96:
    if (b == 208 || b == 217)
        res = 2;
    else
        res = 1;
    goto end;
end:
    return res;
}
