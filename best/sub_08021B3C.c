extern u16 D_03002620[][16];
extern void sub_08000758(const void *src, void *dst, u32 size);

void sub_08021B3C(u8 slot, const u16 *first, const u16 *last, u8 weight)
{
    u16 *out = D_03002620[slot];
    const u16 *source;
    int i;
    u32 a, b;
    u32 ar, ag, ab, br, bg, bb;
    int mask;

    if (weight == 0) {
        source = first;
        goto copy;
    }
    if (weight > 14) {
        source = last;
copy:
        sub_08000758(source, out, 32);
        return;
    }

    mask = 31;
    i = 15;
    do {
        b = *last;
        br = b & mask;
        b >>= 5;
        bg = b & mask;
        bb = (b >> 5) & mask;
        a = *first;
        ar = a & mask;
        a >>= 5;
        ag = a & mask;
        ab = (a >> 5) & mask;

        ar += ((u32)(((int)(br - ar) * weight) >> 4) << 24) >> 24;
        ag += ((u32)(((int)(bg - ag) * weight) >> 4) << 24) >> 24;
        ab += ((u32)(((int)(bb - ab) * weight) >> 4) << 24) >> 24;

        last++;
        first++;
        *out = (u8)ar | ((u32)(u8)ag << 5) | ((u32)(u8)ab << 10);
        out++;
    } while (--i >= 0);
}
