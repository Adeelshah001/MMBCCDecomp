/* Wave 138-B v6 (STAGED ONLY, NOT LANDED): 0x08016400, TRUE extent 656 B
 * (next fn 0x08016690). Hand-read state machine on s[14] (0..11, default
 * = tail call only), sibling of MATCHED w36c 0x08011F88 (same p = s+124
 * idiom, same 0xffffc400 Vec2 literal, same s16 Sub_08011F50 test).
 * Cases: 0 falls through into 1 after s[14]++; 4 and 8 share the cleanup
 * sequence (written out in full in both cases here — compiler may
 * cross-jump them as ROM does); 11 has its own copy after an
 * s[10] &= 0xFE prefix. Plain C + .set stubs only (no pin, no inline
 * asm in the body, no barrier, no alias). NOTE: Sub_0801B98C is
 * declared here with an s32 4th parameter because ROM loads the full
 * 0xFFFFC400 literal into r3 at the case-1 call site; the w17c
 * prototype for that callee uses u16 there — a discrepancy the
 * coordinator must reconcile before any landing.
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
extern u32 *Sub_0801B98C(int a, int b, int c, s32 d, int e, u8 *f);
extern void Sub_0801EE14(int a, int b, int c, s32 d, int e);
extern void Sub_0804A378(int a);
extern u8 gEwram_02003670[];

__asm__(".set Sub_0800DD2C, 0x0800dd2c");
__asm__(".set Sub_080174A4, 0x080174a4");
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");
__asm__(".set Sub_08017478, 0x08017478");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_0801B98C, 0x0801b98c");
__asm__(".set Sub_0801EE14, 0x0801ee14");
__asm__(".set Sub_0804A378, 0x0804a378");
__asm__(".set gEwram_02003670, 0x02003670");

__attribute__((section(".text.w138b_08016400_v6")))
void Sub_08016400(u8 *s)
{
    u8 *p = s + 124;

    switch (s[14]) {
    case 0:
        if (p[7] == 0)
            Sub_080174A4(*(u32 *)(s + 44), 1);
        Sub_0800DD2C(s, (int)0xffffc400, 0);
        Sub_0800D9EC(s, 0);
        s[14]++;
        /* fallthrough into case 1 */
    case 1: {
        u8 flag = p[7];
        if (flag == 0) {
            Sub_0801B98C(11, 0, ((u32)s[35] << 28) >> 28, (int)0xffffc400, flag, *(u32 *)(s + 44));
            s[10] &= 0xFE;
            s[14] = 2;
        } else {
            s[14] = 5;
        }
        break;
    }
    case 2:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            s[18] = 30;
            s[14]++;
        }
        break;
    case 3:
        if (--s[18] == 0) {
            s[10] |= 1;
            Sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 4:
        if (Sub_08011F50(s) != 0) {
            Sub_08017478(*(u32 *)(s + 44), 8);
            Sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Sub_0800DD2C(s, (int)0xffffc400, 0);
            Sub_0800D9EC(s, 0);
            p[4] = 0;
            Sub_08011F68(s, 0);
        }
        break;
    case 5:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) == 0)
            break;
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            s[14] = 8;
            break;
        }
        gEwram_02003670[0x11AF] = (gEwram_02003670[0x11AF] & 0xF) | 0x40;
        s[33] = 6;
        Sub_0800D9EC(s, 3);
        s[14]++;
        break;
    case 6:
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
            s[14] = 9;
            break;
        }
        s[14]++;
        break;
    case 7:
        if (Sub_08011F50(s) != 0) {
            Sub_0800D9EC(s, 0);
            s[14]++;
        }
        break;
    case 8:
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
    case 9: {
        u8 *q = s + 33;
        u32 z = 0;
        *q = 60;
        s[18] = 40;
        Sub_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, (int)0xffffc400, z);
        s[14]++;
        break;
    }
    case 10:
        if (--s[18] == 0) {
            Sub_0800D9EC(s, 2);
            Sub_0804A378(127);
            s[14]++;
        }
        break;
    case 11:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 6) {
            u8 t = s[10] & 0xFE;
            u32 z = 0;
            s[10] = t;
            {
                Sub_08017478(*(u32 *)(s + 44), 8);
                Sub_08017464(*(u32 *)(s + 44));
                *(u32 *)(s + 44) = z;
                Sub_0800DD2C(s, (int)0xffffc400, 0);
                Sub_0800D9EC(s, 0);
                p[4] = z;
                Sub_08011F68(s, 0);
            }
        }
        break;
    default:
        break;
    }
    Sub_0800D9FC(s);
}
