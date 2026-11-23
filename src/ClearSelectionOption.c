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
    int result;
    if (event <= 6)
    {
        state->pending = (1 << event) | state->pending;
        result = 1;
    }
    else
        result = 0;
    return result;
}

int ClearSelectionOption(int event)
{
    struct EventState363 *state = &D_0200BCE8;
    int pending = state->pending;
    int result;
    if ((pending >> event) & 1)
    {
        state->pending = pending ^ (1 << event);
        state->selection = ResolveSelectionOption(state->selection, 0, 0);
        result = 1;
    }
    else
        result = 0;
    return result;
}

s8 UpdateSelectionFromInput(u16 input)
{
    struct EventState363 *state = &D_0200BCE8;
    u8 selection = state->selection;
    if (1 & input)
        state->flags = 2 | state->flags;
    else
        state->selection = ResolveSelectionOption((s8)selection, input, 1);
    return state->selection;
}

void sub_080363EC(struct EventState363 *state)
{
    u8 previous = state->previous;
    u8 pending = state->pending;
    int changed = pending ^ previous;
    if (changed != 0)
    {
        int added = changed & pending;
        signed short event = 0;
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
