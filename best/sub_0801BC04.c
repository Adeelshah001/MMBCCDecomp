extern const u16 D_081705B0[];
extern u16 D_020031E4[];

extern void sub_0800D6E0(u8 *, u32, u32);
extern void sub_0800D9EC(u8 *, u32);
extern void sub_0800DD4C(u8 *, int, u32);
extern void sub_0804A378(u32);

void sub_0801BC04(u8 *arg0)
{
    u8 prio;
    int val;
    u8 *p;
    const u8 *bg;
    int checked;

    sub_0800D6E0(arg0, 0x224, 0);
    sub_0800D9EC(arg0, 0);

    bg = (const u8 *)&D_020031E4[D_081705B0[0] >> 4];
    prio = 3;
    prio &= *bg;
    checked = prio;
    if (checked > 3)
        prio = 3;

    p = arg0 + 0x45;
    checked = prio << 2;
    val = -0x0D;
    val &= *p;
    val |= checked;
    *p = val;

    arg0[0x22] = 0x0D;
    sub_0800DD4C(arg0, -0x3C00, 0);
    sub_0804A378(0x9F);
}
