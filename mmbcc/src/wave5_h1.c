/* Phase 3 Wave 5 POOL-H1 (2 matched C, coordinator-verified).
 * Evidence: docs/match_notes_wave5_h1.md. */

typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;

/* TableCall_BB78 @0x0800BB78 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 52 bytes in built ROM.
 * Indirect call through ROM tables 0x081731A0/0x0817313C, guarded by
 * *(s16*)(s+0x14) != -1. Idiom: declaring tbl/idx as locals assigned
 * inside the if gives ROM's regalloc (s->r3, v->r2) and pool order. */
extern u8 gTbl_0817313C[];
extern u32 gTbl_081731A0[];

__attribute__((section(".text.w5h_bb78")))
void TableCall_BB78(u8 *s)
{
    s16 v = *(s16 *)(s + 0x14);
    u32 *tbl;
    s8 idx;
    if (v != -1) {
        tbl = gTbl_081731A0;
        idx = gTbl_0817313C[v];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}

/* ListIterate_D568 @0x0800D568 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 46 bytes in built ROM.
 * Linked-list traversal: InitLinkedNode(s) setup, then iterates nodes
 * (next at +4, fn pointer at +0x14) calling each via _call_via_r1 until
 * back to the s+0x14 sentinel. Idiom: `if (p != s + 0x14)` with the
 * literal (not via an `end` variable) reproduces the r1->r5 move. */
extern void InitLinkedNode(u8 *s);

__attribute__((section(".text.w5h_d568")))
void ListIterate_D568(u8 *s)
{
    u8 *p;
    u8 *end;
    InitLinkedNode(s);
    p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
    *(u8 **)(s + 0xc) = p;
    if (p != s + 0x14) {
        end = s + 0x14;
        do {
            ((void (*)(u8 *))*(u32 *)(p + 0x14))(p);
            p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
            *(u8 **)(s + 0xc) = p;
        } while (p != end);
    }
}

__asm__(
    ".globl gTbl_0817313C\n.set gTbl_0817313C, 0x0817313C\n"
    ".globl gTbl_081731A0\n.set gTbl_081731A0, 0x081731A0\n"
);
