struct Byte4 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
};

struct ScriptState4DA {
    u8 pad00[0x1F];
    u8 unk1F;
    u8 pad20[4];
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    struct Byte4 unk28;
    u8 unk2C;
    u8 pad2D[0x13];
    const u8 *cursor;
};

void sub_0804DA7C(void *unused, struct ScriptState4DA *state)
{
    state->unk24 = *state->cursor;
    state->cursor++;
}

void sub_0804DA90(void *unused, struct ScriptState4DA *state)
{
    state->unk2C = *state->cursor;
    state->cursor++;
}

void sub_0804DA34(void *unused, struct ScriptState4DA *state)
{
    const u8 *cursor = state->cursor;
    struct Byte4 val;
    val.b0 = cursor[0];
    val.b1 = cursor[1];
    val.b2 = cursor[2];
    val.b3 = cursor[3];
    state->unk28 = val;
    state->cursor = cursor + 4;
}

struct Track4D7 {
    u8 flags;
    u8 pad01[0x15];
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
};

void sub_0804D7A0(struct Track4D7 *track)
{
    track->unk1A = 0;
    track->unk16 = 0;
    if (track->unk18 == 0)
        track->flags |= 0x0C;
    else
        track->flags |= 0x03;
}
