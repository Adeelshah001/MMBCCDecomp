
extern u8 D_02005160[];
extern u8 D_02005130[];
void sub_08010508(int);
void sub_0801052C(void);
void sub_08010724(u8 *);
void sub_08010ACC(u8 *);
u8 sub_08010478(u8);
void sub_0800E1F0(u8);

u8 sub_0800EF3C(u8 *state)
{
    return *state;
}

void InitSceneWorkState(void)
{
    u8 *state = D_02005160;
    u8 *cursor = state;
    u32 index = 0;
    u8 zero = 0;
clear:
    *cursor++ = zero;
    index = ((index << 16) + 0x10000) >> 16;
    if (index <= 75)
        goto clear;
    sub_08010508(0);
    sub_0801052C();
    sub_08010724(state);
    sub_08010ACC(state);
}

void sub_0800EE50(void)
{
    u8 *state = D_02005160;
    u8 *flag = state + 0x44;
    u8 next = *flag + 1;
    u8 value = 0;
    if (next <= 1)
        value = 1;
    *flag = value;
}

s8 sub_0800EDB0(u8 input)
{
    register int flag;
    u8 *dst;
    s8 result;
    if (((u32)input << 24) == 0)
        flag = 0;
    else
        flag = 1;

    dst = D_02005130;
    dst += 0x2B;
    *dst = flag;
    result = sub_08010478(flag);
    if (result == 1) {
        sub_0800E1F0(17);
        return 1;
    }
    return result;
}
