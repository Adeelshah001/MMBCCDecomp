/* Wave 14 worker B: old_agbcc matches.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave14_B.md, docs/wave14_B_results.tsv.
 *
 * 0x0802567C (86 B) is emitted via BYTE() in ldscript.ld: GAS pads the
 * C section to 88 with c046, but ROM has 86 bytes. The verified bytes
 * are the old_agbcc output.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

/* Switch-driven IO register writes (0x4000063-0x400007D region).
 * Decisive idiom: old_agbcc omits push{lr} for true-leaf switch
 * (main agbcc emits it); interleaved pools fall out of barrier placement. */
__attribute__((section(".text.w14b_0804d130")))
void IoRegWrite_4D130(u8 a)
{
    u8 *p;
    switch (a) {
    case 1:
        p = (u8 *)0x4000063;
        *p = 8;
        p += 2;
        goto tail128;
    case 2:
        p = (u8 *)0x4000069;
        goto tail8;
    case 3:
        *(u8 *)0x4000070 = 0;
        return;
    default:
        p = (u8 *)0x4000079;
    tail8:
        *p = 8;
        p += 4;
    tail128:
        *p = 128;
        break;
    }
}

#if 0 /* Documented source for BYTE() block in ldscript.ld (GAS c046 tail
          pad does not match ROM). Not compiled. */
/* Search tables for 0xFF marker.
 * Decisive idiom: counter init before pointer init (i=1;p=a+2) for
 * exact instruction order. */
__attribute__((section(".text.w14b_0802567c")))
u8 SearchFF_2567C(u8 *a)
{
    u8 *p;
    s16 i;
    i = 1;
    p = a + 2;
    for (; i <= 9; i++) {
        if (p[i] == 0xFF)
            return (u8)i;
    }
    i = 0;
    p = a + 12;
    for (; i <= 1; i++) {
        if (p[i] == 0xFF)
            return (u8)(i + 10);
    }
    return 0;
}
#endif

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    u8 pad8[2];
    u16 field10;
    u32 field12;
    struct Node *field16;
} Node;

typedef struct {
    u8 pad[10];
    u16 count;
    u8 pad2[4];
    Node *free;
} ListHeader;

/* Allocate from free list and insert after node.
 * Decisive idiom: if(nw!=0){...}return nw falls through to r0=nw
 * (no mov r0,#0 for the null case). */
__attribute__((section(".text.w14b_08004484")))
Node *List_InsertAfter_4484(Node *node)
{
    ListHeader *h = *(ListHeader **)0x200081C;
    Node *nw = h->free;
    if (nw != 0) {
        h->free = nw->next;
        h->count--;
        nw->next = node->next;
        nw->prev = node;
        node->next->prev = nw;
        node->next = nw;
        nw->field10 = 0;
        nw->field12 = 0;
        nw->field16 = 0;
    }
    return nw;
}

/* Allocate from free list and insert before node. */
__attribute__((section(".text.w14b_080044bc")))
Node *List_InsertBefore_44BC(Node *node)
{
    ListHeader *h = *(ListHeader **)0x200081C;
    Node *nw = h->free;
    if (nw != 0) {
        h->free = nw->next;
        h->count--;
        nw->prev = node->prev;
        nw->next = node;
        node->prev->next = nw;
        node->prev = nw;
        nw->field10 = 0;
        nw->field12 = 0;
        nw->field16 = 0;
    }
    return nw;
}

/* Copy two u16 tables.
 * Decisive idiom: i=0 init before pointer loads (statement order). */
__attribute__((section(".text.w14b_08047c4c")))
void CopyTables_47C4C(void)
{
    u16 *dst;
    u16 *src;
    s16 i;
    i = 0;
    dst = (u16 *)0x200B74C;
    src = (u16 *)0x2000860;
    for (; i <= 4; i++)
        dst[i] = src[i];
    i = 0;
    dst = (u16 *)0x200B756;
    src = (u16 *)0x2000870;
    for (; i <= 24; i++)
        dst[i] = src[i];
}
