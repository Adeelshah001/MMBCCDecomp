extern u8 gUnknown_0200B7A8[];

void sub_080475D4(void) {
    u8 *state = gUnknown_0200B7A8;
    u8 *cursor = state;
    u32 index = 0;
    u8 zero = 0;

clear:
    *cursor++ = zero;
    index = ((index << 16) + 0x10000) >> 16;
    if (index <= 0x23)
        goto clear;
    
    *(u16 *)(state + 4) = 0;
}
