/* W39-C: 0x0801a72c, 240 B, old_agbcc -O2 -mthumb-interwork + 1-byte patch.
 * W38-A V5 (240/1) + patch: dispatch `bhi` -> `bgt` (ROM compares mode
 * signed: bgt dc at 0x0801a75f; gcc emits unsigned bhi d8 for `s[13] > 1`).
 * Pure-C signed-cast variants restructure the whole dispatch (248/252 B),
 * so the single-opcode patch is the minimal fix. All else identical.
 * Trailing `.hword 0` pad as in ROM. Callee .set blocks at END (GAS idiom).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void ChipInit_080178A8(int a, int b, int c, int d, int e);

__attribute__((section(".text.w39c_0801a72c")))
int Sub_0801A72C(u8 *s)
{
    u32 out[2];
    register int o0 __asm__("r1");
    int o1;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored((u8 *)out, s);
    o0 = out[0];
    __asm__ volatile("" : "+r"(o0));
    o1 = out[1];
    if (s[13] == 1)
        goto c1;
    if (s[13] > 1)
        goto gt1;
    if (s[13] == 0)
        goto c0;
    return 0;
gt1:
    if (s[13] == 2)
        goto c2;
    if (s[13] == 3)
        goto c3;
    return 0;
c0:
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    *(u32 *)(s + 88) = 160 << 3;
    *(u32 *)(s + 92) = 160 << 3;
    goto inc;
c1:
    __asm__ volatile("" : "+r"(o0));
    if (o1 <= -1280)
        return 0;
    if (s[17] == 0) {
        int nib = (int)(((u32)s[35] << 28) >> 28);
        ChipInit_080178A8(92, nib, 220 << 6, -3840, *(u32 *)(s + 44));
    }
    *(u32 *)(s + 88) = 0;
    *(u32 *)(s + 92) = 0;
    ChipSlot_IncUse(s, 1);
    goto inc;
c2:
    if ((u8)(s[119] - 3) <= 1) {
        ChipSlot_IncUse(s, 2);
        s[18] = 30;
    } else {
        return 0;
    }
inc:
    s[13]++;
    return 0;
c3:
    if (s[18] & 4)
        s[10] &= 254;
    else
        s[10] |= 1;
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    return 1;
}

__asm__(".hword 0");

__asm__(".set Vec2_AddMirrored, 0x0800dd4c");
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
