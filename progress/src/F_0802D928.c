/* F_0802D928 @ 0x0802D928 (464 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w41c_0802d928_MATCHED.c (registry: mmbcc/src/w41c_0802d928_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 Classify_3FD68(u16 x);

extern u32 Lookup_02D574(u32 x);

extern u32 IsSpecialChip_3FACC(u16 x);

extern u32 Sub_0802DAF8(u16 a, u16 b);

__attribute__((section(".text.w41c_0802d928")))
u8 F_0802D928(u32 a0, u32 a1, u32 a2) {
    u32 lk;
    u16 a0t;
    u16 a1t;
    u16 a2t;
    u8 res;
    u8 cls;
    lk = a1;
    __asm__ volatile("" :: "r" (lk));
    a0t = a0;
    lk <<= 16;
    a1t = lk >> 16;
    a2t = a2;
    res = 0;
    cls = (u8)Classify_3FD68(a0t);
    lk >>= 28;
    switch (a1t) {
    case 640:
    case 641:
        res = 1;
        break;
    case 642:
        res = 5;
        break;
    case 643:
    case 8832:
    case 12928: {
        u8 t = (u8)Lookup_02D574(lk);
        if (cls == 5) {
            u8 d = (u8)(lk - 1);
            res = 3;
            if (d <= 1) goto end;
        }
        res = 2;
        if (cls == t) res = 3;
        break;
    }
    case 644:
    case 645:
    case 646:
    case 4736:
    case 8833:
    case 12929:
    case 17024: {
        u8 t = (u8)Lookup_02D574(lk);
        u8 lim;
        if (cls == 5 && (u8)(lk - 1) <= 1) {
            res = 3;
            break;
        }
        if (cls == t) {
            res = 3;
            break;
        }
        if (a1t == 644) lim = 100;
        else if (a1t == 645) { __asm__ volatile("" ::: "memory"); lim = 120; }
        else {
            u16 t646;
            __asm__ volatile("" ::: "r0");
            t646 = 646;
            lim = 80;
            if (a1t == t646) lim = 150;
        }
        if (a2t <= lim) res = 1;
        break;
    }
    case 930:
        if (cls == 0) res = 1;
        break;
    case 931:
        if (cls != 0) res = 1;
        break;
    case 932:
        if ((u8)IsSpecialChip_3FACC(a0t) == 0) res = 1;
        break;
    case 5024:
    case 5040:
        if (cls == 1 || cls == 5) res = 1;
        break;
    case 4608:
        if (cls == 1 || cls == 5) res = 4;
        else if (cls == 2) res = 3;
        break;
    case 8705:
        if (cls == 2 || cls == 5) res = 4;
        else if (cls == 4) res = 3;
        break;
    case 16897:
        if (cls == 4) res = 4;
        else if (cls == 3) res = 3;
        break;
    default:
        res = (u8)Sub_0802DAF8(a0t, a1t);
        break;
    }
end:
    return res;
}
