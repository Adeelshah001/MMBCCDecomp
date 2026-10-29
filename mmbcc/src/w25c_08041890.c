/* Wave 25-C attempt 4: 0x08041890 (220 B incl pool).
 * v1 in r0, b pinned r1 via asm movs, barrier for base+44, negs for -2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void ShiftPair_Copy_800C(u8 *o, u8 idx);

__attribute__((section(".text.w25c_08041890")))
void ShiftPairCfg_41890(u8 *p)
{
    u8 *q1 = p + 0x46B2;
    int v1 = (s8)q1[0];

    switch (v1) {
    case 1: {
        u8 *base = (u8 *)0x02004D48;
        u8 *p44 = base;
        u32 w;
        register u32 b __asm__("r1");
        p44 += 44;
        __asm__ volatile("movs %0, #1" : "=r"(b));
        b |= *p44;
        {
            u32 v40;
            __asm__ volatile("movs %0, #146\n\tlsl %0, %0, #1" : "=r"(v40));
            *(u16 *)(base + 40) = v40;
        }
        {
            u32 t = 12;
            *(u16 *)(base + 42) = t;
            b &= t - 43;
        }
        b |= 32;
        *p44 = (u8)b;
        w = *(u16 *)(base + 44);
        w &= ~0x3C0;
        w |= 0x40;
        *(u16 *)(base + 44) = w;
        ShiftPair_Copy_800C(base, 1);
        q1[0] = 2;
        break;
    }
    case 3: {
        u8 *base = (u8 *)0x02004D48;
        __asm__ volatile("" : "+r"(base));
        base += 44;
        {
            u32 m = 2;
            m = -m;
            *base &= m;
        }
        q1[0] = 0;
        break;
    }
    }

    {
        u8 *q2 = p + 0x46B3;
        int v2 = (s8)q2[0];

        switch (v2) {
        case 1: {
            u8 *base = (u8 *)0x02004D7C;
            u8 *p44 = base;
            u32 w;
            register u32 b __asm__("r1");
            register u32 c128 __asm__("r4");
            p44 += 44;
            __asm__ volatile("movs %0, #1" : "=r"(b));
            b |= *p44;
            {
            u32 v40;
            __asm__ volatile("movs %0, #146\n\tlsl %0, %0, #1" : "=r"(v40));
            *(u16 *)(base + 40) = v40;
        }
            __asm__ volatile("movs %0, #128" : "=r"(c128));
            {
                u32 t = 128;
                *(u16 *)(base + 42) = t;
                b &= t - 159;
            }
            b |= 32;
            *p44 = (u8)b;
            w = *(u16 *)(base + 44);
            w &= ~0x3C0;
            w |= c128;
            *(u16 *)(base + 44) = w;
            ShiftPair_Copy_800C(base, 2);
            q2[0] = 2;
            break;
        }
        case 3: {
            u8 *base = (u8 *)0x02004D7C;
            __asm__ volatile("" : "+r"(base));
            base += 44;
            {
                u32 m = 2;
                m = -m;
                *base &= m;
            }
            q2[0] = 0;
            break;
        }
        }
    }
}

