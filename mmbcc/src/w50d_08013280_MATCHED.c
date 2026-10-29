/* W50-D 0x08013280 (232 B) v1 — ChipSlot state machine, fresh ROM dis 2026-10-26.
 * TRUE extent 232 B (bx 0x13360, pad 0x13362, pool 0x13364 = 0xffffc400,
 * next fn 0x13368). Pools raw LE: jump-table base 0x080132a0 (at 0x1329c),
 * 0xffffc400 (at 0x132c4, case 0 Vec2 x), 0xffffc400 (at 0x13364, case 4 Vec2 x).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void ChipSlot_IncUse(u8 *s, u8 n);
extern void ChipSlot_Tick(u8 *s);
extern void Vec2_SetMirrored(u8 *o, int x, int y);
extern short Sub_08011F50(u8 *s);
extern void Sub_08011F68(u8 *s, int a);
extern void Sub_080174A4(u32 a, int b);
extern u8 Sub_08017474(u32 a);
extern void Sub_08017478(u32 a, int b);
extern void Sub_08017464(u32 a);
extern void Sub_080178A8(int a, int b, int c, int d, u32 e);
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");
__asm__(".set Sub_080174A4, 0x080174a4");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08017478, 0x08017478");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_080178A8, 0x080178a8");

__attribute__((section(".text.w50d_08013280")))
void Sub_08013280(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Sub_08011F50(s) == 0)
            break;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_080174A4(*(u32 *)(s + 44), 3);
        Sub_080178A8(133, (int)(((u32)s[35] << 28) >> 28), 0x3c00, 0, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 3:
        if (Sub_08011F50(s) == 0)
            break;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 4:
        if (Sub_08017474(*(u32 *)(s + 44)) <= 5)
            break;
        Sub_08017478(*(u32 *)(s + 44), 7);
        Sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        t[4] = 0;
        Sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
