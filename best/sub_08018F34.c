typedef signed int s32;

struct Vec2 {
    s32 x;
    s32 y;
};

struct Obj18F34 {
    u8 pad00[0x22];
    u8 unk22;
    u8 pad23[0x22];
    u8 unk45;
    u8 pad46[0x12];
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
};

extern const u16 D_081705B0[];
extern u16 D_020031E4[];

extern void sub_0800D6E0(struct Obj18F34 *, int, int);
extern void sub_0800D9EC(struct Obj18F34 *, int);
extern struct Vec2 sub_0800DD08(struct Obj18F34 *);
extern void sub_0800DD2C(struct Obj18F34 *, s32, s32);
extern void sub_0804A378(u8);

void sub_08018F34(struct Obj18F34 *obj)
{
    const u8 *e;
    u8 priority;
    int checked;
    int shifted;
    int mask;
    u8 *p;
    int zero;

    sub_0800D6E0(obj, 0x22E, 0);
    sub_0800D9EC(obj, 0);

    e = (const u8 *)&D_020031E4[D_081705B0[0] >> 4];
    priority = 3;
    priority &= *e;
    checked = priority;
    if (checked > 3)
        priority = 3;

    p = &obj->unk45;
    shifted = priority << 2;
    mask = -13;
    checked = *p;
    mask &= checked;
    *p = mask | shifted;
    p -= 0x23;
    zero = 0;
    *p = 13;
    obj->unk58 = zero;
    obj->unk60 = zero;
    obj->unk5C = zero;
    obj->unk64 = zero;
    sub_0800DD08(obj);
    sub_0800DD2C(obj, -0x1400, 0);
    sub_0804A378(0x9F);
}
