extern const u16 D_081705B0[];
extern u16 D_020031E4[];

void sub_0800D770(u8 *s, u32 a, u32 b);
void sub_0800D9EC(u8 *s, u32 x);
void sub_0800DD08(u8 *buf, u8 *s);
void sub_0800DD2C(u8 *s, u32 a, u32 b);
void sub_0804A378(u32 x);

void sub_0801BFB4(u8 *s) {
    u8 buf[8];
    const u8 *priorityByte;
    u8 priority;
    int checked;
    u8 *attributes;
    int flags;
    u8 *timer;

    sub_0800D770(s, 0x82A, 0);
    sub_0800D9EC(s, 0);
    priorityByte = (const u8 *)&D_020031E4[D_081705B0[0] >> 4];
    priority = 3;
    priority &= *priorityByte;
    checked = priority;
    if (checked > 3) {
        priority = 3;
    }
    attributes = s + 0x45;
    checked = priority << 2;
    flags = -13;
    flags &= *attributes;
    flags |= checked;
    *attributes = flags;
    timer = s + 0x22;
    *timer = 0x0D;
    sub_0800DD08(buf, s);
    sub_0800DD2C(s, 0xFFFFEC00, 0);
    sub_0804A378(0x9F);
}
