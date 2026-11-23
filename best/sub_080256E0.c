void sub_0802571C(u8 *entry, u8 id, u8 value)
{
    if (id < 200)
        return;
    {
        entry[1] = id;
        entry[0] = value;
    }
}

struct DeckEntry {
    u8 amount;
    unsigned id:8;
    u8 unk02[2];
};

struct DeckState257 {
    u8 unk00;
    u8 defaultId;
    u8 unk02[12];
    u16 base;
    u8 unk10[4];
    struct DeckEntry entries[30];
    u8 unk8C;
    u8 unk8D;
};

extern u8 sub_08025654(struct DeckState257 *, u8);
extern void sub_080255F4(struct DeckState257 *);
extern u32 sub_080266F0(u32);

u8 sub_08025730(struct DeckState257 *deck, u8 id)
{
    unsigned index = sub_08025654(deck, id);

    if (index == 0xFF)
        return 0;
    return ((struct DeckState257 *)((index << 2) + (u32)deck))->entries[0].amount;
}

void sub_080256E0(struct DeckState257 *deck)
{
    short i;
    u8 *end;
    sub_080255F4(deck);
    i = 0;
    do {
        struct DeckState257 *entry = (struct DeckState257 *)(((int)i * 4) + (u32)deck);
        entry->entries[0].amount = 0;
        entry->entries[0].id = 0xFF;
        i++;
    } while (i <= 29);
    end = &deck->unk8D;
    *end = 0;
    *(end - 1) = 0;
}

u16 sub_08025790(struct DeckState257 *deck)
{
    u32 id = sub_08025730(deck, 0);
    u32 value;
    if (id == 0)
        id = deck->defaultId;
    value = sub_080266F0(id);
    return value + deck->base;
}
