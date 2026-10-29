/* Wave 16 worker B: 0x08010BA0 (14 B + pool).
 * Forwarder: Tbl_ClearEntries(*(u8*)(0x020051B0 + 2)).
 */
typedef unsigned char u8;


extern void Tbl_ClearEntries(u8 a);
void Tbl_ClearEntries(u8 a);
extern u8 RomBase_20051B0[];

void Fwd_10BA0(void) __attribute__((section(".text.w16b_08010ba0")));
void Fwd_10BA0(void)
{
    u8 *base = RomBase_20051B0;
    Tbl_ClearEntries(base[2]);
}

__asm__(
    ".set RomBase_20051B0, 0x020051B0\n"
);