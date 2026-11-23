extern u16 D_081705B0;
extern u8 D_020031E4[];

void sub_0800D770(void *, u32, u32);
void sub_0800D9EC(void *, u32);
void sub_0800DD4C(void *, u32, u32);

struct UnkStruct_0801BD7C {
    u8 filler0[0x22];
    u8 unk22;
    u8 filler1[0x22];
    u8 unk45;
};

void sub_0801BD7C(void *arg0) {
    int var;
    struct UnkStruct_0801BD7C *s = (struct UnkStruct_0801BD7C *)arg0;

    sub_0800D770(arg0, 0x825, 0);
    sub_0800D9EC(arg0, 0);
    {
        u32 idx = ((u16)D_081705B0 >> 4) * 2;
        var = (int)(3 & D_020031E4[idx]);
    }
    if (var > 3) {
        var = 3;
    }
    {
        u8 *dst = &s->unk45;
        u32 shift = (u32)var * 4;
        int mask = -13;
        *dst = (*dst & mask) | shift;
    }
    s->unk22 = 0xD;
    sub_0800DD4C(arg0, 0xFFFFC400, 0);
}
