/* W55-D: 0x08014eb8, 252 B. Move-task step, jump-table switch.
 * 13904-family idiom: natural switch, s[14]++ inline per case.
 * case0: SetMirrored(-15360,0); IncUse(8); inc.
 * case1: Check119? IncUse(9); inc : tail.
 * case2: Check119? SetBit16(s44val,3); ChipInit(97,nib,-10240,-6656,s44);
 *   inc (NO IncUse) : tail.
 * case3: GetField(s44)>5? MaxAssign(7); IncUse(10); inc : tail.
 * case4: Check119? Dec; s44=0; SetMirrored(-15360,0); IncUse(0);
 *   p[4]=0; SetBytes(0) : tail. Tail: Tick(s).
 * Pools (raw LE): table base 0x14ed8; case0 -15360 @0x14efc;
 * ChipInit -10240 @0x14f40, -6656 @0x14f44; trailing -15360 @0x14fb0.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void SetBit16(u32 v, int bit);
extern void ChipInit_080178A8(int a, int b, int c, int d, u32 e);
extern u8 GetField17_U8(u32 v);
extern void MaxAssign_17(u32 v, int n);
extern void DecIfNonZero_18(u32 v);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w55d_08014eb8")))
void Sub_08014EB8(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u32 *)(s + 44), 3);
        {
            int nib = ((u32)s[35] << 28) >> 28;
            ChipInit_080178A8(97, nib, -10240, -6656, *(u32 *)(s + 44));
        }
        s[14]++;
        break;
    case 3:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
            break;
        MaxAssign_17(*(u32 *)(s + 44), 7);
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    }
    ChipSlot_Tick(s);
}
