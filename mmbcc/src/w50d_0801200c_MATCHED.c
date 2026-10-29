/* W50-D 0x0801200c (228 B) v7 — mode switch, fresh ROM dis 2026-10-26.
 * TRUE extent 228 B (bx 0x20ec, pad 0x20ee, NO trailing pool; next fn 0x20f0).
 * No ldr-pc in body. Callees: d9ec ChipSlot_IncUse (MATCHED), d6e0
 * ChipSlot_Setup (MATCHED), d9fc ChipSlot_Tick (MATCHED W35), 1f50/1f68 unknown.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_0800D9EC(u8 *s, u8 idx);
extern void Sub_0800D6E0(u8 *s, u16 b, u8 c);
extern void Sub_0800D9FC(u8 *s);
extern short Sub_08011F50(u8 *s);
extern void Sub_08011F68(u8 *s, u8 v);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");

__attribute__((section(".text.w50d_0801200c")))
void Sub_0801200C(u8 *s)
{
    u8 *t = s + 124;
    u8 mode = s[14];
    switch (mode) {
    case 0:
        if (t[0] == t[1] && t[2] == t[3]) {
            Sub_0800D9EC(s, 0);
            t[4] = mode;
            Sub_08011F68(s, 0);
        } else {
            u8 v = t[1];
            u16 r = v | ((s[35] & 15) ? 0x100 : 0);
            Sub_0800D6E0(s, r, t[3]);
            Sub_0800D9EC(s, 2);
            s[14]++;
        }
        break;
    case 1:
        if (Sub_08011F50(s) == 0)
            break;
        {
            u8 v = t[0];
            u16 r = v | ((s[35] & 15) ? 0x100 : 0);
            Sub_0800D6E0(s, r, t[2]);
            Sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_0800D9EC(s, 0);
        s[14]++;
        break;
    case 3:
        if (Sub_08011F50(s) == 0)
            break;
        t[4] = 0;
        Sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    Sub_0800D9FC(s);
}
__asm__(".balign 4, 0");
