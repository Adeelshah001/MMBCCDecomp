extern void sub_0800D6E0(void *arg0, int arg1, int arg2);
extern void sub_0800D9EC(void *arg0, int arg1);

extern u16 D_081705B0;
extern u8 D_020031E4[];

void sub_0801ACF4(void *arg0) {
    u8 *obj = arg0;
    u16 idx;
    u8 val;
    int tmp;
    int tmp2;
    u8 *ptr;
    
    sub_0800D6E0(arg0, 0x226, 0);
    sub_0800D9EC(arg0, 0);
    
    idx = D_081705B0 >> 4;
    idx *= 2;
    val = D_020031E4[idx] & 3;
    if ((signed char)val > 3) {
        val = 3;
    }
    
    ptr = &obj[0x45];
    tmp = *ptr;
    tmp &= -0xD;
    tmp |= val << 2;
    *ptr = tmp;
    
    ptr -= 0x23;
    *ptr = 0xD;
    
    *(u32 *)&obj[0x58] = 0x700;
    tmp = -8;
    *(u32 *)&obj[0x60] = tmp;
    tmp2 = 0;
    *(u32 *)&obj[0x5C] = tmp2;
    *(u32 *)&obj[0x64] = tmp2;
}
