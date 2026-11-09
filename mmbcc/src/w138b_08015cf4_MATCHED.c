/* Wave 138-B v4 (STAGED ONLY, NOT LANDED): 0x08015CF4, TRUE extent 668 B
 * (next fn 0x08015F90). Hand-read state machine on s[14] (0..8; cases 1
 * and 5 share one block via duplicate jump-table entries), sibling of
 * 0x08016400 (same p = s+124 idiom, same callee family). Case 0 has a
 * table-driven 0x08017D00 call duplicated in an if/else (ROM does NOT
 * cross-jump the two copies); the D table at 0x08223ED8 is a struct
 * array {u16 a; s16 b;} indexed by s[124]. Plain C + .set stubs only
 * (no pin, no inline asm in the body, no barrier, no alias).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern void Sub_0800DD2C(u8 *s, s32 a, s32 b);
extern int Sub_080174A4(u32 a, int b);
extern void Sub_0800D9EC(u8 *s, int a);
extern void Sub_0800D9FC(u8 *s);
extern int Sub_08017474(u32 a);
extern s16 Sub_08011F50(u8 *s);
extern void Sub_08011F68(u8 *s, int a);
extern void Sub_08017478(u32 a, int b);
extern void Sub_08017464(u32 a);
extern void Sub_08017D00(int a, int b, s16 c, s16 d, u8 *e);
extern void Sub_0801EE14(int a, int b, int c, s32 d, int e);
extern void Sub_0804A378(int a);
extern u8 gEwram_02003670[];
extern u8 T_08223EB4[];
extern u8 T_08223ED4[];
extern u8 T_08224060[];

struct DPair {
    u16 a;
    s16 b;
};
extern struct DPair T_08223ED8[];

__asm__(".set Sub_0800DD2C, 0x0800dd2c");
__asm__(".set Sub_080174A4, 0x080174a4");
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");
__asm__(".set Sub_08017478, 0x08017478");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_08017D00, 0x08017d00");
__asm__(".set Sub_0801EE14, 0x0801ee14");
__asm__(".set Sub_0804A378, 0x0804a378");
__asm__(".set gEwram_02003670, 0x02003670");
__asm__(".set T_08223EB4, 0x08223eb4");
__asm__(".set T_08223ED4, 0x08223ed4");
__asm__(".set T_08224060, 0x08224060");
__asm__(".set T_08223ED8, 0x08223ed8");

__attribute__((section(".text.w138b_08015cf4_v4")))
void Sub_08015CF4(u8 *s)
{
    u8 *p = s + 124;

    switch (s[14]) {
    case 0:
        if (p[7] == 0)
            Sub_080174A4(*(u32 *)(s + 44), 1);
        Sub_0800DD2C(s, (int)0xffffc400, 0);
        Sub_0800D9EC(s, 0);
        if (T_08223EB4[s[17]] == 23) {
            Sub_08017D00(T_08223ED4[T_08224060[p[0]]],
                ((u32)s[35] << 28) >> 28,
                (s16)(T_08223ED8[p[0]].a - 14080),
                T_08223ED8[p[0]].b, *(u32 *)(s + 44));
        } else {
            Sub_08017D00(T_08223EB4[s[17]],
                ((u32)s[35] << 28) >> 28,
                (s16)(T_08223ED8[p[0]].a - 14080),
                T_08223ED8[p[0]].b, *(u32 *)(s + 44));
        }
        if (p[7] != 0)
            s[14] = 2;
        else
            s[14]++;
        break;
    case 2:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) == 0)
            break;
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            s[14] = 5;
            break;
        }
        gEwram_02003670[0x11AF] = (gEwram_02003670[0x11AF] & 0xF) | 0x40;
        s[33] = 6;
        Sub_0800D9EC(s, 3);
        s[14]++;
        break;
    case 3:
        if (Sub_08011F50(s) == 0)
            break;
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 1) {
            if ((u8)Sub_08017474(*(u32 *)(s + 44)) <= 5) {
                s[33] = 6;
                Sub_0800D9EC(s, 3);
                break;
            }
        }
        if (p[7] == 2) {
            Sub_0800D9EC(s, 7);
            s[14] = 6;
            break;
        }
        s[14]++;
        break;
    case 4:
        if (Sub_08011F50(s) != 0) {
            Sub_0800D9EC(s, 0);
            s[14]++;
        }
        break;
    case 1:
    case 5:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            Sub_08017478(*(u32 *)(s + 44), 8);
            Sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Sub_0800DD2C(s, (int)0xffffc400, 0);
            Sub_0800D9EC(s, 0);
            p[4] = 0;
            Sub_08011F68(s, 0);
        }
        break;
    case 6: {
        u8 *q = s + 33;
        u32 z = 0;
        *q = 60;
        s[18] = 40;
        Sub_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, (int)0xffffc400, z);
        s[14]++;
        break;
    }
    case 7:
        if (--s[18] == 0) {
            Sub_0800D9EC(s, 2);
            Sub_0804A378(127);
            s[14]++;
        }
        break;
    case 8:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            u8 t = s[10] & 0xFE;
            u32 z = 0;
            s[10] = t;
            Sub_08017478(*(u32 *)(s + 44), 8);
            Sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = z;
            Sub_0800DD2C(s, (int)0xffffc400, 0);
            Sub_0800D9EC(s, 0);
            p[4] = z;
            Sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    Sub_0800D9FC(s);
}
