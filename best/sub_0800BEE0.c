extern u8 gUnknown_02004F40[];

void sub_0800BEE0(u16 arg0, u8 arg1)
{
    u8 *base = gUnknown_02004F40;
    u16 val_14 = *(u16 *)(base + 0x14);
    u16 arg0_16 = arg0;
    u8 r4 = arg0_16;
    u8 r5 = arg1;
    u8 r6 = val_14;
    u8 tmp;
    
    if ((val_14 << 16) != (arg0_16 << 16)) {
        *(u16 *)(base + 0x06) = arg0_16;
        
        if (arg1 == 0x80) {
            tmp = *(base + 0x09);
            tmp = (tmp & 3) | 0x80;
            *(base + 0x09) = tmp;
            
            r6 = *(base + 0x0A);
            tmp = r6 & ~7;
            *(base + 0x0A) = tmp;
        } else {
            if (arg1 > 0x80) {
                r6 = *(base + 0x0A);
                tmp = r6 | 8;
            } else {
                r6 = *(base + 0x0A);
                tmp = r6 & ~9;
            }
            *(base + 0x0A) = tmp;
            
            r6 = *(base + 0x0A);
            tmp = r6 & ~7;
            tmp = tmp | 4;
            *(base + 0x0A) = tmp;
        }
    }
}
