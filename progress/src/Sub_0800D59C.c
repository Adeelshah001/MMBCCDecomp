/* Sub_0800D59C @ 0x0800D59C (228 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_0800d59c_MATCHED.c (registry: src/w50d_0800d59c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

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

extern void InitLinkedNode(u8 *mgr);

extern void F_08003e80(u8 *a, u8 b);

extern void F_08003b70(u8 *a, u8 b);

extern void F_08003874(u8 *a, u8 b);

extern void sub_0800DB6C(u8 *a);

extern void ProcByte_DB40(u8 *a);

extern void SwapPtr_08004188(u8 *a, u8 *b, int c, u8 d);

__attribute__((section(".text.w50d_0800d59c")))
void Sub_0800D59C(Mgr *mgr)
{
    Node *cur;
    InitLinkedNode((u8 *)mgr);
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
                            F_08003e80(cur2, ((u8 *)cur)[32]);
                        else
                            F_08003b70(cur2, ((u8 *)cur)[32]);
                    } else {
                        F_08003874(cur2, ((u8 *)cur)[32]);
                    }
                }
                sub_0800DB6C((u8 *)cur);
                ProcByte_DB40((u8 *)cur);
                {
                    u8 b35 = ((u8 *)cur)[35];
                    int idx = (int)(((u32)b35 << 25) >> 29);
                    u8 *entry = tbl_0200369c + idx * 568;
                    int nib2 = (int)(((u32)cur2[21] << 28) >> 30);
                    SwapPtr_08004188(entry, cur2, nib2, ((u8 *)cur)[34]);
                }
            }
            __asm__ volatile("" : "+r"(mgr));
            mgr->cur = mgr->cur->next;
            cur = mgr->cur;
        } while (cur != (Node *)((u8 *)mgr + 20));
    }
}
