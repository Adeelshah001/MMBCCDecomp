struct ChipSlot34C1C {
    u8 unk00;
    u8 pad01;
    u16 unk02;
};

struct State34C1C {
    u8 pad00[0x150];
    struct ChipSlot34C1C *slots0[7];
    struct ChipSlot34C1C *slots1[7];
};

struct PlayerData5168 {
    u8 pad00[2];
    u8 unk02[3];
    u8 unk05;
    u8 unk06;
    u8 pad07[0x0D];
};

extern struct PlayerData5168 D_02005168[2];
extern struct PlayerData5168 D_0200517C;
extern u8 sub_08034BD4(u8 a, u16 b);

void sub_08034C1C(struct State34C1C *state, u8 side)
{
    struct ChipSlot34C1C **slots;
    u32 addr;
    u32 val;
    u8 i;
    u8 *p1;
    u8 *p0;

    if (side == 0)
        slots = state->slots0;
    else
        slots = state->slots1;

    i = 3;
    p1 = D_02005168[1].unk02;
    p0 = D_02005168[0].unk02;

    do {
        val = (u32)slots[i];
        val = sub_08034BD4(((struct ChipSlot34C1C *)val)->unk00, ((struct ChipSlot34C1C *)val)->unk02);
        if (side != 0) {
            addr = i - 3;
            if (addr == 0xFF)
                goto next;
            addr += (u32)p1;
        } else {
            addr = i - 3;
            if (addr == 0xFF)
                goto next;
            addr += (u32)p0;
        }
        *(u8 *)addr = val;
next:
        i++;
    } while (i <= 5);

    if (side != 0) {
        D_0200517C.unk05 = 4;
        D_0200517C.unk06 = 4;
    } else {
        D_02005168[0].unk05 = 4;
        D_02005168[0].unk06 = 4;
    }
}
