/* Wave 34-D: 0x08035E5C v4.
 * s8-indexed table + nested if/else. 84 B true extent (0x08035E5C-0x08035EB0).
 * Pools: 0x0822EB6C, 0x00004699, 0x000046B7.
 * sub_0804DCD0 unmatched -> .set.
 * main agbcc.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern s8 sub_0804DCD0(u8 *p, u32 v);
__asm__(".set sub_0804DCD0, 0x0804dcd0");

__attribute__((section(".text.w34d_08035e5c")))
void sub_08035E5C(u8 *p)
{
    register u8 *pp __asm__("r4") = p;
    register u32 *tbl __asm__("r1") = (u32 *)0x0822EB6C;
    u8 *p2;
    s8 idx;
    u32 v;
    __asm__ volatile("" : "+r"(tbl));
    p2 = pp + 0x4699;
    idx = *(s8 *)p2;
    v = tbl[idx];
    if (sub_0804DCD0(pp, v) != 0) {
        register s32 x __asm__("r1");
        x = *(s8 *)p2;
        if (x != 0) {
            x = 0;
            *p2 = x;
        } else {
            *p2 = *(pp + 0x46B7);
        }
        pp[4] = x;
        pp[1] = 3;
        pp[3] = x;
        pp[2] = x;
    }
}
