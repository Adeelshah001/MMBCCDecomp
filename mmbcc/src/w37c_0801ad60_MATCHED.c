/* W37-C MATCHED: 0x0801ad60, 160 B, old_agbcc, pure C, 0 diffs.
 * Move-task step on struct *s, returns u8. Idioms: goto-form with
 * ret0 last; x/y as s32 (signed ble, not unsigned bls); two-step
 * AND via temp (defeats &253&254 folding); trailing .hword 0 pad.
 * AddMirrored(s, s[88], s[92]); s[88] += s[96]; s[92] += s[100];
 * CopyMirrored(out, s); x = out[0]; y = out[1]; switch (s[13]):
 *  case 0: if (x <= 12800) return 0;
 *    if (TestBit16(s[44], 0) != 0) { s[13] = 1; return 0; }
 *    ChipInit(67, nibble, (s16)x, (s16)(y + 1280), s[44]);
 *    s[10] &= 253; s[10] &= 254; return 1;
 *  case 1: if (x <= 30720) return 0; return 1;
 *  default: return 0.
 * Extern callees + addresses: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), TestBit16 0x08017494
 * (MATCHED), ChipInit_080178A8 0x080178a8 (MATCHED).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern u8 TestBit16(u8 *p, int bit);
extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

__attribute__((section(".text.w37c_0801ad60")))
u8 Sub_0801AD60(u8 *s)
{
    u32 out[2];
    s32 x;
    s32 y;
    u8 t;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = out[1];
    switch (s[13]) {
    case 0: goto c0;
    case 1: goto c1;
    default: goto ret0;
    }
c0:
    if (x <= 12800)
        goto ret0;
    if (TestBit16(*(u8 **)(s + 44), 0) != 0) {
        s[13] = 1;
        goto ret0;
    }
    ChipInit_080178A8(68, ((u32)s[35] << 28) >> 28, (s16)(x + 5120), (s16)(y + 1280), *(u8 **)(s + 44));
    t = s[10] & 253;
    t = t & 254;
    s[10] = t;
    return 1;
c1:
    if (x <= 30720)
        goto ret0;
    return 1;
ret0:
    return 0;
}
