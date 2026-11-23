/* identical to sub_08004170 (matched), with its names changed by decompdecomp */
/* ListPushFront @ 0x08004170 (8 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Singly-linked list push-front (TENTATIVE name).
 * ROM 0x08004170 (8 B): node->next = *head; *head = node.
 * Callers: sub_080093D0, sub_08009490, sub_0800954C. */
void sub_08003144(void **head, void *node)
{
    void *old = *head;
    *(void **)node = old;
    *head = node;
}
