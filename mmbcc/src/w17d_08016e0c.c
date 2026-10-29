/* Worker D wave17 Part2 revisit @0x08016e0c (64 B).
 * Sets bytes at s+124..128 based on u16 v, then sub_08011F68(s, 1).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void sub_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w17d_08016E0C")))
void Sub_16E0C(u8 *s, u32 v)
{
    register u8 *ss __asm__("r4") = s;
    u16 vv = (u16)v;
    u8 *p = ss + 124;
    u8 z = 0;
    p[0] = (u8)vv;
    p[1] = (u8)vv;
    if ((u8)vv > 38) {
        p[3] = (u8)(vv - 39);
        p[2] = (u8)(vv - 39);
        p[0] = 39;
        p[1] = 39;
    } else {
        p[3] = z;
        p[2] = z;
    }
    p[4] = 1;
    sub_08011F68(ss, 1);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl sub_08011F68\n"
    ".set sub_08011F68, 0x08011F68\n"
);
