struct ChipState {
    u8 *inventory;
    u8 reserved04[16];
    u8 *decks;
};

extern struct ChipState D_02007090;
extern u8 sub_080258C0(u8 *, u16);
extern u8 sub_08026710(u8);
extern u8 sub_08025524(struct ChipState *, u8);
extern u8 sub_08025324(u8 *, u8);
extern void sub_08025EC8(u8 *, u8, u8);

u8 sub_08024818(u16 index)
{
    u8 *decks = D_02007090.decks;
    u8 *activeDeck = decks + 0x1B0;
    u8 slot = *activeDeck;
    return sub_080258C0(decks + slot * 0x90, index);
}

u8 TryAddChipToInventory(int rawIndex)
{
    u8 index = rawIndex;
    struct ChipState *state = &D_02007090;
    u8 result;

    if ((sub_08026710(index) & 2) == 0)
        result = sub_08025524(state, index);
    else
        result = 0;
    return result;
}

u8 GetChipInventoryCount(int rawIndex)
{
    u8 index = rawIndex;
    struct ChipState *state = &D_02007090;
    u8 result;

    if (index <= 248)
        result = sub_08025324(state->inventory, index);
    else
        result = 0;
    return result;
}

void sub_08024878(u8 index, u8 count)
{
    u8 *decks = D_02007090.decks;
    u8 *activeDeck = decks + 0x1B0;
    u8 slot = *activeDeck;
    sub_08025EC8(decks + slot * 0x90, index, count);
}
