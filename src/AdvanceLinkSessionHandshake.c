typedef u8 (*StateHandler4BC0)(u8 *);
extern u8 D_02003668[];
extern StateHandler4BC0 D_081705A4[];
extern s8 sub_08028778(u8 *state, u32 mode);
extern u16 *D_02003250;

s8 sub_08004BC0(void)
{
    u8 *state = D_02003668;
    StateHandler4BC0 *table = D_081705A4;
    u32 index = state[0];
    StateHandler4BC0 handler = *(StateHandler4BC0 *)((index * 4) + (u32)table);
    state[4] = handler(state);
    return (s8)state[4];
}

int AdvanceLinkSessionHandshake(u8 *state)
{
    int result = sub_08028778(state + 1, 0);
    if (result == 0)
    {
        state[0]++;
        state[3] = result;
        state[2] = result;
        state[1] = result;
    }
    return 0;
}

void InitLinkSessionState(void)
{
    u8 *state = D_02003668;
    u8 *cursor = state;
    u32 index = 0;
    u8 zero = 0;

clear:
    *cursor++ = zero;
    index = ((index << 16) + 0x10000) >> 16;
    if (index <= 7)
        goto clear;
    state[4] = 0;
}

void sub_080048B4(const volatile u8 *text, u32 column, u32 row)
{
    u16 *dest = D_02003250;
    u8 character;
    u16 tile;

    if (row <= 31)
    {
        dest = (u16 *)((u32)dest + (column + (row << 5)) * 2);
        character = *text;
        while (character != 0)
        {
            if (column > 31)
                break;
            if (character <= 0x9F)
                tile = *text + 0x3A0;
            else
                tile = *text + 0x2E0;
            *dest++ = tile;
            text++;
            character = *text;
        }
    }
}
