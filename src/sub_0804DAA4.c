struct ScriptState4DA {
    u8 pad00[0x1E];
    u8 unk1E;
    u8 pad1F[0x0E];
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 pad30[0x10];
    const u8 *cursor;
};

void TrackReadByteInto1E(void *unused, struct ScriptState4DA *state)
{
    const u8 *cursor = state->cursor;
    state->unk1E = *cursor;
    state->cursor = cursor + 1;
}

void TrackReadByteInto2F(void *unused, struct ScriptState4DA *state)
{
    state->unk2F = *state->cursor;
    state->cursor++;
}

void TrackReadByteInto2E(void *unused, struct ScriptState4DA *state)
{
    state->unk2E = *state->cursor;
    state->cursor++;
}

void sub_0804DAA4(void *unused, struct ScriptState4DA *state)
{
    state->unk2D = *state->cursor;
    state->cursor++;
}
