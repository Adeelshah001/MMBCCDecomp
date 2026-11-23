extern u16 gUnknown_02000860[];
extern u16 gUnknown_02000870[];
extern u16 gUnknown_0200B74C[];
extern u16 gUnknown_0200B756[];

void sub_08047C4C(void) {
    short var_r0 = 0;
    short temp_r1;
    int temp_r0;
    
    do {
        short temp_r1_2 = var_r0;
        temp_r0 = temp_r1_2 * 2;
        gUnknown_0200B74C[temp_r0 / 2] = gUnknown_02000860[temp_r0 / 2];
        temp_r1 = temp_r1_2 + 1;
        var_r0 = (short)temp_r1;
    } while ((int)(short)temp_r1 <= 4);
    
    var_r0 = 0;
    do {
        short temp_r1_4 = var_r0;
        temp_r0 = temp_r1_4 * 2;
        gUnknown_0200B756[temp_r0 / 2] = gUnknown_02000870[temp_r0 / 2];
        temp_r1 = temp_r1_4 + 1;
        var_r0 = (short)temp_r1;
    } while ((int)(short)temp_r1 <= 0x18);
}
