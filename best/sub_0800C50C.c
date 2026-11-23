struct FadeState {
    u8 pad00[0x1C];
    u8 fade:7;
    u8 flag:1;
};

void sub_0800C50C(struct FadeState *state, u16 *pal) {
    u8 alpha = 0x10 - state->fade;
    short i;

    if (alpha <= 0x0F) {
        pal++;
        for (i = 1; i < 16; i++) {
            u16 color = *pal;
            u16 r = color & 0x001F;
            u16 g = color & 0x03E0;
            u16 b = color & 0x7C00;

            r = (u32)(r * alpha) >> 4;
            r &= 0x001F;
            g = (u32)(g * alpha) >> 4;
            g &= 0x03E0;
            b = (u32)(b * alpha) >> 4;
            b &= 0x7C00;
            *pal++ = b | (r | g);
        }
    }
}
