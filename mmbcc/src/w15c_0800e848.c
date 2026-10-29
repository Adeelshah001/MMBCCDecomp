/* Wave 15-C: GuardedListInit_0800E848 @ 0x0800e848 (main). Coordinator-landed, 0-diff verified. */
/* GuardedListInit_0800E848 @0x0800E848 — wave15_C_redo2 candidate.
 * Template: *(u16*)(0x02005130+24)=1; if ((s8)checker()==1){ p[12]=0; SetByte20(0); }
 * then ListIterate_D568(*(u8**)0x02005270); ListIterate_D568(*(u8**)0x020053C0);
 * Key idiom: u8 z=0 temp reused for the strh and the SetByte20 arg. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 IsZero_02005160_080102F4(void);
extern void SetByte20_0800E1F0(u8 x);
extern void ListIterate_D568_0800D568(u8 *p);

__attribute__((section(".text.w15c2_0800E848")))
void GuardedListInit_0800E848(void)
{
    u16 *p = (u16 *)0x02005130;
    u8 z = 0;
    p[12] = 1;
    if ((s8)IsZero_02005160_080102F4() == 1) {
        p[12] = z;
        SetByte20_0800E1F0(z);
    }
    ListIterate_D568_0800D568(*(u8 **)0x02005270);
    ListIterate_D568_0800D568(*(u8 **)0x020053C0);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl IsZero_02005160_080102F4\n"
    ".set IsZero_02005160_080102F4, 0x080102F4\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_0800E1F0\n"
    ".set SetByte20_0800E1F0, 0x0800E1F0\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl ListIterate_D568_0800D568\n"
    ".set ListIterate_D568_0800D568, 0x0800D568\n"
);
