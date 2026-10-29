/* W37-C MATCHED (C + verified .s patch, see w37c_080231d0.patch.txt):
 * 0x080231d0, TRUE extent 148 B (TSV says 168, but
 * that spans this function plus a separate 20 B function at
 * 0x08023264; coordinator should correct the TSV row). Task step
 * on struct *s, returns void. If-chain dispatch (not jump table).
 * base = 0x02004830 (barrier-kept, never folded into one pool).
 * switch (s[13]): case 0: s[13] = 1; IncUse(s, s[17]);
 *   s[80] = *(base + 621) << 11; s[84] = *(base + 622) << 11;
 *   v = 256; s[76] = s[78] = v (halfwords); fall to case 1;
 * case 1: ub = *(base + 620); b = (s8)ub (shifts, not ldrsb);
 *   if (s[17] == b) goto tail;
 *   if (b < 0) { tp = 0x08226ef0 + s[9]*4; s[12] = 2;
 *     s[20] = *(u32 *)(*tp + 8); goto tail; }
 *   s[17] = ub; s[13] = 0; (fall through to tail);
 * default: goto tail;
 * tail: ChipSlot_Tick(s); return.
 * Extern callees + addresses: ChipSlot_IncUse 0x0800d9ec
 * (MATCHED), ChipSlot_Tick 0x0800d9fc (MATCHED).
 * Pools (LE): 0x02004830, 0x26d (621), 0x26e (622), 620, 0x08226ef0.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void ChipSlot_IncUse(u8 *s, int idx);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w37c_080231d0")))
void Sub_080231D0(u8 *s)
{
    register u8 *base __asm__("r0");
    u16 v;
    switch (s[13]) {
    case 0:
        s[13] = 1;
        ChipSlot_IncUse(s, s[17]);
        base = (u8 *)0x02004830;
        __asm__ volatile("" : "+r"(base));
        *(u32 *)(s + 80) = *(u8 *)(base + 621) << 11;
        *(u32 *)(s + 84) = *(u8 *)(base + 622) << 11;
        v = 256;
        *(u16 *)(s + 76) = v;
        *(u16 *)(s + 78) = v;
    case 1: {
        u8 ub;
        s8 b;
        u32 *tp;
        register u8 *tbase __asm__("r1");
        u8 z;
        base = (u8 *)0x02004830;
        __asm__ volatile("" : "+r"(base));
        ub = *(u8 *)(base + 620);
        b = (s8)ub;
        if (s[17] == b)
            goto tail;
        if (b < 0) {
            tbase = (u8 *)0x08226ef0;
            __asm__ volatile("" : "+r"(tbase));
            tp = (u32 *)(s[9] * 4 + (u32)tbase);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 8);
            goto tail;
        }
        z = 0;
        s[17] = ub;
        s[13] = z;
        goto tail;
    }
    default:
        goto tail;
    }
tail:
    ChipSlot_Tick(s);
}

/* Trailing zero pad: ROM ends this 148 B section with 00 00 after bx;
 * without it GAS pads the section end with mov r8,r8 (0x46c0). */
__asm__(".hword 0x0000");
