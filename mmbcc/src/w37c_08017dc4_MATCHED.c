/* W37-C MATCHED: 0x08017dc4, 168 B, old_agbcc, pure C, 0 diffs.
 * Move-task step on struct *s,
 * returns u8. Same family as 0x0801ac58 (goto-form, mode in r5,
 * out[] on stack, s32 x/y for signed ble).
 * AddMirrored(s, s[88], s[92]); s[88] += s[96]; s[92] += s[100];
 * CopyMirrored(out, s); x = out[0]; y = out[1]; switch (s[13]):
 *  case 0: if (y <= -1024) return 0; SetBit16(s[44], 3); s[13]++;
 *    s[88] = 1280; s[96] = s[92] = s[100] = mode (0, words); return 0;
 *  case 1: if (x <= 12800) return 0;
 *    ChipInit(13, nibble, 15360, 0, s[44]); s[13]++; return 0;
 *  case 2: if (x <= 30720) return 0; return 1;
 *  default: return 0.
 * Extern callees + addresses: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), SetBit16 0x080174a4
 * (MATCHED), ChipInit_080178A8 0x080178a8 (MATCHED).
 * Pools (LE): 0xfffffc00.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void SetBit16(u8 *p, int bit);
extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

__attribute__((section(".text.w37c_08017dc4")))
u8 Sub_08017DC4(u8 *s)
{
    u32 out[2];
    s32 x;
    s32 y;
    u8 mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = out[1];
    mode = s[13];
    switch (mode) {
    case 0: goto c0;
    case 1: goto c1;
    case 2: goto c2;
    default: goto ret0;
    }
c0:
    if (y <= -1024)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    s[13]++;
    *(s32 *)(s + 88) = 1280;
    *(s32 *)(s + 96) = mode;
    *(s32 *)(s + 92) = mode;
    *(s32 *)(s + 100) = mode;
    goto ret0;
c1:
    if (x <= 12800)
        goto ret0;
    ChipInit_080178A8(13, ((u32)s[35] << 28) >> 28, 15360, 0, *(u8 **)(s + 44));
    s[13]++;
    goto ret0;
c2:
    if (x <= 30720)
        goto ret0;
    return 1;
ret0:
    return 0;
}
