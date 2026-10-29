/* Wave 41 coordinator landing: coordinator-verified 0-diff (standalone
 * rebuild + independent ROM-extract cmp). See staging/w41coord_verify/COORD_LOG.md.
 */
/* W41-C v10: F_0802D928 @ 0x0802d928, 464 B. FIRST C attempt (W40 decode).
   Switch in numeric order; sparse-switch binary-search tree left to GCC.
   2da1c uses the "preset" shape (r7=3 set before the (r4-1) test) to
   match ROM's movs-before-cmp; 2da40 uses natural early return.
   Lim sub-switch uses nested-else shape (default 80 set before 646 test).
   Callees declared u32-returning with (u8) casts to reproduce ROM's
   lsls/lsrs truncation shifts. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 Classify_3FD68(u16 x);
extern u32 Lookup_02D574(u32 x);
extern u32 DecisionTree_3FACC(u16 x);
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
        if ((u8)DecisionTree_3FACC(a0t) == 0) res = 1;
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

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".set DecisionTree_3FACC, 0x0803facc\n"
);
