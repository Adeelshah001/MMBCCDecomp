/* Wave 16 worker B: 0x0800EBF0 (30 B + pool).
 * If (s8)F_080104CC(*(u8*)0x02005132) == 1, call SetByte20(8) and return 1.
 */
typedef unsigned char u8;
typedef signed char s8;


extern u8 F_080104CC(u8 x);
extern void SetByte20_Clear21to23_02005130(u8 v);
u8 F_080104CC(u8 x);
void SetByte20_Clear21to23_02005130(u8 v);
extern u8 EwrBase_2005130[];

s8 Fwd_EBF0(void) __attribute__((section(".text.w16b_0800ebf0")));
s8 Fwd_EBF0(void)
{
    u8 *base = EwrBase_2005130;
    s8 v = (s8)F_080104CC(base[2]);
    if (v == 1) {
        SetByte20_Clear21to23_02005130(8);
        return 1;
    }
    return v;
}

__asm__(
    ".set EwrBase_2005130, 0x02005130\n"
);