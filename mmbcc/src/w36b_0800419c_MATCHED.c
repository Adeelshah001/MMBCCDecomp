/* Wave 36-B MATCHED: 0x0800419c, 108 B, old_agbcc -O2 -mthumb-interwork, pure C.
   Extent basis: next function start 0x08004208 (func_list v2) - 0x0800419c = 108,
   no literal pool. Variant count: 1 (v1 first try).
   Key idioms: struct P with arr[4][32] of Node* plus a/b at +512/+516;
   24-byte stack buffer passed as sp; int outer loop i=0..3, short inner
   loop j=0..31 (shifted-counter form); linked-list walk via node->next.
   Callees: Sub_080030C4 (BLOCKED in registry) + Sub_0804DCD4 (unmatched),
   both via .set.
   Harness: ./verify.sh 0x0800419c 108 .text.w36b_0800419c
   w36b_0800419c_MATCHED.c old -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Node { struct Node *next; u32 f4; };
struct P { struct Node *arr[4][32]; struct Node *a; struct Node *b; };

extern void Sub_080030C4(u8 *buf, struct Node *a, struct Node *b);
__asm__(".set Sub_080030C4, 0x080030c4");
extern void Sub_0804DCD4(struct Node *node, u8 *buf, u32 f4);
__asm__(".set Sub_0804DCD4, 0x0804dcd4");

__attribute__((section(".text.w36b_0800419c")))
void Sub_0800419C(struct P *p)
{
    u8 buf[24];
    struct Node *a = p->a;
    if (a != 0) {
        struct Node *b = p->b;
        int i;
        Sub_080030C4(buf, a, b);
        for (i = 0; i <= 3; i++) {
            short j;
            for (j = 0; j <= 31; j++) {
                struct Node *node = p->arr[i][j];
                while (node != 0) {
                    Sub_0804DCD4(node, buf, node->f4);
                    node = node->next;
                }
            }
        }
    }
}
