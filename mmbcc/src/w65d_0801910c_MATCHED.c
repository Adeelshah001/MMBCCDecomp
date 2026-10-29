/* MMBCCDecomp — 0x0801910C (STAGED by Worker D, Wave 65; coordinator lands).
 * MATCHED: old_agbcc -O2 -mthumb-interwork, 0 diffs over the 316 B true
 * extent (code 314 B + 2 pad). Main agbcc: 4 diffs (case3 scheduling).
 * Modelled on matched sibling w36a_0801b428 (same head idiom, same
 * s[10] two-statement bit-clear, same Vec2 call shapes).
 * True extent 316 B: code 0x1910C-0x19245 (314 B) + 2 pad (00 00) to
 * next function @0x19248. Pools are mid-function: 0x1915C = 0x080E9BFC
 * (memcpy src), jump table @0x19164, 0x19200 = 0xFFFFE200.
 * Codegen notes:
 * - Out words are a single u64 (register pair): s is r5, so the free
 *   pair is (r6,r7) = ROM's registers. Two s32s allocate r4/r6 (wrong).
 * - The u64's high half (out.y) is never read by game logic; the empty
 *   volatile asm on the whole u64 keeps it live (emits no code). An
 *   asm on (t>>32) alone emits a move (adds r0,r7,#0) and breaks the
 *   tail; pins to r6/r7 keep the loads but suppress save/restore.
 * - Case1 materializes buf[s[17]] BEFORE computing q, so arg0's loads
 *   precede q's adds (ROM order); q-as-prior-statement hoists the adds
 *   first (wrong order).
 * - Trailing .balign 4,0 gives the ROM pad (00 00); without it the
 *   linker emits a nop (46c0) as the trailing bytes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed char s8;

extern void *Memcpy_4DFA8(void *dst, const void *src, u32 len);
extern void Vec2_AddMirrored(void *o, s32 x, s32 y);
extern void *Vec2_CopyMirrored(void *d, void *s);
extern void SetBit16(u8 *s, u8 bit);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u32 sub_080178A8(u32 a, u32 b, u32 c, u32 d, u8 *e);
extern u8 GetField17_U8(u8 *s);

__attribute__((section(".text.w65d_0801910c")))
u32 Step_0801910C(u8 *s)
{
    u8 buf[12];
    u64 t;
    u8 *p;
    u8 *q;
    u8 v;
    u8 b0;

    Memcpy_4DFA8(buf, (const void *)0x080E9BFC, 3);
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored(buf + 4, s);
    t = *(u64 *)(buf + 4);
    SetBit16(*(u8 **)(s + 44), 3);
    switch (s[13]) {
    case 0:
        p = s; p += 119;
        if ((u8)(p[0] - 3) > 1)
            break;
        ChipSlot_IncUse(s, 1);
        *(u32 *)(s + 88) = 512;
        *(u32 *)(s + 96) = 0;
        *(u32 *)(s + 92) = -128;
        *(u32 *)(s + 100) = 8;
        s[13]++;
        break;
    case 1:
        if (*(s32 *)(s + 100) > 0) {
            if (*(s32 *)(s + 92) > 127)
                *(s32 *)(s + 100) = -8;
        } else if (*(s32 *)(s + 92) <= -128) {
            *(s32 *)(s + 100) = 8;
        }
        if ((s32)t <= 12800)
            break;
        b0 = buf[s[17]];
        q = s; q += 35;
        sub_080178A8(b0, (u32)(q[0] << 28) >> 28, 15360, 0xFFFFE200, *(u8 **)(s + 44));
        *(u32 *)(s + 88) = 0;
        *(u32 *)(s + 96) = 0;
        *(u32 *)(s + 92) = 0;
        *(u32 *)(s + 100) = 0;
        ChipSlot_IncUse(s, 2);
        s[13]++;
        break;
    case 2:
        p = s; p += 119;
        if ((u8)(p[0] - 3) > 1)
            break;
        s[13]++;
        break;
    case 3:
        v = s[10];
        v &= 253;
        v &= 254;
        s[10] = v;
        s[13]++;
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        return 1;
    }
    /* Keep t (both halves; high half otherwise dead) live; emits no code. */
    __asm__ volatile ("" : "+r" (t));
    return 0;
}
__asm__(".balign 4, 0");
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
__asm__(".set sub_080178A8, 0x080178a8");
