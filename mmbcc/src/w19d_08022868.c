/* 0x08022868 (84 B): build 5-node doubly-linked list (idx 0..4), return last node.
 * Guard: s16 at *(u8**)0x020066f0+10 must be > 4.
 * idx++ via shift-first add: (idx<<24)+0x1000000>>24 (matches ROM's
 * lsls/movs/lsls/adds/lsrs dance; plain idx++ emits adds-first instead).
 * Pool already lands inline at +0x14 (branch-shadow). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19d_08022868")))
u8 *BuildList5_08022868(void)
{
    s16 v = *(s16 *)(*(u8 **)0x020066f0 + 10);
    u8 *prev;
    u8 idx;
    u8 z;
    u8 *p;
    if (v <= 4)
        return 0;
    prev = 0;
    idx = 0;
    z = 0;
    do {
        p = (u8 *)Node_PopAndInit_20ED4(1, 1, 0, 5);
        *(u8 **)(p + 40) = prev;
        *(u8 **)(p + 44) = (u8 *)(u32)z;
        if (prev != 0)
            *(u8 **)(prev + 44) = p;
        p[16] = z;
        p[17] = idx;
        prev = p;
        idx = (u8)(((idx << 24) + 0x1000000) >> 24);
    } while ((s8)idx <= 4);
    return prev;
}
