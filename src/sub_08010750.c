extern void sub_080062B4(u8, u8, u8, u8, u16, u16, u32);
extern void sub_080107CC(u8 *);
extern void sub_08010844(u8 *, u8);
extern u32 D_02003670;
extern const u32 D_08173E2C[];
extern u8 D_02005168[];

void sub_08010750(u8 *state)
{
    u32 temp = state[0x44];
    u32 active = -temp;
    int three;
    int shift;
    u8 *s;
    active |= temp;
    active >>= 31;
    temp = (u32)&D_02003670;
    three = 3;
    shift = three - active;
    temp = *(u32 *)temp;
    temp >>= shift;
    temp &= 1;
    sub_080062B4(13, 19, 4, 1, 0x20D, active ? three : 5, D_08173E2C[temp]);
    s = D_02005168;
    sub_080107CC(s);
    sub_08010844(s, 0);
    s += 20;
    sub_080107CC(s);
    sub_08010844(s, 1);
}
