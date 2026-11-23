typedef struct {
    u32 unk0;
    u8 status;
    u8 mode;
    u16 selection;
    u8 unk8[13];
    u8 selectionMode;
    u8 unk16[10];
    u32 unk20;
    u8 entries[1][16];
} SelectionState;

extern SelectionState D_02004E40;
extern void sub_080083F8(u32 b, u8 *p, int n, u8 c);
extern void sub_080082D8(u16 b, u8 *p, u8 c, int z);
extern void sub_0800B4C8(void);
extern void ResetSelectionDisplayEntries(void);
extern void sub_08007DE8(u32 a, u32 b);
extern void sub_08007C04(u32 a, u32 b);

void sub_0800B3F8(u8 index, u32 value, u8 mode)
{
    u32 offset = (u32)index << 24;
    u8 modeByte = (u8)(((u32)mode << 24) >> 24);
    u8 *base = (u8 *)&D_02004E40;

    offset >>= 20;
    offset += 36;
    offset += (u32)base;
    sub_080083F8(value, (u8 *)offset, 8, modeByte);
}

int sub_0800B3B0(u32 value)
{
    SelectionState *state = &D_02004E40;
    u8 status = state->status;

    if (!(status & 0xF)) {
        if (status & 0x80) {
            state->unk20 = value;
            state->mode = 3;
            ResetSelectionDisplayEntries();
            sub_0800B4C8();
            return 1;
        }
        state->mode = 1;
    }
    return 0;
}

void sub_0800B448(u8 index, u16 value, u8 mode)
{
    u32 offset = (u32)index << 24;
    u16 valueHalfword = (u16)(((u32)value << 16) >> 16);
    u8 modeByte = (u8)(((u32)mode << 24) >> 24);
    u8 *base = (u8 *)&D_02004E40;

    offset >>= 20;
    offset += 36;
    offset += (u32)base;
    sub_080082D8(valueHalfword, (u8 *)offset, modeByte, 0);
}

void sub_0800B470(u16 idx)
{
    SelectionState *s = &D_02004E40;
    u8 b = s->selectionMode;
    u32 v = ((u32)b << 28) >> 28;

    switch (v) {
    case 0:
        idx = 0;
        break;
    case 1:
    case 3:
        sub_08007DE8(idx, 0);
        break;
    case 2:
    case 4:
        sub_08007C04(idx, 0);
    default:
        break;
    }
    s->selection = idx;
}
