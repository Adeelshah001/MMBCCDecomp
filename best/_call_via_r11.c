extern void sub_0804DD9C(void);

u32 DivZeroStub_4DD90(void)
{
    sub_0804DD9C();
    return 0;
}

void _call_via_r11(void (*fn)(void))
{
    fn();
}

void _call_via_r10(void (*fn)(void))
{
    fn();
}

void _call_via_r9(void (*fn)(void))
{
    fn();
}
