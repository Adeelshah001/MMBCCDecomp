struct EventState363 {
    u8 unk0;
    s8 selection;
    u8 pending;
    u8 previous;
    u8 flags;
};
extern struct EventState363 D_0200BCE8;
extern s8 ResolveSelectionOption(s8 selection, u16 input, int update);
extern void sub_080217A8(u8 event);

int sub_08036318(u32 event)
{
    struct EventState363 *state = &D_0200BCE8;
    int result = 0;
    if (event <= 6)
    {
        state->pending = (1 << event) | state->pending;
        result = 1;
    }
    return result;
}

s8 UpdateSelectionFromInput(u16 input)
{
    struct EventState363 *state = &D_0200BCE8;
    u8 selection = state->selection;
    if (1 & input)
    {
        u32 flags = 2;
        flags |= state->flags;
        state->flags = flags;
    }
    else
        state->selection = ResolveSelectionOption((s8)selection, input, 1);
    return state->selection;
}

void sub_080363EC(struct EventState363 *state)
{
    u8 previous = state->previous;
    u8 pending = state->pending;
    if (previous != pending)
    {
        int added = pending;
        signed short event = 0;
        added ^= previous;
        added &= pending;
        do
        {
            if ((added >> event) & 1)
                sub_080217A8((u8)event);
            event++;
        } while (event <= 6);
        state->previous = state->pending;
        ResolveSelectionOption(state->selection, 0, 0);
    }
}
