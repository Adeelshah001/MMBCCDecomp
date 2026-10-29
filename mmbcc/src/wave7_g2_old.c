/* Wave 7 batch G2 (66 matched, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave7_g2.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;



/* 0x08000e64: SetTaskField0_030023C8 (28B, coordinator-verified). */
extern unsigned char g_030023c8[];
__attribute__((section(".text.w7g2_08000e64")))
void SetTaskField0_030023C8(unsigned int idx)
{
    unsigned char *p = g_030023c8 + idx * 24;
    if (p[0] != 1)
        p[0] = 1;
}

/* 0x08002a04: Clear16_02003090 (24B, coordinator-verified). */
extern unsigned char g_02003090[];
__attribute__((section(".text.w7g2_08002a04")))
void Clear16_02003090(void)
{
    int p = (int)g_02003090;
    int z = 0;
    int q = p + 15;
    do {
        *(unsigned char *)q = z;
        q--;
    } while (q >= p);
}

/* 0x08002e50: CopyBlendRegs_04000052 (32B, coordinator-verified). */
extern unsigned short g_04000052[];
extern unsigned short g_02003220[];
__attribute__((section(".text.w7g2_08002e50")))
void CopyBlendRegs_04000052(void)
{
    register unsigned short *dst __asm__("r2") = g_04000052;
    register unsigned short *src __asm__("r1") = g_02003220;
    dst[0] = src[1];
    dst += 1;
    dst[0] = src[2];
    dst -= 2;
    dst[0] = src[0];
}

/* 0x08004188: SwapPtr (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08004188")))
void SwapPtr_08004188(unsigned int *p, unsigned int *q, short x, short y)
{
    int off = (y << 2) + (x << 7);
    unsigned int *r = (unsigned int *)((unsigned char *)p + off);
    unsigned int tmp = *r;
    *q = tmp;
    *r = (unsigned int)q;
}

/* 0x08004244: Init_08004244 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08004244")))
void Init_08004244(void *s, void **pp)
{
    *(void **)s = pp;
    ((unsigned char *)s)[4] = 0;
    ((unsigned char *)s)[5] = 0;
    ((unsigned char *)s)[6] = (*(unsigned char **)pp)[1] + 1;
    ((unsigned char *)s)[7] = 0;
}

/* 0x08007cdc: SetBit2 (24B, coordinator-verified). */
extern unsigned char g_02004e18[];
__attribute__((section(".text.w7g2_08007cdc")))
void SetBit2_08007CDC(unsigned short v)
{
    unsigned char *p = g_02004e18 + v * 8;
    p[7] |= 4;
}

/* 0x08008610: GetPtr_08008610 (24B, coordinator-verified). */
extern unsigned int g_02003674;
__attribute__((section(".text.w7g2_08008610")))
unsigned int GetPtr_08008610(unsigned char *s)
{
    if (s[11] != 0)
        return 0x02004aa0;
    return g_02003674;
}

/* 0x08008bb8: SetIfXZero (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08008bb8")))
void SetIfXZero(unsigned short *s, unsigned short v, unsigned char x)
{
    if ((x << 24) == 0)
        *s = v;
}
static const unsigned short pad_08008bb8 __attribute__((section(".text.w7g2_08008bb8"))) = 0;

/* 0x08009640: SetByte620_FF (20B, coordinator-verified). */
extern unsigned char g_02004830[];
__attribute__((section(".text.w7g2_08009640")))
void SetByte620_FF(void)
{
    g_02004830[620] = 0xff;
}

/* 0x0800b29c: OrBit (24B, coordinator-verified). */
extern unsigned short g_02004e40[];
__attribute__((section(".text.w7g2_0800b29c")))
void OrBit_0800B29C(unsigned short v)
{
    if (g_02004e40[7] != 0)
        g_02004e40[7] = v | g_02004e40[7];
}

