/* Wave 7 batch F (1 matched, coordinator-verified, main agbcc).
   Evidence: docs/match_notes_wave7_f.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x0800d3a0: Gfx_PaletteModeSet (128B, coordinator-verified). */
__attribute__((section(".text.w7f_0800d3a0")))
void sub_0800D3A0(u8 a) {
    u8 *p = (u8 *)0x02004F80;
    u8 r4, r3;
    u8 r5 = 0;

    if (a == 0) {
        r4 = 0;
        r3 = 0;
    } else {
        r4 = 31;
        r3 = 1;
        if (a == 2)
            r5 = 1;
    }
    {
        register int lo __asm__("r2");
        register int hi __asm__("r1");
        s8 s;
        lo = r3 << 5;
        hi = r5 << 7;
        s = r4;
        if (s <= 31)
            lo |= s;
        else
            hi |= 31;
        {
            register u32 v __asm__("r0") = lo;
            v |= hi;
            *p = v;
        }
    }
    if (r3 == 2) {
        u8 t = 2;
        if (r5 == 0)
            t = 1;
        p[2] = t;
    }
    if (r5 == 0) {
        u32 t;
        __asm__ volatile("lsl %0, %1, #24" : "=l"(t) : "l"(r4));
        t = -t;
        r4 = t >> 24;
    }
    {
        u8 *q = (u8 *)0x03002420;
        int t = (s8)r4 + 32;
        q[0x400] = t;
        q[0x401] = t;
        q += 0x402;
        *q = t;
    }
}
