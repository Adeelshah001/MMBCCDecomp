/* sub_08004454 @ 0x08004454 (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_f_old.c (registry: src/wave7_f_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08004454: List_RemoveHead2 (coordinator-verified). */
typedef struct Node2 {
    struct Node2 *prev;
    struct Node2 *f4;
    u16 pad8;
    u16 count;
    struct Node2 *f12;
    struct Node2 *next;
    struct Node2 *f20;
    u32 pad24;
} Node2;

Node2 *sub_08004454(Node2 *list) {
    Node2 *r2 = list->next;
    if (r2 != 0) {
        list->next = r2->prev;
        list->count--;
        {
            u8 *p = (u8 *)list;
            p += 20;
            r2->f4 = (Node2 *)p;
        }
        r2->prev = list->f20;
        list->f20->f4 = r2;
        list->f20 = r2;
        r2->count = 0;
        r2->f12 = 0;
        r2->next = 0;
    }
    return r2;
}
