struct ScriptState4DA {
    u8 pad00[0x1F];
    u8 unk1F;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
    u8 pad28[0x18];
    const u8 *cursor;
};

void SoundDriverNoOp(void)
{
}

void TrackReadByteInto27(void *unused, struct ScriptState4DA *state)
{
    state->unk27 = *state->cursor;
    state->cursor++;
}

void TrackReadByteInto26(void *unused, struct ScriptState4DA *state)
{
    state->unk26 = *state->cursor;
    state->cursor++;
}

void TrackReadByteInto1F(void *unused, struct ScriptState4DA *state)
{
    const u8 *cursor = state->cursor;
    state->unk1F = *cursor;
    state->cursor = cursor + 1;
}
