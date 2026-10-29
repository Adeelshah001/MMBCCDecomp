/* W38-A: 0x08014078, 220 B. Move-task step (SetMirrored family).
 * mode = s[14]: c0: SetMirrored(s,-15360,0); IncUse(s,8); s[14]++;
 * c1: if Check119(s): SetBit16(s[44],3);
 *   IncUse(s,9); s[14]++;
 * c2: if Check119(s): SetBit16(s[44],3);
 *   Sub_0801AA70(19,0,nibble,-11520,-8960,s[44]); IncUse(s,10); s[14]++;
 * c3: if (u8)GetField17_U8(s[44])>6: DecIfNonZero(s[44]); s[44]=0;
 *   SetMirrored(s,-15360,0); IncUse(s,0); s[128]=0; SetBytes(s,0);
 * tail: Tick(s).
 * Callees: SetMirrored 0x0800dd2c, Check119 0x08011f50,
 * SetBit16 0x080174a4, Sub_0801AA70 0x0801aa70 (unlisted, .set),
 * GetField17_U8 0x08017474, DecIfNonZero 0x08017464,
 * IncUse 0x0800d9ec, SetBytes 0x08011f68, Tick 0x0800d9fc
 * (all MATCHED except 1aa70).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void SetBit16(u8 *s, int bit);
extern void Sub_0801AA70(int a, int b, int c, int d, int e, u8 *f);
__asm__(".set Sub_0801AA70, 0x0801aa70");
extern u8 GetField17_U8(u8 *p);
extern void DecIfNonZero_18(u8 *s);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w38a_08014078")))
void Sub_08014078(u8 *s)
{
    u8 *p = s + 124;
    int mode;
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
    ChipSlot_IncUse(s, 8);
    s[14]++;
    goto tail;
c1:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    ChipSlot_IncUse(s, 9);
    s[14]++;
    goto tail;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    SetBit16(*(u8 **)(s + 44), 3);
    Sub_0801AA70(19, 0, ((u32)s[35] << 28) >> 28, -11520, -8960,
        *(u8 **)(s + 44));
    ChipSlot_IncUse(s, 10);
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
