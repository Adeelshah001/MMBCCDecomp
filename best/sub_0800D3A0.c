void sub_0800D3A0(s8 arg0) {
    u8 *base = (u8 *)0x02004F80;
    u32 r4;
    u32 r5 = 0;
    u32 r3;
    u32 r2;
    u32 r1;
    u32 r0;

    r0 = (u32)(u8)arg0;
    r0 = (r0 << 0x18) >> 0x18;
    if (r0 == 0) {
        r4 = 0;
        r3 = 0;
    } else {
        r4 = 0x1F;
        r3 = 1;
        if (r0 == 2) {
            r5 = 1;
        }
    }

    r2 = r3 << 5;
    r1 = r5 << 7;
    r0 = r4;
    r0 = (r0 << 0x18);
    r0 = (int)r0 >> 0x18;
    if ((int)r0 <= 0x1F) {
        r2 |= r0;
    } else {
        r1 |= 0x1F;
    }

    r0 = r2;
    r0 |= r1;
    base[0] = (u8)r0;

    if (r3 == 2) {
        r0 = 2;
        if (r5 == 0) {
            r0 = 1;
        }
        base[2] = (u8)r0;
    }

    if (r5 == 0) {
        r0 = r4;
        r0 = (r0 << 0x18);
        r0 = -(int)r0;
        r4 = (u32)((u32)r0 >> 0x18);
    }

    r0 = r4;
    r0 = (r0 << 0x18);
    r0 = (int)r0 >> 0x18;
    r0 += 0x20;

    r2 = 0x03002420;
    r3 = 0x400;
    r1 = r2 + r3;
    *(u8 *)r1 = (u8)r0;
    r3 = r3 + 1;
    r1 = r2 + r3;
    *(u8 *)r1 = (u8)r0;
    r1 = 0x402;
    r1 = r2 + r1;
    *(u8 *)r1 = (u8)r0;
}
