/* W54-D v2: 0x080145cc (twin propagation of 13434 v2), natural switch (no goto inc/tail), s[14]++ inline
 * per successful case; SetBit16 takes the s44 VALUE (ROM ldr r0,[r5,#44],
 * not s+44 address). Hypothesis: gcc cross-jumps the identical inc
 * sequences into one block after case3, and case4 falls through to Tick.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *s, int a, int b);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void SetBit16(u32 v, int bit);
extern void ChipInit_080178A8(int a, int b, int c, int d, int e);
extern u8 GetField17_U8(int v);
extern void MaxAssign_17(int v, int n);
extern void DecIfNonZero_18(int v);
extern void SetBytes_08011F68(u8 *s, int v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w54d_080145cc")))
void Sub_080145cc(u8 *s)
{
    u8 *p = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s)) {
            SetBit16(*(u32 *)(s + 44), 3);
            {
                int nib = (int)(((u32)s[35] << 28) >> 28);
                ChipInit_080178A8(129, nib, -5120, 0, *(u32 *)(s + 44));
            }
            ChipSlot_IncUse(s, 9);
            s[14]++;
        }
        break;
    case 2:
        if (Check119_Minus3_Le1(s)) {
            ChipSlot_IncUse(s, 10);
            s[14]++;
        }
        break;
    case 3:
        if (GetField17_U8(*(u32 *)(s + 44)) > 5) {
            MaxAssign_17(*(u32 *)(s + 44), 7);
            s[14]++;
        }
        break;
    case 4:
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
