// sub_080483DC
u32 sub_080483DC(void *arg0) {
    u8 *base = (u8 *)arg0;
    u32 result = 0;
    if (base[0x46A6] == 6) {
        result = 1;
    } else {
        base[2] = 1;
        base[3] = 0;
    }
    return result;
}

// sub_08047C4C
extern u16 gUnknown_02000860[];
extern u16 gUnknown_02000870[];
extern u16 gUnknown_0200B74C[];
extern u16 gUnknown_0200B756[];

void sub_08047C4C(void) {
    int i;
    
    for (i = 0; i <= 4; i++) {
        gUnknown_0200B74C[i] = gUnknown_02000860[i];
    }
    
    for (i = 0; i <= 0x18; i++) {
        gUnknown_0200B756[i] = gUnknown_02000870[i];
    }
}

// sub_08047600
extern u8 gUnknown_0200B7A8[];
extern u32 gUnknown_08233AFC[];

s8 sub_08047600(u8 *s) {
    u8 *p = gUnknown_0200B7A8;
    u32 *tbl = gUnknown_08233AFC;
    u32 idx = p[0];
    u32 (*func)(u8 *) = (u32 (*)(u8 *))tbl[idx];
    *(u16 *)s = *(u16 *)(p + 4);
    return (s8)func(p);
}

// sub_080475D4
extern u8 gUnknown_0200B7A8[];

void sub_080475D4(void) {
    u8 *state = gUnknown_0200B7A8;
    u8 *cursor = state;
    u32 index = 0;
    u8 zero = 0;

    do {
        *cursor++ = zero;
        index = ((index << 16) + 0x10000) >> 16;
    } while (index <= 0x23);
    
    *(u16 *)(state + 4) = 0;
}
