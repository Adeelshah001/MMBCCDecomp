/* Wave19 worker C @0x08017d00 (78 B). MATCHED with main agbcc.
 * ChipInit family: Node_PopAndInit(0,1,b,2), then q[16]=a, q[17]=q[18]=0,
 * Vec2_SetMirrored(n,(s32)(s16)c,(s32)(s16)d), IncU8_12(e), *(u32*)(q+44)=e.
 * Twin: w19c_08017620.c (Node_PopAndInit 4th arg 2).
 *
 * Same plain-C shape as matched siblings ChipInit_0801AB94/08017A44/
 * 0801BBB4 (u32 z=0 inside the block, (s32)(s16) casts, u32* n) -- no
 * pinning needed; the "alloc rotation" was an artifact of the earlier
 * u8-star/literal-0/(s16) source shape. 78 B: needs FIXALIGN1 (see Makefile).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
struct ObjVec;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
extern void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y);
extern void IncU8_12(u8 *s);
__attribute__((section(".text.w19c_08017D00")))
u32 *ChipInit_08017d00(u8 a, u8 b, u16 c, u16 d, u8 *e)
{
    u32 *n = Node_PopAndInit(0, 1, b, 5);
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
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
