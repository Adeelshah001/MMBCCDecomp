
struct LookupRecord0300C {
    u32 key;
    u16 value;
    u16 unk06;
};

struct LookupGroup0300C {
    const struct LookupRecord0300C *record;
    u32 unk04;
    u32 unk08;
};

extern const struct LookupGroup0300C D_08106D7C[];
extern const u8 D_08106DD0[];

void sub_08003134(u32 *state)
{
    state[1] = 0;
}

void sub_0800313C(u32 *state)
{
    state[0] = 0;
}

void sub_0800314C(u32 *state, u32 value, u32 *previous)
{
    *previous = *state;
    *state = value;
}

u16 sub_0800300C(u16 index)
{
    u32 shifted = (u32)index << 16;
    const struct LookupGroup0300C *groups = D_08106D7C;
    const u8 *entries = D_08106DD0;
    u32 offset = shifted >> 13;
    const struct LookupRecord0300C *entry = (const void *)(entries + offset);
    const struct LookupGroup0300C *group = &groups[entry->value];
    const struct LookupRecord0300C *record = group->record;
    if (record->key == entry->key)
        return record->value;
    return 0;
}
