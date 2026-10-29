/* Wave 7 batch F (4 matched, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave7_f.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08010fb4: Entry_IsInactive (coordinator-verified). */
__attribute__((section(".text.w7f_08010fb4")))
u8 sub_08010FB4(u8 a) {
    u8 *p = (u8 *)0x020051C8 + a * 12;
    int b;
    if (p[0] != 0)
        return 0;
    __asm__ volatile("mov %0, #1\n\tldrsb %0, [%1, %0]" : "=l"(b) : "l"(p));
    if (b != 0)
        return 0;
    return 1;
}

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

__attribute__((section(".text.w7f_08004424")))
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

__attribute__((section(".text.w7f_08004424"))) static const u16 w7f_08004424_pad = 0;

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

__attribute__((section(".text.w7f_08004454")))
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

__attribute__((section(".text.w7f_08004454"))) static const u16 w7f_08004454_pad = 0;
