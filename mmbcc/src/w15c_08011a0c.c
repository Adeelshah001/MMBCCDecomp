/* Wave 15-C: FlagApply_08011A0C @ 0x08011a0c (old_agbcc). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef signed char s8;
extern void FlagBit_Set_11D68(u16 x, u8 y);
int __attribute__((section(".text.w15c2_08011a0c"))) FlagApply_08011A0C(u8 *s)
{
    s8 *p = *(s8 **)(s);
    s8 v = p[6];
    if (v > 0) {
        FlagBit_Set_11D68((u16)v, 1);
    } else if (v < 0) {
        FlagBit_Set_11D68((u16)(-p[6]), 0);
    }
    v = p[7];
    if (v > 0) {
        FlagBit_Set_11D68((u16)v, 1);
    } else if (v < 0) {
        FlagBit_Set_11D68((u16)(-p[7]), 0);
    }
    {
        register u8 t __asm__("r1");
        int zero;
        t = s[4] + 1;
        zero = 0;
        s[4] = t;
        s[5] = zero;
        s[6] = zero;
        s[7] = zero;
        return zero - 1;
    }
}

