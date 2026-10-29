/* Wave 68-A v1: 0x08013138, fresh. True (tiling) extent 328 B
 * (324 code through bx @0x1327A + 4 trailing pool @0x1327C = 0xFFFFC400,
 * next fn @0x13280). Switch-dispatch ChipSlot state machine on s[14]
 * (cases 0-7, default -> Tick), following the landed 0x08015F90 mould:
 * shared Vec2+IncUse / IncUse / s[14]++ tails, eager e = s + 124 used
 * only in case 7 as e[4] = 0 (s[128] = 0). Callee names follow landed
 * conventions (Check119 = 0x08011F50, GetField17_U8 = 0x08017474);
 * 0x080174A4 (case 3, (ptr, 3), return ignored) and 0x08017464 (case 7,
 * ptr, return ignored) are call-site-derived. .set stubs for ALL callees
 * are verification-only; coordinator strips landed-callee stubs at landing. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
void ChipSlot_IncUse(u8 *s, u8 idx);
void ChipSlot_Tick(u8 *s);
u16 Check119(u8 *s);
u8 GetField17_U8(u8 *s);
void SetBytes_08011F68(u8 *s, u8 v);
u8 Check_080174A4(u8 *s, u8 v);
void F_08017464(u8 *s);
u32 *ChipInit_0801AA70(u8 a, u8 b, u8 c, u16 d, u16 e, u8 *f);

__attribute__((section(".text.w68a_08013138")))
void sub_08013138(u8 *s)
{
    u8 *e = s;
    e += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 1:
        if (Check119(s) == 0)
            break;
        Vec2_SetMirrored(s, 0xFFFFEC00, 0);
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 2:
        if (Check119(s) == 0)
            break;
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 3: {
        u8 *p = s;
        u8 nib;
        if (Check119(s) == 0)
            break;
        Check_080174A4(*(u8 **)(s + 44), 3);
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        ChipInit_0801AA70(31, 0, nib, 0x1400, 0, *(u8 **)(s + 44));
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    }
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 6)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 5:
        if (Check119(s) == 0)
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
    ".globl Check_080174A4\n.set Check_080174A4, 0x080174A4\n"
    ".globl F_08017464\n.set F_08017464, 0x08017464\n"
);
