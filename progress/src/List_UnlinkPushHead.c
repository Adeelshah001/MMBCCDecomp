/* List_UnlinkPushHead @ 0x080044F4 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_j_old.c (registry: src/wave4_j_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct W4J_DNode { struct W4J_DNode *prev; struct W4J_DNode *next; };

struct W4J_List { u8 pad[10]; u16 count; u8 pad2[2]; struct W4J_DNode *head; };

/* 0x080044F4: unlink node from its doubly-linked list, then push it as
 * the new head of the global list (head at +0x10, u16 count at +0xA).
 * Tentative.
 * The `node->next->prev = node->prev; node->prev->next = node->next;`
 * shape is required: it forces the ROM's reload sequence
 * (ldr r2,[r0,#4]; ldr r1,[r0]; str r1,[r2]; ldr r2,[r0]; ldr r1,[r0,#4];
 * str r1,[r2,#4]) instead of a CSE'd two-register version.
 * old_agbcc keeps the dereferenced list pointer in r1 (ldr r1,[r1]);
 * main agbcc moves it to r2. */
__attribute__((section(".text.w4j_listunlinkpush")))
void List_UnlinkPushHead(struct W4J_DNode *node)
{
    struct W4J_List *list;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    list = *(struct W4J_List **)0x0200081C;
    node->prev = list->head;
    list->head = node;
    list->count++;
}
