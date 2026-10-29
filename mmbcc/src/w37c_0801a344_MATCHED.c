/* W37-C MATCHED: 0x0801a344, 172 B, old_agbcc, pure C, 0 diffs.
 * Move-task step on struct *s,
 * returns u8. Same family as 0x0801ac58 (goto-form, s32 not needed
 * here since x/y unused; out[] computed but never read).
 * AddMirrored(s, s[88], s[92]); s[88] += s[96]; s[92] += s[100];
 * CopyMirrored(out, s); switch (s[13]):
 *  case 0: s[18] = 30; goto inc;
 *  case 1: s[18]--; if ((s8)s[18] != 0) goto ret0;
 *    SetBit16(s[44], 3); ChipInit(119, nibble, 15360, -1280, s[44]);
 *    s[10] &= 253; s[10] &= 254 (two-step AND temp); goto inc;
 *  inc: s[13]++; goto ret0;
 *  case 2: if ((u8)GetField17_U8(s[44]) <= 5) goto ret0;
 *    MaxAssign_17(s[44], 7); return 1;
 *  default: goto ret0;
 * ret0: return 0.
 * Extern callees + addresses: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), SetBit16 0x080174a4
 * (MATCHED), ChipInit_080178A8 0x080178a8 (MATCHED),
 * GetField17_U8 0x08017474 (MATCHED), MaxAssign_17 0x08017478
 * (MATCHED).
 * Pools (LE): 0xfffffb00 (-1280).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void SetBit16(u8 *p, int bit);
extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);
extern u8 GetField17_U8(u8 *p);
extern void MaxAssign_17(u8 *p, int v);

__attribute__((section(".text.w37c_0801a344")))
u8 Sub_0801A344(u8 *s)
{
    u32 out[2];
    u8 t;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    switch (s[13]) {
    case 0: goto c0;
    case 1: goto c1;
    case 2: goto c2;
    default: goto ret0;
    }
c0:
    s[18] = 30;
    goto inc;
c1:
    s[18]--;
    if ((s8)s[18] != 0)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    ChipInit_080178A8(119, ((u32)s[35] << 28) >> 28, 15360, -1280, *(u8 **)(s + 44));
    t = s[10] & 253;
    t = t & 254;
    s[10] = t;
    goto inc;
inc:
    s[13]++;
    goto ret0;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
