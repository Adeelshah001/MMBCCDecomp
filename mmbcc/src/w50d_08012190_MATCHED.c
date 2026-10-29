/* W50-D 0x08012190 (228 B) v5 — mode switch, fresh ROM dis 2026-10-26.
 * TRUE extent 228 B (bx 0x226c, pad 0x226e, trailing pool 0x2270 = 0xffffc400;
 * mid pools 0x21c4 = 0xffffc400, 0x220c = 0x08223ed8; next fn 0x2274).
 * Callees: dd2c Vec2_SetMirrored (MATCHED), d9ec/d9fc (MATCHED),
 * 11f50/11f68 (same as 1200c), 174a4/17474/17464/1aa70 unknown.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern s16 tbl_08223ed8[][2];
__asm__(".set tbl_08223ed8, 0x08223ed8");

extern void Sub_0800DD2C(u8 *s, int x, int y);
extern void Sub_0800D9EC(u8 *s, u8 idx);
extern void Sub_0800D9FC(u8 *s);
extern short Sub_08011F50(u8 *s);
extern void Sub_08011F68(u8 *s, u8 v);
extern void Sub_080174A4(u32 a, int b);
extern u8 Sub_08017474(u32 a);
extern void Sub_08017464(u32 a);
extern void Sub_0801AA70(int a, u8 b, int c, s16 d, s16 e, u32 f);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");
__asm__(".set Sub_080174A4, 0x080174a4");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_0801AA70, 0x0801aa70");

__attribute__((section(".text.w50d_08012190")))
void Sub_08012190(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        Sub_0800DD2C(s, -15360, 0);
        Sub_0800D9EC(s, 11);
        s[14]++;
        break;
    case 1:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_080174A4(*(u32 *)(s + 44), 3);
        {
            u8 m = s[17];
            int nib = ((u32)s[35] << 28) >> 28;
            s16 (*tp)[2] = tbl_08223ed8;
            s16 *e = tp[t[0]];
            Sub_0801AA70(22, m, nib, e[0], e[1], *(u32 *)(s + 44));
        }
        Sub_0800D9EC(s, 12);
        s[14]++;
        break;
    case 2:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_0800D9EC(s, 13);
        s[14]++;
        break;
    case 3:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            Sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Sub_0800DD2C(s, -15360, 0);
            Sub_0800D9EC(s, 0);
            t[4] = 0;
            Sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    Sub_0800D9FC(s);
}
