extern u32 sub_0804DCD0(u8 *s, u32 x);
extern void sub_0800D9FC(u8 *s);
extern void sub_08017478(u32 x, u32 y);
extern void sub_08017464(u32 x);
extern void sub_080176AC(void);
extern void sub_0801A9F8(u8 *s);

void sub_08017670(void *a0) {
    u8 *s = a0;
    u32 *ent = ((u32 *)0x082243D8)[s[9]];
    *(u32 *)(s + 12) = 1;
    *(u32 *)(s + 20) = *(u32 *)((u8 *)ent + 4);
    s[10] = (u8)(s[10] & 0xFD);
    s[10] = (u8)(s[10] & 0xFE);
    *(u32 *)(s + 40) = ((u32 *)0x08226148)[s[16]];
    sub_080176AC();
}

void sub_0801A9F8(u8 *s) {
    u8 res = (u8)sub_0804DCD0(s, ((u32 *)0x08226644)[s[16]]);
    sub_0800D9FC(s);
    if (res != 0) {
        u32 *ent = ((u32 *)0x082243D8)[s[9]];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)ent + 8);
        sub_08017478(*(u32 *)(s + 44), 7);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}

void sub_0801A9AC(u8 *s) {
    u32 *ent = ((u32 *)0x082243D8)[s[9]];
    *(u32 *)(s + 12) = 1;
    *(u32 *)(s + 20) = *(u32 *)((u8 *)ent + 4);
    *(u32 *)(s + 108) = 0;
    {
        u8 f = 2;
        f |= s[10];
        s[10] = (u8)(f | 1);
    }
    sub_0804DCD0(s, ((u32 *)0x082265C4)[s[16]]);
    sub_0801A9F8(s);
}
