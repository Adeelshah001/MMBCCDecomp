/* Wave 25-C attempt 4: 0x0803ad48 (220 B incl pool).
 * v1 in r0, b pinned r1 via asm movs, barrier for base+44, negs for -2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void ShiftPair_Copy_800C(u8 *o, u8 idx);

__attribute__((section(".text.w25c_0803ad48")))
void ShiftPairCfg_3AD48(u8 *p)
{
    u8 *q1 = p + 0x46A0;
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
        *(u16 *)(base + 40) = 136;
        {
            u32 v = 0xFFFC;
            *(u16 *)(base + 42) = v;
        }
        {
            u32 m = 31;
            m = -m;
            b &= m;
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
        u8 *q2 = p + 0x46A1;
        int v2 = (s8)q2[0];

        switch (v2) {
        case 1: {
            u8 *base = (u8 *)0x02004D7C;
            u8 *p44 = base;
            u32 w;
            register u32 b __asm__("r1");
            p44 += 44;
            __asm__ volatile("movs %0, #1" : "=r"(b));
            b |= *p44;
            *(u16 *)(base + 40) = 136;
            {
                u32 t = 64;
                *(u16 *)(base + 42) = t;
                b &= t - 95;
            }
            b |= 32;
            *p44 = (u8)b;
            w = *(u16 *)(base + 44);
            w &= ~0x3C0;
            w |= 0x80;
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

