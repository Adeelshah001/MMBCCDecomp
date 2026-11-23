typedef short s16;

struct SceneUpdateState {
    u8 unk00[0xC];
    u16 value0C;
    u16 value0E;
    u8 unk10[4];
    u8 mode;
    u8 unk15[3];
    s16 result;
};

struct SceneUpdateValues {
    u16 value0C;
    u8 unk02[0x12];
    u16 value0E;
};

extern struct SceneUpdateState D_02005130;
extern struct SceneUpdateValues D_02005168;
extern u32 D_02005270;
extern u32 D_020053C0;
extern void (*const D_081739BC[])(void);
extern void sub_08004F18(void);
extern void sub_08004F80(void);
extern void sub_0800D59C(u32);
extern void sub_0800EED4(void);

s16 sub_0800EA4C(void)
{
    struct SceneUpdateState *state;
    u32 stateAddressOrIndex;
    u8 mode;
    u32 offset;
    void (*const *updates)(void);

    sub_08004F18();
    stateAddressOrIndex = (u32)&D_02005130;
    mode = ((struct SceneUpdateState *)stateAddressOrIndex)->mode;
    if (mode != 6 && mode != 0xC && mode != 0xD) {
        struct SceneUpdateValues *values = &D_02005168;
        values->value0C = ((struct SceneUpdateState *)stateAddressOrIndex)->value0C;
        values->value0E = ((struct SceneUpdateState *)stateAddressOrIndex)->value0E;
    }
    updates = D_081739BC;
    state = &D_02005130;
    stateAddressOrIndex = state->mode;
    offset = stateAddressOrIndex * sizeof(*updates);
    (*(void (*const *)(void))((u32)updates + offset))();
    sub_0800D59C(D_02005270);
    sub_0800D59C(D_020053C0);
    sub_0800EED4();
    sub_08004F80();
    return state->result;
}
