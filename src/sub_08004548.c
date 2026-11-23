struct Fields4534 {
    u32 words[6];
    u16 halves[2];
};

void sub_08004534(struct Fields4534 *fields)
{
    fields->words[0] = fields->words[1] = fields->words[2] =
        fields->words[3] = fields->words[4] = fields->words[5] = 0;
    fields->halves[0] = fields->halves[1] = 0;
}

extern u8 D_02003250[];
extern const u8 D_0816E314[];
void sub_0800456C(void);

void sub_08004548(void *buffer)
{
    u8 *state = D_02003250;
    *(void **)state = buffer;
    *(const u8 **)(state + 0x414) = D_0816E314;
    sub_0800456C();
}

extern u16 D_020031E4;
extern u8 D_03002420[], D_06007800[];
extern const u8 D_0804E31C[], D_08055B3C[];
extern void sub_0804DB24(const void *, void *, u32);
extern void sub_080045AC(void);

void sub_0800456C(void)
{
    u32 offset = 0xC;
    offset &= D_020031E4;
    sub_0804DB24(D_08055B3C, D_06007800 + (offset << 12), 0x200);
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
    pool = D_0200081C;
    node->prev = pool->freeHead;
    pool->freeHead = node;
    pool->freeCount++;
}
