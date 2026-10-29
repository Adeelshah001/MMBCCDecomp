/* W37-C2: 0x08019e7c, 188 B. Move-task step (1ac58 family,
 * 4-case, x=r5/y=r6): AddMirrored(s,s[88],s[92]);
 * s[88]+=s[96]; s[92]+=s[100]; CopyMirrored(out,s);
 * x=out[0] (dead load, kept by empty "+r" asm), y=out[1];
 * mode=s[13]:
 * case 0: s[18]=10; goto tail;
 * case 1: s[18]--; if !=0 ret0; SetBit16(s[44],3);
 * ChipInit(95,nibble(s[35]),0,(s16)y,s[44]); IncUse(s,1);
 * goto tail;
 * case 2: if (GetField17_U8(s[44])<=5) ret0; s[18]=10;
 * IncUse(s,0); goto tail;
 * case 3: s[18]--; if !=0 ret0; return 1;
 * tail: s[13]++; ret0.
 * Callees: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set), SetBit16
 * 0x080174a4 (MATCHED), ChipInit 0x080178a8 (MATCHED),
 * ChipSlot_IncUse 0x0800d9ec (.set), GetField17_U8
 * 0x08017474 (MATCHED). No pool.
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
extern void ChipSlot_IncUse(u8 *s, int v);
extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_08019e7c")))
u8 Sub_08019E7C(u8 *s)
{
    u32 out[2];
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
    int iv;
    register u8 *sp_ __asm__("r0");
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    x = out[0];
    __asm__ volatile("" : "+r"(x));
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
    s[18] = 10;
    goto tail;
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    ChipInit_080178A8(95, ((u32)s[35] << 28) >> 28, 0, (s16)y, *(u8 **)(s + 44));
    sp_ = s;
    iv = 1;
    goto do_inc;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    s[18] = 10;
    sp_ = s;
    iv = 0;
    goto do_inc;
do_inc:
    ChipSlot_IncUse(sp_, iv);
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    return 1;
ret0:
    return 0;
}
/* Trailing 00 00 pad to the next-function boundary. */
__asm__(".hword 0");
