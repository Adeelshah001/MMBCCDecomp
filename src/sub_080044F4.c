extern volatile u16 D_020031E4;
extern u8 D_03002420[], D_06007800[];
extern const u8 D_0804E31C[], D_08055B3C[];
extern void sub_0804DB24(const void *, void *, u32);
extern void sub_080045AC(void);

void sub_0800456C(void)
{
    const u8 *tiles = D_08055B3C;
    volatile u16 *display = &D_020031E4;
    u32 offset = 0xC;
    offset &= *display;
    sub_0804DB24(tiles, D_06007800 + (offset << 12), 0x200);
    sub_0804DB24(D_0804E31C, D_03002420, 8);
    sub_080045AC();
}

struct ListNode44F4 {
    struct ListNode44F4 *prev;
    struct ListNode44F4 *next;
};

struct NodePool44F4 {
    u8 unk00[10];
    u16 freeCount;
    u8 unk0C[4];
    struct ListNode44F4 *freeHead;
};

extern struct NodePool44F4 *D_0200081C;

void sub_080044F4(struct ListNode44F4 *node)
{
    struct NodePool44F4 *pool;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    pool = (struct NodePool44F4 *)&D_0200081C;
    pool = *(struct NodePool44F4 **)pool;
    node->prev = pool->freeHead;
    pool->freeHead = node;
    pool->freeCount++;
}
