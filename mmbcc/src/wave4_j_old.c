/* MMBCCDecomp — Wave 4 batch J (worker J).
 * MATCHED 2026-10-20. 4/5 real functions byte-identical.
 *
 * COMPILER: all four functions in this file REQUIRE old_agbcc
 * (mmbcc/tools/agbcc/bin/old_agbcc -O2 -mthumb-interwork). Main agbcc
 * mis-allocates registers for each (see notes below); old_agbcc matches
 * the ROM exactly. Precedent: mmbcc/src/wave3_e_old.c (ConstZeroS16_2472C).
 * Suggested Makefile rule (coordinator): $(BUILD)/wave4_j_old.o from
 * this file with $(OLDAGBCC), or split into wave4_j_old.c.
 *
 * Functions (all names tentative — inferred from behavior only):
 *  0x080044F4 List_UnlinkPushHead (36 B) unlink node from doubly-linked
 *               list; push onto global list head at *(0x0200081C)+0x10;
 *               increment u16 count at +0xA. 29 table refs, 0 bl callers.
 *  0x08011E98 Obj_SetFromTableA  (24 B) *(u32*)(obj+12)=4;
 *               *(u32*)(obj+20)=gTbl_08223CC0[obj[9]]->w10. 2 table refs.
 *  0x08017084 Obj_SetFromTableB  (24 B) idem with gTbl_082243D8. 19 refs.
 *  0x08020F58 Obj_SetFromTableC  (24 B) idem with gTbl_08226EF0. 8 refs.
 *
 * The 25 thunk-span v2.4 entries (0x0802BCE2-0x0802C71E) plus 0x08033962
 * are INTERIOR long-branch targets, NOT functions — see
 * docs/match_notes_wave4_j.md. They are not in this file.
 * 0x0804C4FC is BLOCKED (lr-push quirk) — see match notes.
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct W4J_DNode { struct W4J_DNode *prev; struct W4J_DNode *next; };
struct W4J_List { u8 pad[10]; u16 count; u8 pad2[2]; struct W4J_DNode *head; };
struct W4J_TblEntry { u8 pad[0x10]; u32 val10; };

extern struct W4J_TblEntry *gTbl_08223CC0[];
extern struct W4J_TblEntry *gTbl_082243D8[];
extern struct W4J_TblEntry *gTbl_08226EF0[];

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

/* 0x08011E98: *(u32*)(obj+12)=4; *(u32*)(obj+20)=table[obj[9]]->val10.
 * Tentative.
 * The `base` + `&base[obj[9]]` two-statement shape is required for the
 * ROM's order (pool load, ldrb, lsls, adds, then the =4 store, then the
 * double deref). old_agbcc puts the index byte in r3; main agbcc uses r1.
 * Sections .text.w4j_objsetfromtablea/b/c. */
__attribute__((section(".text.w4j_objsetfromtablea")))
void Obj_SetFromTableA(u8 *obj)
{
    struct W4J_TblEntry **base = gTbl_08223CC0;
    struct W4J_TblEntry **slot = &base[obj[9]];
    *(u32 *)(obj + 12) = 4;
    *(u32 *)(obj + 20) = (*slot)->val10;
}

/* 0x08017084: idem with gTbl_082243D8. Tentative. */
__attribute__((section(".text.w4j_objsetfromtableb")))
void Obj_SetFromTableB(u8 *obj)
{
    struct W4J_TblEntry **base = gTbl_082243D8;
    struct W4J_TblEntry **slot = &base[obj[9]];
    *(u32 *)(obj + 12) = 4;
    *(u32 *)(obj + 20) = (*slot)->val10;
}

/* 0x08020F58: idem with gTbl_08226EF0. Tentative. */
__attribute__((section(".text.w4j_objsetfromtablec")))
void Obj_SetFromTableC(u8 *obj)
{
    struct W4J_TblEntry **base = gTbl_08226EF0;
    struct W4J_TblEntry **slot = &base[obj[9]];
    *(u32 *)(obj + 12) = 4;
    *(u32 *)(obj + 20) = (*slot)->val10;
}

__asm__(
    ".globl gTbl_08223CC0\n.set gTbl_08223CC0, 0x08223CC0\n"
    ".globl gTbl_082243D8\n.set gTbl_082243D8, 0x082243D8\n"
    ".globl gTbl_08226EF0\n.set gTbl_08226EF0, 0x08226EF0\n"
);
