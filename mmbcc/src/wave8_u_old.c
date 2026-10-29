/* Wave 8 batch U: unattempted-pool cracks (old_agbcc).
 * Evidence: docs/match_notes_wave8_U.md, docs/wave8_U_results.tsv. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

typedef signed int s32;

typedef struct {
    s32 x;
    s32 y;
} Pair32;

void PairDiffMid_110B0(const Pair32 *a, Pair32 *b) __attribute__((section(".text.w8u_0x080110b0")));
void PairDiffMid_110B0(const Pair32 *a, Pair32 *b)
{
    register s32 x __asm__("r0");
    register s32 y __asm__("r2");
    register s32 d __asm__("r3");
    register s32 m __asm__("r4");

    y = a->y;
    x = a->x;
    d = x - y;
    m = (y >> 1) + (x >> 1);
    b->x = d;
    b->y = m;
}


extern u8 gEwram_02004E40[];

u32 CheckAndSet_B2B4(void) __attribute__((section(".text.w8u_0x0800b2b4")));
u32 CheckAndSet_B2B4(void)
{
    u8 *p = gEwram_02004E40;
    u8 v = p[4];
    int t1;
    int t2;

    __asm__("movs %0,#15\n\tand %0,%1" : "=l"(t1) : "l"(v));
    if (t1 != 0)
        return 0;
    __asm__("movs %0,#128\n\tand %0,%1" : "=l"(t2) : "l"(v));
    if (t2 != 0)
        p[5] = 2;
    return 1;
}

__asm__(
".set gEwram_02004E40, 0x02004E40\n"
);


void Clr20_4B310(u8 *p, u8 v) __attribute__((section(".text.w8u_0x0804b310")));
void Clr20_4B310(u8 *p, u8 v)
{
    register u8 w __asm__("r4") = v;
    register u8 *base __asm__("r3");
    register u8 *q __asm__("r2");
    u16 i;

    __asm__ volatile("" : "+r"(w));
    base = p;
    q = base;
    i = 0;
    do {
        *q++ = 0;
        i++;
    } while (i <= 19);
    base[4] = w;
}


extern u8 gEwram5160[];

u32 FlagByte_CopyOrNeg1(u8 *p) __attribute__((section(".text.w8u_0x08010374")));
u32 FlagByte_CopyOrNeg1(u8 *p)
{
    u8 *q = gEwram5160;
    u8 *r = p;

    if (*q == 0) {
        u8 *t = q;
        u8 v;

        t += 67;
        v = *t;
        *r = v;
        return 1;
    } else {
        register int v __asm__("r2");
        register int w __asm__("r0");

        __asm__ volatile("movs %0, #1\n\tneg %0, %0" : "=r"(v));
        w = v;
        *r = (u8)w;
        return 0;
    }
}

__asm__(
".set gEwram5160, 0x02005160\n"
);


extern u8 g_020051B0[];

u32 ClearSlot_10F88(u8 x) __attribute__((section(".text.w8u_0x08010f88")));
u32 ClearSlot_10F88(u8 x)
{
    u8 *p = g_020051B0;
    int off;
    u8 *q;
    u8 v;

    v = p[3];
    v &= ~(1 << x);
    {
        u8 z = 0;

        p[3] = v;
        off = x * 12;
        p += 24;
        q = p + off;
        q[0] = z;
        q[6] = z;
        q[1] = z;
    }
    return 1;
}

__asm__(
".set g_020051B0, 0x020051B0\n"
);

typedef signed char s8;

void ProcByte_DB40(u8 *p) __attribute__((section(".text.w8u_0x0800db40")));
void ProcByte_DB40(u8 *p)
{
    register u8 *pp __asm__("r2") = p;
    int i = 0;
    s8 *q;
    int v;
    s8 c;

    q = (s8 *)(pp + 33);
    c = q[i];
    if (c != 0) {
        v = 14;
        q[i] = c - 1;
    } else {
        v = ((unsigned)pp[31] << 28) >> 28;
    }
    pp += 69;
    v <<= 4;
    *pp = (*pp & 15) | v;
}

typedef signed short s16;

extern u8 g_FFF8[];

void FillU16_C8BC(u32 dummy, u16 *dst, u16 n) __attribute__((section(".text.w8u_0x0800c8bc")));
void FillU16_C8BC(u32 dummy, u16 *dst, u16 n)
{
    register u32 base __asm__("r4") = (u32)g_FFF8;

    (void)dummy;
    __asm__ volatile(
        "add r5, r4, #0\n\t"
        "mov r3, #0\n\t"
        "cmp r3, %1\n\t"
        "bge 2f\n\t"
        "1:\n\t"
        "strh r5, [%0, #0]\n\t"
        "add %0, #2\n\t"
        "strh r4, [%0, #0]\n\t"
        "add %0, #2\n\t"
        "lsl r0, r3, #16\n\t"
        "mov r3, #128\n\t"
        "lsl r3, r3, #9\n\t"
        "add r0, r0, r3\n\t"
        "lsr r3, r0, #16\n\t"
        "asr r0, r0, #16\n\t"
        "cmp r0, %1\n\t"
        "blt 1b\n\t"
        "2:"
        :
        : "r"(dst), "r"(n), "r"(base)
        : "r0", "r3", "r5", "cc", "memory"
    );
}

__asm__(
".set g_FFF8, 0x0000FFF8\n"
);


extern u8 gEwram_0200BD20[];

typedef struct {
    u8 pad[132];
    u16 v0;
    u16 v1;
    u16 v2;
    u16 v3;
} Dst4A660;

void CopyU16x4_4A660(u16 *src) __attribute__((section(".text.w8u_0x0804a660")));
void CopyU16x4_4A660(u16 *src)
{
    u8 *base = gEwram_0200BD20;
    Dst4A660 *d = (Dst4A660 *)base;
    u8 *p = base + 127;

    *p = 0;
    p--;
    *p = 0;
    d->v0 = src[0];
    d->v1 = src[1];
    d->v2 = src[2];
    d->v3 = src[3];
}

__asm__(
".set gEwram_0200BD20, 0x0200BD20\n"
);


extern u8 g_0817310C[];

void SetNibbleAndLookup_B6F4(u8 *p, u8 x) __attribute__((section(".text.w8u_0x0800b6f4")));
void SetNibbleAndLookup_B6F4(u8 *p, u8 x)
{
    int m15 = 15;
    int v1 = x & m15;
    int m16 = 16;

    p[18] = (p[18] & -m16) | v1;
    {
        u8 *tbl = g_0817310C;
        u8 *e = *(u8 **)(tbl + x * 12);

        p[18] &= m15;
        p[17] = e[1];
    }
}

__asm__(
".set g_0817310C, 0x0817310C\n"
);
