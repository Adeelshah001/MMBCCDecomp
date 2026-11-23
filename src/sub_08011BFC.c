
int sub_08011BDE(int value)
{
    return value;
}

void sub_08011BFC(void)
{
}

void sub_08011C00(void)
{
}

struct WorkBuffers_02005260 {
    u8 *unk0;
    u8 *first;
    u8 *second;
};

void sub_08011C14(void)
{
    struct WorkBuffers_02005260 *buffers = (void *)0x02005260;
    short i;
    for (i = 0; i <= 15; i++)
        buffers->first[i] = 0;
    for (i = 0; i <= 7; i++)
        buffers->second[i] = 0;
}
