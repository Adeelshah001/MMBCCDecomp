struct MPlayInfo4C6 {
    u8 pad00[0x24];
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u8 pad2A[0x0A];
    u32 ident;
};

void sub_0804C610(struct MPlayInfo4C6 *info, u16 val)
{
    if (info->ident == 0x68736D53) {
        info->unk26 = val;
        info->unk24 = val;
        info->unk28 = 0x100;
    }
}

extern u32 D_08106D7C[];
extern u8 D_08106DD0[];
void sub_0804CDE8(u32 a, u32 b);

void sub_0804C6B4(u16 idx)
{
    u32 off = (u32)idx << 16;
    u32 *cfgs = D_08106D7C;
    u8 *dir = D_08106DD0;
    u32 *entry;
    u16 sub;

    off >>= 13;
    entry = (u32 *)(dir + off);
    sub = *(u16 *)((u8 *)entry + 4);
    sub_0804CDE8(*(u32 *)((u8 *)cfgs + sub * 12), entry[0]);
}

void sub_0804C53C(void);
void sub_0804C558(void);

void sub_0804C564(void)
{
    sub_0804C558();
    sub_0804C53C();
}

void sub_0804C2CC(void)
{
}
