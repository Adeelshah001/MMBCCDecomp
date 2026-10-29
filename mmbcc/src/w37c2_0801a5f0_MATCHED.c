/* W37-C2: 0x0801a5f0, 188 B. Move-task step (1ac58 family,
 * 4-case, no out loads): AddMirrored(s,s[88],s[92]);
 * s[88]+=s[96]; s[92]+=s[100]; CopyMirrored(out,s);
 * mode=s[13]:
 * case 0: if ((u8)(s[119]-3)>1) ret0;
 * ChipInit(124,nibble(s[35]),15360,0,s[44]); sp_=s; iv=1;
 * goto shared;
 * case 1: if (GetField17_U8(s[44])<=5) ret0; s[18]=15;
 * goto tail;
 * case 2: s[18]--; if !=0 ret0; sp_=s; iv=2; (fallthrough)
 * shared: ChipSlot_IncUse(sp_,iv); goto tail;
 * tail: s[13]++; goto ret0;
 * case 3: (u8)GetField17_U8(s[44])>5 -> return 1 else ret0.
 * Callees: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), ChipInit
 * 0x080178a8 (MATCHED), GetField17_U8 0x08017474
 * (MATCHED), ChipSlot_IncUse 0x0800d9ec (.set).
 * No pool.
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
extern u8 GetField17_U8(u8 *p);
extern void ChipSlot_IncUse(u8 *s, int v);

__attribute__((section(".text.w37c2_0801a5f0")))
u8 Sub_0801A5F0(u8 *s)
{
    u32 out[2];
    int mode;
    int iv;
    register u8 *sp_ __asm__("r0");
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
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    ChipInit_080178A8(124, ((u32)s[35] << 28) >> 28, 15360, 0, *(u8 **)(s + 44));
    sp_ = s;
    iv = 1;
    goto shared;
c1:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    s[18] = 15;
    goto tail;
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    sp_ = s;
    iv = 2;
    /* fallthrough */
shared:
    ChipSlot_IncUse(sp_, iv);
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
