/* Worker B wave19 @0x080214f4 (36 B). MATCHED.
 * Idioms: non-void fn with no return stmt -> pop {r1} epilogue (r0 is the
 * reserved return slot); p pinned r2; z and ff double-pinned r0 in
 * disjoint lifetimes -> movs r0,#0 / movs r0,#255 ordering. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_080214F4")))
u8 *NewNode_080214F4(void)
{
    register u8 *p __asm__("r2") = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 1);
    if (p != 0) {
        register u8 z __asm__("r0") = 0;
        p[16] = 1;
        p[17] = z;
        { register u8 ff __asm__("r0") = 255; p[18] = ff; }
    }
}
