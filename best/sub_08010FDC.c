struct SceneRequest {
    u8 pad[4];
    u8 mode;
    u8 option;
    u16 value;
    u32 resource;
    u8 selection;
    u8 padD[2];
    u8 flags;
};

extern struct SceneRequest D_020051B0;
void sub_080111B4(int);
void sub_0800B3EC(u32, u32, u32);

int sub_08010FDC(u8 option, u16 value, u32 resource, u32 slot, u32 parameter, u32 mode)
{
    struct SceneRequest *state = &D_020051B0;
    if (state->mode == 1) {
        int flags;
        u32 bit;
        sub_080111B4(2);
        state->resource = resource;
        state->option = option & 0xF;
        bit = (option >> 7) << 1;
        flags = ~2;
        flags &= state->flags;
        flags |= bit;
        bit = ((option >> 6) & 1) << 2;
        flags &= ~4;
        flags |= bit;
        state->flags = flags;
        state->value = value;
        state->selection = 0xFF;
        sub_0800B3EC(slot, parameter, mode);
        return 1;
    }
    return 0;
}
