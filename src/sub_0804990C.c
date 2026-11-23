struct State47510 {
    u8 pad00[4];
    s8 unk04;
};

void sub_08047510(struct State47510 *state, u16 *dst)
{
    if (state->unk04 != 0) {
        state->unk04--;
        dst[state->unk04] = state->unk04 + 0x8000;
    }
}

struct State4990C {
    u8 pad00[0x15];
    u8 index;
};

extern struct State4990C D_020070F0;
extern const u8 D_082344E0[];
void sub_08011D68(u8 a, u8 b);

void sub_0804990C(void)
{
    struct State4990C *state = &D_020070F0;
    const u8 *table = D_082344E0;

    sub_08011D68(table[state->index++], 1);
}

extern u8 D_020070F0_raw[];

u8 sub_08049934(u8 idx)
{
    u8 *pool = (u8 *)&D_020070F0;
    u8 r = 0;
    u16 v = *(u16 *)(pool + idx * 12 + 0x32);

    switch (v) {
    case 253:
        r = 1;
        break;
    case 254:
        r = 2;
        break;
    case 255:
        r = 3;
        break;
    }
    return r;
}

u8 sub_0804996C(u8 idx)
{
    u8 *pool = (u8 *)&D_020070F0;
    u8 r = 0;
    u16 v = *(u16 *)(pool + idx * 12 + 0x122);

    switch (v) {
    case 253:
        r = 1;
        break;
    case 254:
        r = 2;
        break;
    case 255:
        r = 3;
        break;
    }
    return r;
}
