/* W40-B v7: F_08003874 @ 0x08003874, 304 B.
 * v6 + : base block-pinned r4 inside the A-D block (e assigned there),
 * e2 plain (born in block B, so r2 is free for k in block A).
 * Known remaining: prologue k roundtrip (+4) -> .s patch.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    u8 pad0[19];
    u8 b19;
    u8 pad1[4];
    u8 b24;
    u8 b25;
    u8 pad2;
    u8 b27;
} S_t;

extern s32 SDiv_0804DD08(s32 a, s32 b);

__attribute__((section(".text.w40b_08003874")))
void F_08003874(S_t *p, u8 k) {
    register S_t *pp __asm__("r6");
    register u8 kk __asm__("r9");
    register u8 *e __asm__("r5");
    u8 h;
    int t;
    int idx;
    int sh;
    int mask;
    int b;

    pp = p;
    kk = k;
    sh = ((((u32)pp->b19 << 26) >> 27) << 5);
    {
        register u8 *base __asm__("r4");
        register u16 *tbl __asm__("r8");
        base = (u8 *)0x03002830;
        e = (u8 *)(sh + (int)base);
        tbl = (u16 *)0x0804e05c;
        h = pp->b25;
        __asm__ volatile("" ::: "memory");
        h ^= pp->b24;
        t = (((h << 8) - h) ^ kk) + h;
        idx = t & 0xFF;
        idx += 64;
        *(s16 *)(e + 6) = tbl[idx];

        {
        register u8 *e2 __asm__("r2");
        e2 = (u8 *)(((((u32)pp->b19 << 26) >> 27) << 5) + (int)base);
        h = pp->b25;
        __asm__ volatile("" ::: "memory");
        h ^= pp->b24;
        t = (((h << 8) - h) ^ kk) + h;
        idx = t & 0xFF;
        idx += 64;
        *(s16 *)(e2 + 30) = tbl[idx];

        e2 = (u8 *)(((((u32)pp->b19 << 26) >> 27) << 5) + (int)base);
        h = pp->b25;
        __asm__ volatile("" ::: "memory");
        h ^= pp->b24;
        t = (((h << 8) - h) ^ kk) + h;
        *(s16 *)(e2 + 14) = tbl[t & 0xFF];

        e2 = (u8 *)(((((u32)pp->b19 << 26) >> 27) << 5) + (int)base);
        h = pp->b25;
        __asm__ volatile("" ::: "memory");
        h ^= pp->b24;
        t = (((h << 8) - h) ^ kk) + h;
        *(s16 *)(e2 + 22) = -tbl[t & 0xFF];
        }
    }
    {
        register int vA __asm__("r4");
        register int vB __asm__("r0");
        {
            register int off6 __asm__("r7");
            int sv;
            off6 = 6;
            __asm__ volatile("ldrsh %0, [%1, %2]" : "=l"(sv) : "l"(e), "r"(off6));
            vA = SDiv_0804DD08(sv << 8, 257);
            *(s16 *)(e + 6) = vA;
        }
        {
            register int off14 __asm__("r2");
            int sv;
            off14 = 14;
            __asm__ volatile("ldrsh %0, [%1, %2]" : "=l"(sv) : "l"(e), "r"(off14));
            vB = SDiv_0804DD08(sv << 8, 257);
            *(s16 *)(e + 14) = vB;
        }
        b = pp->b24;
        mask = (b << 31) >> 31;
        vA ^= mask;
        vA += b;
        *(s16 *)(e + 6) = vA;
        mask ^= vB;
        vB = mask + b;
        *(s16 *)(e + 14) = vB;

        {
            register int off22 __asm__("r4");
            int sv;
            off22 = 22;
            __asm__ volatile("ldrsh %0, [%1, %2]" : "=l"(sv) : "l"(e), "r"(off22));
            vA = SDiv_0804DD08(sv << 8, 257);
            *(s16 *)(e + 22) = vA;
        }
        {
            register int off30 __asm__("r7");
            int sv;
            off30 = 30;
            __asm__ volatile("ldrsh %0, [%1, %2]" : "=l"(sv) : "l"(e), "r"(off30));
            vB = SDiv_0804DD08(sv << 8, 257);
            *(s16 *)(e + 30) = vB;
        }
        b = pp->b25;
        mask = (b << 31) >> 31;
        vA ^= mask;
        vA += b;
        *(s16 *)(e + 22) = vA;
        mask ^= vB;
        vB = mask + b;
        *(s16 *)(e + 30) = vB;
    }

    pp->b27 = kk;
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
