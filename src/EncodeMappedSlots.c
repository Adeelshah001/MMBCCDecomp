extern u8 sub_080258C0(u8 *state, u16 index);
extern void sub_08023A7C(u8 *key, u8 *bytes, u16 *code);

void EncodeMappedSlots(u8 *state, u8 *key, u16 *code)
{
    u8 bytes[16];
    s8 i;
    u8 *slots;

    bytes[0] = state[0];
    i = 0;
    slots = bytes + 1;
    for (; i <= 9; i++) {
        int index = i;
        u8 *entry = state + 2;
        entry = (u8 *)((u32)entry + index);
        slots[index] = sub_080258C0(state, *entry);
    }

    bytes[11] = sub_080258C0(state, state[12]);
    bytes[12] = sub_080258C0(state, state[13]);
    bytes[13] = 1;
    sub_08023A7C(key, bytes, code);
}
