struct Entry1DF {
    u32 unk00[4];
    u32 value;
};

extern struct Entry1DF *D_082243D8[];

void sub_0801DFAC(u8 *state)
{
    struct Entry1DF **table = D_082243D8;
    unsigned int index = state[9];
    struct Entry1DF **entry = table + index;
    *(u32 *)(state + 0xC) = 4;
    *(u32 *)(state + 0x14) = (*entry)->value;
}

extern void (*D_08233A44[])(u8 *);

void sub_080468EC(u8 *s)
{
    void (**tbl)(u8 *) = D_08233A44;
    u8 idx = s[2];
    tbl[idx](s);
}

u32 sub_08046DE4(void *s, u16 b)
{
    u32 result = 0;
    if (*(u16 *)((u8 *)s + 6) == b)
        result = 1;
    return result;
}
