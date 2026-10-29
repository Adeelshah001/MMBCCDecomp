/* Wave 68-A v1: 0x08012504, fresh. True (tiling) extent 328 B
 * (324 code through bx @0x12646 + 4 trailing pool @0x12648 = 0xFFFFC400,
 * next fn @0x1264C). Switch-dispatch ChipSlot state machine on s[14]
 * (cases 0-6, default -> Tick), following the landed 0x08015F90 mould:
 * shared Vec2+IncUse / IncUse / s[14]++ tails, eager e = s + 124 used
 * only in case 6 as e[4] = 0 (s[128] = 0). Case 3 calls ChipInit_0801BBB4
 * with full-word pool constants 0xFFFFA600 / 0xFFFFCD00 (the landed BBB4
 * signature says u16 c/d, but the caller loads the full words; the
 * callee's (s16) casts make the high bits moot -- call-site prototype
 * here uses s32 c/d to reproduce the pool loads; coordinator to rule
 * on landing). Case 3 temps are in ROM order (a17, then p = s + 35,
 * then nibble). .set stubs for ALL callees are verification-only;
 * coordinator strips landed-callee stubs at landing. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
void ChipSlot_IncUse(u8 *s, u8 idx);
void ChipSlot_Tick(u8 *s);
u16 Check119(u8 *s);
u8 GetField17_U8(u8 *s);
void SetBytes_08011F68(u8 *s, u8 v);
void F_08017464(u8 *s);
s16 Text_SelectBlobIdx(u16 idx);
u32 *ChipInit_0801BBB4(u8 a, u8 b, s32 c, s32 d, u8 *e);

__attribute__((section(".text.w68a_08012504")))
void sub_08012504(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    case 1:
        if (Check119(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFF9C00, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 2:
        if (Check119(s) == 0)
            break;
        ChipSlot_IncUse(s, 15);
        s[14]++;
        break;
    case 3: {
        u8 a17;
        u8 *p;
        u8 nib;
        if (Check119(s) == 0)
            break;
        ChipSlot_IncUse(s, 16);
        Text_SelectBlobIdx(131);
        s[14]++;
        a17 = s[17];
        p = s;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_0801BBB4(a17, nib, 0xFFFFA600, 0xFFFFCD00, *(u8 **)(s + 44));
        break;
    }
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 5:
        if (Check119(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 6:
        if (Check119(s) == 0)
            break;
        F_08017464(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        e[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
__asm__(
    ".globl Check119\n.set Check119, 0x08011F50\n"
    ".globl F_08017464\n.set F_08017464, 0x08017464\n"
);
