/* W37-C MATCHED: 0x080185a8, 152 B, old_agbcc, pure C, 0 diffs.
 * Init task on struct *s. Idioms: barrier-kept clamp copy (adds r0,r1 +
 * cmp r0); barrier-kept q pointer (subs r2,#35 reuse); shift-then-OR via
 * sh variable (ORR into r0); chained zero stores via z variable assigned
 * before the s[34] store (str r1 zeros); y volatile-load + y=0 + pass y
 * as SetMirrored third arg (movs r2,#0 before adds r0 call setup).
 * ChipSlot_Setup(s, 544, s[17]); ChipSlot_IncUse(s, 0);
 * v = *(u8*)(0x020031e4 + ((*(u16*)0x081705b0 >> 4) << 1)) & 3, clamped to 3;
 * s[69] = (s[69] & -13) | (v << 2); s[34] = 13;
 * s[88] = 1088; s[96] = s[92] = s[100] = 0;
 * Vec2_AddMirrored(s, -14080, 0); Vec2_CopyMirrored(out, s);
 * Vec2_SetMirrored(s, out[0], 0); SetBit16(*(s+44), 3);
 * Text_SelectBlobIdx(138).
 * Extern callees + addresses: ChipSlot_Setup 0x0800d6e0 (MATCHED),
 * ChipSlot_IncUse 0x0800d9ec (MATCHED), Vec2_AddMirrored 0x0800dd4c
 * (MATCHED), Vec2_CopyMirrored 0x0800dd08 (BLOCKED/permanent, .set),
 * Vec2_SetMirrored 0x0800dd2c (MATCHED), SetBit16 0x080174a4 (MATCHED),
 * Text_SelectBlobIdx 0x0804a378 (MATCHED).
 * Pools (LE): 0x081705b0, 0x020031e4, 0xffffc900.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern void SetBit16(u8 *s, int bit);
extern int Text_SelectBlobIdx(int idx);

__attribute__((section(".text.w37c_080185a8")))
void Sub_080185A8(u8 *s)
{
    u32 out[2];
    register u32 y __asm__("r2");
    u32 z;
    int v;
    ChipSlot_Setup(s, 544, s[17]);
    ChipSlot_IncUse(s, 0);
    {
        u8 *q;
        int tmp;
        int w;
        v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
        w = v;
        __asm__ volatile("" : "+r"(w));
        if (w > 3)
            v = 3;
        q = s + 69;
        {
            int sh = v << 2;
            tmp = (s[69] & -13) | sh;
        }
        *q = tmp;
        __asm__ volatile("" : "+r"(q));
        q -= 35;
        z = 0;
        *q = 13;
    }
    *(u32 *)(s + 88) = 1088;
    *(u32 *)(s + 100) = *(u32 *)(s + 92) = *(u32 *)(s + 96) = z;
    Vec2_AddMirrored(s, -14080, 0);
    Vec2_CopyMirrored(out, s);
    {
        s32 x = out[0];
        y = *(volatile u32 *)&out[1];
        y = 0;
        Vec2_SetMirrored(s, x, y);
    }
    SetBit16(*(u8 **)(s + 44), 3);
    Text_SelectBlobIdx(138);
}
