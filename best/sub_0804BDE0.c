/* Node structure for the doubly-linked list */
typedef struct Node {
    u8 pad[0x2C];
    struct Node *next;   // +0x2C
    struct Node *prev;   // +0x30
    struct Node *x;      // +0x34
} Node;

/* Container structure for sub_0804BDE0 */
typedef struct Container {
    u8 unk0;             // +0x00
    u8 pad1[0x1F];
    Node *head;          // +0x20
} Container;

/* sub_0804BDE0 - iterate list via x pointers, call sub_0804BDC0 on each */
/* First parameter comes in r1, so use dummy first parameter */
void sub_0804BDE0(int dummy, Container *c) {
    Node *n;
    u8 val;
    
    n = c->head;
    if (n != 0) {
        do {
            val = n->pad[0];
            if (val & 0xC7) {
                n->pad[0] = val | 0x40;
            }
            sub_0804BDC0(n);
            n = n->x;
        } while (n != 0);
    }
    c->unk0 = 0;
}
