/* W56-D v5: 0x0801509c, TRUE extent 256 B (code thru bx @0x14a3e + 4 B trailing pool @0x14a40).
 * Jump table confirmed from raw LE words: base 0x080150bc, cases -> 150d0/150e8/150fe/15140/15154.
 * case0: SetMirrored(s,-15360,0); IncUse(s,11) -> inc.
 * case1: if Check119(s): table block (nib=s[35]&15, t=tbl08223ed8[p[0]], ChipInit(11,0,nib,t.b,s44)); IncUse(s,9) -> inc.
 * case2: if Check119(s): IncUse(s,10) -> inc.
 * case3: if Check119(s) -> inc (fallthrough).
 * case4: if (u8)GetField(s44)>6: Dec(s44); s44=0; SetMirrored(s,-15360,0); IncUse(s,0); p[4]=0; SetBytes(s,0) -> tail.
 * inc: s[14]++. tail: Tick(s). W38-A file for this address is STALE (244 B note, wrong case bodies) - fresh decode.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef struct { s16 a; s16 b; } T2;

extern void Sub_0800DD2C(u8 *s, int a, int b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0800D9EC(u8 *s, int idx);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern u16 Sub_08011F50(u8 *s);
__asm__(".set Sub_08011F50, 0x08011f50");
extern void Sub_0801CD50(int a, int b, int c, s16 d, s16 e, u32 f);
__asm__(".set Sub_0801CD50, 0x0801cd50");
extern u8 Sub_08017474(u32 v);
__asm__(".set Sub_08017474, 0x08017474");
extern void Sub_08017464(u32 v);
__asm__(".set Sub_08017464, 0x08017464");
extern void Sub_08011F68(u8 *s, int v);
__asm__(".set Sub_08011F68, 0x08011f68");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w56d_0801509c")))
void Sub_0801509c(u8 *s)
{
    u8 *p = s + 124;
    u32 s44;
    switch (s[14]) {
    case 0:
        Sub_0800DD2C(s, -15360, 0);
        Sub_0800D9EC(s, 11);
        goto inc;
    case 1:
        if ((u16)Sub_08011F50(s) != 0) {
            Sub_0800D9EC(s, 9);
            goto inc;
        }
        break;
    case 2:
        if ((u16)Sub_08011F50(s) != 0) {
            int nib;
            T2 *tbl;
            T2 t;
            nib = ((unsigned)s[35] << 28) >> 28;
            tbl = (T2 *)0x08223ed8;
            __asm__ volatile("" : "+r"(tbl));
            t = tbl[p[0]];
            Sub_0801CD50(1, 0, nib, t.a, t.b, *(u32 *)(s + 44));
            Sub_0800D9EC(s, 10);
            goto inc;
        }
        break;
    case 3:
        if ((u16)Sub_08011F50(s) == 0)
            goto tail;
    inc:
        s[14]++;
        goto tail;
    case 4:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            Sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Sub_0800DD2C(s, -15360, 0);
            Sub_0800D9EC(s, 0);
            p[4] = 0;
            Sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    goto tail;
tail:
    Sub_0800D9FC(s);
}
