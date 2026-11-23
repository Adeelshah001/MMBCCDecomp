s8 RectOverlapsView(s8, s8, u8, u8);

extern const u8 D_082329E0[];

s8 sub_08040364(int arg0) {
    u32 index = (u32)(arg0 << 0x18) >> 0x16;
    return RectOverlapsView(
        *(s8*)(D_082329E0 + index),
        (s8)*(D_082329E0 + index + 1),
        *(D_082329E0 + index + 2),
        *(D_082329E0 + index + 3)
    );
}
