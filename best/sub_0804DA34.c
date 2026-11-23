struct Byte4 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
};

struct ScriptState4DA {
    u8 pad00[0x28];
    struct Byte4 unk28;
    u8 pad2C[0x14];
    const u8 *cursor;
};

void sub_0804DA34(void *unused, struct ScriptState4DA *state)
{
    const u8 *cursor = state->cursor;
    union {
        struct Byte4 s;
        u32 w;
    } val;
    u32 b;
    val.s.b0 = 0;
    val.w |= cursor[0];
    b = cursor[1] << 8;
    val.w = b | (val.w & 0xFFFF00FF);
    b = cursor[2] << 16;
    val.w = b | (val.w & 0xFF00FFFF);
    b = cursor[3] << 24;
    val.w = b | (val.w & 0x00FFFFFF);
    state->unk28 = val.s;
    state->cursor = cursor + 4;
}
