extern s8 sub_08028778(u8 *phase, u8 mode);
extern void sub_08028874(u32 *state, u8 mode);
extern const u8 D_0822DDE0[];

void RunLinkHandshakeForMode(u8 *state)
{
    switch (state[2])
    {
    case 0:
    {
        u8 *phase = state + 3;
        const u8 *table = D_0822DDE0;
        u8 index = state[1];
        table = (const u8 *)(index + (u32)table);
        if (sub_08028778(phase, *table) != 0)
            break;
        state[2]++;
    }
    case 1:
        sub_08028874((u32 *)state, state[1]);
        break;
    }
}
