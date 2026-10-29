/* Wave 6 BLK-A batch (coordinator-verified).
   Evidence: docs/match_notes_wave6_blkA.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08003154: sub_08003154 (coordinator-verified). */
extern void SetU32_4(u8 *s, u32 v);

__attribute__((section(".text.w6a_3154")))
void sub_08003154(u8 *s, u32 a1, u32 a2) {
    u32 m, a;
    u32 z;
    int c16, c8;
    int k2;

    {
        register u32 v800 __asm__("r1");
        __asm__("ldr %0,=0x0800330d" : "=r"(v800));
        SetU32_4(s, v800);
    }

    {
        register int k1 __asm__("r2");
        register u32 b0 __asm__("r0");
        k1 = -0x21;
        b0 = s[17];
        m = k1 & b0;
    }
    __asm__("movs %0,#15" : "=l"(a));
    {
        u32 b = s[21];
        __asm__("and %0,%1" : "+l"(a) : "l"(b));
    }
    __asm__("movs %0,#0" : "=l"(z));
    *(u16 *)(s + 22) = 0;
    s[24] = z;
    s[25] = z;
    __asm__("movs %0,#16" : "=l"(c16));
    m |= c16;
    k2 = -0x0d;
    m &= k2;
    a &= k2;
    __asm__("movs %0,#8" : "=l"(c8));
    a |= c8;
    s[21] = a;
    *(u32 *)(s + 8) = a1;
    *(u32 *)(s + 12) = a2;
    {
        register int k3 __asm__("r0");
        k3 = -4;
        m &= k3;
        s[17] = m;
        {
            register int k4 __asm__("r0");
            register u32 b19 __asm__("r1");
            k4 = k3 - 0x3b;
            b19 = s[19];
            __asm__("and %0,%1" : "+r"(k4) : "r"(b19));
            s[19] = k4;
        }
    }
    {
        register u32 mfe __asm__("r0");
        register u32 h __asm__("r1");
        __asm__("ldr %0,=0xfffffe00" : "=r"(mfe));
        h = *(u16 *)(s + 18);
        __asm__("and %0,%1" : "+r"(mfe) : "r"(h));
        *(u16 *)(s + 18) = mfe;
    }
    s[16] = z;
}

/* 0x08003298: sub_08003298 (coordinator-verified). */
extern void SetU32_4(u8 *s, u32 v);

__attribute__((section(".text.w6a_3298")))
void sub_08003298(u8 *s, u32 a1, u32 a2) {
    u32 m, a;
    u32 z;
    int c16, c8;
    int k2;

    {
        register u32 v800 __asm__("r1");
        __asm__("ldr %0,=0x08003cb9" : "=r"(v800));
        SetU32_4(s, v800);
    }

    {
        register int k1 __asm__("r2");
        register u32 b0 __asm__("r0");
        k1 = -0x21;
        b0 = s[17];
        m = k1 & b0;
    }
    __asm__("movs %0,#15" : "=l"(a));
    {
        u32 b = s[21];
        __asm__("and %0,%1" : "+l"(a) : "l"(b));
    }
    __asm__("movs %0,#0" : "=l"(z));
    *(u16 *)(s + 22) = 0;
    s[24] = z;
    s[25] = z;
    __asm__("movs %0,#16" : "=l"(c16));
    m |= c16;
    k2 = -0x0d;
    m &= k2;
    a &= k2;
    __asm__("movs %0,#8" : "=l"(c8));
    a |= c8;
    s[21] = a;
    *(u32 *)(s + 8) = a1;
    *(u32 *)(s + 12) = a2;
    {
        int k3f;
        __asm__("movs %0,#0x3f" : "=l"(k3f));
        k3f = -k3f;
        {
            u32 b19 = s[19];
            s[19] = k3f & b19;
        }
    }
    {
        register u32 v100 __asm__("r0");
        v100 = (0x80 << 1);
        *(u16 *)(s + 28) = v100;
        *(u16 *)(s + 30) = v100;
    }
    {
        register int k3 __asm__("r0");
        k3 = -4;
        m &= k3;
    }
    {
        int c1;
        __asm__("movs %0,#1" : "=l"(c1));
        __asm__("orr %0,%1" : "+l"(m) : "l"(c1));
        s[17] = m;
    }
    {
        register u32 mfe __asm__("r0");
        register u32 h __asm__("r1");
        __asm__("ldr %0,=0xfffffe00" : "=r"(mfe));
        h = *(u16 *)(s + 18);
        __asm__("and %0,%1" : "+r"(mfe) : "r"(h));
        *(u16 *)(s + 18) = mfe;
    }
    s[16] = z;
}
