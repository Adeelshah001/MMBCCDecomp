extern void sub_0804DB24(void *src, void *dst, u32 mode);
extern u8 gUnknown_0805633C[];
extern u16 gUnknown_020031E4[];
extern u8 gUnknown_06007000[];

void sub_080045F8(void)
{
    void *src = (void *)0x0805633C;
    u16 *flag = (u16 *)0x020031E4;
    void *dst_base = (void *)0x06007000;
    u32 mode = 0x200;
    u32 offset;
    void *dst;
    offset = (*flag & 0xC) << 12;
    dst = (void *)((u32)dst_base + offset);
    sub_0804DB24(src, dst, mode);
}

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
    u32 *head = (u32 *)(base + 0x410);
    u8 *node;
    u16 val;
    int count;
    *head = 0;
    node = base + 0x400;
    val = 0x37E;
    count = 0x4F;
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

struct ListHead *sub_08004484(struct ListHead *head)
{
    struct ListHead *global = D_0200081C;
    struct ListHead *node = global->first;
    if (node != 0) {
        global->first = node->next;
        global->count--;
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
        node->count = 0;
        node->unkC = 0;
        node->first = 0;
    }
    return node;
}

struct ListHead *sub_08004454(struct ListHead *head)
{
    struct ListHead *node = head->first;
    if (node != 0) {
        head->first = node->next;
        head->count--;
        node->prev = (struct ListHead *)((u8 *)head + 0x14);
        node->next = head->tail;
        head->tail->prev = node;
        head->tail = node;
        node->count = 0;
        node->unkC = 0;
        node->first = 0;
    }
    return node;
}
