/* Wave 11 worker A: 26 matched functions, all old_agbcc. */
/* See docs/match_notes_wave11_A.md for idioms. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Node {
    u8 pad[44];
    struct Node *next;
    struct Node *prev;
    struct Node *x;
} Node;

__attribute__((section(".text.w11a_08020230")))
void F_20230(u8 *a, u8 *p, u8 x)
{
    u8 *q = p;
    u8 xx = x;
    a += 0x23;
    if ((*a & 15) == 0)
        q[5] = xx;
    else
        q[6] = xx;
}
__asm__(".section .text.w11a_08020230,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_08024744")))
int F_24744(u8 x)
{
    u8 xx = x;
    register int t __asm__("r1");
    u8 u;
    __asm__ volatile("" : "+r" (xx));
    t = xx;
    t -= 50;
    u = (u8)t;
    if (u <= 6)
        return t;
    return -1;
}
__asm__(".section .text.w11a_08024744,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_0803fe00")))
int F_3FE00(u16 x)
{
    u16 xx = x;
    int r = 0;
    switch (xx) {
    case 0x60:
    case 0xD3:
    case 0xD4:
        r = 1;
        break;
    }
    return r;
}

__attribute__((section(".text.w11a_0804c53c")))
void F_4C53C(u8 dummy, u8 *p)
{
    register u8 *pp __asm__("r1") = p;
    register u8 t __asm__("r2");
    register u8 v __asm__("r3");
    __asm__ volatile("movs %0, #0" : "=r" (t));
    (void)dummy;
    pp[22] = t;
    pp[26] = t;
    t = pp[24];
    if (t == 0)
        t = 12;
    else
        t = 3;
    v = pp[0];
    v |= t;
    pp[0] = v;
}
__asm__(".section .text.w11a_0804c53c,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_0800ee50")))
void F_EE50(void)
{
    register u8 *pp __asm__("r0");
    register u8 *qq __asm__("r2");
    u8 v, r;
    __asm__ volatile("" : "=r" (pp) : "0" ((u8 *)0x02005160));
    qq = pp;
    qq += 0x44;
    v = *qq + 1;
    r = 0;
    if (v <= 1)
        r = 1;
    *qq = r;
}

__attribute__((section(".text.w11a_0800d104")))
void F_D104(u8 *p)
{
    register u16 *pp __asm__("r3");
    register u32 m1 __asm__("r1");
    register u32 m2 __asm__("r2");
    u16 v;
    __asm__ volatile("" : "=r" (pp) : "0" ((u16 *)0x020031e0));
    __asm__ volatile("" : "=r" (m1) : "0" (0x0000edff));
    v = *pp;
    m1 &= v;
    __asm__ volatile("" : "=r" (m2) : "0" (0x0000dbff));
    m1 &= m2;
    *pp = (u16)m1;
    {
        u32 m3 = (u32)-3;
        u32 t = p[9];
        m3 &= t;
        p[9] = (u8)m3;
    }
}

__attribute__((section(".text.w11a_0803f440")))
void F_3F440(u8 *base, u8 i, u8 j)
{
    u8 *t;
    u32 off;
    u8 a, b;
    __asm__ volatile("" : "=r" (off) : "0" (0x45C4));
    t = base + off;
    a = t[i];
    b = t[j];
    t[i] = b;
    t[j] = a;
}

__attribute__((section(".text.w11a_0803f460")))
void F_3F460(u8 *base, u8 i, u8 j)
{
    u8 *t;
    u32 off;
    u8 a, b;
    __asm__ volatile("" : "=r" (off) : "0" (0x464C));
    t = base + off;
    a = t[i];
    b = t[j];
    t[i] = b;
    t[j] = a;
}

__attribute__((section(".text.w11a_0803fd9c")))
int F_3FD9C(u16 x)
{
    u16 xx = x;
    int r = 0;
    u32 p;
    __asm__ volatile("" : "=r" (p) : "0" (0x222));
    if (xx == p || xx == 0x3000)
        r = 1;
    return r;
}

__attribute__((section(".text.w11a_0804c610")))
void F_4C610(u8 *p, u16 x)
{
    u8 *q = p;
    u16 xx = x;
    register u32 vv __asm__("r3") = *(u32 *)(q + 52);
    u32 pv;
    __asm__ volatile("" : "=r" (pv) : "0" (0x68736d53));
    if (vv == pv) {
        register u32 c100 __asm__("r0");
        *(u16 *)(q + 38) = xx;
        *(u16 *)(q + 36) = xx;
        __asm__ volatile("" : "=r" (c100) : "0" (0x100));
        *(u16 *)(q + 40) = (u16)c100;
    }
}

__attribute__((section(".text.w11a_08011054")))
int F_11054(u8 *p)
{
    u8 *q = p;
    u8 *g;
    __asm__ volatile("" : "=r" (g) : "0" ((u8 *)0x020051b0));
    if (g[4] == 1) {
        q[0] = g[12];
        return 1;
    }
    return 0;
}

__attribute__((section(".text.w11a_080173fc")))
void F_173FC(u8 *p)
{
    u8 *q = p;
    if (q[18] == 0) {
        register u32 pool __asm__("r1");
        register u32 *tt __asm__("r0");
        u32 off;
        __asm__ volatile("" : "=r" (pool) : "0" (0x082243d8));
        off = q[9] * 4;
        tt = (u32 *)off;
        tt = (u32 *)((u8 *)tt + pool);
        *(u32 *)(q + 12) = 2;
        tt = *(u32 **)tt;
        *(u32 *)(q + 20) = *(u32 *)((u8 *)tt + 8);
    }
}

__attribute__((section(".text.w11a_08021c0c")))
u8 *F_21C0C(u32 x)
{
    register u32 xx __asm__("r2") = x;
    u32 *g;
    u32 *t;
    u32 o;
    u8 *p;
    u8 *q;
    __asm__ volatile("lsl %0, %0, #24" : "+r" (xx));
    __asm__ volatile("" : "=r" (g) : "0" ((u32 *)0x08173760));
    t = *(u32 **)((u8 *)g + 108);
    o = *(u32 *)((u8 *)t + 68);
    o += 68;
    p = (u8 *)t + o;
    q = p;
    q += 12;
    q += *(u32 *)(p + 12);
    __asm__ volatile("lsr %0, %0, #19" : "+r" (xx));
    return q + xx;
}

__attribute__((section(".text.w11a_08025308")))
void F_25308(u8 *p)
{
    u8 *q = p;
    s16 i = 0;
    u8 z = 0;
    do {
        q[i] = z;
        i++;
    } while (i <= 0xF8);
}

__attribute__((section(".text.w11a_08001d68")))
void F_1D68(u8 *p)
{
    u8 *q = p;
    u16 z = 0;
    u8 *a;
    u8 *b;
    *(u16 *)(q + 8) = z;
    *(u16 *)(q + 6) = z;
    *(u16 *)(q + 4) = z;
    *(u16 *)(q + 2) = z;
    *(u16 *)(q + 0) = z;
    a = q; a += 10;
    b = q; b += 14;
    *(u32 *)b = z;
    *(u32 *)a = z;
    *(u16 *)(q + 18) = z;
}
__asm__(".section .text.w11a_08001d68,\"ax\",%progbits\n.byte 0, 0\n.previous");




__attribute__((section(".text.w11a_0804bdc0")))
void F_4BDC0(Node *p)
{
    register Node *pp __asm__("r0") = p;
    Node *nx = pp->next;
    if (nx == 0)
        return;
    {
        Node *xv = pp->x;
        Node *pv = pp->prev;
        if (pv != 0)
            pv->x = xv;
        else
            *(Node **)((u8 *)nx + 32) = xv;
        if (xv != 0)
            xv->prev = pv;
        pp->next = 0;
    }
}

__attribute__((section(".text.w11a_08000ef8")))
void F_EF8(u8 *p)
{
    int i;
    u8 *a;
    u8 z;
    u8 *b;
    i = 0;
    a = p; a += 12;
    z = 0;
    b = p; b += 16;
    do {
        a[i] = z;
        *(u16 *)b = z;
        b += 2;
        i++;
    } while (i <= 3);
}
__asm__(".section .text.w11a_08000ef8,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_08023b64")))
void F_23B64(u16 *p)
{
    u16 *q = p;
    u8 i = 0;
    do {
        u16 t = q[i];
        if (t <= 9)
            q[i] = t + 1;
        else
            q[i] = t + 0x54;
        i++;
    } while (i <= 23);
}
__asm__(".section .text.w11a_08023b64,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_08023d10")))
u8 F_23D10(u8 *p)
{
    u8 *q = p;
    u8 sum = 0;
    u8 i = 0;
    do {
        sum += q[i];
        i++;
    } while (i <= 13);
    return -sum;
}
__asm__(".section .text.w11a_08023d10,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_08025490")))
void F_25490(u8 *p, u8 a, u8 b)
{
    u8 aa = a;
    u8 bb = b;
    u8 *bs = *(u8 **)(p + 8);
    u8 *pa = bs + aa;
    u8 tmp = *pa;
    u8 v = bs[bb];
    *pa = v;
    {
        u8 *b2 = *(u8 **)(p + 8);
        b2[bb] = tmp;
    }
}
__asm__(".section .text.w11a_08025490,\"ax\",%progbits\n.byte 0, 0\n.previous");

__attribute__((section(".text.w11a_0804acdc")))
void F_4ACDC(u32 x)
{
    u8 *base;
    u8 *p;
    u8 *q;
    __asm__ volatile("" : "=r" (base) : "0" ((u8 *)0x0200bd20));
    p = base + 0x7f;
    *p = 0;
    p--;
    *p = 0;
    p += 0x22;
    (*p)++;
    q = base + 0xa1;
    *q = (u8)x;
}

__attribute__((section(".text.w11a_08036318")))
u32 F_36318(u32 x)
{
    u32 xx = x;
    u8 *base;
    __asm__ volatile("" : "=r" (base) : "0" ((u8 *)0x0200bce8));
    if (xx > 6)
        return 0;
    *(base + 2) |= (1 << xx);
    return 1;
}

__attribute__((section(".text.w11a_0803fa48")))
u32 F_3FA48(u16 x)
{
    u16 xx = x;
    u32 r = 0;
    int pool;
    __asm__ volatile("" : "=r" (pool) : "0" (0x3a1));
    if (xx >= pool) {
        pool++;
        if (xx <= pool)
            r = 1;
        else if (xx == 0x13a0)
            r = 1;
    }
    return r;
}
