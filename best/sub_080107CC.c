extern u32 D_02003670;
extern u8 D_08173EA8[];

void sub_080107CC(u8 *state) {
    int diff;
    u32 val;
    u32 tableAddr;
    u8 tableVal;
    int diff2;
    int var;
    u8 saved_e;

    saved_e = state[0x0E];

    if (state[0x0B] != state[0x0C]) {
        diff = state[0x0C] - state[0x0B];
        if (diff >= 0) {
            val = D_02003670 & 1;
        } else {
            val = 0xFFFF;
        }
        state[0x0B] = (u8)(state[0x0B] + val);
    }

    tableAddr = (u32)D_08173EA8;
    if (state[0x0E] != state[0x0D]) {
        tableAddr += 1;
    }
    tableVal = ((u8 *)tableAddr)[(s8)state[0x0D] * 2];

    if (tableVal != state[0x0F]) {
        diff2 = tableVal - state[0x0F];
        var = 1;
        {
            unsigned int tmp = (unsigned int)diff2 << 14;
            if (((tmp >> 16) << 16) != 0) {
                var = (int)(tmp >> 16);
            }
        }
        state[0x0F] = (u8)(state[0x0F] + var);
    } else {
        state[0x0D] = saved_e;
    }
}
