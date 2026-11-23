typedef short s16;

struct PositionOffsets {
    s16 x;
    s16 y;
};

extern const struct PositionOffsets D_082270BC[];
extern void sub_0800D9FC(u8 *state);

void UpdateSelectionCursor(u8 *state)
{
    u8 *source = *(u8 **)(state + 0x28);
    int scanned = source[0];
    u8 selection = scanned;
    u8 phase = state[0xD];

    switch (phase) {
    case 0:
        if (scanned == 0xFF) {
            int clear = 0xFE;
            state[0xA] = clear & state[0xA];
        } else {
            int visible = 1;
            visible |= state[0xA];
            state[0xA] = visible;
            state[0xD]++;
            state[0x12] = selection;
        }
        break;
    case 1: {
        const u8 *offsets;
        u32 byteOffset;
        state[0xD] = 0;
        offsets = (const u8 *)D_082270BC;
        selection = state[0x12];
        byteOffset = selection * sizeof(struct PositionOffsets);
        *(u32 *)(state + 0x50) = (u32)*(const s16 *)(byteOffset + (u32)offsets) << 8;
        selection = state[0x12];
        byteOffset = selection * sizeof(struct PositionOffsets);
        offsets += sizeof(s16);
        *(u32 *)(state + 0x54) = (u32)*(const s16 *)(byteOffset + (u32)offsets) << 8;
        break;
    }
    }
    sub_0800D9FC(state);
}
