extern u16 gUnknown_02002F50[];
extern u16 gUnknown_02004CE0[];

void sub_0804A378(int);

int sub_080481FC(void *arg0) {
    int result = 0;
    u16 *base = gUnknown_02002F50;
    u32 temp = 0x30;
    u16 flags;
    u8 *ptr;
    u8 oldVal;
    u8 newVal;
    u16 *dst;
    
    flags = base[2];
    if ((temp & flags) != 0) {
        sub_0804A378(0x66);
        ptr = (u8 *)arg0 + 0x46B4;
        oldVal = *ptr;
        newVal = 1 ^ oldVal;
        *ptr = newVal;
        dst = gUnknown_02004CE0;
        dst[0x14] = (newVal * 8 - newVal) * 16 + 0x18;
        dst[0x15] = 0x20;
    }
    
    flags = base[2];
    if ((flags & 0x01) != 0) {
        result = 1;
    } else if ((flags & 0x02) != 0) {
        result = 2;
    }
    
    return result;
}
