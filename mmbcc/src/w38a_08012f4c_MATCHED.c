/* W38-A: 0x08012f4c, 216 B. Move-task step (SetMirrored family).
 * mode = s[14]: case 0: SetMirrored(s,-15360,0); IncUse(s,8);
 *   s[14]++; case 1: if Check119(s): IncUse(s,9); s[14]++;
 *   case 2: if Check119(s): SetBit16(s[44],3);
 *   Sub_0801AA70(0,0,nibble,-15360,0,s[44]);
 *   Text_SelectBlobIdx(144); IncUse(s,10); s[14]++; case 3:
 *   if Check119(s): DecIfNonZero(s[44]); s[44]=0;
 *   SetMirrored(s,-15360,0); IncUse(s,0); s[128]=0;
 *   SetBytes(s,0); all paths tail: Tick(s).
 * (Identical IncUse+s[14]++ tails expected to cross-jump into
 * one shared block, as in ROM.)
 * Callees: SetMirrored 0x0800dd2c, Check119 0x08011f50,
 * SetBit16 0x080174a4, Sub_0801AA70 0x0801aa70 (unlisted gap
 * callee, .set), Text_SelectBlobIdx 0x0804a378, IncUse
 * 0x0800d9ec, DecIfNonZero 0x08017464, SetBytes 0x08011f68,
 * Tick 0x0800d9fc (all MATCHED except 1aa70).
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
extern int Text_SelectBlobIdx(int idx);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void DecIfNonZero_18(u8 *s);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w38a_08012f4c")))
void Sub_08012F4C(u8 *s)
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
    Sub_0801AA70(0, 0, ((u32)s[35] << 28) >> 28, -15360, 0, *(u8 **)(s + 44));
    Text_SelectBlobIdx(144);
    ChipSlot_IncUse(s, 10);
    s[14]++;
    goto tail;
c3:
    if (Check119_Minus3_Le1(s) == 0)
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
