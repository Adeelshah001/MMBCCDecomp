extern u8 gUnknown_02005130[];
extern u32 gUnknown_02005270;
extern u32 gUnknown_020053C0;

extern int sub_0801709C(int);
extern int sub_080170C4(int);
extern void sub_0800D568(int);
extern void sub_0800E1F0(int);

void sub_0800E748(void) {
    u8 *base = gUnknown_02005130;
    int res;

    *(u16 *)(base + 0x18) = 1;
    if (base[0x15] == 0) goto L0;
    if (base[0x15] == 1) goto L1;
    goto Ltail;

L0:
    res = sub_0801709C(base[0x25] ? 6 : 2);
    *(u32 *)(base + 0x1C) = res;
    if (res != 0) goto L0b;
    *(u16 *)(base + 0x18) = (u16)res;
    sub_0800E1F0(0);
    goto Ltail;

L0b:
    base[0x15] += 1;
    goto Ltail;

L1:
    res = *(u32 *)(base + 0x1C);
    if ((sub_080170C4(res) << 24) != 0) {
        *(u16 *)(base + 0x18) = 0;
        sub_0800E1F0(0);
    }

Ltail:
    sub_0800D568(gUnknown_02005270);
    sub_0800D568(gUnknown_020053C0);
}
