typedef void (*Dispatch0330C)(u8 *, u32);
extern Dispatch0330C D_0816E304[];
extern void _call_via_r2(u8 *, u32, Dispatch0330C);

void sub_0800330C(u8 *state, u32 input)
{
    Dispatch0330C *table = D_0816E304;
    u32 offset = ((state[0x18] << 1) | state[0x19]) & 3;
    Dispatch0330C handler = *(Dispatch0330C *)((offset * 4) + (u32)table);
    _call_via_r2(state, input, handler);
}

struct AudioEntry2FD4 {
    const void *song;
    u32 unk04[2];
};
struct AudioId2FD4 {
    u16 unk00[2];
    u16 index;
    u16 unk06;
};
extern const struct AudioEntry2FD4 D_08106D7C[];
extern const struct AudioId2FD4 D_08106DD0[];
extern int sub_0800300C(u16 id);
extern void sub_0804C84C(const void *song, int mode);

void sub_08002FD4(u16 id)
{
    if (sub_0800300C(id))
    {
        const struct AudioEntry2FD4 *songs = D_08106D7C;
        const struct AudioId2FD4 *ids = D_08106DD0;
        u32 offset = (u32)id << 3;
        u32 index;
        offset += (u32)ids;
        index = ((const struct AudioId2FD4 *)offset)->index;
        offset = index * 12;
        offset += (u32)songs;
        sub_0804C84C(((const struct AudioEntry2FD4 *)offset)->song, 6);
    }
}

struct WindowState2E80 {
    u16 enable;
    u16 unk02;
    u32 horizontal;
    u32 vertical;
    u32 masks;
};
extern struct WindowState2E80 D_02003230;
extern volatile u32 D_04000040[];

void sub_08002E80(void)
{
    volatile u16 control;
    volatile u16 *saved = &control;
    struct WindowState2E80 *state;
    u32 window;

    *saved = *(volatile u16 *)0x04000000;
    control &= 0x1FFF;
    control |= D_02003230.enable;
    state = &D_02003230;
    *(volatile u16 *)0x04000000 = control;
    window = (u32)D_04000040;
    *(volatile u32 *)window = state->horizontal;
    *((volatile u32 *)window + 1) = state->vertical;
    *((volatile u32 *)window + 2) = state->masks;
}

