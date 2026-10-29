/* W37-C MATCHED: 0x0801a220, 156 B, old_agbcc, pure C, 0 diffs.
 * Move-task step on struct *s, returns u8. Idioms: goto-form (label
 * order = block order: c0, c1, inc, c2, ret1, ret0); out[] in r5/r6
 * variables; nibble via (u32)x<<28>>28 shifts; trailing .hword 0 pad.
 * AddMirrored(s, s[88], s[92]); s[88] += s[96]; s[92] += s[100];
 * CopyMirrored(out, s); switch (s[13]):
 *  case 0: s[18] = 15; break;
 *  case 1: if (--s[18] != 0) return 0; SetBit16(s[44], 3);
 *    ChipInit(102, s[35] & 0xF, (s16)out[0], (s16)out[1], s[44]); break;
 *  case 2: if (GetField17_U8(s[44]) <= 5) return 0; return 1;
 *  default: return 0;
 * s[13]++; return 0.
 * Extern callees + addresses: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), SetBit16 0x080174a4
 * (MATCHED), ChipInit_080178A8 0x080178a8 (MATCHED),
 * GetField17_U8 0x08017474 (MATCHED).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void SetBit16(u8 *s, int bit);
extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);
extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c_0801a220")))
u8 Sub_0801A220(u8 *s)
{
    u32 out[2];
    u32 x;
    u32 y;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = out[1];
    switch (s[13]) {
    case 0: goto c0;
    case 1: goto c1;
    case 2: goto c2;
    default: goto ret0;
    }
c0:
    s[18] = 15;
    goto inc;
c1:
    if (--s[18] != 0)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    ChipInit_080178A8(102, ((u32)s[35] << 28) >> 28, (s16)x, (s16)y, *(u8 **)(s + 44));
    goto inc;
inc:
    s[13]++;
    goto ret0;
c2:
    if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    goto ret1;
ret1:
    return 1;
ret0:
    return 0;
}

/* Trailing zero pad: ROM ends this 156 B section with 00 00 after bx;
 * without it GAS pads the section end with mov r8,r8 (0x46c0). */
__asm__(".hword 0x0000");
