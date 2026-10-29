/* Wave 8 batch S: small-leaf matches (old_agbcc).
 * Evidence: docs/match_notes_wave8_S.md, docs/wave8_S_results.tsv. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
struct Ent12 { u32 *f0; u16 f4; u16 _06; u32 _08; };
extern struct Ent12 rom08106D7C[];
extern u8 rom08106DD0[];
__attribute__((section(".text.w8s_0800300c")))
u16 TblValidate(u16 x)
{
    register u32 xr __asm__("r0") = (u32)x << 16;
    struct Ent12 *tbl = rom08106D7C;
    u8 *pbase = rom08106DD0;
    u32 i = xr >> 13;
    u8 *p = pbase + i;
    u16 vi = *(u16 *)(p + 4);
    struct Ent12 *e = &tbl[vi];
    u32 *q = e->f0;
    if (*q != *(u32 *)p)
        return 0;
    return *(u16 *)((u8 *)q + 4);
}

extern u8 gEwram_02003670[];
__attribute__((section(".text.w8s_08008628")))
s8 FlagA_8628(u8 *p)
{
    int r;
    u32 flag;
    if (p[11])
        goto Ldef;
    flag = gEwram_02003670[0x11ae] & 1;
    r = 32;
    if (flag)
        goto Lend;
    r = 64;
    goto Lend;
Ldef:
    r = 32;
Lend:
    __asm__ volatile("" : "+r" (r));
    return (s8)r;
}

extern u8 gEwram_02003670[];
__attribute__((section(".text.w8s_08008654")))
s8 FlagA_8654(u8 *p)
{
    int r;
    u32 flag;
    if (p[11])
        goto Ldef;
    flag = gEwram_02003670[0x11ae] & 1;
    r = 5;
    if (flag)
        goto Lend;
    r = 6;
    goto Lend;
Ldef:
    r = 5;
Lend:
    __asm__ volatile("" : "+r" (r));
    return (s8)r;
}

extern u8 gEwram_02003670[];
__attribute__((section(".text.w8s_08008680")))
s8 FlagA_8680(u8 *p)
{
    int r;
    u32 flag;
    if (p[11])
        goto Ldef;
    flag = gEwram_02003670[0x11ae] & 1;
    r = 32;
    if (flag)
        goto Lend;
    r = 22;
    goto Lend;
Ldef:
    r = 8;
Lend:
    __asm__ volatile("" : "+r" (r));
    return (s8)r;
}

__attribute__((section(".text.w8s_0800960c")))
void TblInit_960C(u8 dummy)
{
    register u32 i __asm__("r2") = 0;
    register u8 *tbl __asm__("r5") = (u8 *)0x02004E18;
    register u16 z __asm__("r4") = 0;
    register u32 m __asm__("r3");
    register s32 si __asm__("r0");
    __asm__ volatile("movs %0, #255" : "=r" (m));
    do {
        register int e __asm__("r1");
        register u8 *p __asm__("r1");
        si = (s32)(i << 16) >> 16;
        __asm__ volatile("" : "+r" (si));
        e = si * 8;
        p = (u8 *)e;
        p += (int)tbl;
        p[0] = (u8)i;
        p[1] |= (u8)m;
        *(u16 *)(p + 2) = z;
        si++;
        si <<= 16;
        i = (u16)((u32)si >> 16);
        si >>= 16;
    } while (si <= 3);
}

extern u8 gEwram_02003670[];
__attribute__((section(".text.w8s_0800c92c")))
void FillPairs(u8 dummy, u16 *dst, u16 n)
{
    u8 v = gEwram_02003670[0];
    u16 c = 0xFFF8;
    s16 i = 0;
    if (i >= n)
        return;
    do {
        *dst++ = v;
        *dst++ = c;
        i++;
    } while (i < n);
}

struct Rom0822740C {
    u16 f00; u16 f02; u16 f04; u8 _06[2];
    u16 f08; u8 f0A; u8 _0B; u8 f0C; u8 f0D; u8 f0E; u8 f0F;
};
extern struct Rom0822740C rom0822740C[];
struct Ew02007090 { u8 _00[18]; u16 f18; };
extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_08024554")))
u16 TblGet_f00(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f00;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_08024570")))
u16 TblGet_f04(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f04;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_0802458c")))
u16 TblGet_f02(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f02;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080245c4")))
u8 TblGet_f0A(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f0A;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080245e0")))
u16 TblGet_f08(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f08;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080245fc")))
u8 TblGet_f0C(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f0C;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_08024618")))
u8 TblGet_f0D(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f0D;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_08024670")))
u8 TblGet_f0E(u16 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f0E;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_0802468c")))
u8 TblGet_f0F(u16 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f0F;
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080246a8")))
u32 TblGetW_BB8C(u16 idx)
{
    register u32 i __asm__("r1") = idx;
    u32 *base;
    if (i > 248)
        return 0;
    base = rom0822BB8C;
    return base[i];
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080246c4")))
u32 TblGetW_BF74(u16 idx)
{
    register u32 i __asm__("r1") = idx;
    u32 *base;
    if (i > 248)
        return 0;
    base = rom0822BF74;
    return base[i];
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080246e0")))
u32 TblGetW_C35C(u16 idx)
{
    register u32 i __asm__("r1") = idx;
    u32 *base;
    if (i > 248)
        return 0;
    base = rom0822C35C;
    return base[i];
}


extern struct Rom0822740C rom0822740C[];

extern struct Ew02007090 ew02007090;
extern u32 rom0822BB8C[];
extern u32 rom0822BF74[];
extern u32 rom0822C35C[];
__attribute__((section(".text.w8s_080247a8")))
u8 EwGet8_A8(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    u8 *ew = (u8 *)&ew02007090;
    if (i > 248)
        return 0;
    return *(u8 *)(*(u32 *)(ew + 4) + i);
}

__attribute__((section(".text.w8s_0802637c")))
u32 Cmp8(u16 *a, u16 *b)
{
    if (a[0] != b[0]) return 1;
    if (a[1] != b[1]) return 1;
    if (a[2] != b[2]) return 1;
    if (a[3] != b[3]) return 1;
    return 0;
}

__attribute__((section(".text.w8s_0803fa1c")))
u32 CheckId_FA1C(u16 x)
{
    register int sx __asm__("r0") = (u16)x;
    register int sx2 __asm__("r1") = sx;
    u32 r = 0;
    if (sx == 64)
        goto L1;
    if (sx > 64)
        goto L2;
    if (sx == 17)
        goto L1;
    goto Lend;
L2:
    if (sx2 == (130 << 5))
        goto L1;
    if (sx2 != (157 << 5))
        goto Lend;
L1:
    r = 1;
Lend:
    return r;
}

struct Ew0200BD20 { u8 _00[128]; u16 f128; };
extern struct Ew0200BD20 gEwram_0200BD20;
extern u8 gEwram_02002EE0[];
__attribute__((section(".text.w8s_0804a3c4")))
s32 EwCopy_4A3C4(void)
{
    register u8 *bd __asm__("r2") = (u8 *)&gEwram_0200BD20;
    register u8 *flg __asm__("r1") = gEwram_02002EE0;
    register u8 *p __asm__("r0");
    s32 r;
    if ((*flg & 48) != 48)
        goto Lneg;
    {
        u8 v = flg[4];
        p = bd;
        p += 130;
        *p = v;
    }
    r = 0;
    goto Lend;
Lneg:
    r = -1;
Lend:
    return r;
}
__attribute__((section(".text.w8s_0804a3c4")))
static const u16 pad_0804a3c4 = 0;



extern struct Ew0200BD20 gEwram_0200BD20;
extern u8 gEwram_02002EE0[];
__attribute__((section(".text.w8s_0804ad4c")))
s32 CtrTick_4AD4C(void)
{
    u8 *bd = (u8 *)&gEwram_0200BD20;
    u8 *flg = gEwram_02002EE0;
    s32 *ctr = (s32 *)(bd + 120);
    if ((*flg & 48) == 48)
        goto L1;
    *ctr = *ctr + 1;
    if (*ctr <= 59)
        goto Lret0;
    return -1;
L1:
    *ctr = 0;
Lret0:
    return 0;
}

__asm__(
    ".set rom08106D7C,0x08106D7C\n\t"
    ".set rom08106DD0,0x08106DD0\n\t"
    ".set rom0822BB8C,0x0822BB8C\n\t"
    ".set rom0822BF74,0x0822BF74\n\t"
    ".set rom0822C35C,0x0822C35C\n\t"
    ".set gEwram_02002EE0,0x02002EE0\n\t"
);
