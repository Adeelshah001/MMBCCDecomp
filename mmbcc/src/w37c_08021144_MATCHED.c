/* W37-C MATCHED: 0x08021144, 168 B, old_agbcc, pure C, 0 diffs.
 * Jump-table state machine on
 * struct *s, returns void. Same family as 0x0804713c (dense switch,
 * shared fall-through tails, table of absolute addresses).
 * p40 = s[40]; p44 = s[44]; r5 = *p40; r6 = *p44; switch (s[13]):
 *  case 0: s[13]++; s[18] = 16; fall through to case 1;
 *  case 1: s[18]--; F(s, s[18]); if (s[18] != 0) goto tail;
 *    s[13]++; fall through to case 2;
 *  case 2: if (s[120] != r5) goto inc_tail; if (s[121] == r6)
 *    goto tail; (fall through to inc_tail);
 *  inc_tail (placed between case 2 and case 3): s[13]++; goto tail;
 *  case 3: F(s, s[18]); s[18]++; if ((u8)s[18] <= 15) goto tail;
 *    s[13]++; fall through to case 4;
 *  case 4: s[13] = 0; G(s); (fall through to tail, no default block;
 *    the dispatch bhi goes directly to tail for mode > 4);
 * tail: ChipSlot_Tick(s); return.
 * Extern callees + addresses: F_0802142C 0x0802142c (MATCHED),
 * G_0802129C 0x0802129c (unmatched, .set), ChipSlot_Tick
 * 0x0800d9fc (MATCHED).
 * Jump table (5 words, absolute): 0x08021178, 0x08021182,
 * 0x0802119c, 0x080211b8, 0x080211d4.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern void F_0802142C(u8 *s, u8 x);
__asm__(".set F_0802142C, 0x0802142c");
extern void G_0802129C(u8 *s);
__asm__(".set G_0802129C, 0x0802129c");
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w37c_08021144")))
void Sub_08021144(u8 *s)
{
    u8 *p40 = *(u8 **)(s + 40);
    u8 *p44 = *(u8 **)(s + 44);
    u8 r5 = *p40;
    u8 r6 = *p44;
    switch (s[13]) {
    case 0:
        s[13]++;
        s[18] = 16;
    case 1:
        s[18]--;
        F_0802142C(s, s[18]);
        if (s[18] != 0)
            goto tail;
        s[13]++;
    case 2:
        if (s[120] != r5)
            goto inc_tail;
        if (s[121] == r6)
            goto tail;
    inc_tail:
        s[13]++;
        goto tail;
    case 3:
        F_0802142C(s, s[18]);
        s[18]++;
        if ((u8)s[18] <= 15)
            goto tail;
        s[13]++;
    case 4:
        s[13] = 0;
        G_0802129C(s);
    }
tail:
    ChipSlot_Tick(s);
}

/* Trailing zero pad: ROM ends this 168 B section with 00 00 after bx;
 * without it GAS pads the section end with mov r8,r8 (0x46c0). */
__asm__(".hword 0x0000");
