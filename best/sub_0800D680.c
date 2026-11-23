
extern u8 D_02004F80[];
extern u8 D_03002420[];
extern u8 D_02005030[];
extern u16 D_030027E0[];
extern u8 D_0000FFFF[];
extern u8 D_00000404[];
void sub_080006DC(u16, void *, u32);
void sub_0800D800(u8 *, int, u16, u8, int);

void sub_0800D598(void)
{
}

void sub_0800D680(void)
{
    short index = 0;
    u16 *buffer = (u16 *)0x030027E0;
    u8 *base = (u8 *)0x02005030;
    u32 mask = (u32)D_0000FFFF;
    u8 *last = base + 6;

loop:
    {
        int offset = index * 8;
        volatile u16 *first = (u16 *)((u32)base + offset);
        int old = *first;
        *first = old | mask;
        {
            volatile u16 *second = (u16 *)(offset + (u32)(base + 2));
            int old = *second;
            *second = old | mask;
        }
        {
            volatile u16 *third = (u16 *)(offset + (u32)(base + 4));
            int old = *third;
            *third = old | mask;
        }
        {
            volatile u16 *fourth = (u16 *)(offset + (u32)last);
            int old = *fourth;
            *fourth = old | mask;
        }
    }
    if (++index <= 31)
        goto loop;
    sub_080006DC(0xFFFF, buffer, 32);
}

void sub_0800D420(u8 enabled)
{
    u8 *state = D_02004F80;
    u8 *cursor;
    u16 index;
    u8 *palette;
    u8 zero;
    u8 saved = state[2];
    u32 step;
    cursor = state;
    index = 0;
    palette = D_03002420;
    zero = 0;

clear:
    *cursor++ = zero;
    step = 0x10000;
    index = (((u32)index << 16) + step) >> 16;
    if (index <= 3)
        goto clear;
    state[2] = saved;
    if (enabled != 0) {
        *(volatile u16 *)(palette + 0x404) = 0x20;
    } else {
        u32 offset = (u32)D_00000404;
        *(u16 *)(palette + offset) = enabled;
    }
    {
        u16 *entry;
        step = 0x406;
        entry = (u16 *)(palette + step);
        { u16 color = 0x3E0;
        *entry = color; }
    }
}

void sub_0800D728(u8 *sprite, int id, int frame)
{
    u16 spriteId = id;
    u8 frameId = frame;
    sub_0800D800(sprite, 2, spriteId, frameId, 0);
}
