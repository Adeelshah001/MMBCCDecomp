extern u8 D_02003250[];

struct ListHead {
    struct ListHead *next;
    struct ListHead *prev;
    u8 pad8[2];
    u16 count;
    u32 unkC;
    struct ListHead *first;
    struct ListHead *tail;
};

extern struct ListHead *D_0200081C;

void sub_080045AC(void)
{
    u8 *base = D_02003250;
    u32 *head;
    u8 *node;
    int val;
    int count;
    head = (u32 *)(base + 0x410);
    *head = 0;
    count = 0x4F;
    node = base;
    node = node + 0x400;
    val = 0x37E;
    do {
        *(u16 *)(node + 6) = val;
        *(u32 *)node = *head;
        *head = (u32)node;
        node -= 8;
        val -= 2;
        count -= 1;
    } while (count >= 0);
    *(u32 *)(base + 0x408) = 0;
    *(u32 *)(base + 0x40C) = 0;
    *(u32 *)(base + 4) = 0;
}
