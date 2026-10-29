/* Wave 11 worker B: bulk leaves-up, second half (TAG=B).
 * 7 functions matched byte-identical (all need old_agbcc).
 * See docs/match_notes_wave11_B.md for the idiom catalog.
 *
 * Findings baked into this source:
 * - old_agbcc leaf epilogue: old_agbcc emits pure-leaf `bx lr` for branched
 *   leaves; main agbcc emits `push {lr}`/`pop`+`bx`. All 7 need old_agbcc.
 * - s16-param HI-normalized idiom: `lsls r1,r1,#16; lsrs r2,r1,#16`
 *   (cross-register) signals an `s16`/`short` param; per-use signed (`asrs`)
 *   vs unsigned (`lsrs`) extends.
 * - Pure-u32 address arithmetic defeats ptr-first canonicalization:
 *   `addr = (u32)(u16)idx * 28 + (u32)base; entry = (u8 *)addr;` yields ROM's
 *   `adds r1, r1, r0` (offset-first); plain `base + off` pointer arithmetic
 *   always canonicalizes to `adds r1, r0, r1`.
 * - Pool-load hoisting: declaring a pool-backed pointer at function top
 *   hoists the `ldr` before early-exit branches; moving it into a block after
 *   the first check reproduces ROM's post-branch pool load (sub_08001e74).
 * - CSE beats temp: `u16 v = str[i]` forces an extra `add r1, r0, #0`;
 *   using `str[i]` directly lets old_agbcc CSE the two loads into one
 *   (sub_08023b88).
 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

/* 0x08026554 (32 B): table-entry byte getter. Returns entry[1] of the
 * 28-byte table at *(ctx+4), or 0 if idx > 127 or entry[25] == 0.
 * Priority pick for the Task_3AFFC path: called from sub_080241F8 case 2
 * as sub_08026554(0x020070A8, a & 0xFFF). Signature: u8 (void *ctx, s16 idx). */
__attribute__((section(".text.w11b_08026554")))
u8 GetByte1_26554(void *ctx, s16 idx)
{
    u8 *base;
    u8 *entry;
    u32 addr;
    if ((u16)idx > 127)
        return 0;
    base = *(u8 **)((u8 *)ctx + 4);
    addr = (u32)(u16)idx * 28 + (u32)base;
    entry = (u8 *)addr;
    if (entry[25] == 0)
        return 0;
    return entry[1];
}

/* 0x080265B0 (32 B): twin of 26554. Returns entry[0], or 49 if idx > 127
 * or entry[25] == 0. Called from sub_08024384 case 2.
 * Signature: u8 (void *ctx, s16 idx). */
__attribute__((section(".text.w11b_080265b0")))
u8 GetByte0_265B0(void *ctx, s16 idx)
{
    u8 *base;
    u8 *entry;
    u32 addr;
    if ((u16)idx > 127)
        return 49;
    base = *(u8 **)((u8 *)ctx + 4);
    addr = (u32)(u16)idx * 28 + (u32)base;
    entry = (u8 *)addr;
    if (entry[25] == 0)
        return 49;
    return entry[0];
}

/* 0x080265D0 (34 B): returns &entry[14] of the same 28-byte table,
 * or NULL if idx > 127 or entry[25] == 0. */
__attribute__((section(".text.w11b_080265d0")))
u8 *GetPtr14_265D0(void *ctx, s16 idx)
{
    u8 *base;
    u8 *entry;
    u32 addr;
    if ((u16)idx > 127)
        return 0;
    base = *(u8 **)((u8 *)ctx + 4);
    addr = (u32)(u16)idx * 28 + (u32)base;
    entry = (u8 *)addr;
    if (entry[25] == 0)
        return 0;
    return entry + 14;
}

/* 0x0804AC88 (36 B incl pool): byte pokes at 0x0200BD20.
 * p[127] = 0; p[126] = 0; p[160]++; p[161] = a. */
__attribute__((section(".text.w11b_0804ac88")))
void Poke_4AC88(u8 a)
{
    u8 *p = (u8 *)0x0200BD20;
    p[127] = 0;
    p[126] = 0;
    p[160]++;
    p[161] = a;
}

/* 0x08011C14 (60 B incl pool): two memset loops via pp base 0x02005260.
 * Zeroes 16 bytes at pp[1] and 8 bytes at pp[2]. */
__attribute__((section(".text.w11b_08011c14")))
void Memset_11C14(void)
{
    u32 *pp = (u32 *)0x02005260;
    s16 i;
    for (i = 0; i <= 15; i++)
        ((u8 *)pp[1])[i] = 0;
    for (i = 0; i <= 7; i++)
        ((u8 *)pp[2])[i] = 0;
}

/* 0x08023B88 (60 B): 24-element u16 decoder loop. For each str[i]:
 * if (u16)(v-1) <= 9, decrement; else if (u16)(v-94) <= 26, subtract 84. */
__attribute__((section(".text.w11b_08023b88")))
void Decode_23B88(u16 *str)
{
    u8 i = 0;
    do {
        if ((u16)(str[i] - 1) <= 9) {
            str[i]--;
        } else if ((u16)(str[i] - 94) <= 26) {
            str[i] -= 84;
        }
        i++;
    } while (i <= 23);
}

/* 0x08001E74 (70 B incl pools): guarded struct init at 0x02002F80.
 * Returns -1 if a > 1, *p != 0, or c > 0x2010; else writes
 * p[1]=a, *(p+8)=b, *(p+20)=c, *(u16*)(p+28)=0, p[0]=2, *(u16*)(p+2)=1. */
__attribute__((section(".text.w11b_08001e74")))
int Init_1E74(u8 a, u32 b, u32 c)
{
    if (a > 1)
        return -1;
    {
        u8 *p = (u8 *)0x02002F80;
        if (p[0] != 0)
            return -1;
        if (c > 0x2010)
            return -1;
        p[1] = a;
        *(u32 *)(p + 8) = b;
        *(u32 *)(p + 20) = c;
        *(u16 *)(p + 28) = 0;
        p[0] = 2;
        *(u16 *)(p + 2) = 1;
        return 0;
    }
}
