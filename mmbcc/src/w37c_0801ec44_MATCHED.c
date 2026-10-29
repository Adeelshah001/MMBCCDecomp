/* W37-C MATCHED: 0x0801ec44, 164 B, old_agbcc, pure C, 0 diffs.
 * Init task on struct *s. Idioms: address-first/store-second table
 * pattern (like 0x0801757c); base pinned r1 + barrier; reversed
 * additions; two-step OR via temp (defeats |2|1 folding); value
 * temp for s[34] store order.
 * s[12] = 1 (word); s[20] = *(u32 *)(*(u32 *)(0x082243d8 + s[9]*4) + 4);
 * s[108] = 0; s[10] = (s[10] | 2) | 1;
 * r5 = *(u32 *)(0x08226da4 + s[16]*4); s[40] = r5;
 * ChipSlot_Setup(s, r5[1] | 768, r5[0] >> 4);
 * ChipSlot_IncUse(s, r5[2]);
 * bitfield clamp (same as 0x080185a8); s[69] update;
 * s[34] = s[17] + 14; s[18] = r5[3]; F_0801ECE8(s).
 * Extern callees + addresses: ChipSlot_Setup 0x0800d6e0 (MATCHED),
 * ChipSlot_IncUse 0x0800d9ec (MATCHED), F_0801ECE8 0x0801ece8
 * (MATCHED).
 * Pools (LE): 0x082243d8, 0x08226da4, 0x081705b0, 0x020031e4.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void F_0801ECE8(u8 *s);

__attribute__((section(".text.w37c_0801ec44")))
void Sub_0801EC44(u8 *s)
{
    u8 *r5;
    int v;
    {
        u8 *q;
        int tmp;
        int w;
        u8 t10;
        register u8 *base1 __asm__("r1");
        u32 *tp;
        register u8 *base2 __asm__("r1");
        base1 = (u8 *)0x082243d8;
        __asm__ volatile("" : "+r"(base1));
        tp = (u32 *)(s[9] * 4 + (u32)base1);
        *(u32 *)(s + 12) = 1;
        *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 4);
        *(u32 *)(s + 108) = 0;
        t10 = s[10] | 2;
        t10 = t10 | 1;
        s[10] = t10;
        base2 = (u8 *)0x08226da4;
        __asm__ volatile("" : "+r"(base2));
        r5 = *(u8 **)(s[16] * 4 + (u32)base2);
        *(u32 *)(s + 40) = (u32)r5;
        ChipSlot_Setup(s, r5[1] | 768, r5[0] >> 4);
        ChipSlot_IncUse(s, r5[2]);
        v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
        w = v;
        __asm__ volatile("" : "+r"(w));
        if (w > 3)
            v = 3;
        q = s + 69;
        {
            int sh = v << 2;
            tmp = (s[69] & -13) | sh;
        }
        *q = tmp;
    }
    {
        u8 t34 = s[17] + 14;
        s[34] = t34;
    }
    s[18] = r5[3];
    F_0801ECE8(s);
}
