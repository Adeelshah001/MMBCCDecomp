struct Entry005F44 {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 pad04[0x18];
    u8 unk1C;
    u8 pad1D[2];
    u8 unk1F;
};

struct State02004830 {
    u8 pad00[2];
    u16 unk02;
    u8 pad04[6];
    u8 b0:1;
    u8 b1:7;
    u8 pad0B[0x465];
    struct Entry005F44 entries[32];
};

extern u8 D_02003670[];
extern struct State02004830 D_02004830;

void sub_08022F88(struct Entry005F44 *);

void sub_08005F44(u8 idx, u8 a, u8 b) {
    u8 *s1 = D_02003670;
    struct State02004830 *s2 = &D_02004830;
    struct Entry005F44 *e;
    u8 *base;

    if (s2->b0) {
        s2->b0 = 0;
        s2->unk02 = 0;
    }

    {
        u32 off = idx << 5;
        base = (u8 *)s2 + 0x470;
        e = (struct Entry005F44 *)(off + base);
    }
    e->unk00 = a;
    e->unk01 = b;
    if (e->unk1C == 0) {
        e->unk02 = a;
        e->unk03 = b;
    }
    e->unk1C = 1;

    {
        int m;
        base = s1 + 0x11AE;
        m = 0xF8;
        m &= *base;
        if (m != 0x10) {
            if ((e->unk1F & 0x10) == 0) {
                e->unk1F |= 0x10;
                sub_08022F88(e);
            }
        }
    }
}
