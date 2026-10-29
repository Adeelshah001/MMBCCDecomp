/* W37-C MATCHED (twin-transfer from MATCHED 0x080185a8): 0x0801986c, 152 B,
 * old_agbcc, pure C, 0 diffs.
 * Wrapper_D770(s, 0x837, 0); ChipSlot_IncUse(s, 0);
 * same bitfield block as 0x080185a8 (clamp, s[69], s[34]=13);
 * s[88]=s[96]=s[92]=s[100]=0 (no 1088 store here);
 * Vec2_CopyMirrored(out, s) (result unused);
 * Vec2_SetMirrored(s, 5120, 0xffffba00); Text_SelectBlobIdx(159);
 * if (s[17] == 0) s[17] = 1; if (s[17] > 6) s[17] = 6.
 * Extern callees + addresses: Wrapper_D770 0x0800d770 (MATCHED),
 * ChipSlot_IncUse 0x0800d9ec (MATCHED), Vec2_CopyMirrored 0x0800dd08
 * (BLOCKED/permanent, .set), Vec2_SetMirrored 0x0800dd2c (MATCHED),
 * Text_SelectBlobIdx 0x0804a378 (MATCHED).
 * Pools (LE): 0x00000837, 0x081705b0, 0x020031e4, 0xffffba00.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void Wrapper_D770(u8 *s, int b, int c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern int Text_SelectBlobIdx(int idx);

__attribute__((section(".text.w37c_0801986c")))
void Sub_0801986C(u8 *s)
{
    u32 out[2];
    u32 z;
    int v;
    Wrapper_D770(s, 0x837, 0);
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
    *(u32 *)(s + 100) = *(u32 *)(s + 92) = *(u32 *)(s + 96) = *(u32 *)(s + 88) = z;
    Vec2_CopyMirrored(out, s);
    Vec2_SetMirrored(s, 5120, 0xffffba00);
    Text_SelectBlobIdx(159);
    if (s[17] == 0)
        s[17] = 1;
    if (s[17] > 6)
        s[17] = 6;
}
