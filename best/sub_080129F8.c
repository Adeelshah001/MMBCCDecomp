extern u32 D_08223D6C[];
extern void sub_0804DCD0(void *arg0, u32 arg1);

void sub_080129F8(void *arg0) {
    u8 *base;
    u8 val;
    u8 val2;
    u32 index;
    
    base = (u8 *)arg0;
    val = base[0x7C];
    if (val != 0x27) {
        sub_0804DCD0(arg0, D_08223D6C[val]);
        return;
    }
    val2 = base[0x7E];
    index = (val + val2) << 2;
    sub_0804DCD0(arg0, D_08223D6C[index >> 2]);
}
