typedef short s16;

#define REG_DISPSTAT (*(volatile u16 *)0x04000004)
#define REG_IE       (*(volatile u16 *)0x04000200)

extern const u32 D_0816E22C[];
extern void sub_08000C68(void *desc);

void sub_08000AD4(void)
{
    s16 idx = 0;
    u32 *B = (u32 *)0x03000580;
    u32 *B2;

    if (B[2] != 0) {
        B[3] = B[0];
        sub_08000C68(B);
        idx = 1;
    }
    B2 = B + 7;
    if (B2[2] != 0) {
        B2[3] = B[7];
        sub_08000C68(B2);
        idx += 2;
    }
    if (idx != 0) {
        u32 *base;
        REG_DISPSTAT |= 0x10;
        (void)REG_DISPSTAT;
        base = B - 0x60;
        base[1] = D_0816E22C[idx];
        REG_IE |= 2;
        (void)REG_IE;
    }
}
