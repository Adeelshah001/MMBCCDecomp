void sub_0800D6E0(void *arg0, int arg1, int arg2);
void sub_0800D9EC(void *arg0, int arg1);

void sub_0801AEF4(void *arg0) {
    u8 *r4 = arg0;
    u32 r0, r1;
    u8 r3;
    u8 *r2;
    
    r1 = 0x22D;
    r0 = 0;
    sub_0800D6E0(r4, r1, r0);
    
    r0 = (u32)r4;
    r1 = 0;
    sub_0800D9EC(r4, r1);
    
    r0 = *(u16 *)0x081705B0;
    r0 >>= 4;
    r0 <<= 1;
    r1 = 0x020031E4;
    r0 += r1;
    r1 = 3;
    r0 = *(u8 *)r0;
    r1 &= r0;
    r0 = r1;
    if ((int)r0 <= 3) {
        // ble
    } else {
        r1 = 3;
    }
    
    r2 = r4 + 0x45;
    r1 <<= 2;
    r0 = 0xD;
    r0 = -r0;
    r3 = *r2;
    r0 &= r3;
    r0 |= r1;
    *r2 = r0;
    
    r2 = r4 + 0x22;
    r1 = 0;
    r0 = 0xD;
    *r2 = r0;
    *(u32 *)(r4 + 0x58) = r1;
    *(u32 *)(r4 + 0x60) = r1;
    *(u32 *)(r4 + 0x5C) = r1;
    *(u32 *)(r4 + 0x64) = r1;
}
