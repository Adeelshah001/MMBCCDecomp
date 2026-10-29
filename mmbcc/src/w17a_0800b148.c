typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

void sub_0800B470(s16 b);
void sub_08007EEC(u32 a);
void sub_0800B6F4(u8 *base, u32 b);

__attribute__((section(".text.w17a_0800b148")))
u8 sub_0800B148(u8 a, u16 b, u8 c)
{
    register u32 aa __asm__("ip");
    register u16 bb __asm__("r6");
    u32 c24;
    register u32 cc __asm__("r8");
    register u8 *base __asm__("r5");
    register u32 v21 __asm__("r4");
    register u8 *base9 __asm__("r9");
    register u8 b4 __asm__("r1");
    u8 mask;
    u8 t0;
    register s32 b16 __asm__("r3");

    /* Force exact ROM prologue order (volatile: not reordered). */
    __asm__ volatile (
        "lsl r0, r0, #24\n\t"
        "lsr r0, r0, #24\n\t"
        "mov %0, r0\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr %1, r1, #16\n\t"
        "lsl %2, r2, #24\n\t"
        "lsr r0, %2, #24\n\t"
        "mov %3, r0"
        : "=r" (aa), "=r" (bb), "=r" (c24), "=r" (cc)
        :
        : "r0", "r1", "r2", "cc", "memory"
    );
    base = (u8 *)0x02004E40;

    b4 = base[4];
    mask = 15;
    t0 = mask & b4;
    base9 = base;
    if (t0 != 0)
        return 0;

    if ((b4 & 128) == 0) {
        /* ROM 0x38-0x4a: c1, t19, base[19], base[5] in exact order/regs */
        __asm__ volatile (
            "movs r2, #1\n\t"
            "mov r1, r8\n\t"
            "and r1, r1, r2\n\t"
            "movs r0, #2\n\t"
            "neg r0, r0\n\t"
            "ldrb r3, [r5, #19]\n\t"
            "and r0, r0, r3\n\t"
            "orr r0, r0, r1\n\t"
            "strb r0, [r5, #19]\n\t"
            "strb r2, [r5, #5]"
            :
            :
            : "r0", "r1", "r2", "r3", "cc", "memory"
        );
        v21 = base[21];
        b16 = ((s32)bb) << 16;
        goto join;
    }

    {
        register u32 v21t __asm__("r1");
        u32 sh;
        v21t = base[21];
        sh = (v21t << 28) >> 28;
        v21 = v21t;
        if (sh != aa) {
        u32 tA, tB;
        base[5] = 5;
        tA = (aa << 4);
        tB = (v21 & mask);
        tB |= tA;
        base[21] = (u8)tB;
    } else {
        u8 tm = v21 & mask;
        register u32 tmc __asm__("r0");
        __asm__ volatile ("add %0, %1, #0" : "=r" (tmc) : "r" (tm));
        if (tmc == 2)
            goto memcheck_tm;
        __asm__ volatile ("lsl %0, %1, #16" : "=r" (b16) : "r" (bb));
        if (tmc != 4)
            goto join;
memcheck_tm:
        {
            register u32 bf __asm__("r0") = ((u32)bb) << 16;
            register u16 mh __asm__("r3");
            u32 m16;
            mh = *(u16 *)(base + 6);
            m16 = ((u32)mh) << 16;
            __asm__ volatile ("add %0, %1, #0" : "=r" (b16) : "r" (bf));
            if (m16 != (u32)b16) {
                u32 t21b;
                base[5] = 5;
                t21b = (aa << 4);
                t21b |= tm;
                base[21] = (u8)t21b;
            } else {
                goto join;
            }
        }
    }
    *(u16 *)(base + 24) = bb;
    {
        register u32 bit6 __asm__("r1");
        register u32 one __asm__("r2");
        u32 t30;
        register u32 bit1 __asm__("r1");
        u32 t31;
        register u32 b31 __asm__("r6");
        bit6 = c24 >> 25;
        bit6 = ((bit6 & (one = 1, one)) << 6);
        t30 = (u32)-65;
        t30 &= base[30];
        t30 |= bit6;
        base[30] = (u8)t30;
        bit1 = ((c24 >> 27) & one);
        t31 = (u32)-2;
        __asm__ volatile ("ldrb %0, [%1, #31]" : "=r" (b31) : "r" (base));
        t31 &= b31;
        t31 |= bit1;
        base[31] = (u8)t31;
    }
    return 0;

join:
    {
        register u32 v20 __asm__("r2");
        register u32 v20s __asm__("r1");
        u32 t30;
        u32 v27;
        c24 = (u32)base9;
        v20 = ((u8 *)c24)[20];
        v20s = v20 >> 3;
        t30 = (u32)-32;
        t30 &= ((u8 *)c24)[30];
        t30 |= v20s;
        ((u8 *)c24)[30] = (u8)t30;
        v27 = (v20 & 7) | 0xC0;
        ((u8 *)c24)[20] = (u8)v27;
    }
    {
        register u32 c7 __asm__("r7");
        u8 a15;
        u32 t21;
        a15 = 15;
        c7 = aa;
        a15 &= c7;
        t21 = (u32)-16;
        t21 &= v21;
        t21 |= a15;
        base[21] = (u8)t21;
    }
    sub_0800B470((s16)(b16 >> 16));
    {
        register u32 bit5 __asm__("r1");
        register u32 t30 __asm__("r0");
        bit5 = (((cc >> 1) & 1) << 5);
        t30 = (u32)-33;
        t30 &= base[30];
        t30 |= bit5;
        base[30] = (u8)t30;
        t30 &= 32;
        if (t30 != 0)
            sub_08007EEC(0);
    }
    {
        register u32 cc3 __asm__("r3");
        register u32 c3 __asm__("r1");
        u32 t30;
        register u32 b30 __asm__("r6");
        u8 m4;
        s32 t14;
        __asm__ volatile ("mov %0, r8" : "=r" (cc3));
        c3 = (((cc3 >> 3) & 1) << 7);
        t30 = 127;
        __asm__ volatile ("ldrb %0, [%1, #30]" : "=r" (b30) : "r" (base));
        t30 &= b30;
        t30 |= c3;
        base[30] = (u8)t30;
        m4 = (u8)(4 & cc3);
        t14 = -(s32)m4;
        t14 >>= 31;
        t14 &= 2;
        v21 = 0;
        *(u16 *)(base + 14) = (u16)t14;
    }
    sub_0800B6F4(base, 0);
    base[9] = (u8)v21;
    base[10] = (u8)v21;
    return 1;
}
}

__asm__(
    ".set sub_0800B470, 0x0800B470\n"
    ".set sub_08007EEC, 0x08007EEC\n"
    ".set sub_0800B6F4, 0x0800B6F4\n"
);
