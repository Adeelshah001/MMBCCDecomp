/* W61-C MATCH: 0x0801bc70, TRUE extent 268 B (code to bx @0x1bd78, pad
 * @0x1bd7a, next fn @0x1bd7c; pools mid-function @0x1bcc8=0x0822687c,
 * @0x1bd2c=0x08226880, @0x1bd30=0xffffe600). Template: w38c_0801bde4
 * (DD08 prologue, goto dispatch on s[13]). Differences vs template: case0
 * table load to s[19]; case1 has post-call s[19] test with r8=255 mask;
 * case2 adds IncUse(s,2); case3 has the inline (u8)(s[119]-3) test and
 * returns 1.
 * W61-C key vs W60-D BEST (268 B / 9 diffs old: prologue/epilogue r7-save
 * gap + pool-load vs d-truncation order):
 *  (1) t7 is a PLAIN s32, not pinned to r7 -- the allocator then uses r7
 *      for the 255/152<<6/pool temps and, with x kept live across the
 *      F_0801B98C call (see (3)), includes r7 in the prologue push set,
 *      so the r8 save goes through r7 exactly like the ROM
 *      (push {r4-r7,lr}; mov r7,r8; push {r7} / pop {r4-r7}).
 *      (Pinning t7 to r7 did NOT push r7 -- the known r7-pin poison --
 *      and pinning neg to r7 reintroduced the pool-load hoist.)
 *  (2) The 0xffffe600 constant is a separate plain int local `neg`,
 *      not a reuse of t7 -- the allocator then emits the pool load
 *      AFTER the d truncation (lsls/asrs on r3) into r7, as in the ROM,
 *      instead of hoisting it before the truncation.
 *  (3) An empty-asm "+r"(x) barrier after the F call (emits nothing,
 *      x unchanged -- same idiom as the pre-existing "+r"(y) barrier)
 *      keeps x live across the call; without it the combination above
 *      does not close the prologue gap (Jx blew up to 272 B, Jt stayed
 *      at 12 diffs). Pure C only; no .s patch, no r7 pin.
 * Verified: old_agbcc -O2 -mthumb-interwork, standalone linked-at-address
 * method, 268 B / 0 diffs.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void SetBit16(u8 *p, int bit);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void F_0801B98C(int a, u8 b, int c, s16 d, s16 e, u8 *f);
__asm__(".set F_0801B98C, 0x0801b98c");
extern void MaxAssign_17(u8 *p, int v);
extern u8 Tbl_0822687C[];
__asm__(".set Tbl_0822687C, 0x0822687c");
extern u8 Tbl_08226880[];
__asm__(".set Tbl_08226880, 0x08226880");

__attribute__((section(".text.w61c_0801bc70")))
u8 Sub_0801BC70(u8 *s)
{
    u32 out[2];
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = out[1];
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto ret0;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    s[18] = 1;
    s[19] = Tbl_0822687C[s[17]];
    goto tail;
c1:
    {
        register int mask __asm__("r8");
        s32 t7;
        s[18]--;
        t7 = 255;
        __asm__ volatile("" : "+r"(t7));
        mask = t7;
        if (s[18] != 0)
            goto ret0;
        {
            u8 b = Tbl_08226880[s[17]];
            int nib = ((u32)s[35] << 28) >> 28;
            s16 d;
            int draw;
            t7 = 152;
            t7 <<= 6;
            draw = x + t7;
            d = (s16)draw;
            {
                int neg = 0xffffe600;
                F_0801B98C(0, b, nib, d, (s16)(y + neg),
                    *(u8 **)(s + 44));
            }
            __asm__ volatile("" : "+r"(y));
            __asm__ volatile("" : "+r"(x));
        }
        ChipSlot_IncUse(s, 1);
        s[18] = 8;
        {
            int t = s[19] - 1;
            s[19] = t;
            if ((t & mask) != 0)
                goto ret0;
        }
        s[18] = 10;
        goto tail;
    }
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    ChipSlot_IncUse(s, 2);
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
__asm__(".hword 0");
