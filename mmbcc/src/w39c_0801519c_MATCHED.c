/* W39-C: 0x0801519c, 220 B, old_agbcc -O2 -mthumb-interwork, pure C + inline asm.
 * Same 2-byte pool/shift wall as twin 0x08013708 (revisit together,
 * per W38-A); same fix: base pinned r1 + barrier, tbp pinned r0,
 * inline `add %0, %0, %1`. W38-A V1 (220/2) -> 0 diffs first try.
 * Callee .set blocks at END (GAS idiom).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void Sub_0801CD50(int a, int b, int c, int d, int e, u8 *f);
extern u8 GetField17_U8(u8 *p);
extern void DecIfNonZero_18(u8 *s);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w39c_0801519c")))
void Sub_0801519C(u8 *s)
{
    u8 *p = s + 124;
    int mode;
    int nib;
    int z;
    s16 h0;
    int t;
    s16 h1;
    mode = s[14];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto tail;
c0:
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 11);
    goto inc;
c1:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    ChipSlot_IncUse(s, 12);
    goto inc;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    nib = ((u32)s[35] << 28) >> 28;
    {
        register u8 *base __asm__("r1");
        register u8 *tbp __asm__("r0");
        base = (u8 *)0x08223ED8;
        __asm__ volatile("" : "+r"(base));
        tbp = (u8 *)(p[0] * 4);
        __asm__ volatile("add %0, %0, %1" : "+r"(tbp) : "r"(base));
        z = 0;
        h0 = *(s16 *)(tbp + z);
        t = 2;
        h1 = *(s16 *)(tbp + t);
    }
    Sub_0801CD50(2, 1, nib, h0, h1, *(u8 **)(s + 44));
inc:
    s[14]++;
    goto tail;
c3:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 6)
        goto tail;
    DecIfNonZero_18(*(u8 **)(s + 44));
    *(u8 **)(s + 44) = 0;
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 0);
    p[4] = 0;
    SetBytes_08011F68(s, 0);
    goto tail;
tail:
    ChipSlot_Tick(s);
}

__asm__(".set Sub_0801CD50, 0x0801cd50");
