typedef signed short s16;

extern u8 gUnknown_020051B0[];
extern s8 sub_08010FB4(u8);

int sub_08010F34(u8 arg0, u8 arg1, u8 arg2) {
    u8 *base = gUnknown_020051B0;
    u8 temp_r3 = arg0;
    u8 *temp_r4;
    s8 result;
    
    if (((base[3] >> temp_r3) & 1) != 0) {
        u32 offset = temp_r3 * 0xC;
        u8 *base_plus_18 = base + 0x18;
        temp_r4 = base_plus_18 + offset;
        result = sub_08010FB4(temp_r3);
        if (result == 1) {
            u8 zero = 0;
            u8 two = 2;
            (void)result;
            temp_r4[0] = two;
            temp_r4[6] = zero;
            temp_r4[2] = arg1;
            temp_r4[5] = arg2;
            return 1;
        }
    }
    return 0;
}
