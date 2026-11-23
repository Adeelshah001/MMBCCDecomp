typedef void (*Dispatch0330C)(u8 *, u32);
extern Dispatch0330C D_0816E304[];

void sub_0800330C(u8 *state, u32 input)
{
    Dispatch0330C *table = D_0816E304;
    u32 offset = ((state[0x18] << 1) | state[0x19]) & 3;
    Dispatch0330C handler = *(Dispatch0330C *)((offset * 4) + (u32)table);
    handler(state, input);
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
        u16 index = ((const struct AudioId2FD4 *)((id * 8) + (u32)ids))->index;
        const struct AudioEntry2FD4 *song = (const struct AudioEntry2FD4 *)((index * 12) + (u32)songs);
        sub_0804C84C(song->song, 6);
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
    volatile u16 *display = (volatile u16 *)0x04000000;
    struct WindowState2E80 *state;
    volatile u16 control;
    volatile u32 *window;

    control = *display;
    control &= 0x1FFF;
    state = &D_02003230;
    control |= state->enable;
    *display = control;
    window = D_04000040;
    *window++ = state->horizontal;
    *window++ = state->vertical;
    *window = state->masks;
}

extern u8 D_03002830[];
extern volatile u32 D_040000D4[];
extern void sub_08002DCC(u32 value);

void InitOamShadowBuffer(void)
{
    u32 base = (u32)D_03002830;
    volatile u32 *dma;
    u32 fill;

    *(u32 *)(base + 0x404) = 0x1000;
    *(u32 *)(base + 0x400) = base;
    fill = 0x200;
    dma = D_040000D4;
    dma[0] = (u32)&fill;
    dma[1] = base;
    dma[2] = 0x85000100;
    sub_08002DCC(dma[2]);
}
