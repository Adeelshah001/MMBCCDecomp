/* sub_08004424 @ 0x08004424 (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_f_old.c (registry: src/wave7_f_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08004424: List_RemoveHead (coordinator-verified). */
typedef struct Node {
    struct Node *prev;
    struct Node *f4;
    u16 pad8;
    u16 count;
    struct Node *f12;
    struct Node *next;
    u32 f20;
    struct Node *f24;
} Node;

Node *sub_08004424(Node *list) {
    Node *r2 = list->next;
    if (r2 != 0) {
        list->next = r2->prev;
        list->count--;
        {
            u8 *p = (u8 *)list;
            p += 20;
            r2->prev = (Node *)p;
        }
        r2->f4 = list->f24;
        list->f24->prev = r2;
        list->f24 = r2;
        r2->count = 0;
        r2->f12 = 0;
        r2->next = 0;
    }
    return r2;
}
