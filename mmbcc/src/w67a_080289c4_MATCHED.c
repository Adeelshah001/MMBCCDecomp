/* Wave 66-A v1: 0x080289C4 (328 B true extent: 320 code + 8 pool @0x28B04=0x00000189, @0x28B08=0x02005168).
 * Struct init: head stores, 29504 call, 7-iteration zero loop over u32 arrays at s+336/s+364
 * and byte arrays at s+320/s+328, flag-gated init blocks, table lookups, tail zero stores.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void sub_08029504(u8 *s);
void sub_0800E994(void);
void sub_0800EA14(u8 v);
void sub_0800EA30(u8 v);
void BitCtl_0800520C(void);
void EwSet8_0800EE44(u8 v);
u8 TblGetByte_08024384(u16 v);
void EwramSet2_0800EA08(u8 a, u8 b);
void Sub_0802E9F8(u16 a, u8 *p);
u8 TblGet_08024618(u8 v);
extern u8 gEwram_02005168[];

__attribute__((section(".text.w67a_080289c4")))
u8 sub_080289C4(u8 *s)
{
    u8 i;
    u8 t;
    u8 v1, v2;
    u16 z = 0;

    s[4] = z;
    s[28] = z;
    s[6] &= 0xF8;
    s[2] = z;
    s[3] = z;
    { register u8 w __asm__("r0") = 0; s[24] = w; }
    s[5] = 50;
    sub_08029504(s);
    *(u16 *)(s + 18) = z;
    s[392] = 2;
    s[393] = 2;
    i = 0;
    {
        u32 *a = (u32 *)(s + 336);
        u32 zero = 0;
        u32 *b = (u32 *)(s + 364);
        u8 *c = s + 320;
        u8 *d = s + 328;
        for (; i <= 6; i++) {
            u32 *ap = a + i; *ap = zero;
            b[i] = zero;
            c[i] = zero;
            d[i] = zero;
        }
    }
    t = s[6] & 8;
    if (t == 0) {
        sub_0800E994();
        sub_0800EA14(s[29]);
        sub_0800EA30(s[10]);
        s[2] = 1;
        s[3] = t;
        BitCtl_0800520C();
    }
    if ((s[6] & 16) != 0)
        EwSet8_0800EE44(1);
    v1 = TblGetByte_08024384(*(u16 *)(s + 20));
    v2 = TblGetByte_08024384(*(u16 *)(s + 22));
    EwramSet2_0800EA08(v1, v2);
    Sub_0802E9F8(*(u16 *)(s + 20), s + 32);
    Sub_0802E9F8(*(u16 *)(s + 22), s + 176);
    {
        u8 tmp = TblGet_08024618(s[32]);
        u8 tz = 0;
        s[8] = tmp;
        s[9] = TblGet_08024618(s[176]);
        s[404] = tz;
        s[408] = tz;
        s[400] = tz;
        s[0] = 2;
        s[1] = tz;
        s[394] = tz;
        s[395] = tz;
        {
            u8 *ep = gEwram_02005168;
            ep[12] = tz;
            ep += 20;
            ep[12] = tz;
        }
        s[412] = tz;
        s[416] = tz;
    }
    return 1;
}

__asm__(
    ".globl sub_08029504\n.set sub_08029504, 0x08029504\n"
    ".globl sub_0800E994\n.set sub_0800E994, 0x0800E994\n"
        ".globl sub_0800EA30\n.set sub_0800EA30, 0x0800EA30\n"
    ".globl BitCtl_0800520C\n.set BitCtl_0800520C, 0x0800520C\n"
    ".globl EwSet8_0800EE44\n.set EwSet8_0800EE44, 0x0800EE44\n"
    ".globl TblGetByte_08024384\n.set TblGetByte_08024384, 0x08024384\n"
    ".globl EwramSet2_0800EA08\n.set EwramSet2_0800EA08, 0x0800EA08\n"
        ".globl TblGet_08024618\n.set TblGet_08024618, 0x08024618\n"
    ".globl gEwram_02005168\n.set gEwram_02005168, 0x02005168\n"
);
