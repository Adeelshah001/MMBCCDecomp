/* Wave 15 worker B: bulk leaves-up rows 0-90 (main agbcc, 17 functions)
 * Coordinator-landed after independent clean-room re-verification (0 diffs).
 * Evidence: docs/match_notes_wave15_B.md, docs/wave15_B_results.tsv.
 */
extern void F_08002F40(void);
typedef unsigned short u16;
typedef unsigned char u8;
struct Ew02007090 { u8 _00[18]; u16 f18; u8 *f20; };
extern struct Ew02007090 ew02007090;
extern u16 F_0802663C(const void *p, u16 idx);
extern u8 GetBoundedByte_18(void *s, u16 idx);
extern void SetByte432(u8 *s, u8 v);
extern unsigned int Gt199(u8 v);
extern void SetDiffSum(short a, short b, unsigned int *out);
extern u8 GetMaskedByte(u8 *p, u8 idx);
typedef short s16;
extern u16 TblGet_f00(u8 idx);
extern void FilterCopy(u8 *p, u8 a, u8 b);
extern void F_25490(u8 *p, u8 a, u8 b);
extern u16 Scramble_400A8(void);
extern void SyncObjFlagBits_BEE0(unsigned int a, unsigned int b);
extern int TblValidate_300C(u16 x);
extern u8 GetBoundedByte_6(void *s, u16 idx);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void Ewram5160_Init_10508(u8 v);
extern unsigned int Sram_VerifySlot(unsigned int a0, unsigned int key);

__attribute__((section(".text.w15b_08000624")))
void F_08000624(void)
{
    F_08002F40();
}

__attribute__((section(".text.w15b_08025070")))
u8 F_08025070(u16 idx)
{
    const u8 *p = (const u8 *)&ew02007090;
    return (u8)F_0802663C(p + 24, idx);
}

__attribute__((section(".text.w15b_0802478c")))
u8 F_0802478C(u16 idx)
{
    return GetBoundedByte_18((void *)0x02007090, idx);
}

__attribute__((section(".text.w15b_080248ac")))
void F_080248AC(u8 v)
{
    SetByte432(ew02007090.f20, v);
}

__attribute__((section(".text.w15b_08024648")))
u16 F_08024648(u8 x)
{
    return Gt199(x);
}

__attribute__((section(".text.w15b_0801e87c")))
void F_0801E87C(short a, short b, unsigned int *out)
{
    SetDiffSum(a, b, out);
}

__attribute__((section(".text.w15b_080247c4")))
u8 F_080247C4(u8 idx)
{
    u8 v = idx;
    u8 **pp = (u8 **)0x02007090;
    __asm__ volatile("" : "+r" (pp));
    if (v > 248)
        return 0;
    return GetMaskedByte(*pp, v);
}

__attribute__((section(".text.w15b_0802d5a8")))
void F_0802D5A8(s16 delta, u16 *p, u8 idx)
{
    u16 lim;
    int d = delta;
    s16 cur;
    u16 pv = *p;
    __asm__("add %0, %1, %0" : "+r" (d) : "r" (pv));
    *p = (u16)d;
    lim = TblGet_f00(idx);
    cur = *(s16 *)p;
    if (cur > lim)
        *p = lim;
}

__attribute__((section(".text.w15b_0802476c")))
void F_0802476C(u8 a, u8 b)
{
    FilterCopy((u8 *)0x02007090, a, b);
}

__attribute__((section(".text.w15b_08024918")))
u8 F_08024918(u8 *p, u8 b, u8 c)
{
    u16 lim = *(u16 *)(p + 18);
    if (b >= lim)
        return 1;
    if (c >= lim)
        return 1;
    F_25490(p, b, c);
    return 0;
}

__attribute__((section(".text.w15b_08040078")))
void F_08040078(u16 x)
{
    u16 v = x;
    u16 w = v;
    u8 *p = (u8 *)0x020070F0;
    if (v == 0xAE84)
        w = 0x259E;
    *(u16 *)(p + 8) = w;
    Scramble_400A8();
    Scramble_400A8();
    Scramble_400A8();
}

__attribute__((section(".text.w15b_080104cc")))
u8 F_080104CC(u8 x)
{
    if (*(u8 *)0x02005160 != 0)
        return 0;
    SyncObjFlagBits_BEE0(x, 0);
    return 1;
}

__attribute__((section(".text.w15b_0804a340")))
s16 F_0804A340(void)
{
    u16 *p = (u16 *)0x0200BD10;
    if (p[1] == 0)
        return -1;
    if (TblValidate_300C(p[0]) == 0)
        return -1;
    return (s16)p[0];
}

__attribute__((section(".text.w15b_0802660c")))
u16 F_0802660C(u8 *p, u16 idx)
{
    u16 i = idx;
    if (i == 0)
        return 0x1000;
    if (i >= *(u16 *)(p + 22))
        return 0;
    {
        u8 v = GetBoundedByte_6(p + 16, i);
        return v | 0x2000;
    }
}

__attribute__((section(".text.w15b_08016e4c")))
void F_08016E4C(u8 *p, u16 v)
{
    u8 *q = p + 124;
    *q = (u8)v;
    if ((u8)v > 38) {
        q[2] = (u8)(v - 39);
        *q = 39;
    } else {
        q[2] = 0;
    }
    q[4] = 1;
    SetBytes_08011F68(p, 2);
}

__attribute__((section(".text.w15b_0801039c")))
u8 F_0801039C(u8 *p, u8 b)
{
    u8 bb;
    u8 *q;
    bb = b;
    q = (u8 *)0x02005160;
    __asm__ volatile("" : "+r" (q));
    if (*q != 0)
        return 0;
    Ewram5160_Init_10508(6);
    *(u8 **)(q + 48) = p;
    *(q + 66) = bb;
    return 1;
}

__attribute__((section(".text.w15b_08026a48")))
void F_08026A48(u8 *p)
{
    u8 *k;
    unsigned int z = 0;
    p[10] = (u8)z;
    k = (u8 *)0x00001734;
    if (Sram_VerifySlot(z, (unsigned int)k) != 0) {
        u8 v1 = 1;
        p[10] = v1 | p[10];
    }
    if (Sram_VerifySlot(1, (unsigned int)k) != 0) {
        u8 v2 = 2;
        p[10] = v2 | p[10];
    }
}

/* Absolute callee aliases (not defined in the build; must FOLLOW code per GAS .set ordering rule). */
__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl F_08002F40\n"
    ".set F_08002F40, 0x08002f40\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl F_0802663C\n"
    ".set F_0802663C, 0x0802663c\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl GetBoundedByte_18\n"
    ".set GetBoundedByte_18, 0x08025478\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte432\n"
    ".set SetByte432, 0x08026108\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl Gt199\n"
    ".set Gt199, 0x08026700\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetDiffSum\n"
    ".set SetDiffSum, 0x080110c8\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl GetMaskedByte\n"
    ".set GetMaskedByte, 0x08025324\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl TblValidate_300C\n"
    ".set TblValidate_300C, 0x0800300c\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl GetBoundedByte_6\n"
    ".set GetBoundedByte_6, 0x080252d0\n"
);
