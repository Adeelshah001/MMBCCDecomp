/* W38-A: 0x0801a484, 228 B. 1823c family, int return (like #8 18fb8).
 * AddMirrored(s,s[88],s[92]); s[88]+=s[96]; s[92]+=s[100];
 * CopyMirrored(out,s) (out on stack, sp+4/sp+8); out[0] dead (pin+barrier),
 * out[1] live (c0 test). mode = s[13]:
 * c0: if out[1] > -1280: ChipInit(93,nib,14080,-3840,s[44]); s[88]=0;
 *   s[92]=0; IncUse(s,1); -> inc (s[13]++); return 0. Else return 0.
 * c1: if (u8)(s[119]-3) <= 1: IncUse(s,2); s[18]=30; -> inc; return 0.
 *   Else return 0.
 * c2: s[10] = (s[18]&4) ? (s[10]&254) : (s[10]|1); s[18]--;
 *   if (s[18] != 0) return 0; else -> inc; return 0.
 * c3: if GetField17_U8(s[44]) > 5: return 1. Else return 0.
 * inc: s[13]++; return 0. Default: return 0.
 * Epilogue pops return into r1 (int return).
 * Callees: AddMirrored 0x0800dd4c (MATCHED), CopyMirrored 0x0800dd08
 * (BLOCKED, .set), IncUse 0x0800d9ec (MATCHED), ChipInit 0x080178a8
 * (MATCHED, staged (int,int,int,int,u8*) — real (u8,u8,u16,u16,u8*),
 * flag), GetField 0x08017474 (MATCHED).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void ChipSlot_IncUse(u8 *s, int idx);
extern u32 *ChipInit_080178A8(int a, int b, int c, int d, int e);
extern u8 GetField17_U8(int v);

__attribute__((section(".text.w38a_0801a484")))
int Sub_0801A484(u8 *s)
{
    int out[2];
    register int o0 __asm__("r1");
    register int o1 __asm__("r2");
    int mode;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored((u8 *)out, s);
    o0 = out[0];
    __asm__ volatile("" : "+r"(o0));
    o1 = out[1];
    __asm__ volatile("" : "+r"(o1));
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
    if (o1 <= -1280)
        goto ret0;
    ChipInit_080178A8(93, (int)(((u32)s[35] << 28) >> 28), 220 << 6, -3840, *(u32 *)(s + 44));
    *(u32 *)(s + 88) = mode;
    *(u32 *)(s + 92) = mode;
    ChipSlot_IncUse(s, 1);
    goto inc;
c1:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    ChipSlot_IncUse(s, 2);
    s[18] = 30;
    goto inc;
c2:
    if (s[18] & 4)
        s[10] &= 254;
    else
        s[10] |= 1;
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    goto inc;
inc:
    s[13]++;
    goto ret0;
c3:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
__asm__(".hword 0");
