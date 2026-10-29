/* W37-C2: 0x08019aac, 184 B. Move-task step (1ac58 family):
 * AddMirrored(s,s[88],s[92]); s[88]+=s[96]; s[92]+=s[100];
 * CopyMirrored(out,s); x=out[0], y=out[1] (y dead load kept
 * by empty "+r" asm); mode=s[13]:
 * case 0: if ((u8)(s[119]-3)>1) ret0;
 * ChipInit(93,nibble(s[35]),15360,0xffffe700,s[44]);
 * ChipSlot_IncUse(s,1); s[34]=18; s[13]++; ret0;
 * case 1: if ((u8)(s[119]-3)>1) ret0; s[13]=2; ret0;
 * case 2: (u8)GetField17_U8(s[44])>5 -> return 1 else ret0.
 * Callees: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), ChipInit
 * 0x080178a8 (MATCHED), ChipSlot_IncUse 0x0800d9ec (.set),
 * GetField17_U8 0x08017474 (MATCHED).
 * Pool (LE): 0xffffe700.
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
extern void ChipSlot_IncUse(u8 *s, int v);
extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_08019aac")))
u8 Sub_08019AAC(u8 *s)
{
    u32 out[2];
    int mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
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
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    ChipInit_080178A8(93, ((u32)s[35] << 28) >> 28, 15360, 0xffffe700, *(u8 **)(s + 44));
    ChipSlot_IncUse(s, 1);
    s[34] = 18;
    s[13]++;
    goto ret0;
c1:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    s[13] = 2;
    goto ret0;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
/* Trailing 00 00 pad to the next-function boundary. */
__asm__(".hword 0");
