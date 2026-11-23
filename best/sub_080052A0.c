typedef signed short s16;
typedef signed int s32;
extern u16 D_02004828;
extern u32 sub_0804DD08(void);

void sub_080052A0(void) {
    u32 val;
    u16 t;

    val = (u32)D_02004828 * 11;
    val += sub_0804DD08();
    t = (u16)val;
    if ((s32)(s16)t < 0) {
        t = (u16)(-(s16)t);
    }
    D_02004828 = (u16)(((u32)(((u16)t << 16) + 0xFF890000) >> 16) & 0xFFFF);
}
