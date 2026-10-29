/* Wave 15-C: GuardedListInit_0800E90C @ 0x0800e90c (main). Coordinator-landed, 0-diff verified. */
/* GuardedListInit_0800E90C @0x0800E90C — wave15_C_redo2 candidate.
 * Template + u8 *q=(u8*)p; q+=10; checker takes pointer arg. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 Test_08010454(u8 b);
extern void SetByte20_0800E1F0(u8 x);
extern void ListIterate_D568_0800D568(u8 *p);

__attribute__((section(".text.w15c2_0800E90C")))
void GuardedListInit_0800E90C(void)
{
    u16 *p = (u16 *)0x02005130;
    u8 *q = (u8 *)p;
    u8 z = 0;
    p[12] = 1;
    q += 43;
    if ((s8)Test_08010454(*q) == 1) {
        p[12] = z;
        SetByte20_0800E1F0(z);
    }
    ListIterate_D568_0800D568(*(u8 **)0x02005270);
    ListIterate_D568_0800D568(*(u8 **)0x020053C0);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_0800E1F0\n"
    ".set SetByte20_0800E1F0, 0x0800E1F0\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl ListIterate_D568_0800D568\n"
    ".set ListIterate_D568_0800D568, 0x0800D568\n"
);
