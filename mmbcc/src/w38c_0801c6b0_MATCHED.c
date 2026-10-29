/* W37-C2: 0x0801c6b0, 196 B. Move-task step:
 * Vec2_AddMirrored(s,s[88],s[92]); s[88]+=s[96];
 * s[92]+=s[100]; CopyMirrored(out,s) (out at sp+8);
 * x=out[0] (r3), y=out[1] (r4); mode=s[13]:
 * case 0: s[18]--; if !=0 ret0;
 * F_0801EBF0(57,0,nibble(s[35]),(s16)x,(s16)y,s[44]);
 * F_0801B98C(6,s[17],nibble(s[35]),(s16)x,(s16)y,s[44]);
 * s[13]++; goto ret0;
 * case 1: if (GetField17_U8(s[44])>5) {
 * s[18]=15; s[13]++; goto ret0; } goto c2;
 * c2: s[18]--; if !=0 ret0; MaxAssign_17(s[44],7);
 * return 1.
 * Callees: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set),
 * F_0801EBF0 0x0801ebf0 (.set), F_0801B98C
 * 0x0801b98c (.set), GetField17_U8 0x08017474
 * (MATCHED), MaxAssign_17 0x08017478 (MATCHED).
 * No pools.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *s, s32 a, s32 b);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
extern void F_0801EBF0(int a, int b, int c, s16 d, s16 e);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
__asm__(".set F_0801EBF0, 0x0801ebf0");
extern void F_0801B98C(int a, u8 b, int c, s16 d, s16 e, u8 *f);
__asm__(".set F_0801B98C, 0x0801b98c");
extern int GetField17_U8(u8 *p);
extern void MaxAssign_17(u8 *p, int v);
__asm__(".set MaxAssign_17, 0x08017478");

__attribute__((section(".text.w38c_0801c6b0")))
u8 Sub_0801C6B0(u8 *s)
{
    u32 out[2];
    s32 x, y;
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
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    F_0801EBF0(57, 0, ((u32)s[35] << 28) >> 28,
        (s16)x, (s16)y);
    F_0801B98C(6, s[17], ((u32)s[35] << 28) >> 28,
        (s16)x, (s16)y, *(u8 **)(s + 44));
    s[13]++;
    goto ret0;
c1:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5) {
        s[18] = 15;
        s[13]++;
    }
    /* fall through to c2 (ROM has no branch here) */
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
__asm__(".hword 0");
