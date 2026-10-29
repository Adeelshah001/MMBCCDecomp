/* W50-D 0x0800d59c (228 B) v2 — nested dispatch, int 0x40 block,
 * shift-pair idx/nib2, asm barrier vs sentinel CSE. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Node Node;
struct Node {
    u32 f0;
    Node *next;
    u8 pad[2];
    u8 f10;
    u8 f11;
};

typedef struct {
    u8 pad[12];
    Node *cur;
} Mgr;

extern u8 g_02005028;
extern u8 tbl_0200369c[];
__asm__(".set g_02005028, 0x02005028");
__asm__(".set tbl_0200369c, 0x0200369c");

extern void Sub_0800440C(u8 *mgr);
extern void Sub_08003E80(u8 *a, u8 b);
extern void Sub_08003B70(u8 *a, u8 b);
extern void Sub_08003874(u8 *a, u8 b);
extern void Sub_0800DB6C(u8 *a);
extern void Sub_0800DB40(u8 *a);
extern void Sub_08004188(u8 *a, u8 *b, int c, u8 d);
__asm__(".set Sub_0800440C, 0x0800440c");
__asm__(".set Sub_08003E80, 0x08003e80");
__asm__(".set Sub_08003B70, 0x08003b70");
__asm__(".set Sub_08003874, 0x08003874");
__asm__(".set Sub_0800DB6C, 0x0800db6c");
__asm__(".set Sub_0800DB40, 0x0800db40");
__asm__(".set Sub_08004188, 0x08004188");

__attribute__((section(".text.w50d_0800d59c")))
void Sub_0800D59C(Mgr *mgr)
{
    Node *cur;
    Sub_0800440C((u8 *)mgr);
    mgr->cur = mgr->cur->next;
    cur = mgr->cur;
    if (cur != (Node *)((u8 *)mgr + 20)) {
        u8 bit = 1;
        do {
            if ((cur->f10 & bit) != 0) {
                u8 *cur2 = (u8 *)cur + 48;
                if ((cur->f10 & 0x40) != 0) {
                    register int t __asm__("r1") = (g_02005028 & 31) << 1;
                    register int mask __asm__("r3") = ~62;
                    int x;
                    __asm__("mov %0, %1" : "=&r"(x) : "r"(mask));
                    x &= cur2[19];
                    cur2[19] = x | t;
                    if (g_02005028 <= 30)
                        g_02005028++;
                    if ((cur->f11 & bit) != 0) {
                        if ((cur->f11 & 2) != 0)
                            Sub_08003E80(cur2, ((u8 *)cur)[32]);
                        else
                            Sub_08003B70(cur2, ((u8 *)cur)[32]);
                    } else {
                        Sub_08003874(cur2, ((u8 *)cur)[32]);
                    }
                }
                Sub_0800DB6C((u8 *)cur);
                Sub_0800DB40((u8 *)cur);
                {
                    u8 b35 = ((u8 *)cur)[35];
                    int idx = (int)(((u32)b35 << 25) >> 29);
                    u8 *entry = tbl_0200369c + idx * 568;
                    int nib2 = (int)(((u32)cur2[21] << 28) >> 30);
                    Sub_08004188(entry, cur2, nib2, ((u8 *)cur)[34]);
                }
            }
            __asm__ volatile("" : "+r"(mgr));
            mgr->cur = mgr->cur->next;
            cur = mgr->cur;
        } while (cur != (Node *)((u8 *)mgr + 20));
    }
}