/* 0x0800dcf8: GetPtr_0800DCF8 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_0800dcf8")))
unsigned char *GetPtr_0800dcf8(unsigned char *s, unsigned char b)
{
    unsigned char *t = s;
    unsigned int u = (unsigned int)b << 24;
    s += 12;
    s += *(unsigned int *)(t + 12);
    u >>= 19;
    s += u;
    return s;
}

/* 0x0800edfc: SetHalfs_0800EDFC (24B, coordinator-verified). */
extern unsigned short g_02005130[];
extern unsigned short g_02005168[];
__attribute__((section(".text.w7g2_0800edfc")))
void SetHalfs_0800EDFC(unsigned short v)
{
    g_02005130[6] = v;
    g_02005168[0] = v;
}

/* 0x0800ee14: SetHalfs_0800EE14 (24B, coordinator-verified). */
extern unsigned short g_02005130[];
extern unsigned short g_0200517c[];
__attribute__((section(".text.w7g2_0800ee14")))
void SetHalfs_0800EE14(unsigned short v)
{
    g_02005130[7] = v;
    g_0200517c[0] = v;
}

/* 0x08010088: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char g_02005160[];
__attribute__((section(".text.w7g2_08010088")))
unsigned int IsZero_02005160_08010088(void)
{
    unsigned int v = g_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x08010124: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char g_02005160[];
__attribute__((section(".text.w7g2_08010124")))
unsigned int IsZero_02005160_08010124(void)
{
    unsigned int v = g_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x08010248: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char g_02005160[];
__attribute__((section(".text.w7g2_08010248")))
unsigned int IsZero_02005160_08010248(void)
{
    unsigned int v = g_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x080102f4: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char g_02005160[];
__attribute__((section(".text.w7g2_080102f4")))
unsigned int IsZero_02005160_080102f4(void)
{
    unsigned int v = g_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x080103cc: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char g_02005160[];
__attribute__((section(".text.w7g2_080103cc")))
unsigned int IsZero_02005160_080103cc(void)
{
    unsigned int v = g_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x080104f4: IsZero_02005160 (20B, coordinator-verified). */
