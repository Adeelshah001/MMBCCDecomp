extern u8 gUnknown_02003090[];

void sub_08002C74(u32 arg0) {
    u32 r0_val = arg0;
    u32 r1_val;
    u32 r2_val;
    u8 *r3_ptr;
    u8 *r4_ptr;
    u32 i;

    r0_val = r0_val << 24;
    r1_val = 0x80;
    r1_val = r1_val << 17;
    r0_val = r0_val + r1_val;
    r2_val = r0_val >> 24;

    r3_ptr = gUnknown_02003090;
    r4_ptr = r3_ptr;

    i = 0;
    if (r3_ptr[0] != r2_val) {
        while (1) {
            i = i + 1;
            if ((int)i > 15) break;
            if (r4_ptr[i] == r2_val) break;
        }
    }

    if (i != 16) {
        r4_ptr[i] = 0;
    }
}
