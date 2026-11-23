typedef u8 (*StateHandler4BC0)(u8 *);
extern u8 D_02003668[];
extern StateHandler4BC0 D_081705A4[];
extern s8 sub_08028778(u8 *state, u32 mode);
extern u16 *D_02003250;

extern u8 _call_via_r1(u8 *, StateHandler4BC0);
s8 sub_08004BC0(void)
{
    u8 *state = D_02003668;
    StateHandler4BC0 *table = D_081705A4;
    u32 index = *(volatile u8 *)state;
    StateHandler4BC0 handler = *(StateHandler4BC0 *)((index * 4) + (u32)table);
    state[4] = _call_via_r1(state, handler);
    return (s8)state[4];
}

void sub_080048B4(const volatile u8 *text, u32 column, u32 row)
{
    u16 *dest = D_02003250;
    u8 character;
    u16 tile;
    u16 baseLower;
    u16 baseUpper;

    if (row > 31)
        return;
    dest = (u16 *)((u32)dest + (column + (row << 5)) * 2);
    character = *text;
    if (character == 0)
        return;
    baseLower = 0x3A0;
    baseUpper = 0x2E0;
next:
    if (column > 31)
        return;
    if (character <= 0x9F)
        tile = baseLower + *text;
    else
        tile = baseUpper + *text;
    *dest = tile;
    text++;
    dest++;
    character = *text;
    if (character != 0)
        goto next;
}
