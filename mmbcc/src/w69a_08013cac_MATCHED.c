/* Wave 69-A v1: 0x08013CAC, fresh. True (tiling) extent 332 B
 * (330 code through bx @0x13DF6 + 2 pad to next fn @0x13DF8).
 * Switch state machine on s[14] (cases 0..6, default -> Tick tail).
 * s+124 pointer q kept in r5 (sibling 12A3C template: q = s; q += 124).
 * case 0: Vec2_SetMirrored(s, 0xFFFFC400, 0); ChipSlot_IncUse(s, 8); s[14]++;
 * case 1: if (Check119(s)) { s[18]=5; IncUse(s,9); Text_SelectBlobIdx(148); s[14]++; }
 * case 2: if (--s[18] != 0) break; SetBit16(*(s+44), 3); s[14]++;
 * case 3: Vec2_AddMirrored(s, 0x700, 0); v = Vec2_CopyMirrored(s);
 *         if (v.x > 55) { ChipInit(s[35] nibble, 0x3C00, 0xFFFFE200, *(s+44));
 *         s[10] &= ~1; s[18]=10; s[14]++; }
 * case 4: if (--s[18] != 0) break; s[10] |= 1;
 *         Vec2_SetMirrored(s, 0xFFFFC400, 0); IncUse(s, 10); s[14]++;
 * case 5: if (Check119(s)) { IncUse(s, 0); s[14]++; }
 * case 6: if ((u8)GetField17(*(s+44)) > 5) { MaxAssign(*(s+44),7);
 *         DecIfNonZero(*(s+44)); *(s+44)=0; q[4]=0; SetBytes(s,0); }
 * tail (all paths): ChipSlot_Tick(s).
 * Check119 declared u16 (ROM lsl #16 test after both calls; v1 proved
 * u16 decl alone does not emit it -- v2a struct-return CopyMirrored
 * supplies the dead double-load; Check119 lsl comes from the u16
 * return value used in != 0 test).
 * .set stubs are verification-only; coordinator strips landed-callee stubs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

typedef struct { s32 x, y; } Pair;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
void ChipSlot_IncUse(u8 *s, u8 idx);
u16 Check119_Minus3_Le1(u8 *s);
u16 Text_SelectBlobIdx(u16 idx);
void SetBit16(u8 *s, u8 bit);
void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
Pair Vec2_CopyMirrored(u8 *s);
void ChipInit_080178A8(u8 a, u8 b, u16 c, s32 d, u8 *e);
u8 GetField17_U8(u8 *s);
void MaxAssign_17(u8 *s, u8 v);
void DecIfNonZero_18(u8 *s);
void SetBytes_08011F68(u8 *s, u8 v);
void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w69a_08013cac")))
void sub_08013CAC(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) != 0) {
            s[18] = 5;
            ChipSlot_IncUse(s, 9);
            Text_SelectBlobIdx(148);
            s[14]++;
        }
        break;
    case 2:
        if (--s[18] != 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        s[14]++;
        break;
    case 3: {
        Pair v;
        Vec2_AddMirrored(s, 0x700, 0);
        v = Vec2_CopyMirrored(s);
        if (v.x > 55) {
            u8 *p35 = s + 35;
            u8 nib = (u32)(p35[0] << 28) >> 28;
            ChipInit_080178A8(126, nib, 0x3C00, 0xFFFFE200, *(u8 **)(s + 44));
            s[10] &= 0xFE;
            s[18] = 10;
            s[14]++;
        }
        break;
    }
    case 4:
        if (--s[18] != 0)
            break;
        s[10] |= 1;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 5:
        if (Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 0);
            s[14]++;
        }
        break;
    case 6:
        if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
            MaxAssign_17(*(u8 **)(s + 44), 7);
            DecIfNonZero_18(*(u8 **)(s + 44));
            *(u32 *)(s + 44) = 0;
            q[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}

__asm__(
    ".globl Vec2_CopyMirrored\n.set Vec2_CopyMirrored, 0x0800DD08\n"
);
