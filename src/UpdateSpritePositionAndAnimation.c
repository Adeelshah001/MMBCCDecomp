
typedef signed int s32;

struct HandlerSet23278 {
    void (*handler[3])(u8 *);
};

struct SpritePosition23110 {
    s8 x;
    s8 y;
    u8 unk02[0x1D];
    u8 flags;
};

struct SpriteState23110 {
    u8 unk00[0x12];
    u8 timer;
    u8 unk13[0x15];
    struct SpritePosition23110 *position;
    u8 unk2C[0x24];
    s32 x;
    s32 y;
};

extern const struct HandlerSet23278 D_080E9C04;
void _call_via_r1(u8 *, void (*)(u8 *));
void sub_0800D9EC(struct SpriteState23110 *, int);
void sub_0800D9FC(struct SpriteState23110 *);

/* First block of the Thumb body. The project currently records only its prologue. */
void sub_08023304(u8 *state)
{
    u8 *record = *(u8 **)(state + 0x28);
    if (((s8 *)record)[1] == 0
        && ((u16 *)record)[1] == *(u32 *)(state + 0x58)
        && ((s8 *)record)[4] == *(s32 *)(state + 0x60)
        && ((s8 *)record)[5] == *(s32 *)(state + 0x64)
        && (record[7] & 4)) {
        state[0x0D] = 0;
        state[0x0E] = 0;
        state[0x0A] &= 0xFE;
    }
}

void sub_08023278(u8 *state)
{
    struct HandlerSet23278 local = D_080E9C04;
    u8 index = state[0xD];
    u32 offset = index * sizeof(local.handler[0]);
    void (**entry)(u8 *) = (void (**)(u8 *))((u8 *)&local + offset);
    _call_via_r1(state, *entry);
}

void sub_08023264(u8 *state)
{
    u8 flags;
    *(u32 *)(state + 0x6C) = 0;
    flags = 2;
    flags |= state[0xA];
    flags &= 0xFE;
    state[0xA] = flags;
}

void UpdateSpritePositionAndAnimation(struct SpriteState23110 *state)
{
    struct SpritePosition23110 *position = state->position;
    int flags = position->flags;
    if (8 & flags) {
        int mask = -9;
        mask &= flags;
        position->flags = mask;
        sub_0800D9EC(state, 1);
        state->timer = 4;
    } else {
        u32 timer = state->timer;
        if (timer != 0) {
            --timer;
            state->timer = timer;
            if ((timer << 24) == 0)
                sub_0800D9EC(state, 0);
        }
    }
    state->x = (position->x + 7) * 2048;
    state->y = position->y * 2048;
    sub_0800D9FC(state);
}
