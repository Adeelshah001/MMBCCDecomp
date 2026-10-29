typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ChipSlot_Tick(u8 *s);
extern u32 Tbl_082243D8[];

__attribute__((section(".text.w36a_0801e93c")))
void Step_0801e93c(u8 *s)
{
    ChipSlot_Tick(s);
    if ((u8)(s[119] - 3) <= 1) {
        u32 *entry = (u32 *)Tbl_082243D8[s[9]];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)entry + 8);
    }
}

__asm__(".set ChipSlot_Tick, 0x0800d9fc");
__asm__(".set Tbl_082243D8, 0x082243d8");
