extern u16 sub_080266F0(u8 idx);
extern u16 sub_08025790(void);
extern s8 sub_08025754(u8 *arg0);
extern void sub_080256D4(u8 *ptr, u8 arg1);

u16 sub_0802588C(u8 *s)
{
    return sub_080266F0(s[1]) + *(u16 *)(s + 0xE);
}

u8 sub_0802583C(u8 *arg0, u16 arg1, u16 arg2)
{
    u16 temp_r5 = sub_08025790();
    s8 val = sub_08025754(arg0);
    if ((val + (s8)arg2) - (s8)arg1 <= (s8)temp_r5)
        return 0;
    return 1;
}

u8 sub_08025958(u8 *arg0, u8 arg1)
{
    u16 var_r2 = 0;
    while (1) {
        u16 temp_r3 = var_r2;
        u8 *ptr = arg0 + 0x14 + temp_r3 * 4;
        if (*ptr == 0) {
            sub_080256D4(ptr, arg1);
            return 0;
        }
        var_r2 = temp_r3 + 1;
        if (var_r2 > 0x1D)
            return 4;
    }
}

u8 sub_0802567C(u8 *arg0)
{
    u16 var_r2 = 1;
    while (1) {
        u16 temp_r1 = var_r2;
        if (arg0[2 + temp_r1] == 0xFF)
            return (u8)var_r2;
        var_r2 = temp_r1 + 1;
        if (var_r2 > 9) {
            var_r2 = 0;
            while (1) {
                u16 temp_r1_2 = var_r2;
                if (arg0[0xC + temp_r1_2] == 0xFF)
                    return (u8)(var_r2 + 0xA);
                var_r2 = temp_r1_2 + 1;
                if (var_r2 > 1)
                    return 0;
            }
        }
    }
}
