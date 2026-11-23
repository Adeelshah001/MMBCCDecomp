
extern u8 D_02000EC0[];
extern u16 D_020031E0;
extern u32 D_081734F4[];
extern u8 D_0817313C[];
extern u8 _call_via_r1(u8 *, u32);

void sub_0800C928(void)
{
}

void sub_0800CD00(void)
{
    u8 *state = D_02000EC0;
    if (!(state[9] & 4)) {
        D_020031E0 &= 0xC7FF;
        return;
    }
    D_020031E0 |= 0x3800;
}

void sub_0800CD38(void)
{
    u8 *state = D_02000EC0;
    u32 *handlers = D_081734F4;
    state[8] = _call_via_r1(state, handlers[state[0]]);
}

int sub_0800C248(short index)
{
    int id = index;
    int result = -1;

    if (id != -1 && id > 59)
        result = (s8)D_0817313C[id];
    return result;
}
