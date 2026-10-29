/* W60-C v1: 0x08015538, TRUE extent 268 B (code 262 through bx @0x1563c
 * + pad 2 @0x1563e + trailing pool @0x15640 = 0xFFFFC400; next fn
 * @0x15644). Switch on s[14], jump table at 0x08015558 (absolute case
 * addresses). Cases 0-3 share one D9EC call block at 0x080155f0 (each
 * sets r1, case 3 falls into it); inc sits between shared block and
 * case 4 (13600/15378 layout trick, via labels inside the switch).
 * case 0: DD2C(s, 0xFFFFC400, 0); D9EC(s, 11) [shared].
 * case 1: if (11F50(s) == 0) -> tail; D9EC(s, 12) [shared].
 * case 2: if (11F50(s) == 0) -> tail; a = TblB[2*s[17]];
 *   b = TblB[2*s[17]+1]; nib = s[35]&15 (u32 shifts);
 *   pair = TblS[p[0]] (s16 pair); 1AA70(a, b, nib, pair[0], pair[1],
 *   p44); D9EC(s, 13) [shared].
 * case 3: if (11F50(s) == 0) -> tail; D9EC(s, 0) [shared, fallthrough].
 * inc: s[14]++; -> tail.
 * case 4: if (17474(p44) <= 6) -> tail; 17464(p44); s44 = 0;
 *   DD2C(s, 0xFFFFC400, 0); D9EC(s, 0); p[4] = 0; 11F68(s, 0); -> tail.
 * default / out-of-range: -> tail (no inc). tail: D9FC(s); return.
 * Shared block: cases preset q (D9EC arg0, r0) and d9arg (arg1, r1);
 * case 0's q is DD2C's return (declared u8* caller-view, so no reload
 * after the call — ROM case 0 has no adds between DD2C and the jump).
 * p = s + 124 (two-add idiom); p44 = word at s+44 (pointer field).
 * TblB @0x08223E52 (u8 pairs); TblS @0x08223ED8 (s16 pairs).
 * 11F50 declared s16 (W36/W50 caller-view idiom).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef signed int s32;

extern void Sub_0800DD2C(u8 *s, s32 x, s32 y);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern u8 *Sub_0800DD2C_Ret(u8 *s, s32 x, s32 y);
__asm__(".set Sub_0800DD2C_Ret, 0x0800dd2c");
extern void Sub_0800D9EC(u8 *s, u8 idx);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern s16 Sub_08011F50(u8 *s);
__asm__(".set Sub_08011F50, 0x08011f50");
extern void Sub_0801AA70(u8 a, u8 b, u8 c, s16 d, s16 e, u8 *f);
__asm__(".set Sub_0801AA70, 0x0801aa70");
extern u8 Sub_08017474(u8 *p);
__asm__(".set Sub_08017474, 0x08017474");
extern void Sub_08017464(u8 *p);
__asm__(".set Sub_08017464, 0x08017464");
extern void Sub_08011F68(u8 *s, u8 v);
__asm__(".set Sub_08011F68, 0x08011f68");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
extern const u8 Tbl_08223E52[];
__asm__(".set Tbl_08223E52, 0x08223e52");
extern const s16 Tbl_08223ED8[][2];
__asm__(".set Tbl_08223ED8, 0x08223ed8");

__attribute__((section(".text.w60c_08015538")))
void Sub_08015538(u8 *s)
{
    u8 *p = s;
    register u8 *q __asm__("r0");
    u8 d9arg;
    p += 124;
    switch (s[14]) {
    case 0:
        Sub_0800DD2C(s, 0xFFFFC400, 0);
        __asm__ volatile("add r0, r5, #0");
        d9arg = 11;
        goto shared;
    case 1:
        if (Sub_08011F50(s) == 0)
            goto tail;
        q = s;
        d9arg = 12;
        goto shared;
    case 2: {
        const u8 *t;
        u8 idx;
        u8 a;
        u8 b;
        u8 nib;
        const s16 (*tblS)[2];
        const s16 *pair;
        if (Sub_08011F50(s) == 0)
            goto tail;
        t = Tbl_08223E52;
        idx = s[17];
        a = t[2 * idx];
        t++;
        b = t[2 * idx];
        nib = ((u32)s[35] << 28) >> 28;
        tblS = Tbl_08223ED8;
        pair = tblS[p[0]];
        Sub_0801AA70(a, b, nib, pair[0], pair[1], *(u8 **)(s + 44));
        q = s;
        d9arg = 13;
        goto shared;
    }
    case 3:
        if (Sub_08011F50(s) == 0)
            goto tail;
        q = s;
        d9arg = 0;
        /* fall through to shared */
    shared:
        Sub_0800D9EC(q, d9arg);
        goto inc;
    inc:
        s[14]++;
        goto tail;
    case 4:
        if (Sub_08017474(*(u8 **)(s + 44)) <= 6)
            goto tail;
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
