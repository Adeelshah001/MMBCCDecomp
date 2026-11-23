struct OamShadowState {
    u8 *cursor;
    u32 dispcntFlag;
};

extern struct OamShadowState D_03002C30;

void sub_08002DCC(void)
{
    volatile u16 control;
    volatile u16 *saved = &control;
    volatile u16 *display = (volatile u16 *)0x04000000;
    struct OamShadowState *state;
    u8 *cursor;
    u32 base;
    volatile u32 *dma;

    *saved = *display;
    state = &D_03002C30;
    cursor = state->cursor;
    control &= 0xEFFF;
    saved = &control;
    control = state->dispcntFlag | *saved;
    *display = control;
    base = (u32)state - 0x400;
    while ((u32)cursor < (u32)state) {
        *(u16 *)cursor = 0x200;
        cursor += 8;
    }
    dma = (volatile u32 *)0x040000D4;
    dma[0] = base;
    dma[1] = 0x07000000;
    dma[2] = 0x84000100;
    dma[2];
    *(u32 *)(base + 0x400) = base;
}