extern unsigned char g_02005160[];
__attribute__((section(".text.w7g2_080104f4")))
unsigned int IsZero_02005160_080104f4(void)
{
    unsigned int v = g_02005160[0];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x0801109c: IsOne_020051B0_4 (20B, coordinator-verified). */
extern unsigned char g_020051b0[];
__attribute__((section(".text.w7g2_0801109c")))
unsigned int IsOne_020051B0_4(void)
{
    unsigned int v = g_020051b0[4];
    if (v == 1)
        goto L1;
    __asm__ volatile("movs %0, #0" : "=r"(v));
    goto L2;
L1:
    __asm__ volatile("movs %0, #1" : "=r"(v));
L2:
    return v;
}

/* 0x080110c8: SetDiffSum (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_080110c8")))
void SetDiffSum_080110C8(short a, short b, unsigned int *out)
{
    int bb = b;
    int aa = a;
    out[0] = (aa - bb) << 12;
    out[1] = (bb + aa) << 11;
}
static const unsigned short pad_080110c8 __attribute__((section(".text.w7g2_080110c8"))) = 0;

/* 0x080112bc: Inc4_Clear5_7 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080112bc")))
void Inc4_Clear5_7(unsigned char *s)
{
    unsigned int v = s[4] + 1;
    unsigned int z = 0;
    s[4] = v;
    s[5] = z;
    s[6] = z;
    s[7] = z;
}

/* 0x08011cac: GetTableEntry_08173FAC (24B, coordinator-verified). */
extern unsigned int g_08173fac[];
__attribute__((section(".text.w7g2_08011cac")))
unsigned int *GetTableEntry_08173FAC(unsigned short idx)
{
    if (idx == 0)
        return 0;
    return &g_08173fac[idx];
}

/* 0x08011f50: Check119_Minus3_Le1 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_08011f50")))
unsigned int Check119_Minus3_Le1(unsigned char *s)
{
    unsigned int v = (unsigned char)(s[119] - 3);
    if (v <= 1)
        return 1;
    return 0;
}
static const unsigned short pad_08011f50 __attribute__((section(".text.w7g2_08011f50"))) = 0;

/* 0x08011f68: SetBytes_08011F68 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08011f68")))
void SetBytes_08011F68(unsigned char *s, unsigned char v)
{
    unsigned char *p = s + 124;
    unsigned int z;
    __asm__ volatile("movs %0, #0" : "=r"(z));
    s[13] = v;
    s[14] = z;
    s[15] = z;
    p[5] = v;
}

/* 0x08016f88: Byte128_IsZero (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08016f88")))
unsigned int Byte128_IsZero(unsigned char *s)
{
    unsigned int v;
    s += 124;
    v = s[4];
    if (v == 0)
        goto L1;
    v = 0;
    goto L2;
L1:
    v = 1;
L2:
    return v;
}

/* 0x08016f98: GetRomTableEntry_082240B8 (20B, coordinator-verified). */
extern unsigned char g_082240b8[];
__attribute__((section(".text.w7g2_08016f98")))
unsigned short GetRomTableEntry_082240B8(unsigned char idx)
{
    unsigned char *base = g_082240b8;
    unsigned int off = idx * 8;
    base += 4;
    return *(unsigned short *)(base + off);
}

/* 0x080170c4: Byte12_Gt1 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080170c4")))
unsigned int Byte12_Gt1_080170c4(unsigned char *s)
{
    unsigned int r = 0;
    if (s[12] > 1)
        r = 1;
    return r;
}
static const unsigned short pad_080170c4 __attribute__((section(".text.w7g2_080170c4"))) = 0;

/* 0x08017464: DecIfNonZero_18 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08017464")))
void DecIfNonZero_18(unsigned char *s)
{
    if (s[18] != 0)
        s[18]--;
}
static const unsigned short pad_08017464 __attribute__((section(".text.w7g2_08017464"))) = 0;

/* 0x08017478: MaxAssign_17 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08017478")))
void MaxAssign_17(unsigned char *s, unsigned char v)
{
    if (s[17] < v)
        s[17] = v;
}
static const unsigned short pad_08017478 __attribute__((section(".text.w7g2_08017478"))) = 0;

/* 0x08017494: TestBit16 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08017494")))
unsigned char TestBit16(unsigned char *s, unsigned char bit)
{
    return (1 << bit) & s[16];
}

/* 0x080174a4: SetBit16 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080174a4")))
void SetBit16(unsigned char *s, unsigned char bit)
{
    s[16] |= (1 << bit);
}

/* 0x0801cdd8: Byte12_Gt1 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_0801cdd8")))
unsigned int Byte12_Gt1_0801cdd8(unsigned char *s)
{
    unsigned int r = 0;
    if (s[12] > 1)
        r = 1;
    return r;
}
static const unsigned short pad_0801cdd8 __attribute__((section(".text.w7g2_0801cdd8"))) = 0;

/* 0x0801d34c: Byte12_Gt1 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_0801d34c")))
unsigned int Byte12_Gt1_0801d34c(unsigned char *s)
{
    unsigned int r = 0;
    if (s[12] > 1)
        r = 1;
    return r;
}
static const unsigned short pad_0801d34c __attribute__((section(".text.w7g2_0801d34c"))) = 0;

/* 0x0801f1d8: Byte12_Gt1 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_0801f1d8")))
unsigned int Byte12_Gt1_0801f1d8(unsigned char *s)
{
    unsigned int r = 0;
    if (s[12] > 1)
        r = 1;
    return r;
}
static const unsigned short pad_0801f1d8 __attribute__((section(".text.w7g2_0801f1d8"))) = 0;

/* 0x08021d84: Byte19_Bits3F_Set (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08021d84")))
unsigned int Byte19_Bits3F_Set(unsigned char *s)
{
    unsigned int r = 0;
    unsigned int mask = 0x3f;
    mask &= s[19];
    if (mask == 0x3f)
        r = 1;
    return r;
}
static const unsigned short pad_08021d84 __attribute__((section(".text.w7g2_08021d84"))) = 0;

/* 0x08022634: Byte12_Gt1 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08022634")))
unsigned int Byte12_Gt1_08022634(unsigned char *s)
{
    unsigned int r = 0;
    if (s[12] > 1)
        r = 1;
    return r;
}
static const unsigned short pad_08022634 __attribute__((section(".text.w7g2_08022634"))) = 0;

/* 0x0802365c: GetPtr_0802365C (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_0802365c")))
unsigned char *GetPtr_0802365c(unsigned char *s, unsigned char b)
{
    unsigned char *t = s;
    unsigned int u = (unsigned int)b << 24;
    s += 12;
    s += *(unsigned int *)(t + 12);
    u >>= 19;
    s += u;
    return s;
}

/* 0x08024500: ClampAdd200 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08024500")))
unsigned char ClampAdd200(unsigned short v)
{
    if (v > 48)
        return 200;
    return (unsigned char)(v + 200);
}

/* 0x08024514: Sub200 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08024514")))
unsigned short Sub200_08024514(unsigned char v)
{
    if (v <= 199)
        return 0;
    return (unsigned short)(v - 200);
}

/* 0x08024528: Clamp48 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08024528")))
unsigned char Clamp48_08024528(unsigned short v)
{
    if (v > 48)
        return 0;
    return (unsigned char)v;
}
static const unsigned short pad_08024528 __attribute__((section(".text.w7g2_08024528"))) = 0;

/* 0x0802453c: GetClampedTable (24B, coordinator-verified). */
extern unsigned int g_08229828[];
__attribute__((section(".text.w7g2_0802453c")))
unsigned int GetClampedTable_08229828(unsigned short v)
{
    if (v > 48)
        v = 48;
    return g_08229828[v];
}

/* 0x080252d0: GetBoundedByte_6 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_080252d0")))
unsigned char GetBoundedByte_080252D0(void *s, unsigned short idx)
{
    unsigned short lim = *(unsigned short *)((unsigned char *)s + 6);
    if (idx >= lim)
        return 0xff;
    return *(*(unsigned char **)s + idx);
}
static const unsigned short pad_080252d0 __attribute__((section(".text.w7g2_080252d0"))) = 0;

/* 0x080252e8: IncMod128 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080252e8")))
void IncMod128_080252E8(unsigned char *s)
{
    unsigned int v = 0x7f;
    unsigned int w;
    v &= s[0];
    v++;
    w = 0x80;
    v |= w;
    s[0] = v;
}

/* 0x080252f8: GetBit80 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_080252f8")))
unsigned char GetBit80(unsigned char *s)
{
    return s[0] & 0x80;
}
static const unsigned short pad_080252f8 __attribute__((section(".text.w7g2_080252f8"))) = 0;

/* 0x08025324: GetMaskedByte (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_08025324")))
unsigned char GetMaskedByte_08025324(unsigned char *p, unsigned char idx)
{
    if (idx > 248)
        return 0;
    return p[idx] & 0x7f;
}

/* 0x08025478: GetBoundedByte_18 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_08025478")))
unsigned char GetBoundedByte_08025478(void *s, unsigned short idx)
{
    unsigned short lim = *(unsigned short *)((unsigned char *)s + 18);
    if (idx >= lim)
        return 0;
    return *(*(unsigned char **)((unsigned char *)s + 8) + idx);
}
static const unsigned short pad_08025478 __attribute__((section(".text.w7g2_08025478"))) = 0;

/* 0x0802571c: SetIfGt199 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_0802571c")))
void SetIfGt199(unsigned char *s, unsigned char a, unsigned char b)
{
    if (a > 199) {
        s[1] = a;
        s[0] = b;
    }
}
static const unsigned short pad_0802571c __attribute__((section(".text.w7g2_0802571c"))) = 0;

/* 0x080258c0: GetStride4Byte20 (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_080258c0")))
unsigned char GetStride4Byte20_080258C0(unsigned char *s, unsigned short idx)
{
    if (idx > 29)
        return 0;
    return *(s + idx * 4 + 20);
}
static const unsigned short pad_080258c0 __attribute__((section(".text.w7g2_080258c0"))) = 0;

/* 0x08025994: Clear20_Set21_FF (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08025994")))
void Clear20_Set21_FF(unsigned char *s, unsigned short idx)
{
    unsigned int off = idx * 4;
    register unsigned char *p __asm__("r1") = (unsigned char *)off;
    p = (unsigned char *)((unsigned int)p + (unsigned int)s);
    p[20] = 0;
    p[21] = 0xff;
}

/* 0x08026108: SetByte432 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08026108")))
void SetByte432_08026108(unsigned char *s, unsigned char v)
{
    if (v > 2)
        v = 2;
    s[432] = v;
}

/* 0x08026700: Gt199 (16B, coordinator-verified). */
__attribute__((section(".text.w7g2_08026700")))
unsigned int Gt199_08026700(unsigned char v)
{
    if (v > 199)
        return 1;
    return 0;
}

/* 0x08027e44: FlagCheck_0200B7E0_3 (24B, coordinator-verified). */
extern unsigned char g_0200b7e0[];
__attribute__((section(".text.w7g2_08027e44")))
unsigned int FlagCheck_0200B7E0_3(void)
{
    unsigned char *p = g_0200b7e0;
    unsigned int v;
    __asm__("movs %0, #1" : "=r"(v));
    v &= p[3];
    if (v == 0)
        return 0;
    return 1;
}

/* 0x080363d4: FlagCheck_0200BCE8_4 (24B, coordinator-verified). */
extern unsigned char g_0200bce8[];
__attribute__((section(".text.w7g2_080363d4")))
unsigned int FlagCheck_0200BCE8_4(void)
{
    unsigned char *p = g_0200bce8;
    unsigned int v;
    __asm__("movs %0, #1" : "=r"(v));
    v &= p[4];
    if (v == 0)
        return 0;
    return 1;
}

/* 0x0803fcc4: InRange3B0_3B1 (28B, coordinator-verified). */
__attribute__((section(".text.w7g2_0803fcc4")))
unsigned int InRange3B0_3B1(unsigned short v)
{
    unsigned int r = 0;
    int lim = 0x3b1;
    int w = v;
    if (w > lim)
        goto L0;
    if (w < lim - 1)
        goto L0;
    r = 1;
L0:
    return r;
}

/* 0x0803fe1c: Is208or217 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_0803fe1c")))
unsigned int Is208or217(unsigned short v)
{
    unsigned int r = 0;
    if (v == 208 || v == 217)
        r = 1;
    return r;
}

/* 0x0803fe30: InRange224_230 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_0803fe30")))
unsigned int InRange224_230(unsigned short v)
{
    unsigned int r = 0;
    int w = v;
    int lo = 224;
    if (w > 230)
        goto L0;
    if (w < lo)
        goto L0;
    r = 1;
L0:
    return r;
}

/* 0x0803fef8: Eq2260000 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_0803fef8")))
unsigned int Eq2260000(unsigned short v)
{
    unsigned int x = (unsigned int)v << 16;
    unsigned int r = 0;
    if (x == 0x02260000)
        r = 1;
    return r;
}

/* 0x08040060: TryConsume (24B, coordinator-verified). */
__attribute__((section(".text.w7g2_08040060")))
unsigned int TryConsume_08040060(unsigned char *s, unsigned short n)
{
    unsigned int *p = (unsigned int *)(s + 32);
    if (*p >= n) {
        *p -= n;
        return 0;
    } else {
        return 1;
    }
}

/* 0x08046de4: CmpH6 (20B, coordinator-verified). */
__attribute__((section(".text.w7g2_08046de4")))
unsigned int CmpH6_08046DE4(void *s, unsigned short b)
{
    unsigned int r = 0;
    if (*(unsigned short *)((unsigned char *)s + 6) == b)
        r = 1;
    return r;
}
static const unsigned short pad_08046de4 __attribute__((section(".text.w7g2_08046de4"))) = 0;

/* 0x080496e8: AddTableEntry_082344CC (28B, coordinator-verified). */
extern unsigned char g_082344cc[];
__attribute__((section(".text.w7g2_080496e8")))
unsigned char AddTableEntry_082344CC(unsigned char a, unsigned char b)
{
    return g_082344cc[a] + b;
}

/* 0x0804a494: Clear126_127_Set131 (28B, coordinator-verified). */
extern unsigned char g_0200bd20[];
__attribute__((section(".text.w7g2_0804a494")))
void Clear126_127_Set131_0200BD20(unsigned char v)
{
    unsigned char *p = g_0200bd20;
    p[127] = 0;
    p[126] = 0;
    p[131] = v;
}

/* 0x0804aa78: Clear126_127_Set156 (28B, coordinator-verified). */
extern unsigned char g_0200bd20[];
__attribute__((section(".text.w7g2_0804aa78")))
void Clear126_127_Set156_0200BD20(unsigned int *src)
{
    unsigned char *p = g_0200bd20;
    unsigned char *q = p + 127;
    *q = 0;
    q--;
    *q = 0;
    *(unsigned int *)(p + 156) = *src;
}

/* 0x0804ac48: Clear126_127_160_Set161 (28B, coordinator-verified). */
extern unsigned char g_0200bd20[];
__attribute__((section(".text.w7g2_0804ac48")))
void Clear126_127_160_Set161_0200BD20(unsigned char v)
{
    unsigned char *p = g_0200bd20;
    p[127] = 0;
    p[126] = 0;
    p[160] = 0;
    p[161] = v;
}

/* 0x0804ad24: Clear126_127_160 (24B, coordinator-verified). */
extern unsigned char g_0200bd20[];
__attribute__((section(".text.w7g2_0804ad24")))
void Clear126_127_160_0200BD20(void)
{
    unsigned char *p = g_0200bd20;
    p[127] = 0;
    p[126] = 0;
    p[160] = 0;
}

/* 0x0804c5f4: ClearSignBit (28B, coordinator-verified). */
__attribute__((section(".text.w7g2_0804c5f4")))
void ClearSignBit_0804C5F4(void *s)
{
    register unsigned int v __asm__("r3") = *(unsigned int *)((unsigned char *)s + 52);
    if (v == 0x68736d53)
        *(unsigned int *)((unsigned char *)s + 4) &= 0x7fffffff;
}

__asm__(
    ".thumb_func\n"
    ".set g_02002ed4, 0x02002ed4\n"
    ".thumb_func\n"
    ".set g_02002f80, 0x02002f80\n"
    ".thumb_func\n"
    ".set g_02003090, 0x02003090\n"
    ".thumb_func\n"
    ".set g_02003220, 0x02003220\n"
    ".thumb_func\n"
    ".set g_02003230, 0x02003230\n"
    ".thumb_func\n"
    ".set g_02003240, 0x02003240\n"
    ".thumb_func\n"
    ".set g_02003674, 0x02003674\n"
    ".thumb_func\n"
    ".set g_02004830, 0x02004830\n"
    ".thumb_func\n"
    ".set g_02004e18, 0x02004e18\n"
    ".thumb_func\n"
    ".set g_02004e40, 0x02004e40\n"
    ".thumb_func\n"
    ".set g_02005160, 0x02005160\n"
    ".thumb_func\n"
    ".set g_02005168, 0x02005168\n"
    ".thumb_func\n"
    ".set g_0200517c, 0x0200517c\n"
    ".thumb_func\n"
    ".set g_020051b0, 0x020051b0\n"
    ".thumb_func\n"
    ".set g_0200b7e0, 0x0200b7e0\n"
    ".thumb_func\n"
    ".set g_0200bce8, 0x0200bce8\n"
    ".thumb_func\n"
    ".set g_0200bd20, 0x0200bd20\n"
    ".thumb_func\n"
    ".set g_030023c8, 0x030023c8\n"
    ".thumb_func\n"
    ".set g_04000052, 0x04000052\n"
    ".thumb_func\n"
    ".set g_08173fac, 0x08173fac\n"
    ".thumb_func\n"
    ".set g_082240b8, 0x082240b8\n"
    ".thumb_func\n"
    ".set g_08229828, 0x08229828\n"
    ".thumb_func\n"
    ".set g_082344cc, 0x082344cc\n"
);
