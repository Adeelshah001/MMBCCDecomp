extern u32 gUnknown_082300F8[];
void sub_0804DCD0(u8 *s, void (*fn)(u8 *));

void Task_3AFFC(u32 x) {
    u32 a = x;
    u32 b = a;
    (void)a;
    (void)b;
}

void sub_0803F440(u32 arg0, u8 arg1, u8 arg2) {
    u8 *base = (u8 *)(arg0 + 0x45C4);
    u8 *p1 = base + arg1;
    u8 tmp = *p1;
    u8 *p2 = base + arg2;
    *p1 = *p2;
    *p2 = tmp;
}

void sub_0803F460(u32 arg0, u8 arg1, u8 arg2) {
    u8 *base = (u8 *)(arg0 + 0x464C);
    u8 *p1 = base + arg1;
    u8 tmp = *p1;
    u8 *p2 = base + arg2;
    *p1 = *p2;
    *p2 = tmp;
}

void sub_080365F8(u8 *s) {
    s[0x469F] = 0;
    sub_0804DCD0(s, (void (*)(u8 *))gUnknown_082300F8[s[1]]);
}
