/* Wave 8 batch R: re-derived Wave-7-G1 claims. Evidence: docs/match_notes_wave8_R.md */
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef short s16;


__attribute__((section(".text.w8r_08026f98")))
void FlagSet_08026F98(u8 x) {
    u16 *p = (u16 *)0x020031E0;
    u16 v;

    v = *p;
    v |= 144 << 5;
    *p = v;
    {
        register u8 *b __asm__("r2") = (u8 *)0x02003670;
        s32 t;

        __asm__ volatile("" : "+r"(b));
        t = (x | -x) >> 31;
        t &= 32;
        b += 0x11AC;
        *b = (u8)t;
    }
}


__attribute__((section(".text.w8r_0802c7b4")))
u8 SubClamp_0802C7B4(int a, u16 *p) {
    int a16 = a << 16;
    int t = *p;
    u8 borrow = 0;
    u16 ua = (u16)((unsigned)a16 >> 16);
    int d = t - (a16 >> 16);

    *p = (u16)d;
    if ((s16)d <= 0) {
        *p = 0;
        borrow = (u8)(ua - t);
    }
    return borrow;
}

__attribute__((section(".text.w8r_0802c7b4")))
static const u16 pad_0802c7b4 = 0;


__attribute__((section(".text.w8r_08010454")))
int Test_08010454(u8 x) {
    u8 *p = (u8 *)0x02005168;

    if (x == 1)
        p += 20;
    if ((p[16] & 2) == 0)
        return 0;
    return 1;
}


typedef struct {
    u8 *p;
    u16 a;
    u16 b;
} Buf_0802520C;

__attribute__((section(".text.w8r_0802520c")))
void Fill_0802520C(Buf_0802520C *s, u8 *ptr, u16 n) {
    s->p = ptr;
    s->a = n;
    s->b = 0;
    while (n != 0) {
        *ptr++ = 0xFF;
        n--;
    }
}


typedef struct {
    u8 *p;
    u16 a;
    u16 b;
} Buf_0802526C;

__attribute__((section(".text.w8r_0802526c")))
int Append_0802526C(Buf_0802526C *s, u8 v) {
    if (s->b >= s->a)
        return 1;
    s->p[s->b] = v;
    s->b++;
    return 0;
}


__attribute__((section(".text.w8r_08004e24")))
void Set_08004E24(u8 x) {
    u8 *p = (u8 *)0x02004F80;
    u8 v;

    p[0] = (x << 7) | 64;
    v = 2;
    if (x == 0)
        v = 1;
    p[2] = v;
}


__attribute__((section(".text.w8r_08004e0c")))
int Cmp_08004E0C(u8 x) {
    u8 *p = (u8 *)0x02004F80;

    if (p[1] == x)
        return 1;
    else
        return 0;
}


__attribute__((section(".text.w8r_08010478")))
int Clr_08010478(u8 x) {
    u8 *p = (u8 *)0x02005168;
    int m2 = 2;

    if (x == 1)
        p += 20;
    p[16] &= -m2;
    return 1;
}


__attribute__((section(".text.w8r_0801052c")))
void Zero_0801052C(void) {
    u8 *p = (u8 *)0x02004CA0;

    if (p[28] != 0)
        p[28] = 0;
    p += 32;
    if (p[28] != 0)
        p[28] = 0;
}
