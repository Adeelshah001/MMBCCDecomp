/* Wave 17 worker C: ChipInit family (Node_PopAndInit wrappers). */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef signed short s16; typedef signed int s32;

struct ObjVec;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
extern void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y);
extern void IncU8_12(u8 *s);

/* 0x080178a8 (84 B): Node_PopAndInit(0,1,b,3), u16*(n+120) stores. */
__attribute__((section(".text.w17c_080178a8")))
u32 *ChipInit_080178A8(u8 a, u8 b, u16 c, u16 d, u8 *e)
{
    u32 *n = Node_PopAndInit(0, 1, b, 3);
    if (n != 0) {
        u16 *p = (u16 *)((u8 *)n + 120);
        u8 *q = (u8 *)n;
        u32 z = 0;
        p[0] = c;
        p[1] = d;
        q[16] = a;
        q[17] = z;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)c, (s32)(s16)d);
        IncU8_12(e);
        *(u32 *)((u8 *)n + 44) = (u32)e;
    }
    return n;
}

/* 0x0801aa70 (92 B): Node_PopAndInit(0,1,c,6), 6 params. */
__attribute__((section(".text.w17c_0801aa70")))
u32 *ChipInit_0801AA70(u8 a, u8 b, u8 c, u16 d, u16 e, u8 *f)
{
    u32 *n = Node_PopAndInit(0, 1, c, 6);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
        IncU8_12(f);
        *(u32 *)(q + 44) = (u32)f;
    }
    return n;
}

/* 0x0801b98c (92 B): Node_PopAndInit(0,1,c,8). */
__attribute__((section(".text.w17c_0801b98c")))
u32 *ChipInit_0801B98C(u8 a, u8 b, u8 c, u16 d, u16 e, u8 *f)
{
    u32 *n = Node_PopAndInit(0, 1, c, 8);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
        IncU8_12(f);
        *(u32 *)(q + 44) = (u32)f;
    }
    return n;
}

/* 0x0801709c (40 B): Node_PopAndInit(0,0,0,0) leaf. */
__attribute__((section(".text.w17c_0801709c")))
u32 *ChipInit_0801709C(u8 a)
{
    u32 *n = Node_PopAndInit(0, 0, 0, 0);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = (u8)z;
        *(u32 *)(q + 40) = z;
    }
    return n;
}

/* 0x0801ebf0 (82 B): Node_PopAndInit(0,1,c,15), 5 params, no tail. */
__attribute__((section(".text.w17c_0801ebf0")))
u32 *ChipInit_0801EBF0(u8 a, u8 b, u8 c, u16 d, u16 e)
{
    u32 *n = Node_PopAndInit(0, 1, c, 15);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
    }
    return n;
}

/* 0x0801cd50 (92 B): Node_PopAndInit(0,1,c,10). */
__attribute__((section(".text.w17c_0801cd50")))
u32 *ChipInit_0801CD50(u8 a, u8 b, u8 c, u16 d, u16 e, u8 *f)
{
    u32 *n = Node_PopAndInit(0, 1, c, 10);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
        IncU8_12(f);
        *(u32 *)(q + 44) = (u32)f;
    }
    return n;
}

/* 0x0801ab94 (78 B): Node_PopAndInit(0,1,b,7), no +120 stores. */
__attribute__((section(".text.w17c_0801ab94")))
u32 *ChipInit_0801AB94(u8 a, u8 b, u16 c, u16 d, u8 *e)
{
    u32 *n = Node_PopAndInit(0, 1, b, 7);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = z;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)c, (s32)(s16)d);
        IncU8_12(e);
        *(u32 *)(q + 44) = (u32)e;
    }
    return n;
}

/* 0x08017a44 (78 B): Node_PopAndInit(0,1,b,4). */
__attribute__((section(".text.w17c_08017a44")))
u32 *ChipInit_08017A44(u8 a, u8 b, u16 c, u16 d, u8 *e)
{
    u32 *n = Node_PopAndInit(0, 1, b, 4);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = z;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)c, (s32)(s16)d);
        IncU8_12(e);
        *(u32 *)(q + 44) = (u32)e;
    }
    return n;
}

/* 0x0801bbb4 (78 B): Node_PopAndInit(0,1,b,9). */
__attribute__((section(".text.w17c_0801bbb4")))
u32 *ChipInit_0801BBB4(u8 a, u8 b, u16 c, u16 d, u8 *e)
{
    u32 *n = Node_PopAndInit(0, 1, b, 9);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = z;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)c, (s32)(s16)d);
        IncU8_12(e);
        *(u32 *)(q + 44) = (u32)e;
    }
    return n;
}

/* 0x0801e990 (82 B): Node_PopAndInit(0,1,c,14). */
__attribute__((section(".text.w17c_0801e990")))
u32 *ChipInit_0801E990(u8 a, u8 b, u8 c, u16 d, u16 e)
{
    u32 *n = Node_PopAndInit(0, 1, c, 14);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        Vec2_SetMirrored((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
    }
    return n;
}
