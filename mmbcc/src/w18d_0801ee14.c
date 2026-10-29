/* Worker D wave18 @0x0801ee14 (82 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
struct ObjVec { u8 _[64]; };
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
extern void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y);
__attribute__((section(".text.w18d_0801EE14")))
u8 *NewNode_0801EE14(u8 a, u8 b, u8 c, u16 d, u16 e)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 1, c, 16);
    if (p != 0) {
        u8 z = 0;
        p[16] = a;
        p[17] = b;
        p[18] = z;
        Vec2_SetMirrored((struct ObjVec *)p, (s16)d, (s16)e);
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
