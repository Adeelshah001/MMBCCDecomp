/* Wave 16 worker B: 0x08025054 (24 B + pool).
 * Forwarder to F_0802660C with ROM table base 0x02007090+24.
 */
typedef unsigned char u8;
typedef unsigned short u16;


extern u16 F_0802660C(u8 *p, u16 idx);
u16 F_0802660C(u8 *p, u16 idx);
extern u8 RomBase_2007090[];

u16 Fwd_25054(u16 idx) __attribute__((section(".text.w16b_08025054")));
u16 Fwd_25054(u16 idx)
{
    u8 *base = RomBase_2007090;
    return F_0802660C(base + 24, idx);
}

__asm__(
    ".set RomBase_2007090, 0x02007090\n"
);