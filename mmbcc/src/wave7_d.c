/* Wave 7 batch D (2 matched, coordinator-verified, main agbcc).
   Evidence: docs/match_notes_wave7_d.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x080031b8: StructInit_031B8 (was sub_080031B8, coordinator-verified). */
extern void SetU32_4(u8 *s, u32 v);

__attribute__((section(".text.w7d_080031b8")))
void StructInit_031B8(u8 *s, u32 a1, u32 a2) {
    register u32 va1 __asm__("r6") = a1;
    register u32 va2 __asm__("r8") = a2;
    register u32 m __asm__("r2");
    u32 a;
    register u32 z __asm__("r5");
    int c16, c8;
    int k2;

    {
        register u32 vptr __asm__("r1");
        __asm__("ldr %0,=0x08003725" : "=r"(vptr));
        SetU32_4(s, vptr);
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
    *(u32 *)(s + 8) = va1;
    {
        register u32 t __asm__("r1");
        __asm__("mov %0,%1" : "=r"(t) : "r"(va2));
        *(u32 *)(s + 12) = t;
    }
    {
        register int k3f __asm__("r3");
        register int t __asm__("r0");
        register u32 b19 __asm__("r1");
        k3f = -0x3f;
        t = k3f;
        b19 = s[19];
        __asm__("and %0,%1" : "+r"(t) : "r"(b19));
        m |= 3;
        s[17] = m;
        __asm__("and %0,%1" : "+r"(t) : "r"(k3f));
        s[19] = t;
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


/* 0x0800322c: StructInit_0322C (was sub_0800322C, coordinator-verified). */
extern void SetU32_4(u8 *s, u32 v);

__attribute__((section(".text.w7d_0800322c")))
void StructInit_0322C(u8 *s, u32 a1, u32 a2) {
    register u32 m __asm__("r2");
    u32 a;
    register u32 z __asm__("r3");
    int c16, c8;
    int k2;

    {
        register u32 vptr __asm__("r1");
        __asm__("ldr %0,=0x080039a5" : "=r"(vptr));
        SetU32_4(s, vptr);
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
    __asm__("movs %0,#0" : "=r"(z));
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
        register int k3f __asm__("r0");
        register u32 b19 __asm__("r1");
        k3f = -0x3f;
        b19 = s[19];
        __asm__("and %0,%1" : "+r"(k3f) : "r"(b19));
        s[19] = k3f;
    }
    {
        register u32 v100 __asm__("r0");
        v100 = (0x80 << 1);
        *(u16 *)(s + 28) = v100;
        *(u16 *)(s + 30) = v100;
    }
    {
        int c3;
        __asm__("movs %0,#3" : "=l"(c3));
        __asm__("orr %0,%1" : "+r"(m) : "r"(c3));
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

