struct State47510 {
    u8 pad00[4];
    s8 unk04;
};

void sub_08047510(struct State47510 *state, u16 *dst)
{
    if (state->unk04 == 0)
        return;
    state->unk04--;
    dst[state->unk04] = state->unk04 + 0x8000;
}

extern u8 D_020070F0[];

u8 sub_08049934(u8 idx)
{
    u8 *pool = D_020070F0;
    u8 r = 0;
    u8 *base = pool + idx * 12;
    int v = *(u16 *)(base + 0x32);
    if (v == 254) goto yes2;
    if (v > 254) goto big;
    if (v == 253) goto yes1;
    goto no;
big:
    if (v != 255) goto no;
    r = 3;
    goto no;
yes2:
    r = 2;
    goto no;
yes1:
    r = 1;
no:
    return r;
}

u8 sub_0804996C(u8 idx)
{
    u8 *pool = D_020070F0;
    u8 r = 0;
    u8 *base = pool + idx * 12;
    int v = *(u16 *)(base + 0x122);
    if (v == 254) goto yes2;
    if (v > 254) goto big;
    if (v == 253) goto yes1;
    goto no;
big:
    if (v != 255) goto no;
    r = 3;
    goto no;
yes2:
    r = 2;
    goto no;
yes1:
    r = 1;
no:
    return r;
}
