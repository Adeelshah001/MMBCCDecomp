/* Wave20 worker C @0x0801d2c8 (62 B), attempt 3. Pin type->r4 (u32, callee-saved,
 * already in push set) to fix the r4/r5 swap; d should then take r5.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w20c_0801d2c8")))
u32 *F_0801D2C8(u8 a, u32 b, u32 c, u32 *d)
{
    register u32 type __asm__("r4");
    u32 *n;
    type = 6;
    if (a == 0)
        type = 5;
    n = Node_PopAndInit(0, 1, 0, 12);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        u32 v0, v1;
        q[16] = type;
        q[17] = z;
        v0 = d[0];
        v1 = d[1];
        *(u32 *)(q + 96) = v0;
        *(u32 *)(q + 100) = v1;
        *(u32 *)(q + 40) = c;
        *(u32 *)(q + 44) = b;
    }
    return n;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
