/* Wave 35-B v5: 0x0804c288 single pinned temp, separate assignments.
 * Needs w35b_0804c288_patch.py (.s post-process: tst, and-shape, thunk call).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__attribute__((section(".text.w35b_0804c288")))
void Sub_0804C288(u8 a, u8 *p)
{
    u8 *pp = p;
    u32 *node;
    if ((*pp & 0x80) == 0)
        return;
    node = *(u32 **)(pp + 32);
    if (node == 0)
        goto done;
    do {
        u32 z = 0;
        if (*(u8 *)node != 0) {
            if ((((u8 *)node)[1] & 7) != 0) {
                typedef void (*Func)(void);
                register u8 *tmp __asm__("r3");
                tmp = *(u8 **)0x03007FF0;
                tmp = *(u8 **)(tmp + 44);
                ((Func)tmp)();
            }
            *(u8 *)node = z;
        }
        *(u32 *)((u8 *)node + 44) = z;
        node = *(u32 **)((u8 *)node + 52);
    } while (node != 0);
done:
    *(u32 **)(pp + 32) = node;
}
