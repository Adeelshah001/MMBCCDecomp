/* W37-C2: 0x0801969c, 176 B. Move-task step (1ac58 family).
 * AddMirrored(s,s[88],s[92]); s[88]+=s[96]; s[92]+=s[100];
 * CopyMirrored(out,s); if-chain on s[13]: case 0: out[0]>12800
 * else ret0; ChipInit(82,nibble,15360,(s16)out[1],s[44]);
 * TestBit16(s[44],0)!=0 -> s[13]=1 ret0; else s[10]&=253&=254,
 * s[13]=2 ret0; case 1: out[0]>30720 -> s[13]=2 ret0 else ret0;
 * case 2: (u8)GetField17_U8(s[44])>5 -> return 1 else ret0;
 * default ret0.
 * Callees: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), ChipInit
 * 0x080178a8 (MATCHED), TestBit16 0x08017494 (MATCHED),
 * GetField17_U8 0x08017474 (MATCHED).
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
extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);
extern u8 TestBit16(u8 *p, int bit);
extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_0801969c")))
u8 Sub_0801969C(u8 *s)
{
    u32 out[2];
    u8 t;
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
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
    goto ret0;
c0:
    if (x <= 12800)
        goto ret0;
    ChipInit_080178A8(82, ((u32)s[35] << 28) >> 28, 15360, (s16)y, *(u8 **)(s + 44));
    if (TestBit16(*(u8 **)(s + 44), 0) != 0) {
        s[13] = 1;
        goto ret0;
    }
    t = s[10] & 253;
    t = t & 254;
    s[10] = t;
    goto c1tail;
c1:
    if (x <= 30720)
        goto ret0;
c1tail:
    s[13] = 2;
    goto ret0;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
