/* Wave 26-D: 0x08016efc (120 B incl. pool) - draft 3 (old_agbcc, natural ldrsh) */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern s16 g_08223ed8[];
extern void IncU8_12(u8 *s);
extern void SetBytes_08011F68(u8 *s, u8 v);
void sub_080174CC(u8 *s, s16 b, s16 c);

__asm__(
    ".set g_08223ed8, 0x08223ed8\n"
    ".thumb_func\n"
    ".globl sub_080174CC\n"
    ".set sub_080174CC, 0x080174cc\n"
);

__attribute__((section(".text.w26d_08016efc")))
void ObjInit_08016EFC(u8 *p, u8 a, u8 b, u8 *s, u16 e, u8 f)
{
    u8 *sl = p + 124;
    u8 aa = a;
    u8 bb = b;
    u8 ff = f;

    *(u8 **) (p + 44) = s;
    IncU8_12(s);
    {
        s16 *base = g_08223ed8;
        s16 *tbl = base + (sl[0] * 2);
        s16 v1 = tbl[0];
        s16 v2 = tbl[1];
        sub_080174CC(s, v1, v2);
    }
    p[16] = aa;
    p[17] = bb;
    SetBytes_08011F68(p, 4);
    sl[4] = 1;
    *(u16 *) (sl + 8) = e;
    sl[7] = ff;
}
