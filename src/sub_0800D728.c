
extern u8 D_02004F80[];
extern u8 D_03002420[];
extern u8 D_02005030[];
extern u16 D_030027E0[];
extern u8 D_0000FFFF[];
void sub_080006DC(u16, void *, u32);
void sub_0800D800(u8 *, int, u16, u8, int);

void sub_0800D598(void)
{
}

void sub_0800D680(void)
{
    short index = 0;
    u16 *buffer = D_030027E0;
    u8 *base = D_02005030;
    u16 mask = (u32)D_0000FFFF;

    do {
        int offset = index * 8;
        *(u16 *)(offset + (u32)base) |= mask;
        *(u16 *)(offset + (u32)(base + 2)) |= mask;
        *(u16 *)(offset + (u32)(base + 4)) |= mask;
        *(u16 *)(offset + (u32)(base + 6)) |= mask;
    } while (++index <= 31);
    sub_080006DC(mask, buffer, 32);
}

void sub_0800D420(u8 enabled)
{
    u8 *state = D_02004F80;
    u8 saved = state[2];
    u8 *cursor = state;
    u16 index = 0;
    u8 *palette = D_03002420;
    u8 zero = 0;

clear:
    *cursor++ = zero;
    if (++index <= 3)
        goto clear;
    state[2] = saved;
    if (enabled != 0) {
        *(u16 *)(palette + 0x404) = 0x20;
    } else {
        *(u16 *)(palette + 0x404) = enabled;
    }
    *(u16 *)(palette + 0x406) = 0x3E0;
}

void sub_0800D728(u8 *sprite, int id, int frame)
{
    u16 spriteId = id;
    u8 frameId = frame;
    sub_0800D800(sprite, 2, spriteId, frameId, 0);
}
