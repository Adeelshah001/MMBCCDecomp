extern u8 D_02004E40[];
extern u8 D_02004830[];
extern u8 (*const D_08173048[])(u8 *);
extern void sub_0800A150(u8 *);

void sub_0800A0D4(void)
{
    u8 *s = D_02004E40;
    u8 (*const *table)(u8 *) = D_08173048;
    unsigned int temp;
    int result;
    int test;
    u8 *b;
    temp = s[0];
    result = table[temp](s);
    test = 2;
    temp = s[0x13];
    test &= temp;
    if (test)
        result |= 0x80;
    s[4] = result;
    {
        int timerFlag = 8;
        result = s[0x1F];
        timerFlag &= result;
        if (!timerFlag && s[0x1C])
            s[0x1C]--;
    }
    b = D_02004830;
    temp = 0x264;
    if (b[temp])
        sub_0800A150(s);
    {
        int clear = -9;
        clear &= s[0x1F];
        s[0x1F] = clear;
    }
    {
        int clear = -2;
        temp = s[0x14];
        clear &= temp;
        result = -3;
        clear &= result;
        s[0x14] = clear;
    }
}
