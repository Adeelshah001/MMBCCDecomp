/* W37-C attempt 1: 0x08016c94, 152 B. State machine on struct *s, mode=s[14].
 * case 0: ChipSlot_IncUse(s,0); s[33]=60; s[18]=mode; mode++.
 * case 1: s[18]++; if <=19 tail; else ChipSlot_IncUse(s,2); mode++.
 * case 2: if Check119_Minus3_Le1(s)==0 tail; else ChipSlot_IncUse(s,0);
 *   s[10]&=0xFE; mode++.
 * case 3: s[18]++; if <=49 tail; else q[4]=0 (q=s+124); SetBytes(s,0); tail.
 * default: tail. Tail: ChipSlot_Tick(s).
 * Extern callees + addresses: ChipSlot_IncUse 0x0800d9ec (MATCHED),
 * Check119_Minus3_Le1 0x08011f50 (MATCHED), SetBytes_08011F68 0x08011f68
 * (MATCHED), ChipSlot_Tick 0x0800d9fc (MATCHED).
 */
typedef unsigned char u8;
typedef unsigned short u16;

extern void ChipSlot_IncUse(u8 *s, int idx);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void SetBytes_08011F68(u8 *s, int v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w37c_08016c94")))
void Sub_08016C94(u8 *s)
{
    u8 *q = s + 124;
    u8 mode = s[14];
    switch (mode) {
    case 0:
        ChipSlot_IncUse(s, 0);
        s[33] = 60;
        s[18] = mode;
        s[14]++;
        break;
    case 1:
        s[18]++;
        if (s[18] <= 19)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[10] &= 0xfe;
        s[14]++;
        break;
    case 3:
        s[18]++;
        if (s[18] <= 49)
            break;
        q[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
