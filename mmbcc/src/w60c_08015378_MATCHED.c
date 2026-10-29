/* W60-C v1: 0x08015378, TRUE extent 264 B (code 260 through bx @0x1547a
 * + trailing pool @0x1547c = 0xFFFFC400; next fn @0x15480). Switch on
 * s[14], jump table at 0x08015398 (absolute case addresses).
 * case 0: DD2C(s, 0xFFFFC400, 0); D9EC(s, 8); -> inc.
 * case 1: if (11F50(s) == 0) -> tail; D9EC(s, 9); -> inc.
 * case 2: if (11F50(s) == 0) -> tail; D9EC(s, 10); 174A4(p44, 3);
 *   178A8(96, nibble, -11520, -6400, p44); -> inc (fallthrough).
 * inc (label inside switch, between case 2 and case 3 — 13600 layout
 * trick): s[14]++; -> tail.
 * case 3: if (11F50(s) != 0) s[14]++; -> fall through to case 4.
 * case 4: if (17474(p44) <= 5) -> tail; 17478(p44, 7); 17464(p44);
 *   s44 = 0; DD2C(s, 0xFFFFC400, 0); D9EC(s, 0); p[4] = 0; 11F68(s, 0);
 *   -> tail.
 * default / out-of-range: -> tail (no inc). tail: D9FC(s); return.
 * p = s + 124 (two-add idiom); p44 = word at s+44 (pointer field).
 * Nibble via ((u32)s[35] << 28) >> 28 (ROM lsls/lsrs form).
 * 11F50 declared s16 (W36/W50 caller-view idiom); 178A8 c/d s16.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef signed int s32;

extern void Sub_0800DD2C(u8 *s, s32 x, s32 y);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0800D9EC(u8 *s, u8 idx);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern s16 Sub_08011F50(u8 *s);
__asm__(".set Sub_08011F50, 0x08011f50");
extern void Sub_080174A4(u8 *p, u8 bit);
__asm__(".set Sub_080174A4, 0x080174a4");
extern u32 *Sub_080178A8(u8 a, u8 b, s16 c, s16 d, u8 *e);
__asm__(".set Sub_080178A8, 0x080178a8");
extern u8 Sub_08017474(u8 *p);
__asm__(".set Sub_08017474, 0x08017474");
extern void Sub_08017478(u8 *p, u8 v);
__asm__(".set Sub_08017478, 0x08017478");
extern void Sub_08017464(u8 *p);
__asm__(".set Sub_08017464, 0x08017464");
extern void Sub_08011F68(u8 *s, u8 v);
__asm__(".set Sub_08011F68, 0x08011f68");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w60c_08015378")))
void Sub_08015378(u8 *s)
{
    u8 *p = s;
    p += 124;
    switch (s[14]) {
    case 0:
        Sub_0800DD2C(s, 0xFFFFC400, 0);
        Sub_0800D9EC(s, 8);
        goto inc;
    case 1:
        if (Sub_08011F50(s) == 0)
            goto tail;
        Sub_0800D9EC(s, 9);
        goto inc;
    case 2:
        if (Sub_08011F50(s) == 0)
            goto tail;
        Sub_0800D9EC(s, 10);
        Sub_080174A4(*(u8 **)(s + 44), 3);
        Sub_080178A8(96, ((u32)s[35] << 28) >> 28, -11520, -6400,
                     *(u8 **)(s + 44));
        /* fall through to inc */
    inc:
        s[14]++;
        goto tail;
    case 3:
        if (Sub_08011F50(s) != 0)
            s[14]++;
        /* fall through to case 4 */
    case 4:
        if (Sub_08017474(*(u8 **)(s + 44)) <= 5)
            goto tail;
        Sub_08017478(*(u8 **)(s + 44), 7);
        Sub_08017464(*(u8 **)(s + 44));
        {
            int z = 0;
            *(u32 *)(s + 44) = z;
            Sub_0800DD2C(s, 0xFFFFC400, 0);
            Sub_0800D9EC(s, 0);
            p[4] = z;
            Sub_08011F68(s, 0);
        }
        goto tail;
    default:
        goto tail;
    }
tail:
    Sub_0800D9FC(s);
}
