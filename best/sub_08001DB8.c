extern void ReadSramFast(u32 src, u32 dst, u32 size);
extern u8 gUnknown_02002FA0[];
extern u32 gUnknown_0804E314;

u32 sub_08001DB8(u8 arg0, u32 arg1) {
    u32 r8_val = arg1;
    u16 r6 = arg0;
    u16 r7;
    u16 r5;
    u32 r4 = (u32)gUnknown_02002FA0;
    
    if (r6 > 1) {
        return 0;
    }
    
    r7 = 3;
    while (r7 != 0) {
        r5 = 0;
        while (r5 <= 1) {
            u32 r0 = r5;
            r0 = r0 << 1;
            r0 = r0 + r6;
            r0 = r0 << 13;
            r0 = r0 + 0x0E000000;
            ReadSramFast(r0, r4, 0x10);
            
            if (*(u32*)r4 == gUnknown_0804E314 &&
                gUnknown_02002FA0[0x0C] == 0 &&
                gUnknown_02002FA0[0x0F] == 1 &&
                *(u32*)(r4 - 0x20 + 0x28) == r8_val) {
                return 1;
            }
            
            r5 = r5 + 1;
        }
        r7 = r7 - 1;
    }
    
    return 0;
}
