/* Wave 31-D: 0x080363EC MATCHED (ChangedBitsInit_080363EC) — do-while with i=(u16)(j+1), fixed ldrsb template. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 *NodeInit_080217A8(u8 x);
extern void WalkBits_0803643C(int a, int b, int c);
__asm__(".set NodeInit_080217A8, 0x080217a8");
__asm__(".set WalkBits_0803643C, 0x0803643c");

__attribute__((section(".text.w31d_080363ec")))
void ChangedBitsInit_080363EC(u8 *p)
{
    register u8 *pp __asm__("r6") = p;
    if (pp[3] != pp[2]) {
        int x = (pp[2] ^ pp[3]) & pp[2];
        u16 i = 0;
        s16 j;
        do {
            j = (s16)i;
            if (((x >> j) & 1) != 0)
                NodeInit_080217A8((u8)i);
            i = (u16)(j + 1);
        } while ((s16)i <= 6);
        pp[3] = pp[2];
        {
            /* ROM uses ldrsb (agbcc never emits it from C); value already sign-extended. */
            register s32 v __asm__("r0");
            __asm__ volatile(
                "movs r0, #1\n\t"
                "ldrsb %0, [%1, r0]"
                : "=r"(v) : "r"(pp));
            WalkBits_0803643C(v, 0, 0);
        }
    }
}
