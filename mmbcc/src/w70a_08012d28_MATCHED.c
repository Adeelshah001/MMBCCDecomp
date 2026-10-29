/* Wave 70-A v1: 0x08012D28, fresh. True (tiling) extent 340 B
 * (336 code through bx @0x12E76 + 4 trailing pool @0x12E78 = 0xFFFFC400;
 * next fn @0x12E7C). Switch on s[14] (cases 0..6, default -> Tick tail).
 * Sibling of 0x08013CAC (same Vec2/SetMirrored/Check119 idioms).
 * case 0: Vec2_SetMirrored(s, 0xFFFFC400, 0); IncUse(s,2);
 *         Text_SelectBlobIdx(152); s[14]++;
 * case 1: if (Check119(s)) { Vec2_SetMirrored(s, 0xFFFFFA00, 0);
 *         IncUse(s,1); s[14]++; }
 * case 2: if (Check119(s)) { IncUse(s,9); s[14]++; }
 * case 3: if (Check119(s)) { SetBit16(*(s+44), 3);
 *         ChipInit_080178A8(138, nibble(s[35]), 0x3C00, 0xFFFFEC00,
 *         *(s+44)); IncUse(s,10); s[14]++; Text_SelectBlobIdx(123); }
 * case 4: if (Check119(s)) { MaxAssign_17(*(s+44), 8);
 *         IncUse(s,2); s[14]++; }
 * case 5: if (Check119(s)) { Vec2_SetMirrored(s, 0xFFFFC400, 0);
 *         IncUse(s,1); s[14]++; }
 * case 6: if (Check119(s)) { DecIfNonZero_18(*(s+44)); *(u32 *)(s+44)=0;
 *         Vec2_SetMirrored(s, 0xFFFFC400, 0); IncUse(s,0); q[4]=0;
 *         SetBytes_08011F68(s, 0); }  (no s[14]++)
 * tail: ChipSlot_Tick(s).
 * .set stubs are verification-only; coordinator strips landed-callee stubs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
void ChipSlot_IncUse(u8 *s, u8 idx);
u16 Check119_Minus3_Le1(u8 *s);
u16 Text_SelectBlobIdx(u16 idx);
void SetBit16(u8 *s, u8 bit);
void ChipInit_080178A8(u8 a, u8 b, u16 c, s32 d, u8 *e);
void MaxAssign_17(u8 *s, u8 v);
void DecIfNonZero_18(u8 *s);
void SetBytes_08011F68(u8 *s, u8 v);
void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w70a_08012d28")))
void sub_08012D28(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(152);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) != 0) {
            Vec2_SetMirrored(s, 0xFFFFFA00, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 9);
            s[14]++;
        }
        break;
    case 3:
        if (Check119_Minus3_Le1(s) != 0) {
            u8 nib;
            SetBit16(*(u8 **)(s + 44), 3);
            nib = (u32)((s + 35)[0] << 28) >> 28;
            ChipInit_080178A8(138, nib, 0x3C00, 0xFFFFEC00, *(u8 **)(s + 44));
            ChipSlot_IncUse(s, 10);
            s[14]++;
            Text_SelectBlobIdx(123);
        }
        break;
    case 4:
        if (Check119_Minus3_Le1(s) != 0) {
            MaxAssign_17(*(u8 **)(s + 44), 8);
            ChipSlot_IncUse(s, 2);
            s[14]++;
        }
        break;
    case 5:
        if (Check119_Minus3_Le1(s) != 0) {
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 6:
        if (Check119_Minus3_Le1(s) != 0) {
            DecIfNonZero_18(*(u8 **)(s + 44));
            *(u32 *)(s + 44) = 0;
            Vec2_SetMirrored(s, 0xFFFFC400, 0);
            ChipSlot_IncUse(s, 0);
            q[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
