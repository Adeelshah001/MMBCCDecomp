struct SlotGroup2FCFC {
    void *unused[3];
    const short *slots[3];
};

int FindActiveSideSlot(u8 *state, u8 side)
{
    const struct SlotGroup2FCFC *group;
    const short *slot;
    int result;

    if (side == 0)
        group = (const struct SlotGroup2FCFC *)(state + 0x150);
    else
        group = (const struct SlotGroup2FCFC *)(state + 0x16C);

    result = 2;
    slot = group->slots[0];
    if (slot && slot[2] && slot[1]) {
        result = 3;
    } else {
        slot = group->slots[1];
        if (slot && slot[2] && slot[1]) {
            result = 4;
        } else {
            slot = group->slots[2];
            if (slot && slot[2] && slot[1])
                result = 5;
        }
    }

    return result;
}
