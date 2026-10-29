/* W37-C2: 0x0801bde4, 188 B. Move-task step (copy-only):
 * CopyMirrored(out,s) (out at sp+8); x=out[0] (r5),
 * y=out[1] (r6); mode=s[13]:
 * case 0: if ((u8)(s[119]-3)>1) ret0; SetBit16(s[44],3);
 * F_0804A378(146); s[18]=1; goto tail;
 * case 1: s[18]--; if !=0 ret0;
 * F_0801B98C(1,s[17],nibble(s[35]),(s16)(x+9728),
 * (s16)(y-6656),s[44]); s[18]=15; goto tail;
 * case 2: s[18]--; if !=0 ret0; goto tail;
 * tail: s[13]++; goto ret0;
 * case 3: MaxAssign_17(s[44],7); return 1.
 * Callees: Vec2_CopyMirrored 0x0800dd08 (BLOCKED, .set),
 * SetBit16 0x080174a4 (MATCHED), F_0804A378 0x0804a378
 * (.set), F_0801B98C 0x0801b98c (.set), MaxAssign_17
 * 0x08017478 (MATCHED). Pool (LE): 0xffffe600.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_CopyMirrored(u32 *out, u8 *src);
extern void SetBit16(u8 *p, int bit);
extern void F_0804A378(int v);
extern void F_0801B98C(int a, u8 b, int c, s16 d, s16 e, u8 *f);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
__asm__(".set F_0804A378, 0x0804a378");
__asm__(".set F_0801B98C, 0x0801b98c");
extern void MaxAssign_17(u8 *p, int v);

__attribute__((section(".text.w38c_0801bde4")))
u8 Sub_0801BDE4(u8 *s)
{
    u32 out[2];
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
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
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    F_0804A378(146);
    s[18] = 1;
    goto tail;
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    {
        u8 b = s[17];
        int nib = ((u32)s[35] << 28) >> 28;
        s16 d = (s16)(x + (152 << 6));
        register u32 pool __asm__("r7");
        pool = 0xffffe600;
        F_0801B98C(1, b, nib, d, (s16)(y + (s32)pool),
            *(u8 **)(s + 44));
    }
    s[18] = 15;
    goto tail;
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
__asm__(".hword 0");
