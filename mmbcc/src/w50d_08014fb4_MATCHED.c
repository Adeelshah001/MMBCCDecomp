/* W50-D 0x08014fb4 (232 B) v1 — ChipSlot state machine, fresh ROM dis 2026-10-26.
 * TRUE extent 232 B (bx 0x15094, pad 0x15096, pool 0x15098 = 0xffffc400,
 * next fn 0x1509c). Pools raw LE: jump-table base 0x08014fd4 (at 0x14fd0),
 * 0xffffc400 (at 0x14ff8, case 0 Vec2 x), 0xffffc400 (at 0x15098, case 4 Vec2 x).
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
extern u8 Sub_08017474(u32 a);
extern void Sub_08017464(u32 a);
extern void Sub_0801AA70(int a, int b, int c, int d, int e, u32 f);
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_0801AA70, 0x0801aa70");

__attribute__((section(".text.w50d_08014fb4")))
void Sub_08014FB4(u8 *s)
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
        Sub_0801AA70(24, 0, (int)(((u32)s[35] << 28) >> 28), 0, 0, *(u32 *)(s + 44));
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2:
        if (Sub_08011F50(s) == 0)
            break;
        s[14]++;
        break;
    case 3:
        if (Sub_08017474(*(u32 *)(s + 44)) <= 6)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (Sub_08011F50(s) == 0)
            break;
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
