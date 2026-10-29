/* Phase 3 Wave 9 batch A (1 matched C, old_agbcc, worker-verified).
 * ObjInit_1D3C0 @0x0801D3C0 (164 B incl. pool at 0x0801D460).
 * Object initializer with ChipSlot_Setup/IncUse; old_agbcc for the
 * else-branch prologue scheduler order.
 * Key idioms:
 * - Single volatile asm emitting `movs r0,#1; movs r1,#0` defeats the
 *   scheduler's insistence on zero-first materialization (old_agbcc
 *   otherwise emits `movs r1,#0` before `movs r0,#1`).
 * - `__asm__ volatile("" ::: "memory")` between `p += 0x50` and the
 *   store defeats the combiner's `s+0x50+28 -> s+108` fold, preserving
 *   ROM's `adds r0,#80; str r1,[r0,#28]`.
 * - Memory barriers between `s[10]|=1` and `*(s+108)=0` fix the
 *   str/strb scheduler reorder (if-branch).
 * - Shared `int m = -13` (BLK-A key) for s[0x41]/s[0x45]; separate
 *   `u8 *p`/`u8 *q` prevent adds-reuse.
 * Evidence: docs/match_notes_wave9_A.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);

__attribute__((section(".text.w9a_0801d3c0")))
void ObjInit_1D3C0(u8 *s)
{
    if (s[17] == 0) {
        s[10] |= 1;
        __asm__ volatile("" ::: "memory");
        *(u32 *)(s + 108) = 0;
        __asm__ volatile("" ::: "memory");
        s[10] |= 2;
        ChipSlot_Setup(s, 0x501, 0);
        ChipSlot_IncUse(s, 8);
        {
            u8 *p = s + 0x45;
            int m = -13;
            *p &= m;
        }
    } else {
        int one;
        int zero;
        u8 *p = s;
        __asm__ volatile("movs %0, #1\n\tmovs %1, #0" : "=l"(one), "=l"(zero));
        s[10] |= one;
        p += 0x50;
        __asm__ volatile("" ::: "memory");
        *(u32 *)(p + 28) = zero;
        s[10] |= 2;
        ChipSlot_Setup(s, 0x501, 0);
        ChipSlot_IncUse(s, 0);
        {
            u8 *p;
            u8 *q;
            int m;
            p = s + 0x41;
            m = -13;
            *p = (*p & m) | 4;
            q = s + 0x45;
            *q &= m;
        }
    }
    s[18] = 0;
    s[19] = 0;
    s[10] |= 1;
}
