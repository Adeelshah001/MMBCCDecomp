/* W37-C2: 0x08019bdc, 184 B. Move-task step (1ac58 family,
 * 4-case): AddMirrored(s,s[88],s[92]); s[88]+=s[96];
 * s[92]+=s[100]; CopyMirrored(out,s); mode=s[13]:
 * case 0: s[18]=15; s[13]++; (fallthrough)
 * case 1: s[18]--; if (s[18]!=0) ret0;
 * ChipInit(1,nibble(s[35]),15360,0xffffea00,s[44]);
 * F_0804A378(128); s[13]++; ret0;
 * case 2: if ((u8)(s[119]-3)>1) ret0; s[13]=3; ret0;
 * case 3: (u8)GetField17_U8(s[44])>5 -> return 1 else ret0.
 * Callees: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), ChipInit
 * 0x080178a8 (MATCHED), F_0804A378 0x0804a378 (.set),
 * GetField17_U8 0x08017474 (MATCHED).
 * Pool (LE): 0xffffea00.
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
extern void F_0804A378(int v);
__asm__(".set F_0804A378, 0x0804a378");
extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_08019bdc")))
u8 Sub_08019BDC(u8 *s)
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
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    s[18] = 15;
    s[13]++;
    /* fallthrough */
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    ChipInit_080178A8(1, ((u32)s[35] << 28) >> 28, 15360, 0xffffea00, *(u8 **)(s + 44));
    F_0804A378(128);
    s[13]++;
    goto ret0;
c2:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    s[13] = 3;
    goto ret0;
c3:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
/* Trailing 00 00 pad to the next-function boundary. */
__asm__(".hword 0");
