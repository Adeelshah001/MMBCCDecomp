extern u8 gUnknown_0200B810[];
extern u8 gUnknown_0822DE04[];

extern u8 sub_0802FDA0(u8 *s);
extern u8 _call_via_r1(u8 *s);

int sub_08028900(void)
{
    int r5 = 0;
    u8 *table_base = gUnknown_0822DE04;
    u8 *state = gUnknown_0200B810;
    
    u8 (**func_table)(u8 *) = (u8 (**)(u8 *))table_base;
    u8 idx = state[0];
    u8 ret1 = func_table[idx](state);
    
    u8 r6 = ret1;
    
    u8 mask = 8;
    u8 flag = state[6];
    if ((flag & mask) == 0) {
        if (r6 != 0) {
            u8 v = sub_0802FDA0(state);
            if (v == 11) {
                r5 = 5;
            }
            if (v == 9) {
                r5 = 3;
            } else if (v == 10) {
                r5 = 4;
            }
        }
    }
    
    if (r6 == 4) {
        u8 tmp = gUnknown_0200B810[4];
        r5 = tmp >> 4;
        gUnknown_0200B810[0] = 0;
        gUnknown_0200B810[1] = 0;
    }
    
    return r5;
}
