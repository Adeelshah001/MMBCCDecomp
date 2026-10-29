/* W67-D v1: 0x08015f90, fresh (smallest-first). True extent 324 B
 * (322 code through bx @0x160d0 + 2 pad bytes to next fn @0x160d4).
 * Switch-dispatch ChipSlot state machine on s[14] (cases 0-8, default ->
 * Tick), shared tail IncUse(s,idx)/s[14]++ blocks, eager e = s + 124
 * used only in case 8 as e[4] = 0 (s[128] = 0). Callee declarations
 * follow the landed 12A3C conventions where the callee overlaps it
 * (IncUse, Tick, Check119=u16, Vec2_SetMirrored, GetField17_U8,
 * MaxAssign_17, DecIfNonZero_18, SetBytes_08011F68, SetBit16).
 * F_08017494 (case 1, (s[44] ptr, 3), return tested == 0) is new:
 * declared u8-return; its true name/type is call-site-derived. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void ChipSlot_IncUse(u8 *s, u8 idx);
void ChipSlot_Tick(u8 *s);
u16 Check119(u8 *s);
__asm__(".set Check119, 0x08011f50");
void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
u8 GetField17_U8(u8 *s);
void MaxAssign_17(u8 *s, u8 v);
void DecIfNonZero_18(u8 *s);
void SetBytes_08011F68(u8 *s, u8 v);
void SetBit16(u8 *s, u8 bit);
u8 Check_08017494(u8 *s, u8 v);
__asm__(".set Check_08017494, 0x08017494");

__attribute__((section(".text.w67d_08015f90")))
void sub_08015F90(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        SetBit16(*(u8 **)(s + 44), 0);
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        s[14]++;
        break;
    case 1:
        if (Check_08017494(*(u8 **)(s + 44), 3) == 0)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 2:
        if (Check119(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFB000, 0xFFFFFB00);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 3:
        if (Check119(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[18] = 20;
        s[14]++;
        break;
    case 4:
        if (--s[18] == 0)
            s[14]++;
        break;
    case 5:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 6:
        if (Check119(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 7:
        if (Check119(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[14]++;
        break;
    case 8:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 8);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        e[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
__asm__(".balign 4, 0");
