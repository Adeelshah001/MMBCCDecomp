extern u16 D_081705B0[];
extern u8 D_020031E4[];
extern void sub_0800D6E0(void *, int, int);
extern void sub_0800D9EC(void *, int);
extern void sub_0800DD08(void *, void *);
extern void sub_0800DD2C(void *, int, int);
extern void sub_0804A378(int);

struct UnkStruct_08019C94 {
    u8 pad0[0x22];
    u8 unk22;
    u8 pad1[0x22];
    u8 unk45;
    u8 pad2[0x12];
    u32 unk58;
    u32 unk5C;
    u32 unk60;
    u32 unk64;
};

void sub_08019C94(struct UnkStruct_08019C94 *arg0) {
    u8 unk[8];
    u8 *p;
    int c;
    int m;
    u16 v;

    sub_0800D6E0(arg0, 0x23E, 0);
    sub_0800D9EC(arg0, 0);
    v = *D_081705B0;
    c = D_020031E4[((u16)(v >> 4) * 2)] & 3;
    if (c > 3) c = 3;
    p = (u8 *)arg0 + 0x45;
    c <<= 2;
    m = -13;
    *p = (u8)((m & *p) | c);
    {
        int zero = 0;
        p -= 0x23;
        *p = 13;
        arg0->unk58 = zero;
        arg0->unk60 = zero;
        arg0->unk5C = zero;
        arg0->unk64 = zero;
    }
    sub_0800DD08(unk, arg0);
    sub_0800DD2C(arg0, 0xFFFFEC00, 0);
    sub_0804A378(0x9F);
}
