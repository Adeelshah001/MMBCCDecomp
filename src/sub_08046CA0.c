struct Entry1DF {
    u32 unk00[4];
    u32 value;
};

void sub_0801DFAC(u32 *state, int unused, struct Entry1DF **table, int index)
{
    struct Entry1DF **entry = table + index;
    state[3] = 4;
    state[5] = (*entry)->value;
}

extern u32 gUnknown_08233A44[];

void sub_080468EC(u8 *s)
{
    u32 *tbl = gUnknown_08233A44;
    u32 idx = s[2];
    ((void (*)(u8 *))tbl[idx])(s);
}

struct UnkStruct_08046CA0 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
    u8 unk8;
};

void sub_08046CA0(struct UnkStruct_08046CA0 *state, u16 *buffer, u8 count, u8 mode)
{
    short i;
    int initial;

    state->unk4 = 0;
    if (mode == 0) {
        state->unk5 = mode;
        initial = 0x14;
    } else {
        state->unk5 = 0;
        initial = 0x19;
    }
    state->unk3 = initial;
    state->unk2 = initial;
    state->unk8 = mode;
    state->unk6 = 0x800A;
    for (i = 0; i < count + 1; i++)
        buffer[i] = 0;
    buffer[0] = 0x8000;
}

u32 sub_08046DE4(void *s, u16 b)
{
    u32 result = 0;
    if (*(u16 *)((u8 *)s + 6) == b)
        result = 1;
    return result;
}
